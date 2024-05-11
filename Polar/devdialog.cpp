#include "devdialog.h"
#include "ui_devdialog.h"
#include<QVBoxLayout>
#include<QScrollArea>
#include<QStringList>

devDialog::devDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::devDialog)
{
    ui->setupUi(this);
    initWidget();
}

devDialog::~devDialog()
{
    delete ui;
}



void devDialog::initWidget()
{
    //this->setWindowTitle(QStringLiteral("
    this->setWindowTitle(QStringLiteral("仪器参数"));
    QFont fnt;
    fnt.setPixelSize(14);
    ui->widget->setFont(fnt);
    //    QWidget *main_area=new QWidget()
    //    ui->widget->setFixedSize(QSize(400,350));
    QHBoxLayout *layoutMain=new QHBoxLayout(ui->widget);


    QScrollArea *main_area=new QScrollArea(ui->widget);
    QWidget *main_log=new QWidget(ui->widget);
    layoutMain->addWidget(main_area,2);
    layoutMain->addWidget(main_log,3);


    QVBoxLayout *layoutLog=new QVBoxLayout(main_log);
    m_log=new QTextEdit(main_log);
    m_log->setReadOnly(true);
    layoutLog->addWidget(m_log);

//    main_area->setFixedWidth(200);
    QVBoxLayout *layoutLeft=new QVBoxLayout(main_area);

    m_port=new QWidget(main_area);
    m_port_lb=new QLabel(m_port);
    m_port_lb->setText(QStringLiteral("串口："));
    m_port_cb=new QComboBox(m_port);
    //    QStringList lstport;
    //    lstbaus<<"9600"<<"57600"<<"115200";
    //    m_baudrate_cb->addItems(lstbaus);
    QHBoxLayout *layoutPort=new QHBoxLayout(m_port);
    layoutPort->addWidget(m_port_lb,2);
    layoutPort->addWidget(m_port_cb,3);
    layoutLeft->addWidget(m_port);

    //枚举portName名称
    QList<QSerialPortInfo> serialPorts=QSerialPortInfo::availablePorts();
    QStringList lstNames;
    foreach (const QSerialPortInfo& serialPort, serialPorts) {
        lstNames<<serialPort.portName();
    }
    m_port_cb->addItems(lstNames);


    m_baudrate=new QWidget(main_area);
    m_baudrate_lb=new QLabel(m_baudrate);
    m_baudrate_lb->setText(QStringLiteral("波特率："));
    m_baudrate_cb=new QComboBox(m_baudrate);
    QStringList lstbaus;
    lstbaus<<"9600"<<"57600"<<"115200";
    m_baudrate_cb->addItems(lstbaus);
    QHBoxLayout *layoutBaud=new QHBoxLayout(m_baudrate);
    layoutBaud->addWidget(m_baudrate_lb,2);
    layoutBaud->addWidget(m_baudrate_cb,3);
    layoutLeft->addWidget(m_baudrate);

    m_databit=new QWidget(main_area);
    m_databit_lb=new QLabel(m_databit);
    m_databit_lb->setText(QStringLiteral("数据位："));
    m_databit_cb=new QComboBox(m_databit);
    QStringList lstdatabits;
    lstdatabits<<"6"<<"7"<<"8";
    m_databit_cb->addItems(lstdatabits);
    QHBoxLayout *layoutDatabit=new QHBoxLayout(m_databit);
    layoutDatabit->addWidget(m_databit_lb,2);
    layoutDatabit->addWidget(m_databit_cb,3);
    layoutLeft->addWidget(m_databit);

    m_stopbit=new QWidget(main_area);
    m_stopbit_lb=new QLabel(m_stopbit);
    m_stopbit_lb->setText(QStringLiteral("停止位："));
    m_stopbit_cb=new QComboBox(m_stopbit);
    QStringList lststopbits;
    lststopbits<<"0"<<"1"<<"2";
    m_stopbit_cb->addItems(lststopbits);

    QHBoxLayout *layoutStopbit=new QHBoxLayout(m_stopbit);
    layoutStopbit->addWidget(m_stopbit_lb,2);
    layoutStopbit->addWidget(m_stopbit_cb,3);
    layoutLeft->addWidget(m_stopbit);

    m_parity=new QWidget(main_area);
    m_parity_lb=new QLabel(m_parity);
    m_parity_lb->setText(QStringLiteral("校验位："));
    m_parity_cb=new QComboBox(m_parity);
    QStringList lststparity;
    lststparity<<"None"<<"Even"<<"Odd";
    m_parity_cb->addItems(lststparity);



    QHBoxLayout *layoutParity=new QHBoxLayout(m_parity);
    layoutParity->addWidget(m_parity_lb,2);
    layoutParity->addWidget(m_parity_cb,3);
    layoutLeft->addWidget(m_parity);


    m_angle_wnd=new QWidget(main_area);
    m_angle_lb=new QLabel(m_angle_wnd);
    m_angle_lb->setText(QStringLiteral("视场角："));
    m_angle_cb=new QComboBox(m_angle_wnd);
    QStringList lststangle;
    lststangle<<QStringLiteral("0.1°")<<QStringLiteral("0.2°")<<QStringLiteral("1°")<<QStringLiteral("2°");
    m_angle_cb->addItems(lststangle);
    QHBoxLayout *layoutAngle=new QHBoxLayout(m_angle_wnd);
    layoutAngle->addWidget(m_angle_lb);
    layoutAngle->addWidget(m_angle_cb);
    layoutLeft->addWidget(m_angle_wnd);
    connect(m_angle_cb,SIGNAL(currentIndexChanged(int)),this,SLOT(on_combo_index_changed_angle(int)));

    m_ctrlpanel=new QWidget(main_area);
    m_init=new QPushButton(m_ctrlpanel);
    m_init->setText(QStringLiteral("打开"));
    m_exit=new QPushButton(m_ctrlpanel);
    m_exit->setText(QStringLiteral("关闭"));
    QHBoxLayout *layoutCtrl=new QHBoxLayout(m_ctrlpanel);
    layoutCtrl->addWidget(m_init,1);
    layoutCtrl->addWidget(m_exit,1);
    layoutLeft->addWidget(m_ctrlpanel);
    connect(m_init,SIGNAL(clicked()),this,SLOT(on_init_com()));
    connect(m_exit,SIGNAL(clicked()),this,SLOT(on_exit_com()));

    m_read=new QWidget(main_area);
    m_readL1=new QPushButton(m_read);
    m_readL1->setText(QStringLiteral("读取数据"));
    m_readL2=new QPushButton(m_read);
    m_readL2->setText(QStringLiteral("保存配置"));
    QHBoxLayout *layoutRead=new QHBoxLayout(m_read);
    layoutRead->addWidget(m_readL1,1);
    layoutRead->addWidget(m_readL2,1);
    layoutLeft->addWidget(m_read);
    connect(m_readL2,SIGNAL(clicked()),this,SLOT(on_ensure_com()));
    connect(m_readL1,SIGNAL(clicked()),this,SLOT(on_readL_com()));
}


//读取数据
void devDialog::read_serial_data(const QByteArray& data)
{
    QString code=">> "+data;
    m_log->append(code);
}


void devDialog::showMessage(const QString& msg)
{
    m_log->append(">>"+ msg);
}


void devDialog::loadConfig(COM_CONFIG* cfg,QSerialPort* ser,sqlHelper* sql)
{
    com_cfg=cfg;
    sport=ser;
    sql_helper=sql;
    update_ui_from_data();
}




void devDialog::update_data_from_ui()
{
    com_cfg->COM_NAME=m_port_cb->currentText();
    com_cfg->COM_BAUDRATE=m_baudrate_cb->currentText().toUInt();
    com_cfg->COM_DATABIT=m_databit_cb->currentText().toUInt();
    com_cfg->COM_STOPBIT=m_stopbit_cb->currentIndex();
    com_cfg->COM_PARITY=m_parity_cb->currentIndex();
}


void devDialog::update_ui_from_data()
{

    if(com_cfg->COM_BAUDRATE==9600)
    {
        m_baudrate_cb->setCurrentIndex(0);
    }
    else if(com_cfg->COM_BAUDRATE==57600){
        m_baudrate_cb->setCurrentIndex(1);
    }
    else if(com_cfg->COM_BAUDRATE==115200){
        m_baudrate_cb->setCurrentIndex(2);
    }
    else{}

    if(com_cfg->COM_STOPBIT==0)
    {
        m_stopbit_cb->setCurrentIndex(0);
    }
    else if(com_cfg->COM_STOPBIT==1){
        m_stopbit_cb->setCurrentIndex(1);
    }
    else if(com_cfg->COM_STOPBIT==2){
        m_stopbit_cb->setCurrentIndex(2);
    }
    else{}

    if(com_cfg->COM_DATABIT==6)
    {
        m_databit_cb->setCurrentIndex(0);
    }
    else if(com_cfg->COM_DATABIT==7){
        m_databit_cb->setCurrentIndex(1);
    }
    else if(com_cfg->COM_DATABIT==8){
        m_databit_cb->setCurrentIndex(2);
    }
    else{}

    if(com_cfg->COM_PARITY==0)
    {
        m_parity_cb->setCurrentIndex(0);
    }
    else if(com_cfg->COM_PARITY==1){
        m_parity_cb->setCurrentIndex(1);
    }
    else if(com_cfg->COM_PARITY==2){
        m_parity_cb->setCurrentIndex(2);
    }
    else{}

}


void devDialog::on_exit_com()
{
    if(sport!=nullptr&&sport->isOpen()) { sport->close(); }
}

//ensure_com
void devDialog::on_ensure_com()
{
    update_data_from_ui();
    sql_helper->saveConfig(com_cfg);
    this->close();

}

void devDialog::on_combo_index_changed_angle(int index)
{
    QByteArray cmd="";
    switch(index)
    {
    case 0: cmd="FLD4\r\n";break;
    case 1: cmd="FLD3\r\n";break;
    case 2: cmd="FLD2\r\n";break;
    case 3: cmd="FLD1\r\n";break;
    }

    if(sport->isOpen())
    {
        sport->write(cmd);
    }
    showMessage(QStringLiteral("切换视场角......"));
}

//读取数据
void devDialog::on_readL_com()
{
    if(sport->isOpen())
    {
        sport->write("D1 ST\r\n");
    }
    showMessage(QStringLiteral("读取亮度数据......"));
}



//清空com
void devDialog::on_clear_com()
{

}




void devDialog::on_init_com()
{
    update_data_from_ui();

    if(sport->isOpen()){sport->close();}
    sport->setPortName(com_cfg->COM_NAME);
    if(com_cfg->COM_BAUDRATE==9600)
    {
        sport->setBaudRate(QSerialPort::Baud9600);
    }
    else if(com_cfg->COM_BAUDRATE==57600)
    {
        sport->setBaudRate(QSerialPort::Baud57600);
    }
    else if(com_cfg->COM_BAUDRATE==115200)
    {
        sport->setBaudRate(QSerialPort::Baud115200);
    }
    else{}

    if(com_cfg->COM_DATABIT==6)
    {
        sport->setDataBits(QSerialPort::Data6);
    }
    else if(com_cfg->COM_DATABIT==7)
    {

        sport->setDataBits(QSerialPort::Data7);
    }
    else if(com_cfg->COM_DATABIT==8)
    {
        sport->setDataBits(QSerialPort::Data8);
    }
    else{}

    if(com_cfg->COM_PARITY==0)
    {
        sport->setParity(QSerialPort::NoParity);
    }
    else if(com_cfg->COM_PARITY==1)
    {

        sport->setParity(QSerialPort::EvenParity);
    }
    else if(com_cfg->COM_PARITY==2)
    {
        sport->setParity(QSerialPort::OddParity);
    }
    else{}

    if(com_cfg->COM_STOPBIT==0)
    {
        sport->setStopBits(QSerialPort::UnknownStopBits);
    }
    else if(com_cfg->COM_STOPBIT==1)
    {
        sport->setStopBits(QSerialPort::OneStop);
    }
    else if(com_cfg->COM_STOPBIT==2)
    {
        sport->setStopBits(QSerialPort::OneAndHalfStop);
    }
    else{}

     if(sport->open(QIODevice::ReadWrite))
    {
     sport->setDataTerminalReady(true);
     sport->setRequestToSend(true);

     sport->write("RM\r\n");
     showMessage(QStringLiteral("打开串口,发送RM "));
     }
}


