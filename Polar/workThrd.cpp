
#include"workThrd.h"
#include<QMap>

//相机内容显示

void workThrd::task_generate_tmp(TASK_CONFIG* tsk)
{


    emit showMessage_tmp(QStringLiteral("归零......"));
    if(!is_generate_tmp){emit showMessage_tmp(QStringLiteral("停止!"));return;}
#ifndef DEBUG_VERSION
    mvctrl->move_home_ext(axe_cfg);
#endif


    QMap<int,double> key_value;
    TEMPLATE_CONFIG* tmp_cfg=tsk->tmp_cfg;
    datas.clear();//清空数据缓存
    for(int i=(tmp_cfg->angleStart*10);i<=(tmp_cfg->angleStop*10);i+=(tmp_cfg->angleStep*10))
    {
        if(!is_generate_tmp){emit showMessage_tmp(QStringLiteral("停止!"));return;}

        emit showMessage_tmp(QStringLiteral("移动......"));
#ifndef DEBUG_VERSION
        mvctrl->move_abs(axe_cfg,i*0.1);
        mvctrl->waitfor_move_finish(axe_cfg);//移动到指定角度
#endif

        emit showMessage_tmp(QStringLiteral("指定角度:")+QString::number(double(i*0.1),'f',1));
        emit sendCmd();
        while(datas.empty()) { QThread::msleep(10); }
        QByteArray data;
        while(!data.contains("END"))
        {
            if(!datas.empty())
            {
                data+=datas.dequeue();
            }
            QThread::msleep(50);
        }
        double lum=parselum(data);
        //        double lum=100;

        if(!is_generate_tmp){emit showMessage_tmp(QStringLiteral("停止!"));return;}
//        double contrast=1.0;
        emit update_tmp_lum_angle(double(i*0.1),lum);//更新angle and lum
        key_value.insert(i,lum);
    }

    if(!key_value.contains(tmp_cfg->angleStop*10))
    {
        int i=double(tmp_cfg->angleStop*10);

        if(!is_generate_tmp){emit showMessage_tmp(QStringLiteral("停止!"));return;}
        emit showMessage_tmp(QStringLiteral("移动......"));
#ifndef DEBUG_VERSION
        mvctrl->move_abs(axe_cfg,i*0.1);
        mvctrl->waitfor_move_finish(axe_cfg);//移动到指定角度
#endif
        emit showMessage_tmp(QStringLiteral("指定角度:")+QString::number(i*0.1));
        //        emit showMessage_tmp(QStringLiteral("移动到指定点"));
        emit sendCmd();
        while(datas.empty()) { QThread::msleep(10); }
        QByteArray data;
        while(!data.contains("END"))
        {
            if(!datas.empty())
            {
                data+=datas.dequeue();
            }
            QThread::msleep(50);
        }
        double lum=parselum(data);
//        double contrast=0.0;
        emit update_tmp_lum_angle(i*0.1,lum);//更新angle and lum
        key_value.insert(i,lum);
    }

    if(!is_generate_tmp){emit showMessage_tmp(QStringLiteral("停止!"));return;}
//    auto maxElement=std::max_element(key_value.begin(),key_value.end(),[](const auto& lhs,const auto &rhs){return lhs<rhs;});
    auto minElement=std::max_element(key_value.begin(),key_value.end(),[](const auto& lhs,const auto &rhs){return lhs>rhs;});
    double contrast_lum=1;
    if(tmp_cfg->contrast_index!=0)
    {
     contrast_lum=minElement.value()*tmp_cfg->contrast_index;
    }

    double minDifference=std::numeric_limits<double>::max();
    QMap<int ,double>::Iterator itor,closet_itor;
    for(itor=key_value.begin();itor!=key_value.end();itor++)
    {
        double difference=std::fabs(itor.value()-contrast_lum);
        if(difference<minDifference)
        {
            minDifference=difference;
            closet_itor=itor;
        }

    }

    emit update_tmp_contrast(minElement.value());//更新所有列的contrast参数
    //更新指定角度
    emit update_tmp_max_min_lumangle(closet_itor.key()*0.1,minElement.key()*0.1);
//    emit update_tmp_contrast_value(closet_itor.key()*0.1);
    double realContrast=closet_itor.value()/minElement.value();
    emit showMessage_tmp(QStringLiteral("模板生成完毕"));
    if((tmp_cfg->contrast_index/realContrast)>1.2)
    {
        emit showMessage_tmp(QStringLiteral("预设对比度过大,")+QStringLiteral("   实际对比度:")+QString::number(realContrast));
    }
#ifndef DEBUG_VERSION
    mvctrl->move_abs(axe_cfg,0);
#endif
}

void workThrd::task_single_test(TASK_CONFIG* tsk)
{
    emit showMessage(QStringLiteral("读取..."));
    datas.clear();//清空数据缓存
    if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}
//    TEMPLATE_CONFIG* tmp_cfg=tsk->tmp_cfg;
    emit sendCmd();
    while(datas.empty()) { QThread::msleep(10); }
    QByteArray data;
    while(!data.contains("END"))
    {
        if(!datas.empty())
        {
            data+=datas.dequeue();
        }
        QThread::msleep(50);
        if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}
    }
    double lum1=parselum(data);
    emit showMessage(QStringLiteral("读取完毕"));
    emit  update_single_result(lum1);
    if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}
    emit showMessage(QStringLiteral("单点测试结束"));
}



void workThrd::task_normal_test(TASK_CONFIG *tsk)
{

//    emit set_status(STATUS_ENUM::ok);
//    return;
    datas.clear();//清空数据缓存
    emit showMessage(QStringLiteral("移动......"));

    if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}
    TEMPLATE_CONFIG* tmp_cfg=tsk->tmp_cfg;
#ifndef DEBUG_VERSION
    mvctrl->move_abs(axe_cfg,tmp_cfg->angle_lmax);
    mvctrl->waitfor_move_finish(axe_cfg);//移动到指定角度
#endif
    emit showMessage(QStringLiteral("L角度:")+QString::number(tmp_cfg->angle_lmax));
    emit sendCmd();
    while(datas.empty()) { QThread::msleep(10); }
    QByteArray data;
    while(!data.contains("END"))
    {
        if(!datas.empty())
        {
            data+=datas.dequeue();
        }
        QThread::msleep(50);
        if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}
    }
    double lum1=parselum(data);
    //移动到指定点...................................
    emit showMessage(QStringLiteral("max读取完毕"));

    //移动到指定点...................................
    emit showMessage(QStringLiteral("移动......"));
#ifndef DEBUG_VERSION
    mvctrl->move_abs(axe_cfg,tmp_cfg->angle_lmin);
    mvctrl->waitfor_move_finish(axe_cfg);//移动到指定角度
#endif
    emit showMessage(QStringLiteral("Min角度:")+QString::number(tmp_cfg->angle_lmin));
    emit sendCmd();
    data.clear();
    while(datas.empty()) { QThread::msleep(10);

    if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}
    }
//    QByteArray data2;
    while(!data.contains("END"))
    {
        if(!datas.empty())
        {
            data+=datas.dequeue();
        }
        QThread::msleep(50);
    if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}
    }
    double lum2=parselum(data);

    RESULT_CONFIG* rst=new RESULT_CONFIG;
    rst->Angle1=tmp_cfg->angle_lmax;
    rst->Angle2=tmp_cfg->angle_lmin;
    rst->L1=lum1;
    rst->L2=lum2;
    if(rst->L2!=0)
    {
        rst->Contrast=rst->L1/rst->L2;
    }
    else{
        rst->Contrast=-1;
    }

//    //移动到指定点...................................
//    emit showMessage(QStringLiteral("移动......"));
//#ifndef DEBUG_VERSION
//    mvctrl->move_abs(axe_cfg,tmp_cfg->contrast_value);
//    mvctrl->waitfor_move_finish(axe_cfg);//移动到指定角度
//#endif
//    emit showMessage(QStringLiteral("指定角度:")+QString::number(tmp_cfg->contrast_value));
//    emit sendCmd();
//    data.clear();
//    while(datas.empty()) { QThread::msleep(10);

//    if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}
//    }
////    QByteArray data2;
//    while(!data.contains("END"))
//    {
//        if(!datas.empty())
//        {
//            data+=datas.dequeue();
//        }
//        QThread::msleep(50);
//    if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}
//    }
//    double lum3=parselum(data);
//    rst->Angle3=tmp_cfg->contrast_value;
//    rst->L3=lum3;
   emit updateResults(rst);
    //更新lum1  lum2
    mvctrl->move_abs(axe_cfg,0);//归零
//    mvctrl->move_home_ext_test(axe_cfg);
    if(!is_main_test){emit showMessage_tmp(QStringLiteral("停止!"));return;}

//    emit showMessage(QStringLiteral("结果保存至："));
    emit showMessage(QStringLiteral("测试结束"));
    //        emit updateResults()
}

void workThrd::task_move_home()
{

    mvctrl->move_home_ext(axe_cfg);
   emit showMessage(QStringLiteral("归零完成"));
}


//添加任务到task lists中
void workThrd::add_tasks(TASK_CONFIG* tsk)
{
    tskqueues.enqueue(tsk);
}

double workThrd::parselum(QByteArray data)
{
    QString str=data;
    QStringList stringList = str.split("\r\n", Qt::SkipEmptyParts);

    if(stringList.count()>4)
    {
        return stringList[4].toDouble();
    }
    else{
        return -1;
    }
}

void workThrd::addDatas(QByteArray data)
{
    datas.enqueue(data);
}


void workThrd::on_start_generate()
{
    is_generate_tmp=true;
}

void workThrd::on_start_main_test()
{
    is_main_test=true;
}


void workThrd::on_start_single_test()
{
    is_single_test=true;
}
void workThrd::on_stop_single_test()
{
    is_single_test=false;
}


void workThrd::on_stop_main_test()
{
    mvctrl->stop_axe(axe_cfg);
    is_main_test=false;
//    mvctrl->
}

void workThrd::on_stop_generate()
{
    mvctrl->stop_axe(axe_cfg);
    is_generate_tmp=false;
}



void workThrd::run()
{

    while(isStrabing)
    {

        //运行到指定点
        if(!tskqueues.empty())
        {
            TASK_CONFIG* tsk=tskqueues.dequeue();
            switch(tsk->task_type)
            {
            case TASK_ENUM::move_home:
                task_move_home();
                break;
            case TASK_ENUM::generate_tmps:
                task_generate_tmp(tsk);
                break;
            case TASK_ENUM::normal_test:
                task_normal_test(tsk);
                break;
            case TASK_ENUM::single_test:
                task_single_test(tsk);
                break;
            default:break;
            }
            delete tsk;//销毁tsk_config
        }
        QThread::msleep(20);//等待2ms
    }
}

void workThrd::init(MoveCtrl* mvc,AXE_CONFIG* axe)
{
    mvctrl=mvc;
    axe_cfg=axe;
    isStrabing=true;
}

void workThrd::exit()
{
    isStrabing=false;
}
