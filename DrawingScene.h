#ifndef DRAWINGSCENE_H
#define DRAWINGSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QWheelEvent>
#include <QTimeLine>
#include <Cell.h>

class DrawingScene : public QGraphicsScene{
    Q_OBJECT

public:
    DrawingScene(int cellSize, int cols, int rows, QColor backgroundColor, QObject *parent = 0);
    void setHoverColor(QColor color);
    void showImage(QImage *image);
    void showSolidGrid();
    void showDottedGrid();
    void showNoGrid();

public slots:
    void onBrushToolActive(QColor primColor, QColor seconColor, Cell *cell);
    void onEraserToolActive(Cell *cell);
    void onPaintBucketToolActive(QColor primColor, QColor seconColor, Cell *cell);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void drawForeground(QPainter *painter, const QRectF &rect);

private:
    std::vector<Cell*> cells;
    int myCols;
    int myRows;
    int grid;
    bool isDrawingPrimary;
    bool isDrawingSecondary;

private slots:

signals:
    void usingToolOnCell(Cell *cell);
    void cellModified(Cell *cell, QColor color);

};

#endif // DRAWINGSCENE_H
