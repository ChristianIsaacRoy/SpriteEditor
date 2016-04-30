#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QPainter>

class Cell : public QObject, public QGraphicsItem{
    Q_OBJECT

public:
    Cell(int size = 25, QColor color = Qt::white, QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;
    int getSize();
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* parent);
    void setColor(QColor color);
    void eraseColor();
    QColor getColor();
    QColor getHoverColor();

public slots:
    void setHoverColor(QColor color);

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:
    bool hovering;
    bool selected;
    QColor myColor;
    QColor hoverColor;
    int size;

signals:
    void clicked();
};

#endif // CELL_H
