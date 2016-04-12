#ifndef COLORPREVIEW_H
#define COLORPREVIEW_H

#include <QObject>
#include <QGraphicsItem>

class ColorPreview: public QObject, public QGraphicsItem{
    Q_OBJECT

public:
    ColorPreview();
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* parent);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    void doubleClicked();
};

#endif // COLORPREVIEW_H
