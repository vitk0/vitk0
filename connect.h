#ifndef CONNECT_H
#define CONNECT_H

#include <QtSql>

class Connect
{
    static QSqlDatabase db;
protected:
    QSqlQuery query;
    Connect();
    void connect();
    void close();
};

#endif // CONNECT_H
