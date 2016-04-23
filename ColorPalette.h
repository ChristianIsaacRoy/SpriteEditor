#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QGridLayout>
#include <QToolButton>
#include <QVector>
#include <QLabel>
#include "ColorPaletteButton.h"

class ColorPalette : public QGridLayout{

private:
    QVector<ColorPaletteButton*> buttons;
    QLabel *label;

public:
    ColorPalette();
    ColorPalette(int columns, int rows);
    ~ColorPalette();

    int numberOfColors();
    QVector<ColorPaletteButton*> getButtons();
};

#endif // COLORPALETTE_H
