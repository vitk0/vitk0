#include "gui\planwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlanWindow w;
    w.show();

    return a.exec();
}
