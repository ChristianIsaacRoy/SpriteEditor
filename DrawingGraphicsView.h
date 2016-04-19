#ifndef DRAWINGGRAPHICSVIEW_H
#define DRAWINGGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QTimeLine>

class DrawingGraphicsView : public QGraphicsView{
    Q_OBJECT
private:
    int _numScheduledScalings;
private slots:
    void scalingTime(qreal x);
    void animFinished();

protected:
    virtual void wheelEvent(QWheelEvent *event);

public:
    explicit DrawingGraphicsView(int width, int height, QWidget *parent = 0);

signals:

public slots:
};

#endif // DRAWINGGRAPHICSVIEW_H
