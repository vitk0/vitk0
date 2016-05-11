#ifndef CONNECT_H
#define CONNECT_H

#include <QtSql>

class Connect
{
    static QSqlDatabase db;


public:
    QString getDbName() const;
    void setDbName(const QString &value);

    QString getDbIP() const;
    void setDbIP(const QString &value);

    QString getDbLogin() const;
    void setDbLogin(const QString &value);

    QString getDbPassword() const;
    void setDbPassword(const QString &value);

    int getDbPort() const;
    void setDbPort(int value);

    static QString dbName;
    static QString dbIP;
    static QString dbLogin;
    static QString dbPassword;
    static int dbPort;

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
