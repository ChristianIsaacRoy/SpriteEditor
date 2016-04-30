#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QColor>
#include <QFile>
#include "Cell.h"

using namespace std;

class Model : public QObject{
    Q_OBJECT

public:
    Model(int width, int height, QColor brushColor1, QColor brushColor2);
    bool isBrushToolActive();
    bool isEraserToolActive();
    QImage* getCurrentFrame();
    vector<QImage*> getFrames();
    bool save(QString filename);
    bool open(QString filename);
    void reset(int width, int height, QColor brushColor1, QColor brushColor2);

public slots:
    void onBrushToolActivated();
    void onEraserToolActivated();
    void onPaintBucketToolActivated();

    void setBrushPrimaryColor(QColor color);
    void setBrushSecondaryColor(QColor color);

    void usingToolOnCell(Cell *cell);
    void onRequestForBrushColors();

    void onCellModified(Cell *cell, QColor cellColor);

    void onRequestToAddFrame();

    void onFrameSelected(int frameNumber);

private:
    vector<QImage*> frames;
    QImage *currentFrame;
    int fps;

    QColor brushPrimaryColor;
    QColor brushSecondaryColor;

    int spriteWidth;
    int spriteHeight;
    int toolNumber;

signals:
    void brushColors(QColor primColor, QColor seconColor);
    void brushToolActive(QColor primColor, QColor seconColor, Cell *cell);
    void eraserToolActive(Cell *cell);
    void currentFrameModified(QImage *currentFrame);
    void frameAdded(QImage *newFrame);
    void currentFrameChanged(QImage *image);
    void paintBucketToolActive(QColor primcolor, QColor seconColor, Cell *cell);
    void openingFile(int spriteWidth, int spriteHeight, int fps);
};

#endif // MODEL_H
