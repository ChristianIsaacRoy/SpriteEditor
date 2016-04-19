#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Build the model
    spriteWidth = DEFAULT_SPRITE_WIDTH;
    spriteHeight = DEFAULT_SPRITE_HEIGHT;
    model = new Model(spriteWidth, spriteHeight, DEFAULT_PRIMARY_COLOR, DEFAULT_SECONDARY_COLOR);

    // Set up drawing area
    drawingGV = new DrawingGraphicsView(DEFAULT_CELL_SIZE * spriteWidth + 2, DEFAULT_CELL_SIZE *spriteHeight + 10, this);
    drawingScene = new DrawingScene(DEFAULT_CELL_SIZE, spriteWidth, spriteHeight, DEFAULT_BACKGROUND_COLOR, drawingGV);
    drawingScene->setHoverColor(DEFAULT_PRIMARY_COLOR);
    drawingGV->setScene(drawingScene);
    ui->MiddleColumn->replaceWidget(ui->becomeDrawingGV, drawingGV);
    delete ui->becomeDrawingGV;

    // Prepare Brush primary Color Preview
    primColorScene = new QGraphicsScene(ui->primColorGV);
    primColorScene->setBackgroundBrush(QBrush(QColor(DEFAULT_PRIMARY_COLOR)));
    primPreview = new ColorPreview();
    primColorText = new QGraphicsTextItem("1", primPreview);
    primColorText->setFont(QFont("Helvetica", 12, QFont::ExtraBold));
    primColorText->setPos(14, 10);
    primColorText->setDefaultTextColor(QColor(Qt::white));
    primColorScene->addItem(primPreview);
    ui->primColorGV->setScene(primColorScene);
    ui->primColorGV->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->primColorGV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Preparte Brush secondary color preview
    secColorScene = new QGraphicsScene(ui->secColorGV);
    secColorScene->setBackgroundBrush(QBrush(QColor(DEFAULT_SECONDARY_COLOR)));
    secPreview = new ColorPreview();
    secColorText = new QGraphicsTextItem("2", secPreview);
    secColorText->setFont(QFont("Helvetica", 12, QFont::ExtraBold));
    secColorText->setPos(13, 10);
    secColorScene->addItem(secPreview);
    ui->secColorGV->setScene(secColorScene);
    ui->secColorGV->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->secColorGV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Prepare film strip
    filmStripScene = new FilmStripScene(ui->filmStripGV);
    ui->filmStripGV->setScene(filmStripScene);
    ui->filmStripGV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Prepare preview window
    previewScene = new PreviewScene(this);
    ui->previewWindow->setScene(previewScene);

    // connect all the signals and slots
    connectSignalsSlots();

    // Add first Frame
    emit requestToAddFrame();
}

MainWindow::~MainWindow(){
    delete model;
    delete primColorText;
    delete primPreview;
    delete primColorScene;
    delete secColorText;
    delete secPreview;
    delete secColorScene;
    delete drawingScene;
    delete filmStripScene;
    delete ui;
}

void MainWindow::connectSignalsSlots(){

    // connections for switching brush colors
    connect(this, SIGNAL(brushPrimaryColorChanged(QColor)), model, SLOT(setBrushPrimaryColor(QColor)));
    connect(this, SIGNAL(brushSecondaryColorChanged(QColor)), model, SLOT(setBrushSecondaryColor(QColor)));
    connect(primPreview, SIGNAL(doubleClicked()), this, SLOT(on_actionBrush_Primary_Color_Picker_triggered()));
    connect(secPreview, SIGNAL(doubleClicked()), this, SLOT(on_actionBrush_Secondary_Color_Picker_triggered()));

    // connections for switching tools
    connect(this, SIGNAL(activateBrushTool()), model, SLOT(onBrushToolActivated()));
    connect(this, SIGNAL(eraserActivated()), model, SLOT(onEraserToolActivated()));

    // connections for tools and drawingScene
    connect(model, SIGNAL(brushToolActive(QColor,QColor,QPointF)), drawingScene, SLOT(onBrushToolActive(QColor,QColor,QPointF)));
    connect(model, &Model::eraserToolActive, drawingScene, &DrawingScene::onEraserToolActive);
    connect(drawingScene, &DrawingScene::usingToolAt, model, &Model::usingToolAt);
    connect(model, &Model::brushColors, this, MainWindow::onBrushColorsReceived);
    connect(drawingScene, &DrawingScene::cellModified, model, &Model::onCellModified);

    // connections for film strip
    connect(model, &Model::currentFrameModified, this, &MainWindow::onCurrentFrameReceived);

    // connections for adding and removing frames
    connect(this, &MainWindow::requestToAddFrame, model, &Model::onRequestToAddFrame);
    connect(model, &Model::frameAdded, drawingScene, &DrawingScene::showImage);
    connect(model, &Model::frameAdded, filmStripScene, &FilmStripScene::addFrame);

    // connections for selecting frames in frames film strip
    connect(filmStripScene, &FilmStripScene::frameSelected, model, &Model::onFrameSelected);
    connect(model, &Model::currentFrameChanged, drawingScene, &DrawingScene::showImage);

    // connections for preview window
    connect(model, &Model::currentFrameModified, previewScene, &PreviewScene::onImageModified);
    connect(model, &Model::currentFrameChanged, previewScene, &PreviewScene::onFrameChanged);
    connect(model, &Model::frameAdded, previewScene, &PreviewScene::onFrameChanged);
}

void MainWindow::updateColorPalette(){
    QPixmap map(70, 70);
    map.fill(QColorDialog::customColor(0));
    ui->coloPaletteB->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(1));
    ui->coloPaletteB_2->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(2));
    ui->coloPaletteB_3->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(3));
    ui->coloPaletteB_4->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(4));
    ui->coloPaletteB_5->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(5));
    ui->coloPaletteB_6->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(6));
    ui->coloPaletteB_7->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(7));
    ui->coloPaletteB_8->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(8));
    ui->coloPaletteB_9->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(9));
    ui->coloPaletteB_10->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(10));
    ui->coloPaletteB_11->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(11));
    ui->coloPaletteB_12->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(12));
    ui->coloPaletteB_13->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(13));
    ui->coloPaletteB_14->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(14));
    ui->coloPaletteB_15->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(15));
    ui->coloPaletteB_16->setIcon(QIcon(map));
    map.fill(QColorDialog::customColor(16));
}

void MainWindow::updateColorPreviews(QColor newColor)
{
    // Update the color displays in the toolbar with text that is legible whether the background is dark or bright
    if (newColor.black() > 100){
        primColorText->setDefaultTextColor(Qt::white);
    }
    else{
        primColorText->setDefaultTextColor(Qt::black);
    }
    primColorScene->setBackgroundBrush(newColor);
}

void MainWindow::on_actionDotGridOn_triggered(){
    drawingScene->showDottedGrid();
}

void MainWindow::on_actionSolidGridOn_triggered(){
    drawingScene->showSolidGrid();
}

void MainWindow::on_actionTurn_Off_Grid_triggered(){
    drawingScene->showNoGrid();
}

void MainWindow::on_actionLightGrayBackground_triggered(){
    drawingScene->setBackgroundBrush(QColor(220, 220, 220));
}

void MainWindow::on_actionWhiteBackground_triggered(){
    drawingScene->setBackgroundBrush(Qt::white);
}

void MainWindow::on_actionCustomBackgroundColor_triggered(){
    QColorDialog colorPicker;
    drawingScene->setBackgroundBrush(colorPicker.getColor());
    updateColorPalette();
}

void MainWindow::on_actionBrush_Primary_Color_Picker_triggered(){
    // Get the new color using a Color Picker Dialog
    QColorDialog colorPicker;
    QColor newColor = colorPicker.getColor();

    drawingScene->setHoverColor(newColor);

    updateColorPreviews(newColor);

    // Let the model know the color has been changed
    emit brushPrimaryColorChanged(newColor);
    updateColorPalette();
}

void MainWindow::on_actionBrush_Secondary_Color_Picker_triggered()
{
    // Get the new color using a Color Picker Dialog
    QColorDialog colorPicker;
    QColor newColor = colorPicker.getColor();

    // Update the color displays in the toolbar with text that is legible whether the background is dark or bright
    if (newColor.black() > 100){
        secColorText->setDefaultTextColor(Qt::white);
    }
    else{
        secColorText->setDefaultTextColor(Qt::black);
    }
    secColorScene->setBackgroundBrush(newColor);

    // Let the model know the color has been changed
    emit brushSecondaryColorChanged(newColor);
    updateColorPalette();
}

void MainWindow::on_brushButton_clicked(){
    ui->primColorGV->setMaximumHeight(48);
    ui->secColorGV->setMaximumHeight(48);
    emit activateBrushTool();
}

void MainWindow::on_eraserButton_clicked(){
    drawingScene->setHoverColor(CLEAR);
    ui->primColorGV->setMaximumHeight(0);
    ui->secColorGV->setMaximumHeight(0);
    emit eraserActivated();
}

void MainWindow::on_actionUse_Brush_triggered(){
    ui->primColorGV->setMaximumHeight(48);
    ui->secColorGV->setMaximumHeight(48);
    emit activateBrushTool();
}

void MainWindow::on_actionUse_Eraser_triggered(){
    drawingScene->setHoverColor(CLEAR);
    ui->primColorGV->setMaximumHeight(0);
    ui->secColorGV->setMaximumHeight(0);
    emit eraserActivated();
}

void MainWindow::onBrushColorsReceived(QColor color1, QColor color2){
    drawingScene->setHoverColor(color1);
}

void MainWindow::onCurrentFrameReceived(QImage *image){
    filmStripScene->setImageOfCurrentFrame(image);
}

void MainWindow::on_addFrameButton_clicked(){
    emit requestToAddFrame();
}

void MainWindow::on_coloPaletteB_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(0));
    drawingScene->setHoverColor(QColorDialog::customColor(0));
    updateColorPreviews(QColorDialog::customColor(0));
}

void MainWindow::on_coloPaletteB_2_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(1));
    drawingScene->setHoverColor(QColorDialog::customColor(1));
    updateColorPreviews(QColorDialog::customColor(1));
}

void MainWindow::on_coloPaletteB_3_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(2));
    drawingScene->setHoverColor(QColorDialog::customColor(2));
    updateColorPreviews(QColorDialog::customColor(2));
}

void MainWindow::on_coloPaletteB_4_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(3));
    drawingScene->setHoverColor(QColorDialog::customColor(3));
    updateColorPreviews(QColorDialog::customColor(3));
}

void MainWindow::on_coloPaletteB_5_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(4));
    drawingScene->setHoverColor(QColorDialog::customColor(4));
    updateColorPreviews(QColorDialog::customColor(4));
}

void MainWindow::on_coloPaletteB_6_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(5));
    drawingScene->setHoverColor(QColorDialog::customColor(5));
    updateColorPreviews(QColorDialog::customColor(5));
}

void MainWindow::on_coloPaletteB_7_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(6));
    drawingScene->setHoverColor(QColorDialog::customColor(6));
    updateColorPreviews(QColorDialog::customColor(6));
}

void MainWindow::on_coloPaletteB_8_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(7));
    drawingScene->setHoverColor(QColorDialog::customColor(7));
    updateColorPreviews(QColorDialog::customColor(7));
}

void MainWindow::on_coloPaletteB_9_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(8));
    drawingScene->setHoverColor(QColorDialog::customColor(8));
    updateColorPreviews(QColorDialog::customColor(8));
}

void MainWindow::on_coloPaletteB_10_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(9));
    drawingScene->setHoverColor(QColorDialog::customColor(9));
    updateColorPreviews(QColorDialog::customColor(9));
}

void MainWindow::on_coloPaletteB_11_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(10));
    drawingScene->setHoverColor(QColorDialog::customColor(10));
    updateColorPreviews(QColorDialog::customColor(10));
}

void MainWindow::on_coloPaletteB_12_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(11));
    drawingScene->setHoverColor(QColorDialog::customColor(11));
    updateColorPreviews(QColorDialog::customColor(11));
}

void MainWindow::on_coloPaletteB_13_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(12));
    drawingScene->setHoverColor(QColorDialog::customColor(12));
    updateColorPreviews(QColorDialog::customColor(12));
}

void MainWindow::on_coloPaletteB_14_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(13));
    drawingScene->setHoverColor(QColorDialog::customColor(13));
    updateColorPreviews(QColorDialog::customColor(13));
}

void MainWindow::on_coloPaletteB_15_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(14));
    drawingScene->setHoverColor(QColorDialog::customColor(14));
    updateColorPreviews(QColorDialog::customColor(14));
}

void MainWindow::on_coloPaletteB_16_clicked(){
    emit brushPrimaryColorChanged(QColorDialog::customColor(15));
    drawingScene->setHoverColor(QColorDialog::customColor(15));
    updateColorPreviews(QColorDialog::customColor(15));
}


void MainWindow::on_actionExport_triggered()
{
    QString saveFile=QFileDialog::getSaveFileName(this,tr("save"),QDir::homePath());
        if(!saveFile.isEmpty())
            if( (!model->getCurrentFrame()->save(saveFile,"PNG", -1)) );

}

void MainWindow::on_playButton_clicked(){
    disconnect(model, &Model::currentFrameModified, previewScene, &PreviewScene::onImageModified);
    disconnect(model, &Model::currentFrameChanged, previewScene, &PreviewScene::onFrameChanged);
    disconnect(model, &Model::frameAdded, previewScene, &PreviewScene::onFrameChanged);

}
