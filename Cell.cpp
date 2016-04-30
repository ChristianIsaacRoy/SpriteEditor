#include "Cell.h"

#include <QDebug>

Cell::Cell(int size, QColor color, QGraphicsItem *parent) : QGraphicsItem(parent){
    setFlag(ItemIsMovable, false);
    setAcceptHoverEvents(true);
    //this->setCacheMode(QGraphicsItem::ItemCoordinateCache);

    this->size = size;
    myColor = QColor(0,0,0,0);
    hoverColor = color;
    selected = false;
    hovering = false;
}

QRectF Cell::boundingRect() const{
    return QRectF(0, 0, size, size);
}

int Cell::getSize(){
    return size;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *parent){
    QRectF rec = boundingRect();

    QBrush brush(Qt::white);
    if (hovering){
        brush.setColor(hoverColor);
    }
    else{
        brush.setColor(myColor);
    }

    if (selected){
        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::yellow);
        painter->setPen(pen);
        brush.setStyle(Qt::Dense1Pattern);
    }
    else {
        QPen pen(Qt::NoPen);
        painter->setPen(pen);
    }
    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

void Cell::setHoverColor(QColor color){
    hoverColor = color;
}

void Cell::setColor(QColor color){
    myColor = color;
    update();
}

void Cell::eraseColor(){
    myColor = QColor(0,0,0,0);
}

QColor Cell::getColor(){
    return myColor;
}

QColor Cell::getHoverColor(){
    return hoverColor;
}

void Cell::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    hovering = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    hovering = false;
    QGraphicsItem::mousePressEvent(event);
}

void Cell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    hovering = false;
    QGraphicsItem::hoverLeaveEvent(event);
}


