/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QGridLayout *gridLayout_3;
    QCheckBox *check_desk;
    QComboBox *ComboBox_Ports_2;
    QComboBox *ComboBox_Ports_1;
    QCheckBox *check_seat;
    QSpacerItem *verticalSpacer;
    QPushButton *Button_ScanPorts;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout;
    QLineEdit *lineEdit_readfile;
    QPushButton *Button_Browse;
    QScrollBar *PosInFileBar;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox;
    QLineEdit *lineEdit_savedir;
    QLabel *label_6;
    QLineEdit *lineEdit_Prefix;
    QPushButton *Button_Browse_Save;
    QPushButton *Button_Start;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_rawData;
    QCheckBox *checkBox_basic;
    QCheckBox *checkBox_openCV;
    QTextEdit *textOutput;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(451, 609);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        QFont font;
        font.setPointSize(10);
        font.setBold(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setKerning(true);
        font.setStyleStrategy(QFont::PreferAntialias);
        label_7->setFont(font);

        verticalLayout->addWidget(label_7);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(12);
        tabWidget->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        check_desk = new QCheckBox(tab);
        check_desk->setObjectName(QStringLiteral("check_desk"));
        check_desk->setMinimumSize(QSize(10, 10));
        check_desk->setIconSize(QSize(20, 20));

        gridLayout_3->addWidget(check_desk, 2, 0, 1, 1);

        ComboBox_Ports_2 = new QComboBox(tab);
        ComboBox_Ports_2->setObjectName(QStringLiteral("ComboBox_Ports_2"));
        ComboBox_Ports_2->setMinimumSize(QSize(0, 32));

        gridLayout_3->addWidget(ComboBox_Ports_2, 2, 1, 1, 1);

        ComboBox_Ports_1 = new QComboBox(tab);
        ComboBox_Ports_1->setObjectName(QStringLiteral("ComboBox_Ports_1"));
        ComboBox_Ports_1->setMinimumSize(QSize(0, 32));
        ComboBox_Ports_1->setFont(font1);

        gridLayout_3->addWidget(ComboBox_Ports_1, 0, 1, 1, 1);

        check_seat = new QCheckBox(tab);
        check_seat->setObjectName(QStringLiteral("check_seat"));
        check_seat->setMinimumSize(QSize(10, 10));
        check_seat->setIconSize(QSize(20, 20));
        check_seat->setChecked(false);

        gridLayout_3->addWidget(check_seat, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 1);
        gridLayout_3->setRowStretch(1, 1);
        gridLayout_3->setRowStretch(2, 1);
        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);

        horizontalLayout_5->addLayout(gridLayout_3);

        Button_ScanPorts = new QPushButton(tab);
        Button_ScanPorts->setObjectName(QStringLiteral("Button_ScanPorts"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(3);
        sizePolicy.setHeightForWidth(Button_ScanPorts->sizePolicy().hasHeightForWidth());
        Button_ScanPorts->setSizePolicy(sizePolicy);
        Button_ScanPorts->setMinimumSize(QSize(0, 32));
        Button_ScanPorts->setFont(font1);
        Button_ScanPorts->setIconSize(QSize(16, 32));

        horizontalLayout_5->addWidget(Button_ScanPorts);

        horizontalLayout_5->setStretch(0, 2);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_4->addLayout(horizontalLayout_5);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        lineEdit_readfile = new QLineEdit(tab_2);
        lineEdit_readfile->setObjectName(QStringLiteral("lineEdit_readfile"));
        lineEdit_readfile->setMinimumSize(QSize(0, 32));
        QFont font2;
        font2.setPointSize(10);
        lineEdit_readfile->setFont(font2);

        formLayout->setWidget(0, QFormLayout::LabelRole, lineEdit_readfile);

        Button_Browse = new QPushButton(tab_2);
        Button_Browse->setObjectName(QStringLiteral("Button_Browse"));
        Button_Browse->setMinimumSize(QSize(0, 32));
        Button_Browse->setFont(font1);

        formLayout->setWidget(0, QFormLayout::FieldRole, Button_Browse);


        verticalLayout_3->addLayout(formLayout);

        PosInFileBar = new QScrollBar(tab_2);
        PosInFileBar->setObjectName(QStringLiteral("PosInFileBar"));
        PosInFileBar->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(PosInFileBar);


        verticalLayout_6->addLayout(verticalLayout_3);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);


        verticalLayout->addLayout(verticalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setMinimumSize(QSize(0, 32));
        checkBox->setFont(font1);
        checkBox->setChecked(false);

        horizontalLayout_4->addWidget(checkBox);

        lineEdit_savedir = new QLineEdit(centralWidget);
        lineEdit_savedir->setObjectName(QStringLiteral("lineEdit_savedir"));
        lineEdit_savedir->setMinimumSize(QSize(0, 32));
        lineEdit_savedir->setFont(font1);

        horizontalLayout_4->addWidget(lineEdit_savedir);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        lineEdit_Prefix = new QLineEdit(centralWidget);
        lineEdit_Prefix->setObjectName(QStringLiteral("lineEdit_Prefix"));
        lineEdit_Prefix->setMinimumSize(QSize(0, 32));
        lineEdit_Prefix->setFont(font1);

        horizontalLayout_4->addWidget(lineEdit_Prefix);

        Button_Browse_Save = new QPushButton(centralWidget);
        Button_Browse_Save->setObjectName(QStringLiteral("Button_Browse_Save"));
        Button_Browse_Save->setMinimumSize(QSize(0, 32));
        Button_Browse_Save->setFont(font1);

        horizontalLayout_4->addWidget(Button_Browse_Save);

        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(3, 1);
        horizontalLayout_4->setStretch(4, 1);

        verticalLayout->addLayout(horizontalLayout_4);

        Button_Start = new QPushButton(centralWidget);
        Button_Start->setObjectName(QStringLiteral("Button_Start"));
        Button_Start->setMinimumSize(QSize(0, 32));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        Button_Start->setFont(font3);

        verticalLayout->addWidget(Button_Start);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBox_rawData = new QCheckBox(centralWidget);
        checkBox_rawData->setObjectName(QStringLiteral("checkBox_rawData"));
        checkBox_rawData->setEnabled(false);
        checkBox_rawData->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_rawData);

        checkBox_basic = new QCheckBox(centralWidget);
        checkBox_basic->setObjectName(QStringLiteral("checkBox_basic"));
        checkBox_basic->setEnabled(false);
        checkBox_basic->setChecked(false);

        horizontalLayout_3->addWidget(checkBox_basic);

        checkBox_openCV = new QCheckBox(centralWidget);
        checkBox_openCV->setObjectName(QStringLiteral("checkBox_openCV"));
        checkBox_openCV->setEnabled(false);

        horizontalLayout_3->addWidget(checkBox_openCV);


        verticalLayout->addLayout(horizontalLayout_3);

        textOutput = new QTextEdit(centralWidget);
        textOutput->setObjectName(QStringLiteral("textOutput"));
        textOutput->setFont(font2);

        verticalLayout->addWidget(textOutput);

        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        verticalLayout->setStretch(5, 2);

        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 451, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_7->setText(QApplication::translate("MainWindow", "Data Source Setting", 0));
        check_desk->setText(QApplication::translate("MainWindow", "Desk Sensor", 0));
        check_seat->setText(QApplication::translate("MainWindow", "Seat Sensor", 0));
        Button_ScanPorts->setText(QApplication::translate("MainWindow", "Scan Ports", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "COM", 0));
        Button_Browse->setText(QApplication::translate("MainWindow", "Browse", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "FILE", 0));
        checkBox->setText(QApplication::translate("MainWindow", "Log Raw Data", 0));
        lineEdit_savedir->setText(QApplication::translate("MainWindow", "c:\\data\\", 0));
        label_6->setText(QApplication::translate("MainWindow", "Prefix", 0));
        lineEdit_Prefix->setText(QApplication::translate("MainWindow", "TPM", 0));
        Button_Browse_Save->setText(QApplication::translate("MainWindow", "Browse", 0));
        Button_Start->setText(QApplication::translate("MainWindow", "Start", 0));
        checkBox_rawData->setText(QApplication::translate("MainWindow", "Raw Data", 0));
        checkBox_basic->setText(QApplication::translate("MainWindow", "Basic", 0));
        checkBox_openCV->setText(QApplication::translate("MainWindow", "openCV", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
