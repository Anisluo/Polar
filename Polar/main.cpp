#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //连接数据库
//    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("database.db");
//    if(!db.open())
//    {
//       qDebug()<<"error:unable to open database." ;
//    }

    w.setWindowTitle(QStringLiteral("偏光片测试机"));
    w.show();
    return a.exec();
}
