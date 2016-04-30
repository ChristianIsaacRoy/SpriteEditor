#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColorDialog>
#include <QImageWriter>
#include <QFileDialog>
#include <QToolButton>
#include <QTimer>
#include <QSpacerItem>
#include "Cell.h"
#include "Model.h"
#include "ColorPreview.h"
#include "DrawingScene.h"
#include "FilmStripFrame.h"
#include "FilmStripScene.h"
#include "DrawingGraphicsView.h"
#include "PreviewScene.h"
#include "ColorPalette.h"
#include "NewProjectDialog.h"

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // Constants...
    const int DEFAULT_SPRITE_WIDTH = 32;
    const int DEFAULT_SPRITE_HEIGHT = 32;
    const int DEFAULT_CELL_SIZE = 50;
    const QColor DEFAULT_BACKGROUND_COLOR = QColor(220, 220, 220);
    const QColor DEFAULT_PRIMARY_COLOR = Qt::black;
    const QColor DEFAULT_SECONDARY_COLOR = Qt::white;
    const QColor CLEAR = QColor(255, 255, 255, 0);
    const int DEFAULT_FPS = 5;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void startNewProject(int columns, int rows, int fps);

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
    void on_addFrameButton_clicked();
    void on_actionExport_triggered();
    void on_playButton_clicked();
    void on_actionNew_triggered();
    void on_paintBucketButton_clicked();
    void on_actionOpen_triggered();

    void onBrushColorsReceived(QColor color1, QColor color2);
    void onCurrentFrameReceived(QImage *image);
    void onPlayButtonTimerShot();

    void on_actionSave_as_triggered();

    void buildNewDrawingArea(int width, int height, int fps);

private:
    Ui::MainWindow *ui;
    Model *model;

    DrawingScene *drawingScene;
    DrawingGraphicsView *drawingGV;

    QGraphicsScene *primColorScene;
    QGraphicsScene *secColorScene;
    QGraphicsTextItem *primColorText;
    QGraphicsTextItem *secColorText;
    ColorPreview *primPreview;
    ColorPreview *secPreview;

    FilmStripScene *filmStripScene;

    PreviewScene *previewScene;
    vector<QImage*> images;
    QToolButton *playButton;
    vector<QImage*>::iterator imageBeingShown;

    ColorPalette *colorPalette;

    int spriteWidth;
    int spriteHeight;
    int fps;

    void connectSignalsSlots();
    void updateColorPalette();
    void setUp();
    void disconnectAll();
    void write(QString filename);

signals:
    void brushPrimaryColorChanged(QColor color);
    void brushSecondaryColorChanged(QColor color);
    void activateBrushTool();
    void eraserActivated();
    void activatePaintBucket();
    void requestToAddFrame();
    void framesReqeusted();
};

#endif // MAINWINDOW_H
