#include "FilmStripFrame.h"

FilmStripFrame::FilmStripFrame(QImage *newImage, QGraphicsItem *parent) : QGraphicsItem(parent){
    selected = false;
    image = newImage;
}

void FilmStripFrame::setImage(QImage *newImage){
    image = newImage;
    update();
}

void FilmStripFrame::selectFrame(){
    selected = true;
    update();
}

void FilmStripFrame::deselectFrame(){
    selected = false;
    update();
}

QRectF FilmStripFrame::boundingRect() const{
    return QRectF(0, 0, 120, 120);
}

void FilmStripFrame::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *parent){
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

