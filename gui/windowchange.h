#ifndef WINDOWCHANGE_H
#define WINDOWCHANGE_H

#include <QMainWindow>


namespace Ui {
class WindowChange;
}

class WindowChange : public QMainWindow
{
    Q_OBJECT

public:
    explicit WindowChange(QWidget *parent = 0);
    ~WindowChange();

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_tableWidget_cellChanged(int row, int column);

    void on_deleteButton_clicked();

private:
    Ui::WindowChange *ui;

    void Fill(int index);
};

#endif // WINDOWCHANGE_H
