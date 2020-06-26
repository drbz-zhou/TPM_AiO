#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*

COPYRIGHT

All contributions by Deutsches Forschungszentrum für Künstliche Intelligenz, DFKI
Copyright (c) 2016-2017, Bo Zhou
All rights reserved. Free for academic use only.

DESCRIPTION

This class is the main function hub for receiving data, visualizing (optional) and
send out through web socket

*/

#include <QMainWindow>
#include <Ftdilistener.h>
#include <QTimer>
#include <QComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void mainRoutine();

private slots:

    void on_Button_Start_clicked();

private:
    void SetupListener();

    Ui::MainWindow *ui;

    FTDIListener m_listener;
    QTimer m_listenerTimer;
    QTimer m_mainTimer;
};

#endif // MAINWINDOW_H
