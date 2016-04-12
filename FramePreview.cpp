#include "FramePreview.h"

FramePreview::FramePreview(QImage *newImage, QGraphicsItem *parent) : QGraphicsItem(parent){
    selected = false;
    image = newImage;
}

void FramePreview::setImage(QImage *newImage){
    image = newImage;
    update();
}

void FramePreview::selectFrame(){
    selected = true;
    update();
}

void FramePreview::deselectFrame(){
    selected = false;
    update();
}

QRectF FramePreview::boundingRect() const{
    return QRectF(0, 0, 120, 120);
}

void FramePreview::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *parent){
    QRectF rec = boundingRect();
    QPen pen(Qt::SolidLine);
    pen.setWidth(5);

    if (selected){
        pen.setColor(Qt::yellow);
    }
    else{
        pen.setColor(Qt::black);
    }

    painter->setPen(pen);
    QImage scaledImage = image->scaled(110, 110);
    painter->drawImage(5, 5, scaledImage);
    painter->drawRect(rec);
}

