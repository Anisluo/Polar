#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTableWidget>
#include<QPushButton>
#include<QTextEdit>
#include<QLineEdit>
#include<QLabel>
#include<QScrollArea>
#include<QTimer>
#include<QSpinBox>
#include<QSerialPort>
#include"Conifg.h"
#include"movectrl.h"
#include"showtmpdialog.h"



//#define NO_CAMERA
//#include"include/MvCameraControl.h"//添加相机库



#ifndef NO_CAMERA
#include"include/MvCamera.h"
#endif
#include"workThrd.h"
#include"sqlhelper.h"
#include"axedialog.h"
#include"devdialog.h"
//#include"templatedialog.h"
#include"createtmpdialog.h"
#include<QRadioButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;  }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    bool isRunningCamera=true;
    AXE_CONFIG* curAxe;
//    COM_CONFIG* com_cfg;
    MOVESPEED	curSpeed;
    TEMPLATE_CONFIG* tmp_cfg;

private:
    Ui::MainWindow 	*ui;
    sqlHelper		*sql;
    axeDialog		*axe_dlg;
    devDialog		*com_dlg;
    createTmpDialog	*tmp_dlg;
//    showtmpDialog	*tmp_lists;
    workThrd		*workthr;//工作线程

    QTableWidget 	*main_table;
    QTableWidget	*main_single_table;
    QScrollArea		*main_camera;//显示相机内容
    QLabel			*main_camera_display;
    QScrollArea 	*main_camera_panel;
    QLabel			*main_camera_exptime_lb;
    QSpinBox		*main_camera_exptime_sp;
    QPushButton		*main_camera_exptime_set;
    QTextEdit		*main_log_text;



    QScrollArea 	*main_area;

    QScrollArea *main_ctrlpanel;
    QScrollArea *main_status;
    QPushButton *main_start;
    QPushButton *main_reset;
    QPushButton *main_stop;
    QPushButton *main_single;
    QLabel		*main_OK_NG;

    QScrollArea *main_infopanel;
    QLabel 		*main_template_title;
    QPushButton *main_template_btn;
    QLabel 		*main_resultfile_title;
    QLabel		*main_resultfile;
    QPushButton	*main_resultfile_btn;


    //测试信息
    QLabel	*main_log;
    QLabel	*main_total;
    QLabel	*main_pass;
    QLabel	*main_fail;
    QLabel	*main_result;
    QLabel	*main_template;

    QLabel	*main_dev_status;//设备状态
    QLabel	*main_axe_status;//设备状态
    QLabel	*main_io_status;//IO状态
    QLabel	*main_camera_status;//相机状态
    QRadioButton *main_axe_speedL;
    QRadioButton *main_axe_speedM;
    QRadioButton *main_axe_speedH;
    QPushButton	*main_axe_left;
    QPushButton	*main_axe_right;
    QPushButton* main_axe_home;



    void connect_serialport();//连接串口

    MoveCtrl* mvctrl;
#ifndef NO_CAMERA
    CMvCamera 	*m_camera;
#endif
    workThrd *m_workThrd;//相机线程
    void initWidget();
    void initMenu();
    bool connectCamera();//连接相机
private:
    MAIN_CONFIG main_config;
    COM_CONFIG	com_config;
    CAMERA_CONFIG	camera_config;
    AXE_CONFIG		axe_config;
    void loadConfig();//载入配置
    void saveConfig();//保存配置
    void init_main_table();
    void init_single_table();

private:
#ifndef NO_CAMERA
    MV_FRAME_OUT stImageInfo = {0};
    MV_DISPLAY_FRAME_INFO stDisplayInfo = {0};
    unsigned char*          m_pSaveImageBuf;
    unsigned int            m_nSaveImageBufSize;
    MV_FRAME_OUT_INFO_EX    m_stImageInfo;
    int				   m_nTriggMode;
#endif
    QTimer *updateTimer;
    QSerialPort	*serialport;
private:
    bool eventFilter(QObject* obj,QEvent* e)override;//事件过滤

public:
signals:
    void read_serial_data(const QByteArray& data);

public slots:
    void displayCamera();//显示相机
    void showMessage(const QString& msg);
    void updateImage();

    void onAction_edit_dev();
    void onAction_edit_axe();
    void onAction_create_template();//创建模板
    void onAction_export_report();
    void onAction_show_template_lists();//显示模板列表
    void onBnClicked_set_exptime();
    void write_serial_cmd(const QByteArray& str);
    void read_serial_data();//读取数据
    void update_results(RESULT_CONFIG* result);
    void update_single_results(double lum);
    void onBnClickedStart();//开启测试任务
    void onRadioButtonToggled(bool checked);
    void onMoveHome();
    void add_temps(TEMPLATE_CONFIG* tmp_cfg);
    void sendCmd();
    void on_btn_clicked_start();
    void on_btn_clicked_clear();//清空数据
    void on_btn_clicked_stop();
    void update_main_tmpname(QString tmpname);
    void set_status(STATUS_ENUM status);
    void on_btn_clicked_single_start();
    void on_btn_clicked_set_result_title();
    void on_btn_clicked_set_template_title();

    //    void mousePressEvent(QMouseEvent* event)override;
    //    void mouseReleaseEvent(QMouseEvent* event)override;

    //    void onBnClickedGenerateTemplate();//生成测试模板
};
#endif // MAINWINDOW_H
