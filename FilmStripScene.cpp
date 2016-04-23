#include "FilmStripScene.h"

FilmStripScene::FilmStripScene(QObject *parent) : QGraphicsScene(parent){
    this->setBackgroundBrush(QBrush(QColor(210, 210, 210)));
    currentFrame = nullptr;
}

void FilmStripScene::setImageOfCurrentFrame(QImage *image){
    currentFrame->setImage(image);
}

void FilmStripScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (mouseEvent->button() == Qt::LeftButton){
        // Get the frame at the mouse event and select it
        QPointF point = mouseEvent->scenePos();
        QGraphicsItem *item = this->itemAt(point, QTransform());
        FilmStripFrame *preview;
        if ( (preview = dynamic_cast<FilmStripFrame*>(item)) ){
            preview->selectFrame();
            int xPos = preview->scenePos().x();
            int frameNumber = xPos/150-1;
            currentFrame->deselectFrame();
            currentFrame = preview;
            emit frameSelected(frameNumber);
        }
    }
}

void FilmStripScene::addFrame(QImage *newFrameImage){
    if (currentFrame != nullptr){
        currentFrame->deselectFrame();
    }
    currentFrame = new FilmStripFrame(newFrameImage);
    currentFrame->selectFrame();
    frames.push_back(currentFrame);
    currentFrame->setPos(frames.size()*150, 0);
    this->addItem(currentFrame);
}
