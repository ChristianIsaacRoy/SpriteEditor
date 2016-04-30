#include "DrawingScene.h"

#include <QDebug>

DrawingScene::DrawingScene(int cellSize, int cols, int rows, QColor backgroundColor, QObject *parent) : QGraphicsScene(parent){
    myCols = cols;
    myRows = rows;
    grid = 0;

    // Add a background to the drawing scene.
    this->setBackgroundBrush(QBrush(backgroundColor));

    // Fill the drawing scene with cells
    Cell *cell;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cell = new Cell(cellSize);
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
    grid = 2;
    update();
}

void DrawingScene::showDottedGrid(){
    grid = 0;
    update();
}

void DrawingScene::showNoGrid(){
    grid = 1;
    update();
}

void DrawingScene::onBrushToolActive(QColor primColor, QColor seconColor, Cell *cell){
        if (isDrawingPrimary){
            cell->setColor(primColor);
            emit cellModified(cell, primColor);
        }
        else if (isDrawingSecondary){
            cell->setColor(seconColor);
            emit cellModified(cell, seconColor);
        }
}

void DrawingScene::onEraserToolActive(Cell *cell){
    if (isDrawingPrimary | isDrawingSecondary){
        cell->eraseColor();
        emit cellModified(cell, cell->getColor());
    }
}

void DrawingScene::onPaintBucketToolActive(QColor primColor, QColor seconColor, Cell *cell){
    // If the color of the cell is the same as the color being used, just stop
    if (cell->getColor() == primColor && isDrawingPrimary ||
            cell->getColor() == seconColor && isDrawingSecondary){
        return;
    }

    // Store the old color of the cell being modified
    QColor oldColor = cell->getColor();

    // Color this cell if needed, else return
    onBrushToolActive(primColor, seconColor, cell);

    // If the cells around this one are the same color, tell them to color themselves too.

    // Locations of cells on scene
    QPoint above(cell->scenePos().x(), cell->scenePos().y() - cell->getSize());
    QPoint below(cell->scenePos().x(), cell->scenePos().y() + cell->getSize());
    QPoint left  (cell->scenePos().x() - cell->getSize(), cell->scenePos().y());
    QPoint right(cell->scenePos().x() + cell->getSize(), cell->scenePos().y());

    // Find items in scene
    QVector<QGraphicsItem*> items;
    items.push_back(this->itemAt(above, QTransform()));
    items.push_back(this->itemAt(right, QTransform()));
    items.push_back(this->itemAt(below, QTransform()));
    items.push_back(this->itemAt(left, QTransform()));

    // Confirm that the items are cells
    for (int i = 0; i < 4; i++){
        Cell *cell2;
        if ( cell2 = qgraphicsitem_cast<Cell*>(items.at(i)) ){

            // If the cell is the same color as this cell, we want to change it too.
            if (cell2->getColor() == oldColor){
                onPaintBucketToolActive(primColor, seconColor, cell2);
            }
        }
    }
}

void DrawingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent){
    if (isDrawingPrimary | isDrawingSecondary){
        // Get the cell at the mouse event and color it
        QGraphicsItem *item = this->itemAt(mouseEvent->scenePos(), QTransform());
        Cell *cell;
        if ( (cell = dynamic_cast<Cell*>(item)) ){
            emit usingToolOnCell(cell);
        }
    }
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void DrawingScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent){
    // Get the cell at the mouse event
    QGraphicsItem *item = this->itemAt(mouseEvent->scenePos(), QTransform());
    Cell *cell;
    if ( (cell = dynamic_cast<Cell*>(item)) ){

        // Check for left click
        if (mouseEvent->button() == Qt::LeftButton){
            isDrawingPrimary = true;
            emit usingToolOnCell(cell);
        }

        // Check for right click
        else if (mouseEvent->button() == Qt::RightButton){
            isDrawingSecondary = true;
            emit usingToolOnCell(cell);
        }
    }
}

void DrawingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent){
    isDrawingPrimary = false;
    isDrawingSecondary = false;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void DrawingScene::drawForeground(QPainter *painter, const QRectF &rect){
    Cell *cell = *cells.begin();

    int width = cell->getSize();
    qreal left = 0;
    qreal top = 0;
    qreal right = width*myCols;
    qreal bottom = width*myRows;

    QVarLengthArray<QLineF, 1000> lines;

    for (qreal x = left; x <= right; x += width){
        lines.append(QLineF(x, 0, x, bottom));
    }
    for (qreal y = top; y <= bottom; y += width)
        lines.append(QLineF(left, y, right, y));

    if (grid == 0){
        painter->setPen(Qt::DotLine);
    }
    else if (grid == 1){
        painter->setPen(Qt::NoPen);
    }
    painter->drawLines(lines.data(), lines.size());
    QGraphicsScene::drawForeground(painter, rect);
}



