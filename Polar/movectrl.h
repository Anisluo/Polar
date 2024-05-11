#ifndef MOVECTRL_H
#define MOVECTRL_H

#include<QLibrary>
#include"Conifg.h"

class MoveCtrl
{
private:
    MoveCtrl();
public:
    ~MoveCtrl();


private:
    static MoveCtrl* obj;
public:
    static MoveCtrl* init();
    const long long limitValue = 100000000;//定义限制速度
    const long long maxVal = 4294967296;//定义最大速度

public:
    int get_io_status(int port);
    int set_io_status(int port,int status);
    void move_axe_nowait(AXE_CONFIG* curAxe,int steps,MOVESPEED speed);

    void move_left(AXE_CONFIG* curAxe,MOVESPEED speed);
    void move_right(AXE_CONFIG* curAxe,MOVESPEED speed);
    void move_home(AXE_CONFIG* curAxe);//直接返回org
    void move_home_test(AXE_CONFIG* curAxe);
    void move_home_ext(AXE_CONFIG* curAxe);//先接触极限，再返回org
    void move_home_ext_test(AXE_CONFIG* curAxe);
    void enable_axe(AXE_CONFIG* curAxe,int status);
    void move_stop(AXE_CONFIG* curAxe);
    void move_abs(AXE_CONFIG* curAxe,double dm);
    void move_abs_home(AXE_CONFIG* curAxe,double dm);
    void get_curpos(AXE_CONFIG* curAxe,double& x);
    void waitfor_move_finish(AXE_CONFIG* curAxe);
    void reset_axe(AXE_CONFIG* curAxe);
    void stop_axe(AXE_CONFIG* curAxe);

};

#endif // MOVECTRL_H
