#include "NewProjectDialog.h"
#include "ui_NewProjectDialog.h"

#include <QDebug>

NewProjectDialog::NewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectDialog)
{
    ui->setupUi(this);
    ui->rowsLineEdit->setValidator(new QIntValidator(2, 1000, this));
    ui->columnsLineEdit->setValidator(new QIntValidator(2, 1000, this));
    ui->fpsLineEdit->setValidator(new QIntValidator(1, 100, this));
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}

void NewProjectDialog::on_sizeComboBox_activated(int index){
    switch (index) {
     case 0:
        ui->columnsLineEdit->setText("8");
        ui->rowsLineEdit->setText("8");
        ui->columnsLineEdit->setEnabled(false);
        ui->rowsLineEdit->setEnabled(false);
        break;
     case 1:
        ui->columnsLineEdit->setText("16");
        ui->rowsLineEdit->setText("16");
        ui->columnsLineEdit->setEnabled(false);
        ui->rowsLineEdit->setEnabled(false);
        break;
    case 2:
        ui->columnsLineEdit->setText("32");
        ui->rowsLineEdit->setText("32");
        ui->columnsLineEdit->setEnabled(false);
        ui->rowsLineEdit->setEnabled(false);
        break;
    case 3:
        ui->columnsLineEdit->setText("64");
        ui->rowsLineEdit->setText("64");
        ui->columnsLineEdit->setEnabled(false);
        ui->rowsLineEdit->setEnabled(false);
        break;
    case 4:
        ui->columnsLineEdit->setEnabled(true);
        ui->rowsLineEdit->setEnabled(true);
        columns = ui->columnsLineEdit->text().toInt();
        rows = ui->rowsLineEdit->text().toInt();
    default:
        ;
    }
}

void NewProjectDialog::on_columnsLineEdit_textChanged(const QString &arg1){
    if ( ui->columnsLineEdit->text().toInt() < 2){
        ui->columnsLineEdit->setText("2");
        columns = 2;
    }
}

void NewProjectDialog::on_rowsLineEdit_textChanged(const QString &arg1){
    if ( ui->rowsLineEdit->text().toInt() < 2){
        ui->rowsLineEdit->setText("2");
        rows = 2;
    }
}

void NewProjectDialog::on_fpsLineEdit_textChanged(const QString &arg1){
    if ( ui->fpsLineEdit->text().toInt() < 1){
        ui->fpsLineEdit->setText("1");
        fps = 1;
    }
    else{
        fps = ui->fpsLineEdit->text().toInt();
    }
}

void NewProjectDialog::on_buttonBox_accepted(){
    columns = ui->columnsLineEdit->text().toInt();
    rows = ui->rowsLineEdit->text().toInt();
    emit newGameRequest(columns, rows, fps);
    this->close();
}

void NewProjectDialog::on_buttonBox_rejected(){
    this->close();
}
