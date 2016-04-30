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

void Model::onPaintBucketToolActivated(){
    toolNumber = 2;
}

void Model::setBrushPrimaryColor(QColor color){
    brushPrimaryColor = color;
    emit brushColors(brushPrimaryColor, brushSecondaryColor);
}

void Model::setBrushSecondaryColor(QColor color){
    brushSecondaryColor = color;
    emit brushColors(brushPrimaryColor, brushSecondaryColor);
}

void Model::usingToolOnCell(Cell *cell){
    if (toolNumber == 0){
        emit brushToolActive(brushPrimaryColor, brushSecondaryColor, cell);
    }
    else if (toolNumber == 1){
        emit eraserToolActive(cell);
    }
    else if (toolNumber == 2){
        emit paintBucketToolActive(brushPrimaryColor, brushSecondaryColor, cell);
    }
}

void Model::onRequestForBrushColors(){
    emit brushColors(brushPrimaryColor, brushSecondaryColor);
}

void Model::onCellModified(Cell *cell, QColor cellColor){
    int col = cell->scenePos().x()/cell->getSize();
    int row = cell->scenePos().y()/cell->getSize();
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
    currentFrame = frames.at(frameNumber);
    emit currentFrameChanged(currentFrame);
}

QImage* Model::getCurrentFrame(){
    return currentFrame;
}

vector<QImage*> Model::getFrames(){
    return frames;
}

bool Model::save(QString filename){
    QFile file(filename);

    // Return false if we cannot open file
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        return false;
    }

    QTextStream out(&file);

    // First line is width, height, number of frames, and fps
    out << spriteWidth << " " << spriteHeight << " " << frames.size() << endl;

    // Go through each frame, and print each pixel
    QImage *image;
    for (auto it = frames.begin(); it != frames.end(); it++){
        for (int i = 0; i < spriteWidth; i++){
            for (int j = 0; j < spriteHeight; j++){
                image = *it;
                out << image->pixelColor(i,j).red() << " "
                    << image->pixelColor(i,j).green() << " "
                    << image->pixelColor(i,j).blue() << " "
                    << image->pixelColor(i,j).alpha() << " ";
            }
            out << "\n";
        }
    }

    file.flush();
    file.close();
    return true;
}

bool Model::open(QString filename){
    qDebug() << "before" << frames.size();
    // Get rid of old stuff
    frames.clear();
    qDebug() << "after" << frames.size();
    // Create a QFile with the file address
    QFile file(filename);

    // If it doesn't open, return false
    if (!file.open(QFile::ReadOnly | QFile::Text)){
            return false;
    }

    // Acts as a input stream
    QTextStream in(&file);
    int numOfFrames;

    // Read the file, line by line
    // First line is width, height, number of frames, and fps
    if (!in.atEnd()){
        QString line = in.readLine();
        spriteWidth = line.section(' ', 0, 0).toInt();
        spriteHeight = line.section(' ', 1, 1).toInt();
        numOfFrames = line.section(' ', 2, 2).toInt();
        emit openingFile(spriteWidth, spriteHeight, 5);
    }
    else {
        return false;
    }

    // The rest of the lines are pixel colors
    while (!in.atEnd()) {
        QImage *image = new QImage(spriteWidth, spriteHeight, QImage::Format_ARGB32_Premultiplied);
        for (int i = 0; i < spriteWidth; i++){
            QString line = in.readLine();
            for (int j = 0; j < spriteHeight*4; j+=4){
                int r = line.section(' ', j, j).toInt();
                int g = line.section(' ', j+1, j+1).toInt();
                int b = line.section(' ', j+2, j+2).toInt();
                int a = line.section(' ', j+3, j+3).toInt();
                image->setPixelColor(i, j/4, QColor(r, g, b, a));
            }
        }
        frames.push_back(image);
        currentFrame = image;
        emit frameAdded(image);
    }

    file.flush();
    file.close();

    // Update UI
    emit currentFrameChanged(currentFrame);

    return true;

}

void Model::reset(int width, int height, QColor brushColor1, QColor brushColor2){
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

    frames.empty();
    currentFrame = nullptr;

}
