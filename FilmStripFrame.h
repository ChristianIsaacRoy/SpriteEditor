#ifndef FILMSTRIPFRAME_H
#define FILMSTRIPFRAME_H

#include <QObject>
#include <QGraphicsItem>
#include <QPen>
#include <QPainter>

class FilmStripFrame : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit FilmStripFrame(QImage *newImage, QGraphicsItem *parent = 0);
    void setImage(QImage *newImage);
    void selectFrame();
    void deselectFrame();

protected:
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* options, QWidget* parent);

private:
    QImage *image;
    bool selected;

signals:

public slots:
};

#endif // FILMSTRIPFRAME_H
