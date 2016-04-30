#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Build the model
    spriteWidth = DEFAULT_SPRITE_WIDTH;
    spriteHeight = DEFAULT_SPRITE_HEIGHT;
    fps = DEFAULT_FPS;
    setUp();
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
    delete colorPalette;
    delete ui;
}

void MainWindow::startNewProject(int columns, int rows, int fps){
    disconnectAll();
    spriteWidth = columns;
    spriteHeight = rows;
    this->fps = fps;

    model->reset(spriteWidth, spriteHeight, Qt::black, Qt::white);

    // Set up drawing area
    DrawingGraphicsView *newdrawingGV = new DrawingGraphicsView(DEFAULT_CELL_SIZE * spriteWidth + 2, DEFAULT_CELL_SIZE *spriteHeight + 10, this);
    ui->horizontalLayout->replaceWidget(drawingGV, newdrawingGV);
    delete drawingGV;
    drawingGV = newdrawingGV;
    drawingScene = new DrawingScene(DEFAULT_CELL_SIZE, spriteWidth, spriteHeight, DEFAULT_BACKGROUND_COLOR, drawingGV);
    drawingScene->setHoverColor(DEFAULT_PRIMARY_COLOR);
    drawingGV->setScene(drawingScene);

    // Prepare Brush primary Color Preview
    primColorScene->setBackgroundBrush(QBrush(QColor(DEFAULT_PRIMARY_COLOR)));
    primColorText->setDefaultTextColor(QColor(Qt::white));

    // Preparte Brush secondary color preview
    secColorScene->setBackgroundBrush(QBrush(QColor(DEFAULT_SECONDARY_COLOR)));

    // Prepare film strip
    FilmStripScene *newfilmStripScene = new FilmStripScene(ui->filmStripGV);
    ui->filmStripGV->setScene(newfilmStripScene);
    ui->filmStripGV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    delete filmStripScene;
    filmStripScene = newfilmStripScene;

    // Prepare preview window
    PreviewScene *newPreviewScene = new PreviewScene(this);
    ui->previewWindow->setScene(newPreviewScene);
    delete previewScene;
    previewScene = newPreviewScene;

    // connect all the signals and slots
    connectSignalsSlots();

    // Add first Frame
    emit requestToAddFrame();
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
    connect(this, &MainWindow::activatePaintBucket, model, &Model::onPaintBucketToolActivated);

    // connections for tools and drawingScene
    connect(model, &Model::brushToolActive, drawingScene, &DrawingScene::onBrushToolActive);
    connect(model, &Model::eraserToolActive, drawingScene, &DrawingScene::onEraserToolActive);
    connect(model, &Model::paintBucketToolActive, drawingScene, &DrawingScene::onPaintBucketToolActive);
    connect(drawingScene, &DrawingScene::usingToolOnCell, model, &Model::usingToolOnCell);
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
    connect(playButton, &QToolButton::clicked, this, &MainWindow::on_playButton_clicked);
    connect(model, &Model::currentFrameModified, previewScene, &PreviewScene::showImage);
    connect(model, &Model::currentFrameChanged, previewScene, &PreviewScene::showImage);
    connect(model, &Model::frameAdded, previewScene, &PreviewScene::showImage);

    // connections for palette
    QVector<ColorPaletteButton*> buttons = colorPalette->getButtons();
    for (auto it = buttons.begin(); it != buttons.end(); it++){
        ColorPaletteButton *button = *it;
        connect(button, &ColorPaletteButton::primaryColorChangeRequest, model, &Model::setBrushPrimaryColor);
        connect(button, &ColorPaletteButton::secondaryColorChangeRequest, model, &Model::setBrushSecondaryColor);
    }

    // connections for opening a file
    connect(model, &Model::openingFile, this, &MainWindow::buildNewDrawingArea);
}

void MainWindow::setUp()
{
    model = new Model(spriteWidth, spriteHeight, DEFAULT_PRIMARY_COLOR, DEFAULT_SECONDARY_COLOR);

    // Set up drawing area
    drawingGV = new DrawingGraphicsView(DEFAULT_CELL_SIZE * spriteWidth + 2, DEFAULT_CELL_SIZE *spriteHeight + 10, this);
    drawingScene = new DrawingScene(DEFAULT_CELL_SIZE, spriteWidth, spriteHeight, DEFAULT_BACKGROUND_COLOR, drawingGV);
    drawingScene->setHoverColor(DEFAULT_PRIMARY_COLOR);
    drawingGV->setScene(drawingScene);
    ui->horizontalLayout->replaceWidget(ui->becomeDrawingGV, drawingGV);
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
    ui->gridLayout_2->removeWidget(ui->previewWindow);
    ui->gridLayout_2->addWidget(ui->previewWindow, 0, 0, 2, 2);
    ui->previewWindow->setScene(previewScene);
    playButton = new QToolButton(ui->previewWindow);
    playButton->setIcon(QPixmap(":/images/images/playButton.png"));
    ui->gridLayout_2->addWidget(playButton, 1, 1, 1 ,1, Qt::AlignRight);

    // Add the color palette
    colorPalette = new ColorPalette(10, 3);
    ui->RightColumn->addLayout(colorPalette);

    // connect all the signals and slots
    connectSignalsSlots();

    // Add first Frame
    emit requestToAddFrame();
}

void MainWindow::disconnectAll(){
    // connections for switching brush colors
    disconnect(this, SIGNAL(brushPrimaryColorChanged(QColor)), model, SLOT(setBrushPrimaryColor(QColor)));
    disconnect(this, SIGNAL(brushSecondaryColorChanged(QColor)), model, SLOT(setBrushSecondaryColor(QColor)));
    disconnect(primPreview, SIGNAL(doubleClicked()), this, SLOT(on_actionBrush_Primary_Color_Picker_triggered()));
    disconnect(secPreview, SIGNAL(doubleClicked()), this, SLOT(on_actionBrush_Secondary_Color_Picker_triggered()));

    // connections for switching tools
    disconnect(this, SIGNAL(activateBrushTool()), model, SLOT(onBrushToolActivated()));
    disconnect(this, SIGNAL(eraserActivated()), model, SLOT(onEraserToolActivated()));
    disconnect(this, &MainWindow::activatePaintBucket, model, &Model::onPaintBucketToolActivated);

    // connections for tools and drawingScene
    disconnect(model, &Model::brushToolActive, drawingScene, &DrawingScene::onBrushToolActive);
    disconnect(model, &Model::eraserToolActive, drawingScene, &DrawingScene::onEraserToolActive);
    disconnect(drawingScene, &DrawingScene::usingToolOnCell, model, &Model::usingToolOnCell);
    disconnect(model, &Model::brushColors, this, MainWindow::onBrushColorsReceived);
    disconnect(drawingScene, &DrawingScene::cellModified, model, &Model::onCellModified);

    // connections for film strip
    disconnect(model, &Model::currentFrameModified, this, &MainWindow::onCurrentFrameReceived);
    // connections for adding and removing frames
    disconnect(this, &MainWindow::requestToAddFrame, model, &Model::onRequestToAddFrame);
    disconnect(model, &Model::frameAdded, drawingScene, &DrawingScene::showImage);
    disconnect(model, &Model::frameAdded, filmStripScene, &FilmStripScene::addFrame);
    // connections for selecting frames in frames film strip
    disconnect(filmStripScene, &FilmStripScene::frameSelected, model, &Model::onFrameSelected);
    disconnect(model, &Model::currentFrameChanged, drawingScene, &DrawingScene::showImage);

    // connections for preview window
    disconnect(playButton, &QToolButton::clicked, this, &MainWindow::on_playButton_clicked);
    disconnect(model, &Model::currentFrameModified, previewScene, &PreviewScene::showImage);
    disconnect(model, &Model::currentFrameChanged, previewScene, &PreviewScene::showImage);
    disconnect(model, &Model::frameAdded, previewScene, &PreviewScene::showImage);

    // connections for palette
    QVector<ColorPaletteButton*> buttons = colorPalette->getButtons();
    for (auto it = buttons.begin(); it != buttons.end(); it++){
        ColorPaletteButton *button = *it;
        disconnect(button, &ColorPaletteButton::primaryColorChangeRequest, model, &Model::setBrushPrimaryColor);
        disconnect(button, &ColorPaletteButton::secondaryColorChangeRequest, model, &Model::setBrushSecondaryColor);
    }
}

void MainWindow::write(QString filename){

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
}

void MainWindow::on_actionBrush_Primary_Color_Picker_triggered(){
    // Get the new color using a Color Picker Dialog
    QColorDialog colorPicker;
    QColor newColor = colorPicker.getColor();

    drawingScene->setHoverColor(newColor);

    // Let the model know the color has been changed
    emit brushPrimaryColorChanged(newColor);
}

void MainWindow::on_actionBrush_Secondary_Color_Picker_triggered()
{
    // Get the new color using a Color Picker Dialog
    QColorDialog colorPicker;
    QColor newColor = colorPicker.getColor();

    // Let the model know the color has been changed
    emit brushSecondaryColorChanged(newColor);
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
    if (model->isBrushToolActive()){
        drawingScene->setHoverColor(color1);
    }

    // Update the color displays in the toolbar with text that is legible whether the background is dark or bright
    if (color1.black() > 100){
        primColorText->setDefaultTextColor(Qt::white);
    }
    else{
        primColorText->setDefaultTextColor(Qt::black);
    }
    primColorScene->setBackgroundBrush(color1);

    // Update the color displays in the toolbar with text that is legible whether the background is dark or bright
    if (color2.black() > 100){
        secColorText->setDefaultTextColor(Qt::white);
    }
    else{
        secColorText->setDefaultTextColor(Qt::black);
    }
    secColorScene->setBackgroundBrush(color2);
}

void MainWindow::onCurrentFrameReceived(QImage *image){
    filmStripScene->setImageOfCurrentFrame(image);
}

void MainWindow::onPlayButtonTimerShot(){
    if (imageBeingShown != images.end()){
        previewScene->showImage(*imageBeingShown);
        QTimer::singleShot(1000/fps, this, onPlayButtonTimerShot);
    }
    else{
        previewScene->showImage(model->getCurrentFrame());
        connect(model, &Model::currentFrameModified, previewScene, &PreviewScene::showImage);
        connect(model, &Model::currentFrameChanged, previewScene, &PreviewScene::showImage);
        connect(model, &Model::frameAdded, previewScene, &PreviewScene::showImage);
    }
    imageBeingShown++;
}

void MainWindow::on_addFrameButton_clicked(){
    emit requestToAddFrame();
}

void MainWindow::on_actionExport_triggered()
{
    QString saveFile=QFileDialog::getSaveFileName(this,tr("Export"),QDir::homePath());
        if(!saveFile.isEmpty())
            if( (!model->getCurrentFrame()->save(saveFile,"PNG", -1)) );

}

void MainWindow::on_playButton_clicked(){
    disconnect(model, &Model::currentFrameModified, previewScene, &PreviewScene::showImage);
    disconnect(model, &Model::currentFrameChanged, previewScene, &PreviewScene::showImage);
    disconnect(model, &Model::frameAdded, previewScene, &PreviewScene::showImage);
    images = model->getFrames();
    imageBeingShown = images.begin();
    onPlayButtonTimerShot();
}

void MainWindow::on_actionNew_triggered(){
    NewProjectDialog newWindow;
    connect(&newWindow, &NewProjectDialog::newGameRequest, this, &MainWindow::startNewProject);
    newWindow.exec();

}

void MainWindow::on_paintBucketButton_clicked(){
    ui->primColorGV->setMaximumHeight(0);
    ui->secColorGV->setMaximumHeight(0);
    emit activatePaintBucket();
}

void MainWindow::on_actionOpen_triggered(){
    QString openFile = QFileDialog::getOpenFileName(this, tr("Open"), QDir::homePath(), tr(" PixEdt (*.pxl)"));
    qDebug() << openFile;
    if (!model->open(openFile))
        qDebug() << "suck";
}

void MainWindow::on_actionSave_as_triggered(){
    QString saveFile = QFileDialog::getSaveFileName(this, tr("Save"), QDir::homePath(), tr(" PixEdt (*.pxl)"));
    if (!model->save(saveFile))
        qDebug() << "suck";
}

void MainWindow::buildNewDrawingArea(int width, int height, int fps){
    // Prepare film strip
    delete filmStripScene;
    filmStripScene = new FilmStripScene(ui->filmStripGV);
    ui->filmStripGV->setScene(filmStripScene);
    ui->filmStripGV->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Set up drawing area
    spriteWidth = width;
    spriteHeight = height;
    delete drawingScene;
    drawingScene = new DrawingScene(DEFAULT_CELL_SIZE, width, height, DEFAULT_BACKGROUND_COLOR, drawingGV);
    drawingScene->setHoverColor(DEFAULT_PRIMARY_COLOR);
    drawingGV->setScene(drawingScene);

    // connections for tools and drawingScene
    connect(model, &Model::brushToolActive, drawingScene, &DrawingScene::onBrushToolActive);
    connect(model, &Model::eraserToolActive, drawingScene, &DrawingScene::onEraserToolActive);
    connect(model, &Model::paintBucketToolActive, drawingScene, &DrawingScene::onPaintBucketToolActive);
    connect(drawingScene, &DrawingScene::usingToolOnCell, model, &Model::usingToolOnCell);
    connect(model, &Model::brushColors, this, MainWindow::onBrushColorsReceived);
    connect(drawingScene, &DrawingScene::cellModified, model, &Model::onCellModified);

    // connections for film strip
    // connections for adding and removing frames
    connect(model, &Model::frameAdded, drawingScene, &DrawingScene::showImage);
    connect(model, &Model::frameAdded, filmStripScene, &FilmStripScene::addFrame);
    // connections for selecting frames in frames film strip
    connect(filmStripScene, &FilmStripScene::frameSelected, model, &Model::onFrameSelected);
    connect(model, &Model::currentFrameChanged, drawingScene, &DrawingScene::showImage);

}
