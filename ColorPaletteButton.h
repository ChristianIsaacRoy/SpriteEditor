#ifndef COLORPALETTEBUTTON_H
#define COLORPALETTEBUTTON_H

#include <QToolButton>
#include <QColorDialog>
#include <QMouseEvent>

class ColorPaletteButton : public QToolButton{
    Q_OBJECT

private:
    QColor myColor;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

public:
    ColorPaletteButton();
    ColorPaletteButton(int width, int height, QColor color);

    void setBackgroundColor(QColor color);

signals:
    void primaryColorChangeRequest(QColor color);
    void secondaryColorChangeRequest(QColor color);
};

#endif // COLORPALETTEBUTTON_H
