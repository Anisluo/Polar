// LoadDll.h: interface for the CLoadDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADDLL_H__B8267873_59D6_11D5_B5A0_B42C742B6543__INCLUDED_)
#define AFX_LOADDLL_H__B8267873_59D6_11D5_B5A0_B42C742B6543__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
//DLL����ָ�����Ͷ���
//���ƿ��������ú���
typedef int (CALLBACK* LPFNDLL_auto_set)(void);
typedef int (CALLBACK* LPFNDLL_init_board)(void);
typedef int (CALLBACK* LPFNDLL_get_max_axe)(void);
typedef int (CALLBACK* LPFNDLL_get_board_num)(void);
typedef int (CALLBACK* LPFNDLL_get_axe)(int board_no);
typedef int (CALLBACK* LPFNDLL_set_outmode)(int ch,int mode,int logic);
typedef int (CALLBACK* LPFNDLL_set_home_mode)(int ch,int origin_mode);
typedef int (CALLBACK* LPFNDLL_set_maxspeed)(int ch , double speed);
typedef int (CALLBACK* LPFNDLL_set_conspeed)(int ch , double conspeed);
typedef double (CALLBACK* LPFNDLL_get_conspeed)(int ch);
typedef int (CALLBACK* LPFNDLL_set_profile)(int ch , double vl , double vh , double ad);
typedef int (CALLBACK* LPFNDLL_get_profile)(int ch , double *vl , double *vh , double *ad);
typedef int (CALLBACK* LPFNDLL_set_vector_conspeed)(double conspeed);
typedef int (CALLBACK* LPFNDLL_set_vector_profile)(double vec_vl , double vec_vh ,double vec_ad);
typedef double (CALLBACK* LPFNDLL_get_vector_conspeed)();
typedef int (CALLBACK* LPFNDLL_get_vector_profile)(double *vec_vl , double *vec_vh ,double *vec_ad);
typedef double (CALLBACK* LPFNDLL_get_rate)(int ch);

//�˶�ָ���
typedef int (CALLBACK* LPFNDLL_con_pmove)(int ch,long step);
typedef int (CALLBACK* LPFNDLL_fast_pmove)(int ch,long step);
typedef int (CALLBACK* LPFNDLL_con_pmove2)(int ch1,long step1,int ch2,long step2);
typedef int (CALLBACK* LPFNDLL_fast_pmove2)(int ch1,long step1,int ch2,long step2);
typedef int (CALLBACK* LPFNDLL_con_pmove3)(int ch1,long step1,int ch2,long step2,int ch3,long step3);
typedef int (CALLBACK* LPFNDLL_fast_pmove3)(int ch1,long step1,int ch2,long step2,int ch3,long step3);
typedef int (CALLBACK* LPFNDLL_con_pmove4)(int ch1,long step1,int ch2,long step2,int ch3,long step3,int ch4,long step4);
typedef int (CALLBACK* LPFNDLL_fast_pmove4)(int ch1,long step1,int ch2,long step2,int ch3,long step3,int ch4,long step4);
typedef int (CALLBACK* LPFNDLL_con_vmove)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_fast_vmove)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_con_vmove2)(int ch1,int dir1,int ch2,int dir2);
typedef int (CALLBACK* LPFNDLL_fast_vmove2)(int ch1,int dir1,int ch2,int dir2);
typedef int (CALLBACK* LPFNDLL_con_vmove3)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
typedef int (CALLBACK* LPFNDLL_fast_vmove3)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
typedef int (CALLBACK* LPFNDLL_con_vmove4)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);
typedef int (CALLBACK* LPFNDLL_fast_vmove4)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);
typedef int (CALLBACK* LPFNDLL_con_hmove)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_fast_hmove)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_con_hmove2)(int ch1,int dir1,int ch2,int dir2);
typedef int (CALLBACK* LPFNDLL_fast_hmove2)(int ch1,int dir1,int ch2,int dir2);
typedef int (CALLBACK* LPFNDLL_con_hmove3)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
typedef int (CALLBACK* LPFNDLL_fast_hmove3)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3);
typedef int (CALLBACK* LPFNDLL_con_hmove4)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);
typedef int (CALLBACK* LPFNDLL_fast_hmove4)(int ch1,int dir1,int ch2,int dir2,int ch3,int dir3,int ch4,int dir4);
typedef int (CALLBACK* LPFNDLL_con_line2)(int ch1,long pos1,int ch2, long pos2);
typedef int (CALLBACK* LPFNDLL_con_line3)(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3);
typedef int (CALLBACK* LPFNDLL_con_line4)(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3,int ch4,long pos4);
typedef int (CALLBACK* LPFNDLL_fast_line2)(int ch1,long pos1,int ch2, long pos2);
typedef int (CALLBACK* LPFNDLL_fast_line3)(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3);
typedef int (CALLBACK* LPFNDLL_fast_line4)(int ch1,long pos1,int ch2,long pos2,int ch3,long pos3,int ch4,long pos4);

//20080131,V220
typedef int (CALLBACK* LPFNDLL_change_pos)(int ch, long pos);

//�ƶ�����
typedef void (CALLBACK* LPFNDLL_sudden_stop)(int ch);
typedef void (CALLBACK* LPFNDLL_sudden_stop2)(int ch1,int ch2);
typedef void (CALLBACK* LPFNDLL_sudden_stop3)(int ch1,int ch2,int ch3);
typedef void (CALLBACK* LPFNDLL_sudden_stop4)(int ch1,int ch2,int ch3,int ch4);
typedef void (CALLBACK* LPFNDLL_decel_stop)(int ch);
typedef void (CALLBACK* LPFNDLL_decel_stop2)(int ch1,int ch2);
typedef void (CALLBACK* LPFNDLL_decel_stop3)(int ch1,int ch2,int ch3);
typedef void (CALLBACK* LPFNDLL_decel_stop4)(int ch1,int ch2,int ch3,int ch4);

//λ�ú�״̬���ú���
typedef long (CALLBACK* LPFNDLL_set_abs_pos)(int ch,long pos);
typedef int (CALLBACK* LPFNDLL_reset_pos)(int ch);
typedef int (CALLBACK* LPFNDLL_reset_enc_pos)(int ch);
typedef int (CALLBACK* LPFNDLL_reset_cmd_counter)();
typedef int (CALLBACK* LPFNDLL_set_getpos_mode)(int ch,int mode);
typedef int (CALLBACK* LPFNDLL_set_encoder_mode)(long ch,long mode,long multip,long count_unit);
typedef int (CALLBACK* LPFNDLL_set_dir)(int ch,int dir);
typedef int (CALLBACK* LPFNDLL_enable_sd)(int ch,int flag);
typedef int (CALLBACK* LPFNDLL_enable_el)(int ch,int flag);//flag--1,��Ч;flag--0,��Ч
typedef int (CALLBACK* LPFNDLL_enable_org)(int ch,int flag);//flag--1,��Ч;flag--0,��Ч
typedef int (CALLBACK* LPFNDLL_set_sd_logic)(int ch,int flag);
typedef int (CALLBACK* LPFNDLL_set_el_logic)(int ch,int flag);
typedef int (CALLBACK* LPFNDLL_set_org_logic)(int ch,int flag);
typedef int (CALLBACK* LPFNDLL_set_alm_logic)(int ch,int flag);
typedef int (CALLBACK* LPFNDLL_get_abs_pos)(int ch,long *pos);
typedef int (CALLBACK* LPFNDLL_get_rel_pos)(int ch,long *pos);
typedef int (CALLBACK* LPFNDLL_get_encoder)(int ch,long *count);
typedef long (CALLBACK* LPFNDLL_get_cur_dir)(int ch);

//״̬��ѯ����
typedef int (CALLBACK* LPFNDLL_check_status)(int ch);
typedef int (CALLBACK* LPFNDLL_check_done)(int ch);
typedef int (CALLBACK* LPFNDLL_check_limit)(int ch);
typedef int (CALLBACK* LPFNDLL_check_home)(int ch);
typedef int (CALLBACK* LPFNDLL_check_SD)(int ch);
typedef int (CALLBACK* LPFNDLL_check_alarm)(int ch);
typedef int (CALLBACK* LPFNDLL_get_cmd_counter)();

//I/O�ڲ�������
typedef int (CALLBACK* LPFNDLL_checkin_byte)(int cardno);
typedef int (CALLBACK* LPFNDLL_checkin_bit)(int cardno,int bitno);
typedef int (CALLBACK* LPFNDLL_outport_bit)(int cardno,int bitno,int status);
typedef int (CALLBACK* LPFNDLL_outport_byte)(int cardno,int bytedata);
typedef int (CALLBACK* LPFNDLL_check_SFR)(int cardno);

//��������
typedef int (CALLBACK* LPFNDLL_set_backlash)(int axis,int blash);
typedef int (CALLBACK* LPFNDLL_start_backlash)(int axis);
typedef int (CALLBACK* LPFNDLL_end_backlash)(int axis);
typedef int (CALLBACK* LPFNDLL_change_speed)(int ch,double speed);
typedef int (CALLBACK* LPFNDLL_change_accel)(int ch,double accel);
typedef int (CALLBACK* LPFNDLL_Outport)(int portid,unsigned char byte);
typedef int (CALLBACK* LPFNDLL_Inport)(int portid);
typedef int (CALLBACK* LPFNDLL_set_ramp_flag)(int flag);
typedef int (CALLBACK* LPFNDLL_get_lib_ver)(long* major,long *minor1,long *minor2);
typedef int (CALLBACK* LPFNDLL_get_sys_ver)(long* major,long *minor1,long *minor2);
typedef int (CALLBACK* LPFNDLL_get_card_ver)(long cardno,long *type,long* major,long *minor1,long *minor2);

//ͬ��λ�ÿ��ƺ���
typedef int (CALLBACK* LPFNDLL_enable_io_pos)(int cardno,int flag);
typedef int (CALLBACK* LPFNDLL_set_io_pos)(int ch,int open_pos,int close_pos);

//mpc.dll������װ��
class CLoadDll  
{
public:
	CLoadDll();
	virtual ~CLoadDll();
private:
	HINSTANCE hDLL;
	int LoadDllFun();
public:
	///////////////////////////////////
	//����ָ�붨��
	//���ƿ��������ú���
	LPFNDLL_auto_set auto_set;
	LPFNDLL_init_board init_board;
	LPFNDLL_get_max_axe get_max_axe;
	LPFNDLL_get_board_num get_board_num;
	LPFNDLL_get_axe get_axe;
	LPFNDLL_set_outmode set_outmode;
	LPFNDLL_set_home_mode set_home_mode;
	LPFNDLL_set_maxspeed set_maxspeed;
	LPFNDLL_set_conspeed set_conspeed;
	LPFNDLL_get_conspeed get_conspeed;
	LPFNDLL_set_profile set_profile;
	LPFNDLL_get_profile get_profile;
	LPFNDLL_set_vector_conspeed set_vector_conspeed;
	LPFNDLL_set_vector_profile set_vector_profile;
	LPFNDLL_get_vector_conspeed get_vector_conspeed;
	LPFNDLL_get_vector_profile get_vector_profile;
	LPFNDLL_get_rate get_rate;

	//�˶�����
	LPFNDLL_con_pmove con_pmove;
	LPFNDLL_fast_pmove fast_pmove;
	LPFNDLL_con_pmove2 con_pmove2;
	LPFNDLL_fast_pmove2 fast_pmove2;
	LPFNDLL_con_pmove3 con_pmove3;
	LPFNDLL_fast_pmove3 fast_pmove3;
	LPFNDLL_con_pmove4 con_pmove4;
	LPFNDLL_fast_pmove4 fast_pmove4;
	LPFNDLL_con_vmove con_vmove;
	LPFNDLL_fast_vmove fast_vmove;
	LPFNDLL_con_vmove2 con_vmove2;
	LPFNDLL_fast_vmove2 fast_vmove2;
	LPFNDLL_con_vmove3 con_vmove3;
	LPFNDLL_fast_vmove3 fast_vmove3;
	LPFNDLL_con_vmove4 con_vmove4;
	LPFNDLL_fast_vmove4 fast_vmove4;
	LPFNDLL_con_hmove con_hmove;
	LPFNDLL_fast_hmove fast_hmove;
	LPFNDLL_con_hmove2 con_hmove2;
	LPFNDLL_fast_hmove2 fast_hmove2;
	LPFNDLL_con_hmove3 con_hmove3;
	LPFNDLL_fast_hmove3 fast_hmove3;
	LPFNDLL_con_hmove4 con_hmove4;
	LPFNDLL_fast_hmove4 fast_hmove4;
	LPFNDLL_con_line2 con_line2;
	LPFNDLL_con_line3 con_line3;
	LPFNDLL_con_line4 con_line4;
	LPFNDLL_fast_line2 fast_line2;
	LPFNDLL_fast_line3 fast_line3;
	LPFNDLL_fast_line4 fast_line4;

	LPFNDLL_change_pos change_pos;
	//�ƶ�����
	LPFNDLL_sudden_stop sudden_stop;
	LPFNDLL_sudden_stop2 sudden_stop2;
	LPFNDLL_sudden_stop3 sudden_stop3;
	LPFNDLL_sudden_stop4 sudden_stop4;
	LPFNDLL_decel_stop decel_stop;
	LPFNDLL_decel_stop2 decel_stop2;
	LPFNDLL_decel_stop3 decel_stop3;
	LPFNDLL_decel_stop4 decel_stop4;
	
	//λ�ú�״̬���ú���
	LPFNDLL_set_abs_pos set_abs_pos;
	LPFNDLL_reset_pos reset_pos;
	LPFNDLL_reset_enc_pos reset_enc_pos;
	LPFNDLL_reset_cmd_counter reset_cmd_counter;
	LPFNDLL_set_getpos_mode set_getpos_mode;
	LPFNDLL_set_encoder_mode set_encoder_mode;
	LPFNDLL_set_dir set_dir;
	LPFNDLL_enable_sd enable_sd;
	LPFNDLL_enable_el enable_el;
	LPFNDLL_enable_org enable_org;
	LPFNDLL_set_sd_logic set_sd_logic;
	LPFNDLL_set_el_logic set_el_logic;
	LPFNDLL_set_org_logic set_org_logic;
	LPFNDLL_set_alm_logic set_alm_logic;
	LPFNDLL_get_abs_pos get_abs_pos;
	LPFNDLL_get_rel_pos get_rel_pos;
	LPFNDLL_get_encoder get_encoder;
	LPFNDLL_get_cur_dir get_cur_dir;

	//״̬��ѯ����
	LPFNDLL_check_status check_status;
	LPFNDLL_check_done check_done;
	LPFNDLL_check_limit check_limit;
	LPFNDLL_check_home check_home;
	LPFNDLL_check_SD check_SD;
	LPFNDLL_check_alarm check_alarm;
	LPFNDLL_get_cmd_counter get_cmd_counter;

	//I/O�ڲ�������
	LPFNDLL_checkin_byte checkin_byte;
	LPFNDLL_checkin_bit checkin_bit;
	LPFNDLL_outport_bit outport_bit;
	LPFNDLL_outport_byte outport_byte;
	LPFNDLL_check_SFR check_SFR;

	//��������
	LPFNDLL_set_backlash set_backlash;
	LPFNDLL_start_backlash start_backlash;
	LPFNDLL_end_backlash end_backlash;
	LPFNDLL_change_speed change_speed;
	LPFNDLL_change_accel change_accel;
	LPFNDLL_Outport Outport;
	LPFNDLL_Inport Inport;
	LPFNDLL_set_ramp_flag set_ramp_flag;
	LPFNDLL_get_lib_ver get_lib_ver;
	LPFNDLL_get_sys_ver get_sys_ver;
	LPFNDLL_get_card_ver get_card_ver;

	LPFNDLL_enable_io_pos enable_io_pos;
	LPFNDLL_set_io_pos set_io_pos;

};

#endif // !defined(AFX_LOADDLL_H__B8267873_59D6_11D5_B5A0_B42C742B6543__INCLUDED_)
