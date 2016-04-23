#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = 0);
    ~NewProjectDialog();

private slots:
    void on_sizeComboBox_activated(int index);

    void on_columnsLineEdit_textChanged(const QString &arg1);

    void on_rowsLineEdit_textChanged(const QString &arg1);

    void on_fpsLineEdit_editingFinished();

    void on_fpsLineEdit_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewProjectDialog *ui;

    int columns = 8;
    int rows = 8;
    int fps = 5;

signals:
    void newGameRequest(int columns, int rows, int fps);
};

#endif // NEWPROJECTDIALOG_H
