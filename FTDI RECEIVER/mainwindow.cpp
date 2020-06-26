#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&m_mainTimer, SIGNAL(timeout()), this, SLOT(mainRoutine()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mainRoutine(){
    ui->textOutput->setText(QString::number(m_listener.calculateFPS()));
}

void MainWindow::SetupListener(){
    connect(&m_listenerTimer, SIGNAL(timeout()),&m_listener, SLOT(run()));
    //m_listener.setPort(ui->ComboBox_Ports->currentText());
    m_listenerTimer.setSingleShot(false);
    QString fileName="C";
    m_listener.setFileName(fileName);
}

void MainWindow::on_Button_Start_clicked()
{
    if(ui->Button_Start->text()=="Start"){
        /// set up listeners and sensor dimensions
        SetupListener();
        m_listenerTimer.start(1); //the max value i get is 782 fps which belongs to this period of the timer
        ui->Button_Start->setText("Stop");
        m_mainTimer.start(100);
    }else{
        ui->Button_Start->setText("Start");
        m_listener.manualStart();
        m_listenerTimer.stop();
        m_mainTimer.stop();
    }
}
