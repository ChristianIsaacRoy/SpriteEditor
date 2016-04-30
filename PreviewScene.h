#ifndef PREVIEWSCENE_H
#define PREVIEWSCENE_H

#include <QGraphicsScene>

/**
 * @brief The PreviewScene class - Used to display a QImage.
 */
class PreviewScene : public QGraphicsScene{
public:
    PreviewScene(QObject* parent);

public slots:
    /**
     * @brief showImage - The preview scene will display a given image
     * @param image - A pointer to a QImage to display.
     */
    void showImage(QImage* image);

private:
    QImage *image;

};

#endif // PREVIEWSCENE_H
