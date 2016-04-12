#include "Model.h"

#include <QDebug>
Model::Model(int width, int height, QColor brushColor1, QColor brushColor2){

    if ( (width > 0) | (height > 0) ){
        spriteWidth = width;
        spriteHeight = height;
    }
    else{
        spriteWidth = 2;
        spriteHeight = 2;
    }

    // Set up Brush
    toolNumber = 0;
    brushPrimaryColor = brushColor1;
    brushSecondaryColor = brushColor2;
}

bool Model::isBrushToolActive(){
    return (toolNumber == 0);
}

bool Model::isEraserToolActive(){
    return (toolNumber == 1);
}

void Model::onBrushToolActivated(){
    toolNumber = 0;
    emit brushColors(brushPrimaryColor, brushSecondaryColor);
}

void Model::onEraserToolActivated(){
    toolNumber = 1;
}

void Model::setBrushPrimaryColor(QColor color){
    brushPrimaryColor = color;
}

void Model::setBrushSecondaryColor(QColor color){
    brushSecondaryColor = color;
}

void Model::usingToolAt(QPointF mousePos){
    if (toolNumber == 0){
        emit brushToolActive(brushPrimaryColor, brushSecondaryColor, mousePos);
    }
    else if (toolNumber == 1){
        emit eraserToolActive(mousePos);
    }
}

void Model::onRequestForBrushColors(){
    emit brushColors(brushPrimaryColor, brushSecondaryColor);
}

void Model::onCellModified(QPointF cellPos, QColor cellColor){
    int col = cellPos.x()/25;
    int row = cellPos.y()/25;
    currentFrame->setPixelColor(col, row, cellColor);
    emit currentFrameModified(currentFrame);
}

void Model::onRequestToAddFrame(){
    QImage *newImage = new QImage(spriteWidth, spriteHeight, QImage::Format_ARGB32_Premultiplied);
    QColor color(Qt::white);
    color.setAlpha(0);
    newImage->fill(color);
    frames.push_back(newImage);
    currentFrame = newImage;
    emit frameAdded(newImage);
}

void Model::onFrameSelected(int frameNumber){
    qDebug() << frameNumber;
    currentFrame = frames.at(frameNumber);
    emit currentFrameChanged(currentFrame);
}
