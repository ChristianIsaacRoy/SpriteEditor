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
    void buildGrid(int cols, int rows, int cellSize, QColor hoverColor);
    void setHoverColor(QColor color);
    void showImage(QImage *image);
    void showSolidGrid();
    void showDottedGrid();
    void showNoGrid();

public slots:
    void onBrushToolActive(QColor primColor, QColor seconColor, QPointF mousePos);
    void onEraserToolActive(QPointF mousePos);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
    std::vector<Cell*> cells;
    int myCols;
    int myRows;

    bool isDrawingPrimary;
    bool isDrawingSecondary;
    Cell* clickedCell;

private slots:

signals:
    void usingToolAt(QPointF mousePos);
    void cellModified(QPointF cellPos, QColor color);

};

#endif // DRAWINGSCENE_H
