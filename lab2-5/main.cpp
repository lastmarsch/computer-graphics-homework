#include "MainWindow.h"

#include <QApplication>

/*
 * 5. Сформировать на плоскости кривую Безье на основе задающей ломаной,
 * определяемой  3  и большим количеством точек.
 * Обеспечить редактирование координат точек
 * задающей ломаной с перерисовкой сплайна Безье.
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
