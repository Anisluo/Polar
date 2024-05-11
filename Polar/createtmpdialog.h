#ifndef CREATETMPDIALOG_H
#define CREATETMPDIALOG_H
#include"Conifg.h"
#include<QLabel>
#include<QLineEdit>
#include<QSpinBox>
#include<QPushButton>
#include<QTableWidget>
#include"sqlhelper.h"
#include<QDoubleSpinBox>
#include<QCheckBox>

#include <QDialog>

#include<QFileDialog>

namespace Ui {
class createTmpDialog;
}

class createTmpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit createTmpDialog(QWidget *parent = nullptr);
    ~createTmpDialog();

private:
    Ui::createTmpDialog *ui;
    void initWidget();
    TEMPLATE_CONFIG* tmp_cfg;
    sqlHelper* sql;
    TEMPLATE_CONFIG* cur_tmp;
//    TEMPLA

private:

    QLabel* tmp_tmpname_lb;
    QLineEdit* tmp_tmpname_ledit;

    QLabel* tmp_start_lb;
    QDoubleSpinBox* tmp_start_sp;

    QLabel* tmp_step_lb;
    QDoubleSpinBox* tmp_step_sp;

    QLabel* tmp_stop_lb;
    QDoubleSpinBox* tmp_stop_sp;

    QLabel* tmp_lmax_lb;
    QDoubleSpinBox* tmp_lmax_sp;

    QLabel* tmp_lmin_lb;
    QDoubleSpinBox* tmp_lmin_sp;


    //指定角度
    QLabel* tmp_contrast_lb;
    QDoubleSpinBox* tmp_contrast_sp;
    QLabel* tmp_contrast_angle_lb;
    QDoubleSpinBox* tmp_contrast_angle_sp;



    QPushButton* tmp_generate_btn;//生成模板
    QPushButton* tmp_stopgen_btn;//停止生成

    QPushButton* tmp_clear_btn;//清空模板
    QPushButton* tmp_save_btn;//停止清空

    QTableWidget* tmp_table;//生成测试模板表


    QLabel* tmp_ctrst_lb;
    QDoubleSpinBox* tmp_ctrst_max_sp;
    QDoubleSpinBox* tmp_ctrst_min_sp;

    QPushButton* tmp_loadtmp;//导入模板
    QPushButton* tmp_savetmp;//导出模板

    QLabel*		tmp_status;
    void update_data_from_ui();//从ui中更新数据
    void update_ui_from_data();//更新数据至ui

public:

    void loadConfigXML(TEMPLATE_CONFIG* config,const QString& filename);
    void saveConfigXML(TEMPLATE_CONFIG* config,const QString& filename);



public:
//    void loadConfig(sqlHelper* sql_help,TEMPLATE_CONFIG* tmp);
    void loadConfig(TEMPLATE_CONFIG* tmp);
public:
signals:
    void add_template(TEMPLATE_CONFIG* tmp_cfg);
    void update_main_tmp_name(QString tempname);
    void on_start_generate();
    void on_stop_generate();

public slots:
    void on_generate_tmps();//生成模板
    void update_tmp_max_min_lumangle(double max,double min);
    void update_tmp_contrast_value(double);
    void update_tmp_lum_angle(double,double);
    void update_tmp_contrast(double minLum);//更新所有的contrast数据
    void showMessage(const QString& msg);
    void on_clear_tmps();
    void on_save_tmps();
    void on_clicked_stop();
    void on_clicked_loadtmp();//导入模板
    void on_clicked_savetmp();//导出模板

};

#endif // CREATETMPDIALOG_H
