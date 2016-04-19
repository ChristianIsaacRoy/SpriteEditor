#include "Cell.h"

#include <QDebug>

Cell::Cell(QGraphicsItem *parent) : QGraphicsItem(parent){
    setFlag(ItemIsMovable, false);
    setAcceptHoverEvents(true);

    myColor = Qt::white;
    myColor.setAlpha(0);

    hoverColor = myColor;
    selected = false;
    outline = 0;
}

QRectF Cell::boundingRect() const{
    return QRectF(0, 0, 25, 25);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *parent){
    QRectF rec = boundingRect();

    QBrush brush(myColor);

    if (selected){
        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::yellow);
        painter->setPen(pen);
        brush.setStyle(Qt::Dense1Pattern);
    }
    else if (outline == 0){
        QPen pen(Qt::DotLine);
        pen.setColor(Qt::black);
        painter->setPen(pen);
    }
    else if (outline == 1){
        QPen pen(Qt::SolidLine);
        pen.setColor(Qt::black);
        painter->setPen(pen);
    }
    else {
        QPen pen(Qt::NoPen);
        painter->setPen(pen);
    }
    painter->fillRect(rec, brush);
    painter->drawRect(rec);
}

void Cell::setDottedOutline(){
    outline = 0;
    update();
}

void Cell::setSolidOutline(){
    outline = 1;
    update();
}

void Cell::setNoOutline(){
    outline = 3;
    update();
}

void Cell::setHoverColor(QColor color){
    hoverColor = color;
    update();
}

void Cell::setColor(QColor color){
    myColor = color;
    update();
}

void Cell::eraseColor(){
    myColor.setAlpha(0);
    hoverColor.setAlpha(0);
    update();
}

void Cell::swapColors(){
    QColor color = myColor;
    myColor = hoverColor;
    hoverColor = color;
}

QColor Cell::getColor(){
    return myColor;
}

QColor Cell::getHoverColor(){
    return hoverColor;
}


void Cell::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    swapColors();

    update();
    QGraphicsItem::hoverEnterEvent(event);
}

void Cell::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    swapColors();

    update();
    QGraphicsItem::hoverLeaveEvent(event);
}


