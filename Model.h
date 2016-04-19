#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QColor>
#include "Cell.h"

using namespace std;

class Model : public QObject{
    Q_OBJECT

public:
    Model(int width, int height, QColor brushColor1, QColor brushColor2);
    bool isBrushToolActive();
    bool isEraserToolActive();
    QImage* getCurrentFrame();

public slots:
    void onBrushToolActivated();
    void onEraserToolActivated();

    void setBrushPrimaryColor(QColor color);
    void setBrushSecondaryColor(QColor color);

    void usingToolAt(QPointF mousePos);
    void onRequestForBrushColors();

    void onCellModified(QPointF cellPos, QColor cellColor);

    void onRequestToAddFrame();

    void onFrameSelected(int frameNumber);

private:
    vector<QImage*> frames;
    QImage *currentFrame;

    QColor brushPrimaryColor;
    QColor brushSecondaryColor;

    int spriteWidth;
    int spriteHeight;
    int toolNumber;

signals:
    void brushColors(QColor primColor, QColor seconColor);
    void brushToolActive(QColor primColor, QColor seconColor, QPointF mousePos);
    void eraserToolActive(QPointF);
    void currentFrameModified(QImage *currentFrame);
    void frameAdded(QImage *newFrame);
    void currentFrameChanged(QImage *image);
};

#endif // MODEL_H
