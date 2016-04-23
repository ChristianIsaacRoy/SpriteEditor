#include "ColorPalette.h"

ColorPalette::ColorPalette(){
    ColorPalette(10, 3);
}

ColorPalette::ColorPalette(int columns, int rows){
    this->setSpacing(1);

    // Add the label
    label = new QLabel();
    label->setText("Color Palette");
    QFont font("Segoe UI");
    font.setBold(true);
    font.setPointSize(10);
    label->setFont(font);
    this->addWidget(label, 0, 0, 1, columns);

    // Add the buttons
    for (int i = 1; i < rows+1; i++){
        for ( int j = 0; j < columns; j++){
            ColorPaletteButton *button = new ColorPaletteButton(25, 25, Qt::lightGray);
            this->addWidget(button, i, j);
            buttons.push_back(button);
        }
    }
}

ColorPalette::~ColorPalette(){
    for (auto it = buttons.begin(); it != buttons.end(); it++){
        delete *it;
    }
    delete label;
}

int ColorPalette::numberOfColors(){
    return buttons.size();
}

QVector<ColorPaletteButton *> ColorPalette::getButtons(){
    return buttons;
}
