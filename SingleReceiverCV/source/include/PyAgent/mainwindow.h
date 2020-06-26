#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pyagent.h"
#include <QTimer>

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
    void probeAgent();
private:
    Ui::MainWindow *ui;
    PyAgent m_PyAgent;
    QTimer m_Timer;
};

#endif // MAINWINDOW_H
