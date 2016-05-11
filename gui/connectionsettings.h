#ifndef CONNECTIONSETTINGS_H
#define CONNECTIONSETTINGS_H

#include <QDialog>

namespace Ui {
class ConnectionSettings;
}

class ConnectionSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionSettings(QWidget *parent = 0);
    ~ConnectionSettings();

private slots:

    void on_buttonBox_accepted();

private:
    Ui::ConnectionSettings *ui;
};

#endif // CONNECTIONSETTINGS_H
