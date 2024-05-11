#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QVBoxLayout>
#include<QHeaderView>
#include<QSpacerItem>
//#include"devdialog.h"
//#include"axedialog.h"
//#include"devdialog.h"
#include<QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    setMouseTracking(true);
    tmp_cfg=new TEMPLATE_CONFIG;
    loadConfig();
    axe_dlg=new axeDialog;
    com_dlg=new devDialog;
    tmp_dlg=new createTmpDialog;
//    tmp_lists=new showtmpDialog;

    mvctrl=MoveCtrl::init();

    initWidget();
    initMenu();
    connectCamera();//连接相机
    updateTimer=new QTimer(this);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updateImage()));
    updateTimer->start(100);

    serialport=new QSerialPort(this);
    connect_serialport();

    connect(serialport,
        SIGNAL(readyRead()),
        this,
        SLOT(read_serial_data()),Qt::DirectConnection);

    connect(this,SIGNAL(read_serial_data(const QByteArray&)),
        com_dlg,SLOT(read_serial_data(const QByteArray&)));
    workthr=new workThrd;

    //连接connect
    connect(workthr,SIGNAL(updateResults(RESULT_CONFIG*)),this,SLOT(update_results(RESULT_CONFIG*)));
    connect(workthr,SIGNAL(update_single_result(double)),this,SLOT(update_single_results(double)));
    connect(workthr,SIGNAL(showMessage(const QString&)),this,SLOT(showMessage(const QString&)));

    connect(workthr,SIGNAL(showMessage_tmp(const QString&)),tmp_dlg,SLOT(showMessage(const QString&)));
    connect(workthr,SIGNAL(update_tmp_lum_angle(double,double)),tmp_dlg,SLOT(update_tmp_lum_angle(double,double)));
    connect(workthr,SIGNAL(update_tmp_contrast(double)),tmp_dlg,SLOT(update_tmp_contrast(double)));
    connect(workthr,SIGNAL(update_tmp_max_min_lumangle(double,double)),tmp_dlg,SLOT(update_tmp_max_min_lumangle(double,double)));
//    connect(workthr,SIGNAL(update_tmp_max_min_lumangle(double)),tmp_dlg,SLOT(update_tmp_contrast_value(double)));
    connect(tmp_dlg,SIGNAL(add_template(TEMPLATE_CONFIG*)),this,SLOT(add_temps(TEMPLATE_CONFIG*)));//添加模板
    connect(workthr,SIGNAL(sendCmd()),this,SLOT(sendCmd()));
// bool flag= connect(workthr,SIGNAL(set_status(STATUS_ENUM)),this,SLOT(set_status(STATUS_ENUM)));

    workthr->init(mvctrl,curAxe);
    workthr->start();//开启后台线程

    connect(tmp_dlg,SIGNAL(on_start_generate()),workthr,SLOT(on_start_generate()));
    connect(tmp_dlg,SIGNAL(on_stop_generate()),workthr,SLOT(on_stop_generate()));
    //    this->installEventFilter();

}
void MainWindow::sendCmd()
{
    if(serialport->isOpen())
    {
        serialport->write("D1 ST\r\n");
    }

}

void MainWindow::on_btn_clicked_start()
{
    main_table->setHidden(false);
    main_single_table->setHidden(true);
    workthr->on_start_main_test();
    showMessage(QStringLiteral("开始测试......"));
    set_status(STATUS_ENUM::waiting);
    TASK_CONFIG* tsk=new TASK_CONFIG;
    tsk->tmp_cfg=tmp_cfg;
    tsk->task_type=TASK_ENUM::normal_test;
    workthr->add_tasks(tsk);
}

//单点测量
void MainWindow::on_btn_clicked_single_start()
{
    main_table->setHidden(true);
    main_single_table->setHidden(false);
    workthr->on_start_single_test();
    showMessage(QStringLiteral("开始单点测试......"));
    set_status(STATUS_ENUM::waiting);
    TASK_CONFIG* tsk=new TASK_CONFIG;
    tsk->tmp_cfg=tmp_cfg;
    tsk->task_type=TASK_ENUM::single_test;
    workthr->add_tasks(tsk);
}






//停止测试
void MainWindow::on_btn_clicked_stop()
{
    workthr->on_stop_main_test();
}


void MainWindow::on_btn_clicked_clear()
{
    if(main_table->isVisible())
    {
        int rowNum=   main_table->rowCount();
        for(int i = 0 ; i < rowNum ; i++)//清空列表
        {
            main_table->removeRow(0);
        }

    }
    if(main_single_table->isVisible())
    {
        int rowNum=   main_single_table->rowCount();
        for(int i = 0 ; i < rowNum ; i++)//清空列表
        {
            main_single_table->removeRow(0);
        }

    }
}

void MainWindow::update_main_tmpname(QString tmpname)
{
    main_template_title->setText(QStringLiteral("模板: ")+tmpname);
}


//设置状态
void MainWindow::set_status(STATUS_ENUM status)
{
    switch(status)
    {
    case STATUS_ENUM::waiting:
        main_OK_NG->setStyleSheet("background:gray;color:white;");
        main_OK_NG->setText(QStringLiteral("测试中..."));
        break;
    case STATUS_ENUM::unrun:
        main_OK_NG->setStyleSheet("background:gray;color:white;");
        main_OK_NG->setText(QStringLiteral("待测试..."));
        break;
    case STATUS_ENUM::ok:
        main_OK_NG->setStyleSheet("background:green;color:white;");
        main_OK_NG->setText(QStringLiteral("OK"));
        break;
    case STATUS_ENUM::ng:
        main_OK_NG->setStyleSheet("background:red;color:white;");
        main_OK_NG->setText(QStringLiteral("NG"));
        break;
    }
}


MainWindow::~MainWindow()
{
    isRunningCamera=false;
#ifndef NO_CAMERA
    //    m_camera->StopGrabbing();
    m_camera->Close();//关闭相机
#endif
    delete ui;
}

//i hope the world will end until you suck the world

//事件过滤器
bool MainWindow::eventFilter(QObject* obj,QEvent*e)
{
    if(obj==main_axe_left)
    {
        if(e->type()==QEvent::MouseButtonPress)
        {
            if(mvctrl!=nullptr) { mvctrl->move_left(curAxe,curSpeed); }
        }
        else if(e->type()==QEvent::MouseButtonRelease)
        {

            if(mvctrl!=nullptr) { mvctrl->move_stop(curAxe); }
        }

    }
    else if(obj==main_axe_right)
    {
        if(e->type()==QEvent::MouseButtonPress)
        {
            if(mvctrl!=nullptr) { mvctrl->move_right(curAxe,curSpeed); }
        }
        else if(e->type()==QEvent::MouseButtonRelease)
        {

            if(mvctrl!=nullptr) { mvctrl->move_stop(curAxe); }
        }
    }
    else{  }

    return QMainWindow::eventFilter(obj,e);
}


void MainWindow::showMessage(const QString& msg)
{
    QString str=">>"+msg;
    main_log->setText(str);
    QString time=QDateTime::currentDateTime().toString("yyyyMMdd:HHmmss");

    main_log_text->append(time+str);
}

void MainWindow::write_serial_cmd(const QByteArray& cmd)
{
    if(serialport->isOpen())
    { serialport->write(cmd); }
}


//读取所有数据
void MainWindow::read_serial_data()
{
    QByteArray data=serialport->readAll();
    workthr->addDatas(data);
    emit read_serial_data(data);
}

//开始执行测试任务
void MainWindow::onBnClickedStart()
{



}

void MainWindow::add_temps(TEMPLATE_CONFIG* tmp_cfg)
{

    //	showMessage(QStringLiteral("转盘归零中......"));
    TASK_CONFIG* tsk=new TASK_CONFIG;
    tsk->task_type=TASK_ENUM::generate_tmps;
    tsk->tmp_cfg=tmp_cfg;
    workthr->add_tasks(tsk);
}




//移动到目的地
void MainWindow::onMoveHome()
{

    showMessage(QStringLiteral("转盘归零中......"));
    TASK_CONFIG* tsk=new TASK_CONFIG;
    workthr->add_tasks(tsk);
    //    mvctrl->move_home_ext(curAxe);
}


void MainWindow::onRadioButtonToggled(bool checked)
{
    if(checked)
    {
        QObject* sender=QObject::sender();
        if(sender==main_axe_speedH)
        {
            curSpeed=MOVESPEED::High;
        }
        else if(sender==main_axe_speedM)
        {
            curSpeed=MOVESPEED::Medium;
        }
        else if(sender==main_axe_speedL)
        {
            curSpeed=MOVESPEED::Low;
        }
        else{
            curSpeed=MOVESPEED::Low;
        }
    }
}




//void MainWindow::mousePressEvent(QMouseEvent* event)
//{
//    QObject* sender=QObject::sender();
//    if(sender==main_axe_left)
//    {
//        if(mvctrl!=nullptr) { mvctrl->move_left(curAxe,MOVESPEED::High); }
//    }
//    else if(sender==main_axe_right)
//    {
//        if(mvctrl!=nullptr) { mvctrl->move_right(curAxe,MOVESPEED::High); }
//    }
//    else{
//        //不处理
//    }
//    QMainWindow::mousePressEvent(event);
//}


//void MainWindow::mouseReleaseEvent(QMouseEvent* event)
//{
//    QObject* sender=QObject::sender();
//    if(sender==main_axe_left||sender==main_axe_right)
//    {
//        if(mvctrl!=nullptr) { mvctrl->move_stop(curAxe); }
//    }
//    QMainWindow::mousePressEvent(event);
//}


//void MainWindow::eventFi





//创建模板列表
void MainWindow::onAction_create_template()
{

//    tmp_dlg->loadConfig(sql,tmp_cfg);
    tmp_dlg->loadConfig(tmp_cfg);
    tmp_dlg->exec();

}

void MainWindow::onAction_show_template_lists()
{
//    tmp_lists->loadConfig(tmp_cfg);
//    tmp_lists->updatetmp();
//    tmp_lists->exec();
}


void MainWindow::update_single_results(double lum)
{
    int index=main_single_table->rowCount();
    main_single_table->setRowCount(index+1);
    double angle=0.0;
    mvctrl->get_curpos(curAxe,angle);
    QTableWidgetItem *itemID = new QTableWidgetItem(QString::number(index+1));
    QTableWidgetItem *itemA1 = new QTableWidgetItem(QString::number(angle));
    QTableWidgetItem *itemL1 = new QTableWidgetItem(QString::number(lum));
    main_single_table->setItem(index,0,itemID);
    main_single_table->setItem(index,1,itemA1);
    main_single_table->setItem(index,2,itemL1);
    main_single_table->scrollToBottom();
    emit set_status(STATUS_ENUM::unrun);
}


//更新测试结果
void MainWindow::update_results(RESULT_CONFIG* result)
{

    int index=main_table->rowCount();
    main_table->setRowCount(index+1);
    QTableWidgetItem *itemID = new QTableWidgetItem(QString::number(index+1));
    QTableWidgetItem *itemA1 = new QTableWidgetItem(QString::number(result->Angle1));
    QTableWidgetItem *itemA2 = new QTableWidgetItem(QString::number(result->Angle2));
//    QTableWidgetItem *itemA3 = new QTableWidgetItem(QString::number(result->Angle3));
    QTableWidgetItem *itemL1 = new QTableWidgetItem(QString::number(result->L1));
    QTableWidgetItem *itemL2 = new QTableWidgetItem(QString::number(result->L2));
//    QTableWidgetItem *itemL3=new QTableWidgetItem(QString::number(result->L3));
    QTableWidgetItem *itemContrast = new QTableWidgetItem(QString::number(result->Contrast));
    main_table->setItem(index,0,itemID);
    main_table->setItem(index,1,itemA1);
    main_table->setItem(index,2,itemA2);
//    main_table->setItem(index,3,itemA3);
    main_table->setItem(index,3,itemL1);
    main_table->setItem(index,4,itemL2);
//    main_table->setItem(index,5,itemL3);
    main_table->setItem(index,5,itemContrast);
//    main_table->item(index,6)->setFlags(Qt::ItemIsEditable);
    main_table->scrollToBottom();
    delete result;


    if(result->Contrast<tmp_cfg->contrast_min||result->Contrast>tmp_cfg->contrast_max)
    {
        itemContrast->setBackground(QBrush(QColor(Qt::red)));
        emit set_status(STATUS_ENUM::ng);

        mvctrl->set_io_status(1,0);
        mvctrl->set_io_status(2,1);
    }
    else{
        itemContrast->setBackground(QBrush(QColor(Qt::green)));
        emit set_status(STATUS_ENUM::ok);

        mvctrl->set_io_status(1,1);
        mvctrl->set_io_status(2,0);
    }
}



//unsigned int cnt=0;
//更新图像
void MainWindow::updateImage()
{

    if(isRunningCamera)
    {
#ifndef NO_CAMERA
        int nRet=MV_OK;
        nRet =m_camera->GetImageBuffer(&stImageInfo, 1000);
        if (nRet == MV_OK)
        {
            memcpy(&m_stImageInfo, &(stImageInfo.stFrameInfo), sizeof(MV_FRAME_OUT_INFO_EX));
            quintptr winId = main_camera_display->winId();
            stDisplayInfo.hWnd=reinterpret_cast<void *>(winId);
            stDisplayInfo.pData = stImageInfo.pBufAddr;
            stDisplayInfo.nDataLen = stImageInfo.stFrameInfo.nFrameLen;
            stDisplayInfo.nWidth = stImageInfo.stFrameInfo.nWidth;
            stDisplayInfo.nHeight = stImageInfo.stFrameInfo.nHeight;
            stDisplayInfo.enPixelType = stImageInfo.stFrameInfo.enPixelType;
            m_camera->DisplayOneFrame(&stDisplayInfo);

            m_camera->FreeImageBuffer(&stImageInfo);
        }
#endif
    }

    double p=90.00;
    if(curAxe!=nullptr)
    {
        mvctrl->get_curpos(curAxe,p);
        if(mvctrl->get_io_status(1)==0)
        {
            mvctrl->set_io_status(1,1);
            mvctrl->set_io_status(2,0);
        }
        else{
            mvctrl->set_io_status(1,0);
            mvctrl->set_io_status(2,1);
        }
    }

    //更新坐标位置
    main_axe_status->setText(QStringLiteral("转盘位置: ")+QString::number(p,'f',2)+QStringLiteral("°"));
}


void MainWindow::displayCamera()
{
    //    showMessage("enter display");
    //    int nRet=MV_OK;
    //    nRet =m_camera->GetImageBuffer(&stImageInfo, 1000);
    //    if (nRet == MV_OK)
    //    {
    //        showMessage(">>	get picture");
    //        //        // 用于保存图片
    //        if (m_pSaveImageBuf == nullptr || stImageInfo.stFrameInfo.nFrameLen > m_nSaveImageBufSize)
    //        {
    //            if (m_pSaveImageBuf)
    //            {
    //                free(m_pSaveImageBuf);
    //                m_pSaveImageBuf = nullptr;
    //            }
    //            m_pSaveImageBuf = (unsigned char *)malloc(sizeof(unsigned char) * stImageInfo.stFrameInfo.nFrameLen);
    //            if (m_pSaveImageBuf == nullptr) { return; }
    //            m_nSaveImageBufSize = stImageInfo.stFrameInfo.nFrameLen;
    //        }
    //        memcpy(m_pSaveImageBuf, stImageInfo.pBufAddr, stImageInfo.stFrameInfo.nFrameLen);
    //        memcpy(&m_stImageInfo, &(stImageInfo.stFrameInfo), sizeof(MV_FRAME_OUT_INFO_EX));
    //        // 显示图像
    ////        QImage image(m_pSaveImageBuf, m_stImageInfo.nWidth, m_stImageInfo.nHeight, QImage::Format_RGB888);
    //        //显示图片
    ////        main_camera_display->setPixmap(QPixmap::fromImage(image));
    //        m_camera->FreeImageBuffer(&stImageInfo);
    //    }
}


bool MainWindow::connectCamera()
{
#ifndef NO_CAMERA
    MV_CC_DEVICE_INFO_LIST m_stDevList;
    memset(&m_stDevList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
    // ch:枚举子网内所有设备 | en:Enumerate all devices within subnet
    int nRet = CMvCamera::EnumDevices(MV_GIGE_DEVICE|MV_USB_DEVICE, &m_stDevList);
    showMessage("enum device "+QString::number(nRet,16));
    if (MV_OK != nRet) { return false; }
    showMessage("enum device "+QString::number(m_stDevList.nDeviceNum));
    for (unsigned int i = 0; i < m_stDevList.nDeviceNum; i++)
    {
        MV_CC_DEVICE_INFO* pDeviceInfo = m_stDevList.pDeviceInfo[i];
        if (NULL == pDeviceInfo) { continue; }
        m_camera=new CMvCamera;
        if(NULL==m_camera){continue;}
        if(MV_OK!=m_camera->Open(pDeviceInfo))
        { continue; }
        m_nTriggMode=MV_TRIGGER_MODE_OFF;
        m_camera->SetEnumValue("TriggerMode",m_nTriggMode);//设置触发模式
        int nRet=m_camera->StartGrabbing();
        if(nRet!=0){continue;}
        showMessage(">>	connect success");
        isRunningCamera=true;

        //设置曝光时间



        return true;
    }
    showMessage(">>	connect error");
    isRunningCamera=false;
#endif
    return false;
}


void MainWindow::connect_serialport()
{
    if(serialport->isOpen()) { serialport->close(); }
    serialport->setPortName(com_config.COM_NAME);
    if(com_config.COM_BAUDRATE==9600)
    {
        serialport->setBaudRate(QSerialPort::Baud9600);
    }

    else if(com_config.COM_BAUDRATE==57600)
    {

        serialport->setBaudRate(QSerialPort::Baud57600);
    }
    else if(com_config.COM_BAUDRATE==115200)
    {

        serialport->setBaudRate(QSerialPort::Baud115200);
    }
    else{}

    if(com_config.COM_STOPBIT==0)
    {
        serialport->setStopBits(QSerialPort::StopBits::UnknownStopBits);
    }

    else if(com_config.COM_STOPBIT==1)
    {

        serialport->setStopBits(QSerialPort::StopBits::OneStop);
    }
    else if(com_config.COM_STOPBIT==2)
    {
        serialport->setStopBits(QSerialPort::StopBits::TwoStop);
    }
    else{}

    if(com_config.COM_DATABIT==6)
    {
        serialport->setDataBits(QSerialPort::Data6);
    }

    else if(com_config.COM_DATABIT==7)
    {

        serialport->setDataBits(QSerialPort::Data7);
    }
    else if(com_config.COM_DATABIT==8)
    {
        serialport->setDataBits(QSerialPort::Data8);
    }
    else{}

    if(com_config.COM_PARITY==0)
    {
        serialport->setParity(QSerialPort::Parity::NoParity);
    }

    else if(com_config.COM_PARITY==1)
    {

        serialport->setParity(QSerialPort::Parity::EvenParity);
    }
    else if(com_config.COM_PARITY==2)
    {
        serialport->setParity(QSerialPort::Parity::OddParity);
    }
    else{}



    if(serialport->open(QIODevice::ReadWrite))
    {
        serialport->setDataTerminalReady(true);
        serialport->setRequestToSend(true);
        showMessage(QStringLiteral("SR-5A仪器接成功"));
    }
    else{
        showMessage(QStringLiteral("SR-5A仪器串口连接失败"));
    }
}


void MainWindow::initMenu()
{
    QAction *open_action=new QAction(QStringLiteral("打开"),ui->menu_file);
    QAction *exit_action=new QAction(QStringLiteral("退出"),ui->menu_file);

    ui->menu_file->addAction(open_action);
    ui->menu_file->addAction(exit_action);

    QAction *edit_machine_action=new QAction(QStringLiteral("机台参数"),ui->menu_coef);
    QAction *edit_dev_action=new QAction(QStringLiteral("仪器参数"),ui->menu_coef);
//    QAction *edit_report_action=new QAction(QStringLiteral("测量标准"),ui->menu_coef);

    ui->menu_coef->addAction(edit_machine_action);
    ui->menu_coef->addAction(edit_dev_action);
//    ui->menu_coef->addAction(edit_report_action);

    connect(edit_dev_action,
            SIGNAL(triggered()),
            this,
            SLOT(onAction_edit_dev()));

     connect(edit_machine_action,
            SIGNAL(triggered()),
            this,
            SLOT(onAction_edit_axe()));

    QAction *template_create_action=new QAction(QStringLiteral("创建模板"),ui->menu_template);
//    QAction *template_show_action=new QAction(QStringLiteral("模板列表"),ui->menu_template);

    ui->menu_template->addAction(template_create_action);
//    ui->menu_template->addAction(template_show_action);

    connect(template_create_action,
        SIGNAL(triggered()),
        this,
        SLOT(onAction_create_template()));


//    connect(template_show_action,
//        SIGNAL(triggered()),
//        this,
//        SLOT(onAction_show_template_lists()));


    QAction *report_action=new QAction(QStringLiteral("导出历史数据"),ui->menu_report);
//    QAction *report_show_action=new QAction(QStringLiteral("模板列表"),ui->menu_template);

    ui->menu_report->addAction(report_action);

    connect(report_action,
        SIGNAL(triggered()),
        this,
        SLOT(onAction_export_report()));

}


void MainWindow::onAction_export_report()
{

    QString path = QFileDialog::getSaveFileName(this, "Save CSV", "", "CSV Files (*.csv);;All Files (*)");
    if (!path.isEmpty()) {
        QFile file(path);
        if (file.open(QFile::WriteOnly | QFile::Truncate)) {
            QTextStream data(&file);
            QStringList strList;
            // 写入表头
            for (int col = 0; col < main_table->columnCount(); ++col) {
                strList << main_table->horizontalHeaderItem(col)->text();
            }
            data << strList.join(",") + "\n";
            // 写入数据
            for (int row = 0; row < main_table->rowCount(); ++row) {
                strList.clear();
                for (int col = 0; col < main_table->columnCount(); ++col) {
                    if(main_table->item(row,col)==nullptr){
                        strList<<" "; continue;}
                    QString celltext=main_table->item(row, col)->text();
                    if(!celltext.isEmpty()) { strList << main_table->item(row, col)->text(); }
                }
                data << strList.join(",") + "\n";
            }
            file.close();
        }
    }
}


//设置曝光时间
void MainWindow::onBnClicked_set_exptime()
{
#ifndef NO_CAMERA
     m_camera->SetEnumValue("ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    m_camera->SetFloatValue("ExposureTime",(float)main_camera_exptime_sp->value());

#endif
    camera_config.MAIN_CAMERA_EXP_TIME=main_camera_exptime_sp->value();
    sql->saveConfig(&camera_config);
}


void MainWindow::onAction_edit_axe()
{
    axe_dlg->loadConfig(&axe_config,sql);
    axe_dlg->exec();
}


void MainWindow::onAction_edit_dev()
{
//    devDialog* dlg=new devDialog;

    com_dlg->loadConfig(&com_config,serialport,sql);
    com_dlg->exec();
}

//载入配置
void MainWindow::loadConfig()
{
    sql=new sqlHelper;
    if(sql)
    {
        sql->loadConfig(&main_config,&com_config,&camera_config,&axe_config);
        sql->loadConfig(main_config.MAIN_TEMPLATE_NAME,tmp_cfg);//载入配置
        curAxe=&axe_config;
    }
}

void MainWindow::saveConfig()
{
    if(sql)
    {
        sql->saveConfig(&main_config);
    }
}


//main table
void MainWindow::init_main_table()
{
    //    main_camera->setStyleSheet("background:green;");
    //init table
    main_table->clear();//清空main_table数据
    main_table->setColumnCount(7);
    QStringList headText;
//    headText << "Item" << "Angle1" << "Angle2"<<"Angle3" << "L1" << "L2"<<"L3"<<"contrast"<<"sample";
    headText << "Item" << "Angle1" << "Angle2"<< "L1" << "L2"<<"contrast"<<"sample";
    main_table->setHorizontalHeaderLabels(headText);
    main_table->setSelectionBehavior(QAbstractItemView::SelectRows);
//    main_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    main_table->setSelectionMode(QAbstractItemView::NoSelection);
//    main_table->horizontalHeader()->setSectionResizeMode(QHeaderView::str);
    main_table->setAlternatingRowColors(true);
    main_table->verticalHeader()->setVisible(false);


}

//init single table
void MainWindow::init_single_table()
{
    //    main_camera->setStyleSheet("background:green;");
    //init table
    main_single_table->clear();//清空main_table数据
    main_single_table->setColumnCount(3);
    QStringList headText;
    headText << "Item" << "Angle"<< "L" <<"info";
    main_single_table->setHorizontalHeaderLabels(headText);
    main_single_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    main_single_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    main_single_table->setSelectionMode(QAbstractItemView::SingleSelection);
//    main_table->horizontalHeader()->setSectionResizeMode(QHeaderView::str);
    main_single_table->setAlternatingRowColors(true);
    main_single_table->verticalHeader()->setVisible(false);
}

void MainWindow::on_btn_clicked_set_template_title()
{
    QString selectFile=QFileDialog::getOpenFileName(NULL,QStringLiteral("选择文件"),"/","Files (*.xml)");
    {
        tmp_dlg->loadConfigXML(tmp_cfg,selectFile);
    }
//    tmp_dlg->loadConfig(tmp_cfg);
    main_template_title->setText(QStringLiteral("模板：")+tmp_cfg->tempName);

//    main_config.MAIN_TEMPLATE_NAME=tmp_cfg->tempName;
//    sql->saveConfig(&main_config);
}






void MainWindow::on_btn_clicked_set_result_title()
{
    // 创建一个 QFileDialog 实例
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory); // 设置文件模式为选择目录
    dialog.setOption(QFileDialog::ShowDirsOnly); // 仅显示目录

    // 打开对话框并获取用户选择的目录
    if (dialog.exec()) {
        QStringList selectedDirectories = dialog.selectedFiles();
        if (!selectedDirectories.isEmpty()) {
            QString selectedDirectory = selectedDirectories.first();
            //获得文件夹对话框
            //                main_config->
            main_config.MAIN_TEMPLATE_NAME=selectedDirectory;
            main_resultfile_title->setText(QStringLiteral("结果路径：")+selectedDirectory);
            // 在这里可以使用选定的目录进行后续操作

            sql->saveConfig(&main_config);
        }
    }
}

//初始化界面
void MainWindow::initWidget()
{
    ui->centralwidget->setContentsMargins(0,0,0,2);
    QVBoxLayout *layoutWidget=new QVBoxLayout(ui->widget);
    main_area=new QScrollArea(ui->widget);
    main_ctrlpanel=new QScrollArea(ui->widget);
    main_ctrlpanel->setFixedHeight(70);
    main_status=new QScrollArea(ui->widget);
    main_status->setFixedHeight(50);
    layoutWidget->addWidget(main_area);
    layoutWidget->addWidget(main_ctrlpanel);
    layoutWidget->addWidget(main_status);


    QHBoxLayout *layoutCtrlPanel=new QHBoxLayout(main_ctrlpanel);//控制界面
    main_start=new QPushButton(main_ctrlpanel);
    main_start->setFixedWidth(70);
    main_start->setFixedHeight(50);
    main_start->setText(QStringLiteral("开始"));
    layoutCtrlPanel->addWidget(main_start);
    connect(main_start,SIGNAL(clicked()),this,SLOT(on_btn_clicked_start()));

    main_stop=new QPushButton(main_ctrlpanel);
    layoutCtrlPanel->addWidget(main_stop);
    main_stop->setFixedWidth(70);
    main_stop->setFixedHeight(50);
    main_stop->setText(QStringLiteral("停止"));
    connect(main_stop,SIGNAL(clicked()),this,SLOT(on_btn_clicked_stop()));

    main_reset=new QPushButton(main_ctrlpanel);
    layoutCtrlPanel->addWidget(main_reset);
    main_reset->setText(QStringLiteral("清空"));
    main_reset->setFixedWidth(70);
    main_reset->setFixedHeight(50);

    connect(main_reset,SIGNAL(clicked()),this,SLOT(on_btn_clicked_clear()));

     main_single=new QPushButton(main_ctrlpanel);
    layoutCtrlPanel->addWidget(main_single);
    main_single->setFixedWidth(70);
    main_single->setFixedHeight(50);
    main_single->setText(QStringLiteral("单点"));

    connect(main_single,SIGNAL(clicked()),this,SLOT(on_btn_clicked_single_start()));
    QFont font_ok_ng;
    font_ok_ng.setBold(true);
    font_ok_ng.setPixelSize(50);
    main_OK_NG=new QLabel(main_ctrlpanel);
    main_OK_NG->setStyleSheet("background:gray;color:white;");
    main_OK_NG->setText(QStringLiteral("待测试..."));
    main_OK_NG->setFixedWidth(140);
    main_OK_NG->setFont(font_ok_ng);
    main_OK_NG->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    layoutCtrlPanel->addWidget(main_OK_NG);



    layoutCtrlPanel->setAlignment(Qt::AlignLeft);
    main_infopanel=new QScrollArea(main_ctrlpanel);
    QHBoxLayout *layoutinfo=new QHBoxLayout(main_infopanel);
    layoutCtrlPanel->addWidget(main_infopanel);

    QFont fontinfo;
    fontinfo.setPixelSize(32);
    fontinfo.setBold(true);
    main_infopanel->setStyleSheet("color:blue;");

    main_infopanel->setFont(fontinfo);
    main_template_title=new QLabel(main_infopanel);
    layoutinfo->addWidget(main_template_title);
    main_template_title->setText(QStringLiteral("模板: ")+tmp_cfg->tempName);
    main_template_title->setMinimumWidth(200);

    main_template_btn=new QPushButton(main_infopanel);
    main_template_btn->setText(QStringLiteral("..."));
    main_template_btn->setFixedWidth(40);
    layoutinfo->addWidget( main_template_btn);
    connect(main_template_btn,SIGNAL(clicked()),this,SLOT(on_btn_clicked_set_template_title()));

    connect(tmp_dlg,SIGNAL(update_main_tmp_name(QString)),this,SLOT(update_main_tmpname(QString)));
//    connect(tmp_lists,SIGNAL(update_tmp_name(QString)),this,SLOT(update_main_tmpname(QString)));

//    main_infopanel->
    layoutinfo->addSpacing(40);
    main_resultfile_title=new QLabel(main_infopanel);
    layoutinfo->addWidget(main_resultfile_title);
    main_resultfile_title->setText(QStringLiteral("结果路径:"));
    main_resultfile=new QLabel(main_infopanel);
    main_resultfile_btn=new QPushButton(main_infopanel);
    main_resultfile->setMinimumWidth(290);
    main_resultfile_btn->setText("...");
    main_resultfile_btn->setFixedWidth(40);
    layoutinfo->addWidget(main_resultfile);
    layoutinfo->addWidget(main_resultfile_btn);
    layoutinfo->setAlignment(Qt::AlignLeft);
    connect(main_resultfile_btn,SIGNAL(clicked()),this,SLOT(on_btn_clicked_set_result_title()));
//    layoutinfo->addSpacing(*);



    QHBoxLayout *layoutLeft=new QHBoxLayout(main_area);
    QScrollArea* wnd_table=new QScrollArea(main_area);
    main_camera=new QScrollArea(main_area);
    main_table=new QTableWidget(wnd_table);
    main_single_table=new QTableWidget(wnd_table);
    layoutLeft->addWidget(wnd_table,5);
    layoutLeft->addWidget(main_camera,3);
    QVBoxLayout *layoutTable=new QVBoxLayout(wnd_table);
    layoutTable->addWidget(main_table);
    layoutTable->addWidget(main_single_table);
    init_single_table();
    init_main_table();
    main_single_table->setHidden(true);

    //    main_table->setsele
    main_table->setSelectionMode(QAbstractItemView::NoSelection);

    QVBoxLayout *layoutCamera=new QVBoxLayout(main_camera);

    QScrollArea* camera_wnd=new QScrollArea(main_camera);
    QHBoxLayout* layout_camera=new QHBoxLayout(camera_wnd);
    main_camera_display=new QLabel(camera_wnd);
    layout_camera->addWidget(main_camera_display);
    //    camera_wnd->setWidget(main_camera_display);
    layoutCamera->addWidget(camera_wnd);

    camera_wnd->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    camera_wnd->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //    main_camera_display->setFixedWidth(2448);
    //    main_camera_display->setFixedHeight(2048);
    //    main_camera_display->setAspectRatio(1.2);


    main_camera_panel=new QScrollArea(main_camera);
    main_camera_panel->setFixedHeight(60);
    layoutCamera->addWidget(main_camera_panel);
    main_log_text=new QTextEdit(main_camera);
    main_log_text->setFixedHeight(120);
    main_log_text->setReadOnly(true);
    layoutCamera->addWidget(main_log_text);
    main_log_text->setStyleSheet("color:green;");

    QHBoxLayout *layoutCamera_panel=new QHBoxLayout(main_camera_panel);
    main_camera_panel->setStyleSheet("font: 11pt \"Microsoft YaHei UI\";");
    main_camera_exptime_lb=new QLabel(main_camera_panel);
    main_camera_exptime_lb->setText(QStringLiteral("曝光间(ms)："));
    main_camera_exptime_lb->setFixedWidth(110);
    layoutCamera_panel->addWidget(main_camera_exptime_lb);

    main_camera_exptime_sp=new QSpinBox(main_camera_panel);
    main_camera_exptime_sp->setRange(0,999999);
    main_camera_exptime_sp->setFixedWidth(80);
    main_camera_exptime_sp->setValue(camera_config.MAIN_CAMERA_EXP_TIME);
    layoutCamera_panel->addWidget(main_camera_exptime_sp);

    main_camera_exptime_set=new QPushButton(main_camera_panel);
    main_camera_exptime_set->setFixedWidth(50);
    main_camera_exptime_set->setText(QStringLiteral("设置"));
    connect(main_camera_exptime_set,SIGNAL(clicked()),this,SLOT(onBnClicked_set_exptime()));
    layoutCamera_panel->addWidget(main_camera_exptime_set);
    layoutCamera_panel->setAlignment(Qt::AlignLeft);


    ui->statusbar->hide();
    QHBoxLayout *layoutStatus=new QHBoxLayout(main_status);
    QFont font;
    font.setPointSize(10);
    main_log=new QLabel(main_status);
    main_log->setFont(font);
    main_log->setFixedWidth(200);
    //main_log->setStyleSheet("color:red;");
    layoutStatus->addWidget(main_log);
    layoutStatus->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    layoutStatus->addSpacing(20);
    main_log->setText(">> test information");

    main_dev_status=new QLabel(main_status);
    main_dev_status->setStyleSheet("color:green;");
    main_dev_status->setText("SR-5A: Normal");
    layoutStatus->addWidget(main_dev_status);
    main_camera_status=new QLabel(main_status);
    main_camera_status->setStyleSheet("color:green;");
    main_camera_status->setText(QStringLiteral("相机: Normal"));
    layoutStatus->addWidget(main_camera_status);
    layoutStatus->addSpacing(40);


    //    layoutStatus->addSpacing(20);
    main_axe_status=new QLabel(main_status);
    main_axe_status->setStyleSheet("color:green;");
    main_axe_status->setText(QStringLiteral(" 0.00 °"));
    layoutStatus->addWidget(main_axe_status);
    layoutStatus->addSpacing(10);
    QLabel* speed_lb=new QLabel(main_status);
    speed_lb->setText("Speed:");
    layoutStatus->addWidget(speed_lb);
    layoutStatus->addSpacing(10);
    main_axe_speedL=new QRadioButton(main_status);
    main_axe_speedM=new QRadioButton(main_status);
    main_axe_speedH=new QRadioButton(main_status);
    layoutStatus->addWidget(main_axe_speedL);
    layoutStatus->addWidget(main_axe_speedM);
    layoutStatus->addWidget(main_axe_speedH);
    main_axe_speedL->setChecked(true);
    main_axe_speedL->setText("Low");
    main_axe_speedM->setText("Medium");
    main_axe_speedH->setText("High");
    layoutStatus->addSpacing(5);
    //    wndSpeed->setFixedWidth(200);
    //    wndSpeed->setStyleSheet("color:green;");
    main_axe_left=new QPushButton(main_status);
    main_axe_right=new QPushButton(main_status);
    main_axe_left->setText("<<<");
    //    main_axe_left->setMouseTracking(true);
    main_axe_right->setText(">>>");
    //    main_axe_right->setMouseTracking(true);
    layoutStatus->addWidget(main_axe_left);
    main_axe_left->setStyleSheet("background:red;color:white;");
    main_axe_right->setStyleSheet("background:red;color:white;");
    main_axe_left->setFixedWidth(40);
    main_axe_right->setFixedWidth(40);
    layoutStatus->addWidget(main_axe_right);
    main_axe_left->installEventFilter(this);
    main_axe_right->installEventFilter(this);

    connect(main_axe_speedH,SIGNAL(toggled(bool)),this,SLOT(onRadioButtonToggled(bool)));
    connect(main_axe_speedM,SIGNAL(toggled(bool)),this,SLOT(onRadioButtonToggled(bool)));
    connect(main_axe_speedL,SIGNAL(toggled(bool)),this,SLOT(onRadioButtonToggled(bool)));
    curSpeed=MOVESPEED::Low;

    layoutStatus->addSpacing(10);
    main_axe_home=new QPushButton(main_status);
    main_axe_home->setText("home");
    layoutStatus->addWidget(main_axe_home);
    connect(main_axe_home,SIGNAL(clicked()),this,SLOT(onMoveHome()));


}
