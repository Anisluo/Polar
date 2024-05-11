#include "sqlhelper.h"


sqlHelper::sqlHelper()
{
    initialize();
}



void sqlHelper::initialize()
{
    db.setDatabaseName("database.db");//设置database名称
    if(!db.open()) {
        return ;
    }
}


void sqlHelper::uninitialize()
{
    db.close();
}


//保存axe配置
void sqlHelper::saveConfig(AXE_CONFIG* curAxe)
{
    //配置结构体所有数据
    insertValue("AXE_ID",curAxe->AXE_ID);
    insertValue("AXE_DIR",curAxe->AXE_DIR);
    insertValue("AXE_PERMM",curAxe->AXE_PERMM);
    insertValue("AXE_SPEED_LOW",curAxe->AXE_SPEED_LOW);
    insertValue("AXE_SPEED_HIGH",curAxe->AXE_SPEED_HIGH);
    insertValue("AXE_SPEED_MEDIUM",curAxe->AXE_SPEED_MEDIUM);
    insertValue("AXE_SPEED_TEST",curAxe->AXE_SPEED_TEST);
    insertValue("AXE_SPEED_HOME",curAxe->AXE_SPEED_HOME);
    insertValue("AXE_AC_SPEED",curAxe->AXE_AC_SPEED);
}

void sqlHelper::saveConfig(MAIN_CONFIG* cfg)
{
    insertValue("CONFIG_NAME",cfg->CONFIG_NAME);
    insertValue("MAIN_CNT",cfg->MAIN_CNT);
    insertValue("MAIN_PASS",cfg->MAIN_PASS);
    insertValue("MAIN_NG",cfg->MAIN_NG);
    insertValue("MAIN_TEMPLATE_NAME",cfg->MAIN_TEMPLATE_NAME);
    insertValue("MAIN_RESULT_NAME",cfg->MAIN_RESULT_NAME);
}


void sqlHelper::saveConfig(COM_CONFIG* cfg)
{
    insertValue("COM_NAME",cfg->COM_NAME);
    insertValue("COM_BAUDRATE",cfg->COM_BAUDRATE);
    insertValue("COM_DATABIT",cfg->COM_DATABIT);
    insertValue("COM_PARITY",cfg->COM_PARITY);
    insertValue("COM_STOPBIT",cfg->COM_STOPBIT);
}



void sqlHelper::saveConfig(CAMERA_CONFIG* cfg)
{
    insertValue("MAIN_CAMERA_EXP_TIME",cfg->MAIN_CAMERA_EXP_TIME);
}

//保存
void sqlHelper::saveConfig(TEMPLATE_CONFIG* tmp_cfg)
{
    QSqlQuery query;

    // 判断表是否存在
    if (!query.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='TEMPLATE'")) {
        qDebug() << "Error checking if table exists:" << query.lastError().text();
        return;
    }

    // 如果表不存在，则创建表
    if (!query.next()) {
        if (!query.exec("CREATE TABLE TEMPLATE ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "tempName TEXT, "
                "angleStart REAL, "
                "angleStep REAL, "
                "angleStop REAL, "
                "angle_lmax REAL, "
                "angle_lmin REAL, "
                "contrast_max REAL, "
                "contrast_min REAL)")) {
            qDebug() << "Error creating table:" << query.lastError().text();
            return;
        }
        qDebug() << "Table created successfully.";
    }
    insertTemplate(tmp_cfg);
}




//void sqlHelper::saveConfig(TEMPLAT_CONFIG* cfg)
//{

//}




void sqlHelper::insertValue(const QString& key,const QVariant& value)
{
    if(db.isOpen())
    {

        // 查询第一行的 rowid
        QString selectRowidQuery = "SELECT rowid FROM CONFIG LIMIT 1";
        QSqlQuery selectRowid(selectRowidQuery);
        if (selectRowid.next()) {
            int rowid = selectRowid.value(0).toInt();

            // 使用查询到的 rowid 进行更新
            QString updateQuery = QString("UPDATE CONFIG SET %1 = :value WHERE rowid = :rowid").arg(key);
            QSqlQuery update;
            update.prepare(updateQuery);
            update.bindValue(":value", value);
            update.bindValue(":rowid", rowid);

            if (!update.exec()) {
                // 查询失败，回滚事务
                db.rollback();
                qDebug() << "Update Query failed:" << update.lastError().text();
            } else {
                // 查询成功，提交事务
                db.commit();
                qDebug() << "Update Query succeeded";
            }
        }
    }
}

//载入配置文件
void sqlHelper::loadConfig(QString tempname,TEMPLATE_CONFIG* tmp_config)
{
//    tmp_config=new TEMPLATE_CONFIG;
    QSqlQuery query;

    QString condition="tempName=";
    // 构建带有条件的查询语句
    QString queryString = QString("SELECT * FROM TEMPLATE WHERE %1").arg(condition);

    // 查询数据
    if (!query.exec(queryString)) {
        qDebug() << "Error retrieving data:" << query.lastError().text();
        return;
    }

    while (query.next()) {

    }
}

void sqlHelper::insertTemplate(TEMPLATE_CONFIG *config) {
    QSqlQuery query;

    // 添加一条记录
    if (!query.prepare("INSERT INTO TEMPLATE (tempName, angleStart, angleStep, angleStop, angle_lmax, angle_lmin, contrast_max, contrast_min) "
                       "VALUES (:tempName, :angleStart, :angleStep, :angleStop, :angle_lmax, :angle_lmin, :contrast_max, :contrast_min)")) {
        qDebug() << "Error preparing query:" << query.lastError().text();
        return;
    }

    query.bindValue(":tempName", config->tempName);
    query.bindValue(":angleStart", config->angleStart);
    query.bindValue(":angleStep", config->angleStep);
    query.bindValue(":angleStop", config->angleStop);
    query.bindValue(":angle_lmax", config->angle_lmax);
    query.bindValue(":angle_lmin", config->angle_lmin);
    query.bindValue(":contrast_max", config->contrast_max);
    query.bindValue(":contrast_min", config->contrast_min);

    if (!query.exec()) {
        qDebug() << "Error inserting data:" << query.lastError().text();
        return;
    }
    qDebug() << "Data inserted successfully.";
}


void sqlHelper::loadConfig(MAIN_CONFIG* main_config,COM_CONFIG* com_config,
                           CAMERA_CONFIG* camera_config,
                           AXE_CONFIG* axe_config)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CONFIG LIMIT 1");

    // 执行查询
    if (query.exec()) {
        if (query.next()) {
            // 从查询结果中获取值

            main_config->CONFIG_NAME=query.value("CONFIG_NAME").toString();
            main_config->MAIN_RESULT_NAME=query.value("MAIN_RESULT_NAME").toString();
            main_config->MAIN_TEMPLATE_NAME=query.value("MAIN_TEMPLATE_NAME").toString();

            main_config->MAIN_NG=query.value("MAIN_NG").toUInt();
            main_config->MAIN_CNT=query.value("MAIN_CNT").toInt();
            main_config->MAIN_PASS=query.value("MAIN_PASS").toInt();

            com_config->COM_NAME=query.value("COM_NAME").toString();
            com_config->COM_BAUDRATE=query.value("COM_BAUDRATE").toUInt();
            com_config->COM_DATABIT=query.value("COM_DATABIT").toUInt();
            com_config->COM_PARITY=query.value("COM_PARITY").toUInt();
            com_config->COM_STOPBIT=query.value("COM_STOPBIT").toUInt();

            camera_config->MAIN_CAMERA_EXP_TIME=query.value("MAIN_CAMERA_EXP_TIME").toUInt();

            axe_config->AXE_DIR=query.value("AXE_DIR").toInt();
            axe_config->AXE_ID=query.value("AXE_ID").toInt();
            axe_config->AXE_PERMM=query.value("AXE_PERMM").toInt();
            axe_config->AXE_SPEED_HIGH=query.value("AXE_SPEED_HIGH").toInt();
            axe_config->AXE_SPEED_MEDIUM=query.value("AXE_SPEED_MEDIUM").toInt();
            axe_config->AXE_SPEED_LOW=query.value("AXE_SPEED_LOW").toInt();
            axe_config->AXE_SPEED_TEST=query.value("AXE_SPEED_TEST").toInt();
            axe_config->AXE_AC_SPEED=query.value("AXE_AC_SPEED").toInt();
            axe_config->AXE_SPEED_HOME=query.value("AXE_SPEED_HOME").toInt();
        } else {
            qDebug() << "No rows returned by the query";
        }
    } else {
        qDebug() << "Error in query:" << query.lastError().text();
    }
}

void sqlHelper::findValueByKey(QString key,QByteArray value)
{

    // 准备SQL查询语句
    QString keyToSearch = key; // 替换为你要查询的键值
    QSqlQuery query;
    query.prepare("SELECT * FROM CONFIG LIMIT 1");

    // 执行查询
    if (query.exec()) {
        if (query.next()) {
            // 从查询结果中获取值
            QString configName = query.value("CONFIG_NAME").toString();
            int mainCnt = query.value("MAIN_CNT").toInt();
            int mainPass = query.value("MAIN_PASS").toInt();
            // ... 获取其他列的值

            qDebug() << "CONFIG_NAME:" << configName;
            qDebug() << "MAIN_CNT:" << mainCnt;
            qDebug() << "MAIN_PASS:" << mainPass;
           // ... 输出其他列的值
        } else {
            qDebug() << "No rows returned by the query";
        }
    } else {
        qDebug() << "Error in query:" << query.lastError().text();
    }

}
