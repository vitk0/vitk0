#ifndef PLANWINDOW_H
#define PLANWINDOW_H

#include "database\database.h"

#include <QAxObject>
#include <QMainWindow>

namespace Ui {
class PlanWindow;
}

class PlanWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlanWindow(QWidget *parent = 0);

    Ui::PlanWindow* GetUI();
    DataBase* db;
    bool update;

    void Fill();

    ~PlanWindow();

private slots:
    void on_VkUvcComboBox_currentIndexChanged(int index);

    void on_VUSComboBox_currentIndexChanged(int index);

    void on_semesterComboBox_currentIndexChanged(int index);

    void on_disciplineComboBox_currentIndexChanged(int index);

    void on_addButton_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_deleteButton_clicked();

    void on_reportButton_clicked();

    void on_openChangeWindowButton_clicked();

    void on_toolButton_clicked();

private:
    Ui::PlanWindow *ui;

};

#endif // PLANWINDOW_H
