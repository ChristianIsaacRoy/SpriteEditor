#include "DrawingGraphicsView.h"
#include <QDebug>

DrawingGraphicsView::DrawingGraphicsView(int width, int height, QWidget *parent) : QGraphicsView(parent){
    _numScheduledScalings = 0;

    // Adjust maximum heigh and width of draw area based on number of cells
    this->setMaximumHeight(height);
    this->setMaximumWidth(width);

}

void DrawingGraphicsView::wheelEvent ( QWheelEvent * event ){
     int numDegrees = event->delta() / 8;
     int numSteps = numDegrees / 15; // see QWheelEvent documentation

     _numScheduledScalings += numSteps;

     if (_numScheduledScalings * numSteps < 0){ // if user moved the wheel in another direction, we reset previously scheduled scalings
        _numScheduledScalings = numSteps;
     }

     QTimeLine *anim = new QTimeLine(350, this);
     anim->setUpdateInterval(20);

     connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
     connect(anim, SIGNAL (finished()), SLOT (animFinished()));
     anim->start();

}

void DrawingGraphicsView::scalingTime(qreal x){
     qreal factor = 1.0+ qreal(_numScheduledScalings) / 300.0;
     scale(factor, factor);
}

void DrawingGraphicsView::animFinished(){
     if (_numScheduledScalings > 0){
        _numScheduledScalings--;
     }
     else{
        _numScheduledScalings++;
     }
     sender()->~QObject();
}
