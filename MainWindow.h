#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColorDialog>
#include "Cell.h"
#include "Model.h"
#include "ColorPreview.h"
#include "DrawingScene.h"
#include "FramePreview.h"
#include "FilmStripScene.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // Constants...
    const int DEFAULT_SPRITE_WIDTH = 64;
    const int DEFAULT_SPRITE_HEIGHT = 64;
    const int DEFAULT_CELL_SIZE = 25;
    const QColor DEFAULT_BACKGROUND_COLOR = QColor(220, 220, 220);
    const QColor DEFAULT_PRIMARY_COLOR = Qt::black;
    const QColor DEFAULT_SECONDARY_COLOR = Qt::white;
    const QColor CLEAR = QColor(255, 255, 255, 0);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionDotGridOn_triggered();
    void on_actionSolidGridOn_triggered();
    void on_actionTurn_Off_Grid_triggered();
    void on_actionLightGrayBackground_triggered();
    void on_actionWhiteBackground_triggered();
    void on_actionCustomBackgroundColor_triggered();
    void on_actionBrush_Primary_Color_Picker_triggered();
    void on_actionBrush_Secondary_Color_Picker_triggered();
    void on_brushButton_clicked();
    void on_eraserButton_clicked();
    void on_actionUse_Brush_triggered();
    void on_actionUse_Eraser_triggered();

    void onBrushColorsReceived(QColor color1, QColor color2);

    void onCurrentFrameReceived(QImage *image);

    void on_addFrameButton_clicked();

    void on_coloPaletteB_clicked();
    void on_coloPaletteB_2_clicked();
    void on_coloPaletteB_3_clicked();
    void on_coloPaletteB_4_clicked();
    void on_coloPaletteB_5_clicked();
    void on_coloPaletteB_6_clicked();
    void on_coloPaletteB_7_clicked();
    void on_coloPaletteB_8_clicked();
    void on_coloPaletteB_9_clicked();
    void on_coloPaletteB_10_clicked();
    void on_coloPaletteB_11_clicked();
    void on_coloPaletteB_12_clicked();
    void on_coloPaletteB_13_clicked();
    void on_coloPaletteB_14_clicked();
    void on_coloPaletteB_15_clicked();
    void on_coloPaletteB_16_clicked();

private:
    Ui::MainWindow *ui;
    Model *model;

    DrawingScene *drawingScene;

    QGraphicsScene *primColorScene;
    QGraphicsScene *secColorScene;
    QGraphicsTextItem *primColorText;
    QGraphicsTextItem *secColorText;
    ColorPreview *primPreview;
    ColorPreview *secPreview;

    FilmStripScene *filmStripScene;

    int spriteWidth;
    int spriteHeight;

    void connectSignalsSlots();
    void updateColorPalette();
    void updateColorPreviews(QColor newColor);

signals:
    void brushPrimaryColorChanged(QColor color);
    void brushSecondaryColorChanged(QColor color);
    void activateBrushTool();
    void eraserActivated();
    void requestToAddFrame();
};

#endif // MAINWINDOW_H
