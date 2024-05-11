#ifndef SHOWTMPDIALOG_H
#define SHOWTMPDIALOG_H

#include <QDialog>
#include<QTableWidget>
#include"sqlhelper.h"
#include<QPushButton>
#include"Conifg.h"

namespace Ui {
class showtmpDialog;
}

class showtmpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit showtmpDialog(QWidget *parent = nullptr);
    ~showtmpDialog();
    QTableWidget* tmp_table;
    void initWidget();

    void updatetmp();//更新tmp数据
    void loadConfig(TEMPLATE_CONFIG* tmp);
private:
    Ui::showtmpDialog *ui;
    TEMPLATE_CONFIG* tmp_cfg;
  public  slots:
    void on_confirm_btn();
    void on_clear_btn();
public:
    signals:
    void update_tmp_name(QString name);

};

#endif // SHOWTMPDIALOG_H
