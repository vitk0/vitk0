#ifndef CLASSEDITWIDGET_H
#define CLASSEDITWIDGET_H

#include <QWidget>

namespace Ui {
class ClassEditWidget;
}

class ClassEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClassEditWidget(QWidget *parent = 0);
    ~ClassEditWidget();

private:
    Ui::ClassEditWidget *ui;
};

#endif // CLASSEDITWIDGET_H
