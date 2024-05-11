#ifndef SQLHELPER_H
#define SQLHELPER_H



#include<QtSql>
#include"Conifg.h"

class sqlHelper
{
private:
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");

public:
    sqlHelper();
    void initialize();
    void uninitialize();
    void findValueByKey(QString key,QByteArray value);//通过key查找数据
    void writeValueByKey(QString key,QByteArray value);//通过key写入数据
    void loadConfig(MAIN_CONFIG* main_config,COM_CONFIG* com_config,CAMERA_CONFIG* camera_config,AXE_CONFIG* axe_config);
    void loadConfig(QString name,TEMPLATE_CONFIG* tmp_cfg);

    void saveConfig(MAIN_CONFIG* config);
    void saveConfig(COM_CONFIG* config);
    void saveConfig(CAMERA_CONFIG* config);
    void saveConfig(AXE_CONFIG* config);
    void insertValue(const QString& key,const QVariant& value);
    void saveConfig(TEMPLATE_CONFIG* tmp_cfg);

    void insertTemplate(TEMPLATE_CONFIG *config);
};

#endif // SQLHELPER_H
