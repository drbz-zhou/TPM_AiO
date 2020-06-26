#include "qmlagent.h"

QMLAgent::QMLAgent(QObject *parent) : QObject(parent)
{
    // load QML file
    m_qmlEngine.load(QUrl(QStringLiteral("qrc:/QMLGUI.qml")));
    // load providers
    m_qmlEngine.addImageProvider(QLatin1String("matrix_provider_1"), &m_MatrixProvider);
    m_qmlEngine.addImageProvider(QLatin1String("plot_Provider_1"), &plotprovider_1);
    // access root object
    m_qmlRootObject = m_qmlEngine.rootObjects().value(0);
    // access canvas obejct
    m_qmlMatrixObject_1 = m_qmlRootObject->findChild<QObject *>("matrix_1",Qt::FindDirectChildrenOnly);
    m_qmlPlotObject_1 = m_qmlRootObject->findChild<QObject *>("plot_1",Qt::FindDirectChildrenOnly);
    m_qmlCanvasObject = m_qmlRootObject->findChild<QObject *>("canvas",Qt::FindDirectChildrenOnly);
    m_qmlSigItemObject= m_qmlRootObject->findChild<QObject *>("item",Qt::FindDirectChildrenOnly);
    QObject::connect(m_qmlRootObject, SIGNAL(qmlSignal(QString)), this, SLOT(respond_click(QString)));

    qDebug()<<"finished setting up QML Agent";
}

void QMLAgent::drawFrame(data_spatial data2D){
    m_MatrixProvider.updateFrame(data2D);

    QMetaObject::invokeMethod(m_qmlMatrixObject_1, "updateGrid");
}

void QMLAgent::addDataToGraph(QString graphKey, double dataPoint){
    plotprovider_1.addDataToGraph(graphKey, dataPoint);

    QMetaObject::invokeMethod(m_qmlPlotObject_1, "updatePlot");
}

void QMLAgent::setYRange(double min, double max){
    plotprovider_1.setYRange(min,max);
}
void QMLAgent::drawCircles(QVariantList circleData){

    QMetaObject::invokeMethod(m_qmlCanvasObject, "drawCircles",
                              Q_ARG(QVariant, QVariant::fromValue(circleData)));
}
void QMLAgent::setLabel_1(QString info){
    QMetaObject::invokeMethod(m_qmlRootObject, "updateLabel_1",
                              Q_ARG(QVariant, info));
}
void QMLAgent::respond_click(QString v){
    qDebug() << "Called the C++ slot with value:" << v;
}
