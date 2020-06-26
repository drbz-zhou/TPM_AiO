#include "mainwindow.h"
#include "ui_mainwindow.h"
/// public
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // scan ports
    on_Button_ScanPorts_clicked();
    // setting default sensor dimension
    m_DIMX = ui->DIM_X->value();
    m_DIMY = ui->DIM_Y->value();
    m_Sensor.setDims(m_DIMX, m_DIMY);
    m_listener.setPacketSize(m_DIMX*m_DIMY*m_PixelDepth);
    m_valueRoundBuffer.setLength(100);
    m_flags.insert("rawData",true);
    m_flags.insert("basic",false);
    m_flags.insert("openCV",false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/// public slots
void MainWindow::mainRoutine(){
    QElapsedTimer tic_timer;
    tic_timer.start();
    QByteArray byteData;
    QString UI_text;


    if(m_sourceMode==0){ //
        if(!m_listener.ifNew()){ return; }// finish if nothing new
        ui->textOutput->setText(QString::number(m_listener.calculateFPS()));
        // receiving new data packet
        byteData = m_listener.get_Packet();
    }else if(m_sourceMode==1){ // file reader
        byteData = m_fileReader.get_Packet();
        if(byteData.size()==0){
            on_Button_Start_clicked();
            return;
        }
        UI_text.append(QString::number(ui->PosInFileBar->value()) + "\n");
        ui->PosInFileBar->setValue(ui->PosInFileBar->value()+1);
    }else if(m_sourceMode==2){
        byteData = m_FTlistener.get_Packet();
        ui->textOutput->setText(QString::number(m_FTlistener.calculateFPS()));
    }
    // parse packet
    QVector<double> currentPacket;
    currentPacket = m_FrameParser.parseBytePacket(byteData);
    m_Sensor.updateValsVector(currentPacket);
    //()<<m_Sensor.copyData2D().max();

    /// raw data visualization
    if(m_flags.value("rawData")){
        m_QMLAgent.drawFrame(m_Sensor.copyData2D());
        //double val = m_FrameParser.max(m_Sensor.getValsVector());//m_Sensor.filter_apply(m_FrameParser.max(m_Sensor.getValsVector()));
        m_Sensor.m_filter.addSample(m_FrameParser.max(m_Sensor.getValsVector()));
        //double val = m_Sensor.m_filter.getHighPass();
        double val = m_FrameParser.mean(m_Sensor.getValsVector());
        m_QMLAgent.addDataToGraph("Sensor", val);
        m_valueRoundBuffer.circleAppend(val);

        double valRange = m_valueRoundBuffer.max() - m_valueRoundBuffer.min();
        double range_min = m_valueRoundBuffer.min()-valRange*0.1;// < 10000 ? m_valueRoundBuffer.min() : 10000;
        double range_max = m_valueRoundBuffer.max()+valRange*0.1;// > 40000.0 ? m_valueRoundBuffer.min() : 40000.0;
        m_QMLAgent.setYRange(range_min, range_max);



        if(m_flags.value("basic")){
            double valRange = m_valueRoundBuffer.max() - m_valueRoundBuffer.min();
            double valMean = m_valueRoundBuffer.mean();
            m_PKcounter.m_thresh_high = valMean + valRange/8;
            m_PKcounter.m_thresh_low = valMean - valRange/8;
            int valCounter = m_PKcounter.feedpoint(val);
            UI_text.append("conter: " + QString::number(valCounter) + "\n");
            static int valGap = 0;
            if(m_GPmeasure.feedpoint(val)==2){
                valGap = m_GPmeasure.m_gapWidth;
            }
            UI_text.append("airtime: " + QString::number(valGap*0.025) + " seconds" + "\n");
        }
    }

    if(m_flags.value("openCV")){
        /// call openCV processor
        data_spatial m_renderedFrame =  m_CVProcessor.processFrame(m_Sensor.copyData2D());

        /// visualize processed frame
        m_QMLAgent.drawFrame(m_renderedFrame);

        double m00 = m_CVProcessor.getM00();
        m_QMLAgent.addDataToGraph("M00", m00);
        m_valueRoundBuffer.circleAppend(m00);
        m_QMLAgent.setYRange(m_valueRoundBuffer.min(),m_valueRoundBuffer.max());
        QVariantList circleData;
        //circleData<<0.1<<0.1<<0.1;
        circleData.append( m_CVProcessor.getBlobs());
        m_QMLAgent.drawCircles(circleData);

    }
    // openCV functions extract features, then either save the features
    // with ground truth as training dataset in to files
    // or send to python to classify
    UI_text.append("processing time: " + QString::number(tic_timer.elapsed()) + "ms" +"\n");
    ui->textOutput->setText(UI_text);
    m_QMLAgent.setLabel_1(UI_text);
}
void MainWindow::callPython(){

}
void MainWindow::sendToJS(){

}

/// private UI slots
void MainWindow::on_Button_ScanPorts_clicked()
{
    QStringList ports = scanPorts();
    ui->ComboBox_Ports->clear();
    ui->ComboBox_Ports->addItems(ports);
    ui->ComboBox_Ports->setCurrentIndex(0);
}

void MainWindow::on_Button_Start_clicked()
{
    m_flags.insert("rawData",ui->checkBox_rawData->isChecked());
    m_flags.insert("basic",ui->checkBox_basic->isChecked());
    m_flags.insert("openCV",ui->checkBox_openCV->isChecked());
    if(ui->Button_Start->text()=="Start"){
        int mainTimerPeriod = 100;
        // check current mode
        if(ui->tabWidget->currentIndex()==0){
            // com mode
            m_sourceMode = 0;
            /// set up listeners and sensor dimensions
            setupListener();
            m_listenerTimer.start(10);
        }else if(ui->tabWidget->currentIndex()==1){
            // file mode
            m_sourceMode = 1;
            /// set up file
            setupFilereader();
            mainTimerPeriod = 86;
        }else if(ui->tabWidget->currentIndex()==2){
            // FTDI 254 FIFO mode
            m_sourceMode = 2;
            setupFTListener();
            m_listenerTimer.start(10);
        }
        // connect main routine timer
        connect(&m_mainTimer, SIGNAL(timeout()), this, SLOT(mainRoutine()));

        ui->Button_Start->setText("Stop");
        m_mainTimer.start(mainTimerPeriod);
    }else{
        ui->Button_Start->setText("Start");
        m_listener.manualStart();
        m_listenerTimer.stop();
        m_mainTimer.stop();
    }
}

void MainWindow::on_DIM_X_editingFinished()
{
    m_DIMX = ui->DIM_X->value();
    m_Sensor.setDims(m_DIMX, m_DIMY);
    qDebug()<<m_DIMX<<m_DIMY;
}

void MainWindow::on_DIM_Y_editingFinished()
{
    m_DIMY = ui->DIM_Y->value();
    m_Sensor.setDims(m_DIMX, m_DIMY);
    qDebug()<<m_DIMX<<m_DIMY;
}

void MainWindow::on_Button_Browse_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load Data File"), "/", tr("Data Files (*.txt *.csv)"));
    ui->lineEdit_readfile->setText(fileName);
    m_fileReader.loadFile(ui->lineEdit_readfile->text());
    ui->PosInFileBar->setMaximum(m_fileReader.m_totalFrames);
}

void MainWindow::on_Button_Browse_Save_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory();
    qDebug()<<dirName;
    ui->lineEdit_savedir->setText(dirName);
}

/// private
void MainWindow::setupListener(){
    connect(&m_listenerTimer, SIGNAL(timeout()),&m_listener, SLOT(run()));
    m_listener.setPort(ui->ComboBox_Ports->currentText());
    m_listenerTimer.setSingleShot(false);
    QString fileName= ui->lineEdit_Prefix->text();
    m_listener.setFileName(fileName);
    m_listener.setPacketSize(getPacketSize());
    m_listener.setHeader(m_Header);
}
void MainWindow::setupFTListener(){
    connect(&m_listenerTimer, SIGNAL(timeout()),&m_FTlistener, SLOT(run()));
    m_listenerTimer.setSingleShot(false);
    QString fileName= ui->lineEdit_Prefix->text();
    m_FTlistener.setFileName(fileName);
    m_FTlistener.setPacketSize(getPacketSize());
    qDebug()<<"FTlistener run() SLOT connected";
    //m_FTlistener.setHeader(m_Header);  change later
}
void MainWindow::setupFilereader(){
    getPacketSize();
}

QStringList MainWindow::scanPorts(){
    QStringList ports;
    QStringList ports_sorted;
    int i=0;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        ports.append(info.portName());
        qDebug()<<ports.at(i)<<ports.at(i).mid(3).toInt();
    }
    while(i<ports.size()){
        int minval = 110;
        int minind = 0;
        for(int n=0; n<ports.size();n++){
            if(ports.at(n).mid(3).toInt() < minval){
                minval = ports.at(n).mid(3).toInt();
                minind = n;
            }
        }
        ports_sorted.append(ports.at(minind));
        ports.removeAt(minind);
    }
    qDebug()<<ports_sorted;
    return ports_sorted;
}

int MainWindow::getPacketSize(){
    setHardParameter();
    int packetsize = m_Header.length()+m_DIMX*m_DIMY*m_PixelDepth;
    qDebug()<<"packetsize"<<packetsize<<"header"<<m_Header<<" x "<<m_DIMX<<" y "<<m_DIMY;
    m_CVProcessor.setPixelBits(m_PixelDepth);
    return packetsize;
}

void MainWindow::setHardParameter(){
    // set byte size and header
    if(ui->ComboBox_HardPara->currentText()=="3 Byte 12-bit \"ff000000\""){
        m_PixelDepth = 3;
        m_Header = "ff000000";
        m_FrameParser.setFormat(3, false);
    }else if(ui->ComboBox_HardPara->currentText()=="4 Byte 16-bit \"ff000000\""){
        m_PixelDepth = 4;
        m_Header = "ff000000";
        m_FrameParser.setFormat(4, true);
    }
}

void MainWindow::on_checkBox_basic_clicked(bool checked)
{
    if(checked){
        ui->checkBox_basic->setChecked(true);
    }
}

void MainWindow::on_PosInFileBar_sliderReleased()
{
    m_fileReader.junpToFrame(ui->PosInFileBar->value());
}
