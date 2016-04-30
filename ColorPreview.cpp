#include "ColorPreview.h"

ColorPreview::ColorPreview(){

}

QRectF ColorPreview::boundingRect() const{
    return QRectF(0, 0, 50, 50);
}

void ColorPreview::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *parent){

}

void ColorPreview::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    emit doubleClicked();
}
