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
    void update(Connect*);
    void insert(Connect*);
    void remove(Connect*);
    template<typename... T>
    void Query(QString queryString, const T&... args)
    {
        connect();
        query.prepare(queryString);
        for (auto&& p : std::initializer_list<QVariant>{args...})
        {
            query.addBindValue(p);
        }
        query.exec();
        close();
    }
};

#endif // CONNECT_H
