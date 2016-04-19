#ifndef PREVIEWSCENE_H
#define PREVIEWSCENE_H

#include <QGraphicsScene>

class PreviewScene : public QGraphicsScene
{
public:
    PreviewScene(QObject* parent);

public slots:
    void onImageModified(QImage* image);
    void onFrameChanged(QImage* image);

};

#endif // PREVIEWSCENE_H
