#ifndef CLASSEDITWINDOW_H
#define CLASSEDITWINDOW_H

#include <QDialog>
#include <QFrame>

namespace Ui {
class ClassEditWindow;
}

class ClassEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ClassEditWindow(QWidget *parent = 0);
    ~ClassEditWindow();

private slots:
    void on_addProfessorButton_clicked();

    void on_deleteProfessorButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::ClassEditWindow *ui;

    QVector<QFrame*> frames;
    int professorsCount;
};

#endif // CLASSEDITWINDOW_H
