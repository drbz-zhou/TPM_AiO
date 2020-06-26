#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_PyAgent.FuncCall("VectorToFrame","2,2,5,4,3,2");
    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(probeAgent()));
    m_Timer.setSingleShot(false);
    m_Timer.start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::probeAgent(){
    qDebug()<<m_PyAgent.FuncFinished();
    if(m_PyAgent.FuncFinished()){
        qDebug()<<m_PyAgent.FuncReturn();
    }
}
