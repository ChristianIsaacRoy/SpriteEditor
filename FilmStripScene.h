#ifndef FILMSTRIPSCENE_H
#define FILMSTRIPSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "FilmStripFrame.h"


class FilmStripScene : public QGraphicsScene{
    Q_OBJECT
public:
    explicit FilmStripScene(QObject *parent = 0);
    void setImageOfCurrentFrame(QImage *image);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
    std::vector<FilmStripFrame *> frames;
    FilmStripFrame *currentFrame;

signals:
    void frameSelected(int frameNumber);

public slots:
    void addFrame(QImage *newFrameImage);

};

#endif // FILMSTRIPSCENE_H
