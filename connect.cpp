#include "connect.h"


QSqlDatabase Connect::db = QSqlDatabase::addDatabase("QMYSQL");
//QSqlQuery Connect::query;

Connect::Connect()
{
}

void Connect::connect()
{
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("db2");
    db.setUserName("root");
    db.setPassword("toor");
    db.open();
}

void Connect::close()
{
    db.close();
}
