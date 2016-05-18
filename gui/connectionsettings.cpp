#include "connectionsettings.h"
#include "ui_connectionsettings.h"
#include "database/connect.h"

ConnectionSettings::ConnectionSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionSettings)
{
    ui->setupUi(this);
    ui->lineEditIpDb->setText(Connect::dbIP);
    ui->lineEditLoginDb->setText(Connect::dbLogin);
    ui->lineEditNameDb->setText(Connect::dbName);
    ui->lineEditPasswordDb->setText(Connect::dbPassword);
    ui->lineEditPortDb->setText(QString::number(Connect::dbPort));
}

ConnectionSettings::~ConnectionSettings()
{
    delete ui;
}

void ConnectionSettings::on_buttonBox_accepted()
{
    Connect::dbIP = ui->lineEditIpDb->text();
    Connect::dbLogin  = ui->lineEditLoginDb->text();
    Connect::dbName = ui->lineEditNameDb->text();
    Connect::dbPassword = ui->lineEditPasswordDb->text();
    Connect::dbPort = ui->lineEditPortDb->text().toInt();

    QFile file("Settings.txt");
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
           QString str = Connect::dbName + QString(" ") +
                 Connect::dbIP + QString(" ") +
                 QString::number(Connect::dbPort) + QString(" ") +
                 Connect::dbLogin + QString(" ") +
                 Connect::dbPassword ;
                QTextStream out(&file);
                out <<str;
                file.close();

    }
}
