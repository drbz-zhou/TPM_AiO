#ifndef IMAGEPROVIDER_PLOT_H
#define IMAGEPROVIDER_PLOT_H

#define TemporalBufferSize 200

#include <QQuickImageProvider>
#include "qcustomplot/qcustomplot.h"
#include "include/data_temporal.h"

class ImageProvider_plot : public QQuickImageProvider
{
public:
    ImageProvider_plot();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

    void addDataToGraph(QString graphKey, double dataPoint);
    void clearGraphs();
    void setDefaultColors();
    void setYRange(double min, double max);

private:

    QCustomPlot *m_plot;
    QMap<QString, int> m_graphMap; // maps graphkeyes to integers
    double m_graphLengthSeconds;
    QVector<QColor> m_graphColorList;
    QVector<data_temporal> m_plotBuffers;
    double m_min;
    double m_max;
};

#endif // IMAGEPROVIDER_PLOT_H
