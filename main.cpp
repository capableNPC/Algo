#include "mainwindow.h"

#include <QApplication>
#include <QMetaType>

int main(int argc, char *argv[])
{
    //注册类型
    qRegisterMetaType<OrderType>("OrderType");
    qRegisterMetaType<Config>("Config");
    qRegisterMetaType<CommandType>("CommandType");
    qRegisterMetaType<ShapeType>("ShapeType");
    qRegisterMetaType<QVector<DataOfLinear>>("QVector<DataOfLinear>");
    qRegisterMetaType<DataOfTree>("DataOfTree");
    qRegisterMetaType<DataOfAnimation>("DataOfAnimation");



    QApplication a(argc, argv);
    MainWindow w;
    w.show();//test
    return a.exec();
}
