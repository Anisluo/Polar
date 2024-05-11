#include "movectrl.h"
#include"include/MPC.H"
#include<QDebug>
#include<QThread>
MoveCtrl* MoveCtrl::obj=nullptr;
MoveCtrl::MoveCtrl()
{
    if(auto_set()<=0){ qDebug()<<"no card";  return; }
    if(init_board()<=0){qDebug()<<"init error";return;}
//    set_io_status(1,1);
}

MoveCtrl::~MoveCtrl()
{
}

MoveCtrl* MoveCtrl::init()
{
    if(obj==nullptr)
    {
        obj=new MoveCtrl;
    }
    return obj;
}

int MoveCtrl::get_io_status(int port)
{
    return checkin_bit(1,port);
}

int MoveCtrl::set_io_status(int port,int status)
{
    return outport_bit(1,port,status);
}

void MoveCtrl::move_axe_nowait(AXE_CONFIG* curAxe,int steps,MOVESPEED speed)
{
    int mspeed=0;
    switch(speed)
    {
    case MOVESPEED::High: mspeed=curAxe->AXE_SPEED_HIGH; break;
    case MOVESPEED::Medium:mspeed=curAxe->AXE_SPEED_MEDIUM;break;
    case MOVESPEED::Low:mspeed=curAxe->AXE_SPEED_LOW;break;
    default:break;
    }

    int nSpeed=(int)(mspeed*curAxe->AXE_PERMM);
    set_profile(curAxe->AXE_ID,0,nSpeed,curAxe->AXE_PERMM*curAxe->AXE_AC_SPEED);//设置速度
    fast_vmove(curAxe->AXE_ID,steps);
}

void MoveCtrl::move_left(AXE_CONFIG* curAxe,MOVESPEED speed)
{
    if(check_done(curAxe->AXE_ID)!=0){return;}
    int steps=curAxe->AXE_DIR;
    move_axe_nowait(curAxe,steps,speed);

}
void MoveCtrl::move_right(AXE_CONFIG* curAxe,MOVESPEED speed)
{
    if(check_done(curAxe->AXE_ID)!=0){return;}
    int steps=-curAxe->AXE_DIR;
    move_axe_nowait(curAxe,steps,speed);
}


void MoveCtrl::move_home(AXE_CONFIG* curAxe)
{
    if(check_done(curAxe->AXE_ID)!=0){return;}
    int nSpeed=(int)(curAxe->AXE_SPEED_HOME*curAxe->AXE_PERMM);
    set_profile(curAxe->AXE_ID,0,nSpeed,curAxe->AXE_AC_SPEED*curAxe->AXE_PERMM);
    fast_hmove(curAxe->AXE_ID,curAxe->AXE_DIR);
}

void MoveCtrl::move_home_test(AXE_CONFIG* curAxe)
{
     if(check_done(curAxe->AXE_ID)!=0){return;}
    int nSpeed=(int)(curAxe->AXE_SPEED_TEST*curAxe->AXE_PERMM);
    set_profile(curAxe->AXE_ID,0,nSpeed,curAxe->AXE_AC_SPEED*curAxe->AXE_PERMM);
    fast_hmove(curAxe->AXE_ID,curAxe->AXE_DIR);
}


void MoveCtrl::waitfor_move_finish(AXE_CONFIG* curAxe)
{
    while(check_done(curAxe->AXE_ID)!=0) { QThread::msleep(10); }
}


void MoveCtrl::reset_axe(AXE_CONFIG* curAxe)
{
    reset_pos(curAxe->AXE_ID);
}

void MoveCtrl::stop_axe(AXE_CONFIG* curAxe)
{
    decel_stop(curAxe->AXE_ID);
}

void MoveCtrl::move_home_ext_test(AXE_CONFIG* curAxe)
{
    move_abs(curAxe,10);
    waitfor_move_finish(curAxe);
    enable_axe(curAxe,1);
    move_home_test(curAxe);
    waitfor_move_finish(curAxe);
}

void MoveCtrl::move_home_ext(AXE_CONFIG* curAxe)
{
    //    enable_axe(curAxe,0);//向极限位置运动
    //    move_home(curAxe);
    //    waitfor_move_finish(curAxe);
    //    reset_axe(curAxe);
    move_abs_home(curAxe,10);
    waitfor_move_finish(curAxe);
    enable_axe(curAxe,1);
    move_home(curAxe);
    waitfor_move_finish(curAxe);
    reset_axe(curAxe);
}

void MoveCtrl::enable_axe(AXE_CONFIG* curAxe,int status)
{
    enable_org(curAxe->AXE_ID,status);
    set_home_mode(curAxe->AXE_ID,0);//设置回零方
}

void MoveCtrl::move_stop(AXE_CONFIG* curAxe)
{
    decel_stop(curAxe->AXE_ID);
}

void MoveCtrl::move_abs(AXE_CONFIG* curAxe,double dm)
{
    if(check_done(curAxe->AXE_ID)!=0){return;}
    int nSpeed=(int)(curAxe->AXE_SPEED_TEST*curAxe->AXE_PERMM);//使用home移动
    set_profile(curAxe->AXE_ID,0,nSpeed,curAxe->AXE_AC_SPEED*curAxe->AXE_PERMM);
    long curPos=0;
    get_abs_pos(curAxe->AXE_ID,&curPos);
    if(curPos>limitValue)
    {
        curPos-=maxVal;
    }
//    double dist=dm;
    double dist = dm - ((double)curPos / curAxe->AXE_PERMM* (-curAxe->AXE_DIR));
    int steps=(int)(dist*curAxe->AXE_PERMM)*(-curAxe->AXE_DIR);
    fast_pmove(curAxe->AXE_ID,steps);

}

void MoveCtrl::move_abs_home(AXE_CONFIG* curAxe,double dm)
{
    if(check_done(curAxe->AXE_ID)!=0){return;}
    int nSpeed=(int)(curAxe->AXE_SPEED_TEST*curAxe->AXE_PERMM);//使用home移动
    set_profile(curAxe->AXE_ID,0,nSpeed,curAxe->AXE_AC_SPEED*curAxe->AXE_PERMM);
    long curPos=9;
    get_abs_pos(curAxe->AXE_ID,&curPos);
    if(curPos>limitValue)
    {
        curPos-=maxVal;
    }
    double dist = dm - ((double)curPos / curAxe->AXE_PERMM* (-curAxe->AXE_DIR));
    int steps=(int)(dist*curAxe->AXE_PERMM)*(-curAxe->AXE_DIR);
    fast_pmove(curAxe->AXE_ID,steps);

}

//获取当前坐标
void MoveCtrl::get_curpos(AXE_CONFIG* curAxe,double& x)
{
    long curPos=0;
    get_abs_pos(curAxe->AXE_ID,&curPos);
    if(curPos>limitValue)
    {
        curPos-=maxVal;
    }
    x=((double)curPos/curAxe->AXE_PERMM)*(-curAxe->AXE_DIR);
}



