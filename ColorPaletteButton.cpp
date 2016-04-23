#include "ColorPaletteButton.h"

void ColorPaletteButton::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        emit primaryColorChangeRequest(myColor);
    }
    else{
        emit secondaryColorChangeRequest(myColor);
    }
}

void ColorPaletteButton::mouseDoubleClickEvent(QMouseEvent *event){
    // Create a color picker dialog to retrieve a color
    QColorDialog colorPicker;
    colorPicker.setWindowTitle("Color Palette Picker");
    colorPicker.setOption(QColorDialog::ShowAlphaChannel);
    colorPicker.setOption(QColorDialog::DontUseNativeDialog);
    colorPicker.setCurrentColor(myColor);
    colorPicker.exec();
    QColor color = colorPicker.selectedColor();
    // If the user clicked cancel, an invalid color would return. We don't want that color.
    if (color.isValid()){
        setBackgroundColor(color);
        emit primaryColorChangeRequest(myColor);
    }
}

ColorPaletteButton::ColorPaletteButton() : ColorPaletteButton(25, 25, Qt::white){ }

ColorPaletteButton::ColorPaletteButton(int width, int height, QColor color){
    setBackgroundColor(color);
    this->setMaximumHeight(height);
    this->setMinimumHeight(height);
    this->setMaximumWidth(width);
    this->setMinimumWidth(width);
}

void ColorPaletteButton::setBackgroundColor(QColor color){
    myColor = color;
    int red = color.red();
    int green = color.green();
    int blue = color.blue();
    int alpha = color.alpha();
    QString stylesheet = "background-color: rgba(%1,%2,%3,%4);"
                                      "border-style: inset;"
                                      "border-width: 3px;"
                                      "padding: 2px;";
    this->setStyleSheet(stylesheet.arg(red).arg(green).arg(blue).arg(alpha));
}


