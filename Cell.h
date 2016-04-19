#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QPainter>

class Cell : public QObject, public QGraphicsItem{
    Q_OBJECT

public:
    Cell(QGraphicsItem* parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* parent);
    void setDottedOutline();
    void setSolidOutline();
    void setNoOutline();
    void setColor(QColor color);
    void eraseColor();
    void swapColors();
    QColor getColor();
    QColor getHoverColor();

public slots:
    void setHoverColor(QColor color);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:
    bool selected;
    bool mouseIsHovering;
    int outline;
    QColor myColor;
    QColor hoverColor;

signals:
    void clicked();
};

#endif // CELL_H
