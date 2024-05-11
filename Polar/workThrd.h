#ifndef WORKTHRD_H
#define WORKTHRD_H

#include <QThread>
#include"Conifg.h"
#include<QQueue>
#include"movectrl.h"
//#define DEBUG_VERSION
class workThrd : public QThread
{
    Q_OBJECT
public:
    MoveCtrl* mvctrl;
    AXE_CONFIG* axe_cfg;
    bool is_generate_tmp;
    bool is_main_test;
    bool is_single_test;


    void run()override;
    bool isStrabing;
    void init(MoveCtrl* mvc,AXE_CONFIG* axe);
    void exit();
    QQueue<TASK_CONFIG*> tskqueues;
    QQueue<QByteArray>	datas;//返回的数据
    void task_move_home();
    void task_normal_test(TASK_CONFIG* tsk);
    void task_single_test(TASK_CONFIG* tsk);
    void task_generate_tmp(TASK_CONFIG* tsk);//生成测试列表
    void add_tasks(TASK_CONFIG* tsk);
    double parselum(QByteArray data);
    void addDatas(QByteArray data);
signals:
    void displayCamera();//显示相机
    void updateResults(RESULT_CONFIG* results);
    void update_single_result(double lum);
    void sendCmd();//发送指令
    void showMessage(const QString&);
    void showMessage_tmp(const QString&);
    void update_tmp_lum_angle(double angle,double lum);
    void update_tmp_max_min_lumangle(double,double min);
   void update_tmp_contrast_value(double);
   void update_tmp_contrast(double minLum);
//    void set_status(STATUS_ENUM status);
public slots:
    void on_stop_generate();
    void on_start_generate();
    void on_stop_main_test();//停止测试
    void on_start_main_test();//开始测试
    void on_start_single_test();//单点测试
    void on_stop_single_test();//结束单点测试
};

#endif // WORKTHRD_H
