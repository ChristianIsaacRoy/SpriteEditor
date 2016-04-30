#include "PreviewScene.h"

PreviewScene::PreviewScene(QObject* parent) : QGraphicsScene(parent){

}

void PreviewScene::showImage(QImage *image){
    this->image = image;
    this->clear();
    QPixmap map = QPixmap::fromImage(*image);
    this->addPixmap(map);
}
