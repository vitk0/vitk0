#include "classeditwidget.h"
#include "ui_classeditwidget.h"

ClassEditWidget::ClassEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClassEditWidget)
{
    ui->setupUi(this);
}

ClassEditWidget::~ClassEditWidget()
{
    delete ui;
}
