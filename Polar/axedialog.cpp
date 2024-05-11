#include "axedialog.h"
#include "ui_axedialog.h"

axeDialog::axeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::axeDialog)
{
    ui->setupUi(this);
    initWidget();
}

axeDialog::~axeDialog()
{
    delete ui;
}

void axeDialog::loadConfig(AXE_CONFIG* axe_config,sqlHelper* sl)
{
    curAxe=axe_config;
    sql=sl;
    update_ui_from_data();
}

void axeDialog::on_bn_clicked_ok()
{
    update_data_from_ui();
    sql->saveConfig(curAxe);
    this->close();
}


void axeDialog::on_bn_clicked_reset()
{


}


void axeDialog::update_ui_from_data()
{
    m_axe_id_sp->setValue(curAxe->AXE_ID);
    m_axe_speedH_sp->setValue(curAxe->AXE_SPEED_HIGH);
    m_axe_speedM_sp->setValue(curAxe->AXE_SPEED_MEDIUM);
    m_axe_speedL_sp->setValue(curAxe->AXE_SPEED_LOW);
    m_axe_speedT_sp->setValue(curAxe->AXE_SPEED_TEST);
    m_axe_perMM_sp->setValue(curAxe->AXE_PERMM);
    m_axe_home_sp->setValue(curAxe->AXE_SPEED_HOME);
    m_axe_ac_sp->setValue(curAxe->AXE_AC_SPEED);
}


void axeDialog::update_data_from_ui()
{
    curAxe->AXE_ID=m_axe_id_sp->value();
    curAxe->AXE_SPEED_HIGH=m_axe_speedH_sp->value();
    curAxe->AXE_SPEED_MEDIUM=m_axe_speedM_sp->value();
    curAxe->AXE_SPEED_LOW=m_axe_speedL_sp->value();
    curAxe->AXE_SPEED_TEST=m_axe_speedT_sp->value();
    curAxe->AXE_PERMM=m_axe_perMM_sp->value();
    curAxe->AXE_AC_SPEED=m_axe_ac_sp->value();
}



//初始化窗口
void axeDialog::initWidget()
{

    QVBoxLayout *layoutMain=new QVBoxLayout(ui->widget);
    QWidget	*wndId=new QWidget(ui->widget);
    QHBoxLayout *layoutId=new QHBoxLayout(wndId);
    m_axe_id_lb	=new QLabel(wndId);
    m_axe_id_lb->setText(QStringLiteral("轴代号:"));
    m_axe_id_lb->setFixedWidth(80);
    layoutId->addWidget(m_axe_id_lb);
    m_axe_id_sp	=new QSpinBox(wndId);
    m_axe_id_sp->setRange(0,1000000);
    layoutId->addWidget(m_axe_id_sp);
    layoutMain->addWidget(wndId);

     QWidget	*wndPerMM=new QWidget(ui->widget);
    QHBoxLayout *layoutPerMM=new QHBoxLayout(wndPerMM);
    m_axe_perMM_lb	=new QLabel(wndPerMM);
    m_axe_perMM_lb->setText(QStringLiteral("脉冲比:"));
    m_axe_perMM_lb->setFixedWidth(80);

    layoutPerMM->addWidget(m_axe_perMM_lb);
    m_axe_perMM_sp	=new QSpinBox(wndPerMM);
    layoutPerMM->addWidget(m_axe_perMM_sp);
    layoutMain->addWidget(wndPerMM);

    m_axe_perMM_sp->setRange(0,1000000);




    QWidget	*wndSpeedH=new QWidget(ui->widget);
    QHBoxLayout *layoutSpeedH=new QHBoxLayout(wndSpeedH);
    m_axe_speedH_lb	=new QLabel(wndSpeedH);
    m_axe_speedH_lb->setText(QStringLiteral("高速:"));
    m_axe_speedH_lb->setFixedWidth(80);

    layoutSpeedH->addWidget(m_axe_speedH_lb);
    m_axe_speedH_sp	=new QSpinBox(wndSpeedH);
    m_axe_speedH_sp->setRange(0,1000000);
    layoutSpeedH->addWidget(m_axe_speedH_sp);
    layoutMain->addWidget(wndSpeedH);




    QWidget	*wndSpeedM=new QWidget(ui->widget);
    QHBoxLayout *layoutSpeedM=new QHBoxLayout(wndSpeedM);


    m_axe_speedM_lb	=new QLabel(wndSpeedM);
    layoutSpeedM->addWidget(m_axe_speedM_lb);
    m_axe_speedM_sp	=new QSpinBox(wndSpeedM);
    layoutSpeedM->addWidget(m_axe_speedM_sp);
    m_axe_speedM_lb->setText(QStringLiteral("中速:"));
    m_axe_speedM_lb->setFixedWidth(80);
    layoutMain->addWidget(wndSpeedM);
    m_axe_speedM_sp->setRange(0,1000000);

    QWidget	*wndSpeedL=new QWidget(ui->widget);
    QHBoxLayout *layoutSpeedL=new QHBoxLayout(wndSpeedL);

    m_axe_speedL_lb	=new QLabel(wndSpeedL);
    layoutSpeedL->addWidget(m_axe_speedL_lb);
    m_axe_speedL_sp	=new QSpinBox(wndSpeedL);
    layoutSpeedL->addWidget(m_axe_speedL_sp);
    m_axe_speedL_lb->setText(QStringLiteral("低速:"));
    m_axe_speedL_lb->setFixedWidth(80);
    layoutMain->addWidget(wndSpeedL);
    m_axe_speedL_sp->setRange(0,1000000);

    QWidget	*wndSpeedT=new QWidget(ui->widget);
    QHBoxLayout *layoutSpeedT=new QHBoxLayout(wndSpeedT);

    m_axe_speedT_lb	=new QLabel(wndSpeedH);
    layoutSpeedT->addWidget(m_axe_speedT_lb);
    m_axe_speedT_sp	=new QSpinBox(wndSpeedH);
    layoutSpeedT->addWidget(m_axe_speedT_sp);
    m_axe_speedT_lb->setText(QStringLiteral("测试速度:"));
    m_axe_speedT_lb->setFixedWidth(80);
    m_axe_speedT_sp->setRange(0,1000000);
    layoutMain->addWidget(wndSpeedT);

    QWidget	*wndSpeedHome=new QWidget(ui->widget);
    QHBoxLayout *layoutSpeedHome=new QHBoxLayout(wndSpeedHome);

    m_axe_home_lb	=new QLabel(wndSpeedHome);
    layoutSpeedHome->addWidget(m_axe_home_lb);
    m_axe_home_sp	=new QSpinBox(wndSpeedHome);
    layoutSpeedHome->addWidget(m_axe_home_sp);
    m_axe_home_lb->setText(QStringLiteral("归零速度:"));
    m_axe_home_lb->setFixedWidth(80);
    m_axe_home_sp->setRange(0,1000000);
    layoutMain->addWidget(wndSpeedHome);





    QWidget	*wndac=new QWidget(ui->widget);
    QHBoxLayout *layoutac=new QHBoxLayout(wndac);

    m_axe_ac_lb	=new QLabel(wndac);
    layoutac->addWidget(m_axe_ac_lb);
    m_axe_ac_sp	=new QSpinBox(wndac);
    layoutac->addWidget(m_axe_ac_sp);
    layoutMain->addWidget(wndac);

    m_axe_ac_lb->setText(QStringLiteral("加速度:"));
    m_axe_ac_lb->setFixedWidth(80);
    m_axe_ac_sp->setRange(0,1000000);


    QWidget	*wndpanel=new QWidget(ui->widget);
    QHBoxLayout *layoutpanel=new QHBoxLayout(wndpanel);

    m_axe_ok=new QPushButton(wndpanel);
    m_axe_ok->setText(QStringLiteral("确定"));
    layoutpanel->addWidget(m_axe_ok);
    m_axe_reset	=new QPushButton(wndpanel);
    m_axe_reset->setText(QStringLiteral("复位"));
    layoutpanel->addWidget(m_axe_reset);
    layoutMain->addWidget(wndpanel);

    connect(m_axe_ok,SIGNAL(clicked()),this,SLOT(on_bn_clicked_ok()));
    connect(m_axe_reset,SIGNAL(clicked()),this,SLOT(on_bn_clicked_reset()));



}
