#ifndef CLASSEDITWINDOW_H
#define CLASSEDITWINDOW_H

#include <QDialog>

namespace Ui {
class ClassEditWindow;
}

class ClassEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ClassEditWindow(QWidget *parent = 0);
    ~ClassEditWindow();

private:
    Ui::ClassEditWindow *ui;
};

#endif // CLASSEDITWINDOW_H
