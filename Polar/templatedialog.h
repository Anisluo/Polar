#ifndef TEMPLATEDIALOG_H
#define TEMPLATEDIALOG_H
#include"Conifg.h"
#include<QLabel>
#include<QLineEdit>
#include<QSpinBox>
#include<QPushButton>
#include<QTableWidget>

class templateDialog
{
public:
    templateDialog();
    void loadConfig(TEMPLATE_CONFIG* config);
    void initWidget();


private:

    QLabel* tmp_tempname_lb;
    QLineEdit* tmp_tempname_ledit;

    QLabel* tmp_start_lb;
    QSpinBox* tmp_start_sp;

    QLabel* tmp_step_lb;
    QSpinBox* tmp_step_sp;

    QLabel* tmp_stop_lb;
    QSpinBox* tmp_stop_sp;

    QLabel* tmp_lmax_lb;
    QSpinBox* tmp_lmax_sp;

    QLabel* tmp_lmin_lb;
    QSpinBox* tmp_lmin_sp;

    QPushButton* tmp_generate_btn;//生成模板
    QPushButton* tmp_stopgen_btn;//停止生成

    QPushButton* tmp_clear_btn;//清空模板
    QPushButton* tmp_save_btn;//停止清空

    QTableWidget* tmp_table;//生成测试模板表
};

#endif // TEMPLATEDIALOG_H
