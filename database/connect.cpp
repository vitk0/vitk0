#include "connect.h"


QSqlDatabase Connect::db = QSqlDatabase::addDatabase("QMYSQL");

QString Connect::dbName;
QString Connect::dbIP;
QString Connect::dbLogin;
QString Connect::dbPassword;
int Connect::dbPort;

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

int Connect::getDbPort() const
{
    return dbPort;
}

void Connect::setDbPort(int value)
{
    dbPort = value;
}

QString Connect::getDbPassword() const
{
    return dbPassword;
}

void Connect::setDbPassword(const QString &value)
{
    dbPassword = value;
}

QString Connect::getDbLogin() const
{
    return dbLogin;
}

void Connect::setDbLogin(const QString &value)
{
    dbLogin = value;
}

QString Connect::getDbIP() const
{
    return dbIP;
}

void Connect::setDbIP(const QString &value)
{
    dbIP = value;
}

QString Connect::getDbName() const
{
    return dbName;
}

void Connect::setDbName(const QString &value)
{
    dbName = value;
}
