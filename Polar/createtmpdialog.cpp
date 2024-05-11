#include "createtmpdialog.h"
#include "ui_createtmpdialog.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QScrollArea>
#include<QHeaderView>

createTmpDialog::createTmpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createTmpDialog)
{
    ui->setupUi(this);
    initWidget();
    tmp_cfg=new TEMPLATE_CONFIG;
//    tmp_
//    tmp_c
}

createTmpDialog::~createTmpDialog()
{
    delete ui;
}

void createTmpDialog::initWidget()
{
    QHBoxLayout* layoutMain=new QHBoxLayout(ui->widget);
    QScrollArea* leftArea=new QScrollArea(ui->widget);
    QScrollArea* rightArea=new QScrollArea(ui->widget);
    layoutMain->addWidget(leftArea,2);
    layoutMain->addWidget(rightArea,3);

    QVBoxLayout* layoutLeft=new QVBoxLayout(leftArea);
    QVBoxLayout* layoutRight=new QVBoxLayout(rightArea);


    //模板名称
    QWidget* tmp_tmpname_wnd=new QWidget(leftArea);
    QHBoxLayout* layouttmpname=new QHBoxLayout(tmp_tmpname_wnd);
    tmp_tmpname_lb=new QLabel(tmp_tmpname_wnd);
    tmp_tmpname_lb->setText(QStringLiteral("模板名称:"));
    tmp_tmpname_ledit=new QLineEdit(tmp_tmpname_wnd);
    layouttmpname->addWidget(tmp_tmpname_lb);
    layouttmpname->addWidget(tmp_tmpname_ledit);
    layoutLeft->addWidget(tmp_tmpname_wnd);

    //模板起始角
    QWidget* tmp_start_wnd=new QWidget(leftArea);
    QHBoxLayout* layoutstart=new QHBoxLayout(tmp_start_wnd);
    tmp_start_lb=new QLabel(tmp_start_wnd);
    tmp_start_lb->setText(QStringLiteral("开始角度:"));
    tmp_start_sp=new QDoubleSpinBox(tmp_start_wnd);
    tmp_start_sp->setRange(-1000.0,1000.0);
    tmp_start_sp->setDecimals(1);
    layoutstart->addWidget(tmp_start_lb);
    layoutstart->addWidget(tmp_start_sp);
    layoutLeft->addWidget(tmp_start_wnd);

    //模板起始角
    QWidget* tmp_step_wnd=new QWidget(leftArea);
    QHBoxLayout* layoutstep=new QHBoxLayout(tmp_step_wnd);
    tmp_step_lb=new QLabel(tmp_step_wnd);
    tmp_step_lb->setText(QStringLiteral("步长:"));
    //    layoutstart->addWidget(tmp_start_lb);
    tmp_step_sp=new QDoubleSpinBox(tmp_step_wnd);
    tmp_step_sp->setRange(0.0,1000.0);
    tmp_step_sp->setDecimals(1);
    layoutstep->addWidget(tmp_step_lb);
    layoutstep->addWidget(tmp_step_sp);
    layoutLeft->addWidget(tmp_step_wnd);

    QWidget* tmp_stop_wnd=new QWidget(leftArea);
    QHBoxLayout* layoutstop=new QHBoxLayout(tmp_stop_wnd);
    tmp_stop_lb=new QLabel(tmp_stop_wnd);
    tmp_stop_lb->setText(QStringLiteral("终止角度:"));
    tmp_stop_sp=new QDoubleSpinBox(tmp_stop_wnd);
    tmp_stop_sp->setDecimals(1);
    tmp_stop_sp->setRange(-1000.0,1000.0);
    layoutstop->addWidget(tmp_stop_lb);
    layoutstop->addWidget(tmp_stop_sp);
    layoutLeft->addWidget(tmp_stop_wnd);


    QWidget* tmp_contrast_angle_wnd=new QWidget(leftArea);
    QHBoxLayout* layout_contrast_angle=new QHBoxLayout(tmp_contrast_angle_wnd);

    tmp_contrast_lb=new QLabel(tmp_contrast_angle_wnd);
    tmp_contrast_lb->setText(QStringLiteral("预设对比度:"));
    tmp_contrast_sp=new QDoubleSpinBox(tmp_contrast_angle_wnd);
    tmp_contrast_sp->setRange(-9999999,9999999);
    tmp_contrast_sp->setDecimals(3);
//    tmp_contrast_angle_lb=new QLabel(tmp_contrast_angle_wnd);
//    tmp_contrast_angle_sp=new QDoubleSpinBox(tmp_contrast_angle_wnd);
//    tmp_contrast_angle_lb->setText(QStringLiteral("角度:"));
//    tmp_contrast_angle_sp->setDecimals(1);
//    tmp_contrast_angle_sp->setRange(-1000,1000);
    layout_contrast_angle->addWidget(tmp_contrast_lb);
    layout_contrast_angle->addWidget(tmp_contrast_sp);
//    layout_contrast_angle->addSpacing(20);
//    layout_contrast_angle->addWidget(tmp_contrast_angle_lb);
//    layout_contrast_angle->addWidget(tmp_contrast_angle_sp);
    layoutLeft->addWidget(tmp_contrast_angle_wnd);



    //最亮点
    QWidget* tmp_lmax_wnd=new QWidget(leftArea);
    QHBoxLayout* layoutlmax=new QHBoxLayout(tmp_lmax_wnd);
    tmp_lmax_lb=new QLabel(tmp_lmax_wnd);
    tmp_lmax_lb->setText(QStringLiteral("L角度:"));
    tmp_lmax_sp=new QDoubleSpinBox(tmp_lmax_wnd);
//    tmp_lmax_sp->setFixedWidth(50);
    tmp_lmax_sp->setRange(-1000.0,1000.0);
    tmp_lmax_sp->setDecimals(1);
    layoutlmax->addWidget(tmp_lmax_lb);
    layoutlmax->addWidget(tmp_lmax_sp);
    layoutLeft->addWidget(tmp_lmax_wnd);

    QWidget* tmp_lmin_wnd=new QWidget(leftArea);
    QHBoxLayout* layoutlmin=new QHBoxLayout(tmp_lmin_wnd);
    tmp_lmin_lb=new QLabel(tmp_lmin_wnd);
    tmp_lmin_lb->setText(QStringLiteral("Lmin角度:"));
    tmp_lmin_sp=new QDoubleSpinBox(tmp_lmin_wnd);
    tmp_lmin_sp->setRange(-1000.0,1000.0);
    tmp_lmin_sp->setDecimals(1);
//    tmp_lmin_sp->setFixedWidth(50);
    layoutlmin->addWidget(tmp_lmin_lb);
    layoutlmin->addWidget(tmp_lmin_sp);
    layoutLeft->addWidget(tmp_lmin_wnd);

    QWidget* tmp_ctrst_wnd=new QWidget(leftArea);
    QHBoxLayout* layoutCtrst=new QHBoxLayout(tmp_ctrst_wnd);
    tmp_ctrst_lb=new QLabel(tmp_ctrst_wnd);
    tmp_ctrst_lb->setText(QStringLiteral("对比度范围"));
    tmp_ctrst_max_sp=new QDoubleSpinBox(tmp_ctrst_wnd);
    tmp_ctrst_min_sp=new QDoubleSpinBox(tmp_ctrst_wnd);
    tmp_ctrst_max_sp->setRange(-10000000.0,10000000.0);
    tmp_ctrst_min_sp->setRange(-10000000.0,10000000.0);

    tmp_ctrst_max_sp->setFixedWidth(90);
    tmp_ctrst_min_sp->setFixedWidth(90);
    QLabel* lb_to=new QLabel(tmp_ctrst_wnd);
    lb_to->setText("~");
    layoutCtrst->addWidget(tmp_ctrst_lb);
    layoutCtrst->addSpacing(10);
    layoutCtrst->addWidget(tmp_ctrst_min_sp);
    layoutCtrst->addSpacing(10);
    layoutCtrst->addWidget(lb_to);
    layoutCtrst->addWidget(tmp_ctrst_max_sp);
    layoutLeft->addWidget(tmp_ctrst_wnd);


    QWidget* tmp_gen_wnd=new QWidget(leftArea);
    QHBoxLayout* layoutgen=new QHBoxLayout(tmp_gen_wnd);
    tmp_generate_btn=new QPushButton(tmp_gen_wnd);
    tmp_stopgen_btn=new QPushButton(tmp_gen_wnd);

    tmp_generate_btn->setText(QStringLiteral("生成模板"));
    tmp_stopgen_btn->setText(QStringLiteral("停止生成"));
    connect(tmp_generate_btn,SIGNAL(clicked()),this,SLOT(on_generate_tmps()));


    layoutgen->addWidget(tmp_generate_btn);
    layoutgen->addWidget(tmp_stopgen_btn);
    layoutLeft->addWidget(tmp_gen_wnd);

    QWidget* tmp_save_wnd=new QWidget(leftArea);
    QHBoxLayout* layoutsave=new QHBoxLayout(tmp_save_wnd);
    tmp_save_btn=new QPushButton(tmp_save_wnd);
    tmp_clear_btn=new QPushButton(tmp_save_wnd);

    tmp_save_btn->setText(QStringLiteral("确认"));
    connect(tmp_save_btn,SIGNAL(clicked()),this,SLOT(on_save_tmps()));
    tmp_clear_btn->setText(QStringLiteral("清空模板"));
    connect(tmp_clear_btn,SIGNAL(clicked()),this,SLOT(on_clear_tmps()));
    connect(tmp_stopgen_btn,SIGNAL(clicked()),this,SLOT(on_clicked_stop()));

    layoutsave->addWidget(tmp_save_btn);
    layoutsave->addWidget(tmp_clear_btn);
    layoutLeft->addWidget(tmp_save_wnd);

    QWidget* tmp_loadsave_wnd=new QWidget(leftArea);
    QHBoxLayout* layoutloadsave=new QHBoxLayout(tmp_loadsave_wnd);
    tmp_loadtmp=new QPushButton(tmp_loadsave_wnd);
    tmp_savetmp=new QPushButton(tmp_loadsave_wnd);

    tmp_loadtmp->setText(QStringLiteral("导入模板"));
    tmp_savetmp->setText(QStringLiteral("导出模板"));

    //导入配置，导出配置
    connect(tmp_loadtmp,SIGNAL(clicked()),this,SLOT(on_clicked_loadtmp()));
    connect(tmp_savetmp,SIGNAL(clicked()),this,SLOT(on_clicked_savetmp()));

    layoutloadsave->addWidget(tmp_loadtmp);
    layoutloadsave->addWidget(tmp_savetmp);
    layoutLeft->addWidget(tmp_loadsave_wnd);


    tmp_table=new QTableWidget(rightArea);
    layoutRight->addWidget(tmp_table);
    tmp_status=new QLabel(rightArea);
    layoutRight->addWidget(tmp_status);
    tmp_status->setFixedHeight(40);

    tmp_table->setColumnCount(4);
    QStringList headText;
    headText << "Item" << "Angle"<< "Luminance"<<"Contrast";
    tmp_table->setHorizontalHeaderLabels(headText);
    tmp_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    tmp_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tmp_table->setSelectionMode(QAbstractItemView::SingleSelection);
    //    main_table->horizontalHeader()->setSectionResizeMode(QHeaderView::str);
    tmp_table->setAlternatingRowColors(true);
    tmp_table->verticalHeader()->setVisible(false);
//    tmp_table->setau

}


void createTmpDialog::update_data_from_ui()
{
    tmp_cfg->angleStart=tmp_start_sp->value();
    tmp_cfg->angleStop=tmp_stop_sp->value();
    tmp_cfg->angleStep=tmp_step_sp->value();
    tmp_cfg->tempName=tmp_tmpname_ledit->text();
    tmp_cfg->angle_lmax=tmp_lmax_sp->value();
    tmp_cfg->angle_lmin=tmp_lmin_sp->value();
    tmp_cfg->contrast_max=tmp_ctrst_max_sp->value();
    tmp_cfg->contrast_min=tmp_ctrst_min_sp->value();

    //配置格式
    tmp_cfg->contrast_index=tmp_contrast_sp->value();
//    tmp_cfg->contrast_value=tmp_contrast_angle_sp->value();
}

/*
void createTmpDialog::loadConfig(sqlHelper* sql_helper,TEMPLATE_CONFIG* tmp)
{
    cur_tmp=tmp;//当前模板
    tmp_cfg->angleStart=tmp->angleStart;
    tmp_cfg->angleStep=tmp->angleStep;
    tmp_cfg->angleStop=tmp->angleStop;
    tmp_cfg->angle_lmax=tmp->angle_lmax;
    tmp_cfg->angle_lmin=tmp->angle_lmin;
    tmp_cfg->tempName=tmp->tempName;
    tmp_cfg->contrast_max=tmp->contrast_max;
    tmp_cfg->contrast_min=tmp->contrast_min;

    sql=sql_helper;
    update_ui_from_data();
}
*/

void createTmpDialog::loadConfig(TEMPLATE_CONFIG* tmp)
{
    cur_tmp=tmp;//当前模板
    tmp_cfg->angleStart=tmp->angleStart;
    tmp_cfg->angleStep=tmp->angleStep;
    tmp_cfg->angleStop=tmp->angleStop;
    tmp_cfg->angle_lmax=tmp->angle_lmax;
    tmp_cfg->angle_lmin=tmp->angle_lmin;
    tmp_cfg->tempName=tmp->tempName;
    tmp_cfg->contrast_max=tmp->contrast_max;
    tmp_cfg->contrast_min=tmp->contrast_min;

    tmp_cfg->contrast_index=tmp->contrast_index;
//    tmp_cfg->contrast_value=tmp->contrast_value;
//    sql=sql_helper;
    update_ui_from_data();
}





void createTmpDialog::update_ui_from_data()
{
    tmp_start_sp->setValue(tmp_cfg->angleStart);
    tmp_stop_sp->setValue(tmp_cfg->angleStop);
    tmp_step_sp->setValue(tmp_cfg->angleStep);
    tmp_lmax_sp->setValue(tmp_cfg->angle_lmax);
    tmp_lmin_sp->setValue(tmp_cfg->angle_lmin);
    tmp_tmpname_ledit->setText(tmp_cfg->tempName);

    tmp_ctrst_max_sp->setValue(tmp_cfg->contrast_max);
    tmp_ctrst_min_sp->setValue(tmp_cfg->contrast_min);

    tmp_contrast_sp->setValue(tmp_cfg->contrast_index);
//    tmp_contrast_angle_sp->setValue(tmp_cfg->contrast_value);

}
void createTmpDialog::on_clear_tmps()
{
    tmp_table->setRowCount(0);
    tmp_lmax_sp->setValue(0);
    tmp_lmin_sp->setValue(0);
}

//停止生成
void createTmpDialog::on_clicked_stop()
{
    emit on_stop_generate();
}


void createTmpDialog::on_save_tmps()
{
    update_data_from_ui();
    if(tmp_cfg->tempName=="") { showMessage(QStringLiteral("请填入模板名称!")); return; }
    else{
    //更新当前template
    cur_tmp->angleStart=tmp_cfg->angleStart;
    cur_tmp->angleStep=tmp_cfg->angleStep;
    cur_tmp->angleStop=tmp_cfg->angleStop;
    cur_tmp->angle_lmax=tmp_cfg->angle_lmax;
    cur_tmp->angle_lmin=tmp_cfg->angle_lmin;
    cur_tmp->tempName=tmp_cfg->tempName;
    cur_tmp->contrast_max=tmp_cfg->contrast_max;
    cur_tmp->contrast_min=tmp_cfg->contrast_min;

    cur_tmp->contrast_index=tmp_cfg->contrast_index;
//    cur_tmp->contrast_value=tmp_cfg->contrast_value;


    showMessage(QStringLiteral("保存模板:")+tmp_cfg->tempName);
//    sql->saveConfig(tmp_cfg);
    emit update_main_tmp_name(tmp_cfg->tempName);
    this->close();
    }
}


//生成模板
void createTmpDialog::on_generate_tmps()
{
    showMessage(QStringLiteral("开始生成模板......"));
    update_data_from_ui();
    emit on_start_generate();
    emit  add_template(tmp_cfg);
}
void createTmpDialog::showMessage(const QString& msg)
{
    QString str=">>"+msg;
    tmp_status->setText(str);
}

void createTmpDialog::update_tmp_max_min_lumangle(double max,double min)
{
    tmp_lmax_sp->setValue(max);
    tmp_lmin_sp->setValue(min);
}

void createTmpDialog::update_tmp_contrast_value(double value)
{
    tmp_contrast_angle_sp->setValue(value);
}

//导入模板
void createTmpDialog::on_clicked_loadtmp()
{

    QString selectFile=QFileDialog::getOpenFileName(NULL,QStringLiteral("选择文件"),"/","Files (*.xml)");
    {
        loadConfigXML(tmp_cfg,selectFile);
    }
//    loadConfig(tmp_cfg);
    update_ui_from_data();
    //导入文件至xml文件
}

//导出模板
void createTmpDialog::on_clicked_savetmp()
{

    update_data_from_ui();
    if(tmp_cfg->tempName=="") { showMessage(QStringLiteral("请填入模板名称!")); return; }
    else{
        //更新当前template
        cur_tmp->angleStart=tmp_cfg->angleStart;
        cur_tmp->angleStep=tmp_cfg->angleStep;
        cur_tmp->angleStop=tmp_cfg->angleStop;
        cur_tmp->angle_lmax=tmp_cfg->angle_lmax;
        cur_tmp->angle_lmin=tmp_cfg->angle_lmin;
        cur_tmp->tempName=tmp_cfg->tempName;
        cur_tmp->contrast_max=tmp_cfg->contrast_max;
        cur_tmp->contrast_min=tmp_cfg->contrast_min;
        showMessage(QStringLiteral("保存模板:")+tmp_cfg->tempName);
        //    sql->saveConfig(tmp_cfg);
        emit update_main_tmp_name(tmp_cfg->tempName);
        QString selectedFile = QFileDialog::getSaveFileName(this, QStringLiteral("保存文件"), "/", "Text Files (*.xml)");
        if (!selectedFile.isEmpty())
        {
            //保存参数至xml配置文件
            saveConfigXML(tmp_cfg,selectedFile);
        }
    }
}


//导入配置文件
void createTmpDialog::saveConfigXML(TEMPLATE_CONFIG* config,const QString& filename)
{
    QFile file(filename);
       if (!file.open(QIODevice::WriteOnly)) {
           return ;
       }

       QXmlStreamWriter writer(&file);
       writer.setAutoFormatting(true);
       writer.writeStartDocument();
       writer.writeStartElement("TEMPLATE_CONFIG");
       writer.writeTextElement("tempName", config->tempName);
       writer.writeTextElement("angleStart", QString::number(config->angleStart));
       writer.writeTextElement("angleStep", QString::number(config->angleStep));

       writer.writeTextElement("angleStop", QString::number(config->angleStop));
       writer.writeTextElement("angle_lmax", QString::number(config->angle_lmax));
       writer.writeTextElement("angle_lmin", QString::number(config->angle_lmin));
       writer.writeTextElement("contrast_max", QString::number(config->contrast_max));
       writer.writeTextElement("contrast_min", QString::number(config->contrast_min));
       writer.writeTextElement("contrast_index", QString::number(config->contrast_index));
       writer.writeTextElement("contrast_value", QString::number(config->contrast_value));
       // 其他字段类似
       writer.writeEndElement();
       writer.writeEndDocument();
       file.close();
}



//保存xml文件
void createTmpDialog::loadConfigXML(TEMPLATE_CONFIG* config,const QString& filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return ;
    }

    QXmlStreamReader reader(&file);
    while (!reader.atEnd() && !reader.hasError()) {
        if (reader.isStartElement() && reader.name() == "TEMPLATE_CONFIG") {
            while (reader.readNextStartElement()) {
                if (reader.name() == "tempName") {
                    config->tempName = reader.readElementText();
                } else if (reader.name() == "angleStart") {
                    config->angleStart = reader.readElementText().toDouble();
                }  else if (reader.name() == "angleStep") {
                    config->angleStep = reader.readElementText().toDouble();
                }
                else if (reader.name() == "angleStop") {
                    config->angleStop = reader.readElementText().toDouble();
                } else if (reader.name() == "angle_lmax") {
                    config->angle_lmax = reader.readElementText().toDouble();
                } else if (reader.name() == "angle_lmin") {
                    config->angle_lmin = reader.readElementText().toDouble();
                } else if (reader.name() == "contrast_max") {
                    config->contrast_max = reader.readElementText().toDouble();
                }else if (reader.name() == "contrast_min") {
                    config->contrast_min = reader.readElementText().toDouble();
                }else if(reader.name()=="contrast_index"){
                    config->contrast_index = reader.readElementText().toDouble();
                }
                else if(reader.name()=="contrast_value")
                {
                    config->contrast_value=reader.readElementText().toDouble();
                }
                else{}
                // 其他字段类似
            }
        }
        reader.readNext();
    }

    file.close();
}


//更新所有列的数据
void createTmpDialog::update_tmp_contrast(double minLum)
{
    int cnt=tmp_table->rowCount();
    if(minLum==0){minLum=1;}
    for (int row = 0; row < cnt; ++row) {
        QTableWidgetItem* item = tmp_table->item(row, 2);
        if (item) {
            double value = item->text().toDouble() /minLum;
            tmp_table->setItem(row, 3, new QTableWidgetItem(QString::number(value)));
        }
    }
}



void createTmpDialog::update_tmp_lum_angle(double angle,double lum)
{
    int index=tmp_table->rowCount();
    tmp_table->setRowCount(index+1);
    QTableWidgetItem *itemID = new QTableWidgetItem(QString::number(index+1));
    QTableWidgetItem *itemA1 = new QTableWidgetItem(QString::number(angle,'f',1));
    QTableWidgetItem *itemL1 = new QTableWidgetItem(QString::number(lum,'f',3));
    QTableWidgetItem *itemContrast = new QTableWidgetItem();
    tmp_table->setItem(index,0,itemID);
    tmp_table->setItem(index,1,itemA1);
    tmp_table->setItem(index,2,itemL1);
    tmp_table->setItem(index,3,itemContrast);
    tmp_table->scrollToBottom();
}
