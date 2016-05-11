#include "connectionSetting.h"
#include "ui_connectionSetting.h"

Dialog::ConnectionSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~ConnectionSetting()
{
    delete ui;
}
