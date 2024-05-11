#ifndef DEVDIALOG_H
#define DEVDIALOG_H
#include<QLabel>
#include<QComboBox>

#include <QDialog>
#include<QPushButton>
#include<QTextEdit>
#include<QSerialPortInfo>
#include<QSerialPort>
#include"Conifg.h"
#include"sqlhelper.h"
namespace Ui {
class devDialog;
}

class devDialog : public QDialog
{
    Q_OBJECT

public:
    explicit devDialog(QWidget *parent = nullptr);
    ~devDialog();

private:
    Ui::devDialog *ui;
    void initWidget();//初始化窗口
    QSerialPort* sport;
    sqlHelper* sql_helper;

    QWidget	  *m_port;
    QLabel 	  *m_port_lb;
    QComboBox *m_port_cb;
    COM_CONFIG* com_cfg;



    QWidget	  *m_baudrate;
    QLabel 	  *m_baudrate_lb;
    QComboBox *m_baudrate_cb;

    QWidget	  *m_stopbit;
    QLabel 	  *m_stopbit_lb;
    QComboBox *m_stopbit_cb;

    QWidget	  *m_databit;
    QLabel 	  *m_databit_lb;
    QComboBox *m_databit_cb;

    QWidget	  *m_parity;
    QLabel 	  *m_parity_lb;
    QComboBox *m_parity_cb;

    QWidget	  *m_ctrlpanel;
    QPushButton 	  *m_init;
    QPushButton 	*m_exit;

    QWidget	  *m_read;
    QPushButton 	  *m_readL1;
    QPushButton 	  *m_readL2;

    QWidget	*m_angle_wnd;
    QLabel*	m_angle_lb;
    QComboBox	*m_angle_cb;

    QTextEdit	*m_log;
    void update_data_from_ui();
    void update_ui_from_data();
    void showMessage(const QString& msg);
public:
    void loadConfig(COM_CONFIG* cfg,QSerialPort* ser,sqlHelper* sql);

public slots:
    void read_serial_data(const QByteArray& data);


public slots:
    void on_init_com();
    void on_exit_com();
    void on_ensure_com();
    void on_clear_com();
    void on_readL_com();
    void on_combo_index_changed_angle(int);


};

#endif // DEVDIALOG_H
