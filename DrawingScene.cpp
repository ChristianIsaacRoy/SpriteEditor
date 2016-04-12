#include "DrawingScene.h"

#include <QDebug>

DrawingScene::DrawingScene(int cellSize, int cols, int rows, QColor backgroundColor, QObject *parent) : QGraphicsScene(parent){
    myCols = cols;
    myRows = rows;

    // Add a background to the drawing scene.
    this->setBackgroundBrush(QBrush(backgroundColor));

    // Fill the drawing scene with cells
    Cell *cell;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cell = new Cell();
            cells.push_back(cell);
            cell->setPos(j*cellSize, i*cellSize);
            this->addItem(cell);
        }
    }

    isDrawingPrimary = false;
    isDrawingSecondary = false;
}

void DrawingScene::setHoverColor(QColor color){
    for (std::vector<Cell*>::iterator it = cells.begin(); it != cells.end(); it++){
        Cell* cell = *it;
        cell->setHoverColor(color);
    }
}

void DrawingScene::showImage(QImage *image){
    if (image->width() == myCols && image->height() == myRows){
        int x = 0;
        int y = 0;
        for (std::vector<Cell*>::iterator it = cells.begin(); it != cells.end(); it++){
            Cell* cell = *it;
            cell->setColor(image->pixelColor(x, y));
            x++;
            if (x == myCols){
                x = 0;
                y++;
            }
        }
    }
}

void DrawingScene::showSolidGrid(){
    for (std::vector<Cell*>::iterator it = cells.begin(); it != cells.end(); it++){
        Cell* cell = *it;
        cell->setSolidOutline();
    }
}

void DrawingScene::showDottedGrid(){
    for (std::vector<Cell*>::iterator it = cells.begin(); it != cells.end(); it++){
        Cell* cell = *it;
        cell->setDottedOutline();
    }
}

void DrawingScene::showNoGrid(){
    for (std::vector<Cell*>::iterator it = cells.begin(); it != cells.end(); it++){
        Cell* cell = *it;
        cell->setNoOutline();
    }
}

void DrawingScene::onBrushToolActive(QColor primColor, QColor seconColor, QPointF mousePos){
    if (isDrawingPrimary | isDrawingSecondary){
        // Get the cell at the mouse event and color it
        QGraphicsItem *item = this->itemAt(mousePos, QTransform());
        Cell *cell;
        if ( (cell = dynamic_cast<Cell*>(item)) ){

            if (isDrawingPrimary){
                cell->setColor(primColor);
                cell->setHoverColor(primColor);
                emit cellModified(cell->scenePos(), primColor);
            }
            else if (isDrawingSecondary){
                cell->setColor(seconColor);
                cell->setHoverColor(primColor);
                emit cellModified(cell->scenePos(), seconColor);
            }

            cell->update();
        }
    }
}

void DrawingScene::onEraserToolActive(QPointF mousePos){
    if (isDrawingPrimary | isDrawingSecondary){
        // Get the cell at the mouse event and erase it
        QGraphicsItem *item = this->itemAt(mousePos, QTransform());
        Cell *cell;
        QColor color = Qt::white;
        color.setAlpha(0);
        if ( (cell = dynamic_cast<Cell*>(item)) ){
                cell->setColor(color);
                cell->setHoverColor(color);
                cell->update();
                emit cellModified(cell->scenePos(), color);
        }

    }
}

void DrawingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (isDrawingPrimary | isDrawingSecondary){
        emit usingToolAt(mouseEvent->scenePos());
    }

    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void DrawingScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){

    if (mouseEvent->button() == Qt::LeftButton){
        // Get the cell at the mouse event and color it
        QPointF point = mouseEvent->scenePos();
        QGraphicsItem *item = this->itemAt(point, QTransform());
        Cell *cell;
        if ( (cell = dynamic_cast<Cell*>(item)) ){
            isDrawingPrimary = true;
            emit usingToolAt(point);
        }
    }
    else if (mouseEvent->button() == Qt::RightButton){
        // Get the cell at the mouse event and color it
        QPointF point = mouseEvent->scenePos();
        QGraphicsItem *item = this->itemAt(point, QTransform());
        Cell *cell;
        if ( (cell = dynamic_cast<Cell*>(item)) ){
            clickedCell = cell;
            isDrawingSecondary = true;
            emit usingToolAt(point);
        }
    }

}

void DrawingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (isDrawingSecondary){
        clickedCell->swapColors();
        emit cellModified(clickedCell->scenePos(), clickedCell->getColor());
    }
    isDrawingPrimary = false;
    isDrawingSecondary = false;
}

