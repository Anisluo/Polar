#ifndef AXEDIALOG_H
#define AXEDIALOG_H

#include<QDialog>
#include<QLabel>
#include<QSpinBox>
#include<QPushButton>
#include"Conifg.h"
#include"sqlhelper.h"

namespace Ui {
class axeDialog;
}

class axeDialog : public QDialog
{
    Q_OBJECT

private:
    void initWidget();
    AXE_CONFIG* curAxe;
    sqlHelper		*sql;

    QLabel		*m_axe_id_lb;
    QSpinBox	*m_axe_id_sp;

    QLabel		*m_axe_perMM_lb;
    QSpinBox	*m_axe_perMM_sp;

    QLabel		*m_axe_speedH_lb;
    QSpinBox	*m_axe_speedH_sp;

    QLabel		*m_axe_speedM_lb;
    QSpinBox	*m_axe_speedM_sp;

    QLabel		*m_axe_speedL_lb;
    QSpinBox	*m_axe_speedL_sp;

    QLabel		*m_axe_speedT_lb;
    QSpinBox	*m_axe_speedT_sp;

    QLabel		*m_axe_ac_lb;
    QSpinBox	*m_axe_ac_sp;

    QLabel		*m_axe_home_lb;
    QSpinBox	*m_axe_home_sp;


    QPushButton	*m_axe_ok;
    QPushButton	*m_axe_reset;

public:
    explicit axeDialog(QWidget *parent = nullptr);
    void loadConfig(AXE_CONFIG* axe_config,sqlHelper* sl);
    ~axeDialog();

private:
    Ui::axeDialog *ui;
private
    slots:
    void on_bn_clicked_ok();
    void on_bn_clicked_reset();
    void update_ui_from_data();
    void update_data_from_ui();

};

#endif // AXEDIALOG_H
