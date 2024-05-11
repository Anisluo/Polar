#ifndef CONIFG_H
#define CONIFG_H
#include<QString>

//#ifdef QT__DEBUG

//#endif

#define DEBUG
#ifdef DEBUG
#define DEBUG_VERSION
#define NO_CAMERA
#endif



typedef struct {
    QString		COM_NAME;
    unsigned int COM_BAUDRATE;
    unsigned int COM_DATABIT;
    unsigned int COM_PARITY;
    unsigned int COM_STOPBIT;
}COM_CONFIG;

typedef enum{
    unrun,
    waiting,
    ok,
    ng
}STATUS_ENUM;


typedef struct{
    int		MAIN_CAMERA_EXP_TIME;
}CAMERA_CONFIG;


typedef enum{
    Low,
    Medium,
    High
}MOVESPEED;

typedef struct{

    int		AXE_ID;
    int		AXE_DIR;
    int		AXE_PERMM;
    int		AXE_SPEED_LOW;
    int		AXE_SPEED_MEDIUM;
    int		AXE_SPEED_HIGH;
    int		AXE_SPEED_TEST;
    int		AXE_SPEED_HOME;
    int		AXE_AC_SPEED;

}AXE_CONFIG;

typedef struct{
    QString CONFIG_NAME;
    int		MAIN_CNT;
    int 	MAIN_PASS;
    int 	MAIN_NG;
    QString		MAIN_TEMPLATE_NAME;
    QString	MAIN_RESULT_NAME;
}MAIN_CONFIG;


typedef enum{
    move_home,
    single_test,
    normal_test,
    generate_tmps,
}TASK_ENUM;


typedef struct{
    QString tempName;
    double angleStart;
    double angleStep;
    double angleStop;
    double angle_lmax;
    double angle_lmin;
    double contrast_max;
    double contrast_min;
    double contrast_index;//指定index
    double contrast_value;//指定value
}TEMPLATE_CONFIG;


typedef struct{
    TASK_ENUM task_type;
    TEMPLATE_CONFIG* tmp_cfg;

}TASK_CONFIG;


typedef struct{
    double L1;
    double L2;
    double L3;
    double Angle1;
    double Angle2;
    double Contrast;
    double Angle3;
}RESULT_CONFIG;
#endif // CONIFG_H
