#ifndef FRAMEPREVIEW_H
#define FRAMEPREVIEW_H

#include <QObject>
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>

class FramePreview : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit FramePreview(QImage *newImage, QGraphicsItem *parent = 0);
    void setImage(QImage *newImage);
    void selectFrame();
    void deselectFrame();

protected:
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* parent);

private:
    QImage *image;
    bool selected;

signals:

public slots:
};

#endif // FRAMEPREVIEW_H
