#include "connect.h"


QSqlDatabase Connect::db = QSqlDatabase::addDatabase("QMYSQL");

Connect::Connect()
{
}

void Connect::connect()
{
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("db2");
    db.setUserName("root");
    db.setPassword("qwerty");
    db.open();
}

void Connect::close()
{
    db.close();
}

//template<typename... T>
//void Connect::Query(QString queryString, const T & ... args)
