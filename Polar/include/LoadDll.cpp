// LoadDll.cpp: implementation of the CLoadDll class.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
#includevduuadDll.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoadDll::CLoadDll()
{
	LoadDllFun();			//加载DLL
}

CLoadDll::~CLoadDll()
{
	if (hDLL != NULL)
	{
		FreeLibrary(hDLL);	//释放DLL
	}
}

int CLoadDll::LoadDllFun()
{
	hDLL = LoadLibrary("MPC08");	//加载mpc07.dll
	if (hDLL != NULL)
	{
		///////////////////////////////////////////////////////////
		//以下取得各个DLL函数指针
		auto_set = (LPFNDLL_auto_set)GetProcAddress(hDLL,"auto_set");
		init_board = (LPFNDLL_init_board)GetProcAddress(hDLL,"init_board");
		get_max_axe = (LPFNDLL_get_max_axe)GetProcAddress(hDLL,"get_max_axe");
		get_board_num = (LPFNDLL_get_board_num)GetProcAddress(hDLL,"get_board_num");
		get_axe = (LPFNDLL_get_axe)GetProcAddress(hDLL,"get_axe");
		set_outmode = (LPFNDLL_set_outmode)GetProcAddress(hDLL,"set_outmode");
		set_home_mode = (LPFNDLL_set_home_mode)GetProcAddress(hDLL,"set_home_mode");
		set_maxspeed = (LPFNDLL_set_maxspeed)GetProcAddress(hDLL,"set_maxspeed");
		set_conspeed = (LPFNDLL_set_conspeed)GetProcAddress(hDLL,"set_conspeed");
		get_conspeed = (LPFNDLL_get_conspeed)GetProcAddress(hDLL,"get_conspeed");
		set_profile = (LPFNDLL_set_profile)GetProcAddress(hDLL,"set_profile");
		get_profile = (LPFNDLL_get_profile)GetProcAddress(hDLL,"get_profile");
		set_vector_conspeed = (LPFNDLL_set_vector_conspeed)GetProcAddress(hDLL,"set_vector_conspeed");
		set_vector_profile = (LPFNDLL_set_vector_profile)GetProcAddress(hDLL,"set_vector_profile");
		get_vector_conspeed = (LPFNDLL_get_vector_conspeed)GetProcAddress(hDLL,"get_vector_conspeed");
		get_vector_profile = (LPFNDLL_get_vector_profile)GetProcAddress(hDLL,"get_vector_profile");
		get_rate = (LPFNDLL_get_rate)GetProcAddress(hDLL,"get_rate");

		con_pmove = (LPFNDLL_con_pmove)GetProcAddress(hDLL,"con_pmove");
		fast_pmove = (LPFNDLL_fast_pmove)GetProcAddress(hDLL,"fast_pmove");
		con_pmove2 = (LPFNDLL_con_pmove2)GetProcAddress(hDLL,"con_pmove2");
		fast_pmove2 = (LPFNDLL_fast_pmove2)GetProcAddress(hDLL,"fast_pmove2");
		con_pmove3 = (LPFNDLL_con_pmove3)GetProcAddress(hDLL,"con_pmove3");
		fast_pmove3 = (LPFNDLL_fast_pmove3)GetProcAddress(hDLL,"fast_pmove3");
		con_pmove4 = (LPFNDLL_con_pmove4)GetProcAddress(hDLL,"con_pmove4");
		fast_pmove4 = (LPFNDLL_fast_pmove4)GetProcAddress(hDLL,"fast_pmove4");
		con_vmove = (LPFNDLL_con_vmove)GetProcAddress(hDLL,"con_vmove");
		fast_vmove = (LPFNDLL_fast_vmove)GetProcAddress(hDLL,"fast_vmove");
		con_vmove2 = (LPFNDLL_con_vmove2)GetProcAddress(hDLL,"con_vmove2");
		fast_vmove2 = (LPFNDLL_fast_vmove2)GetProcAddress(hDLL,"fast_vmove2");
		con_vmove3 = (LPFNDLL_con_vmove3)GetProcAddress(hDLL,"con_vmove3");
		fast_vmove3 = (LPFNDLL_fast_vmove3)GetProcAddress(hDLL,"fast_vmove3");
		con_vmove4 = (LPFNDLL_con_vmove4)GetProcAddress(hDLL,"con_vmove4");
		fast_vmove4 = (LPFNDLL_fast_vmove4)GetProcAddress(hDLL,"fast_vmove4");
		con_hmove = (LPFNDLL_con_hmove)GetProcAddress(hDLL,"con_hmove");
		fast_hmove = (LPFNDLL_fast_hmove)GetProcAddress(hDLL,"fast_hmove");
		con_hmove2 = (LPFNDLL_con_hmove2)GetProcAddress(hDLL,"con_hmove2");
		fast_hmove2 = (LPFNDLL_fast_hmove2)GetProcAddress(hDLL,"fast_hmove2");
		con_hmove3 = (LPFNDLL_con_hmove3)GetProcAddress(hDLL,"con_hmove3");
		fast_hmove3 = (LPFNDLL_fast_hmove3)GetProcAddress(hDLL,"fast_hmove3");
		con_hmove4 = (LPFNDLL_con_hmove4)GetProcAddress(hDLL,"con_hmove4");
		fast_hmove4 = (LPFNDLL_fast_hmove4)GetProcAddress(hDLL,"fast_hmove4");
		con_line2 = (LPFNDLL_con_line2)GetProcAddress(hDLL,"con_line2");
		con_line3 = (LPFNDLL_con_line3)GetProcAddress(hDLL,"con_line3");
		con_line4 = (LPFNDLL_con_line4)GetProcAddress(hDLL,"con_line4");
		fast_line2 = (LPFNDLL_fast_line2)GetProcAddress(hDLL,"fast_line2");
		fast_line3 = (LPFNDLL_fast_line3)GetProcAddress(hDLL,"fast_line3");
		fast_line4 = (LPFNDLL_fast_line4)GetProcAddress(hDLL,"fast_line4");

		change_pos = (LPFNDLL_change_pos)GetProcAddress(hDLL,"change_pos");

		//制动函数
		sudden_stop = (LPFNDLL_sudden_stop)GetProcAddress(hDLL,"sudden_stop");
		sudden_stop2 = (LPFNDLL_sudden_stop2)GetProcAddress(hDLL,"sudden_stop2");
		sudden_stop3 = (LPFNDLL_sudden_stop3)GetProcAddress(hDLL,"sudden_stop3");
		sudden_stop4 = (LPFNDLL_sudden_stop4)GetProcAddress(hDLL,"sudden_stop4");
		decel_stop = (LPFNDLL_decel_stop)GetProcAddress(hDLL,"decel_stop");
		decel_stop2 = (LPFNDLL_decel_stop2)GetProcAddress(hDLL,"decel_stop2");
		decel_stop3 = (LPFNDLL_decel_stop3)GetProcAddress(hDLL,"decel_stop3");
		decel_stop4 = (LPFNDLL_decel_stop4)GetProcAddress(hDLL,"decel_stop4");

		//位置和状态设置函数
		set_abs_pos = (LPFNDLL_set_abs_pos)GetProcAddress(hDLL,"set_abs_pos");
		reset_pos = (LPFNDLL_reset_pos)GetProcAddress(hDLL,"reset_pos");
		reset_enc_pos = (LPFNDLL_reset_enc_pos)GetProcAddress(hDLL,"reset_enc_pos");
		reset_cmd_counter = (LPFNDLL_reset_cmd_counter)GetProcAddress(hDLL,"reset_cmd_counter");
		set_getpos_mode = (LPFNDLL_set_getpos_mode)GetProcAddress(hDLL,"set_getpos_mode");
		set_encoder_mode = (LPFNDLL_set_encoder_mode)GetProcAddress(hDLL,"set_encoder_mode");
		set_dir = (LPFNDLL_set_dir)GetProcAddress(hDLL,"set_dir");
		enable_sd = (LPFNDLL_enable_sd)GetProcAddress(hDLL,"enable_sd");
		enable_el = (LPFNDLL_enable_el)GetProcAddress(hDLL,"enable_el");
		enable_org = (LPFNDLL_enable_org)GetProcAddress(hDLL,"enable_org");
		set_sd_logic = (LPFNDLL_set_sd_logic)GetProcAddress(hDLL,"set_sd_logic");
		set_el_logic = (LPFNDLL_set_el_logic)GetProcAddress(hDLL,"set_el_logic");
		set_org_logic = (LPFNDLL_set_org_logic)GetProcAddress(hDLL,"set_org_logic");
		set_alm_logic = (LPFNDLL_set_alm_logic)GetProcAddress(hDLL,"set_alm_logic");
		get_abs_pos = (LPFNDLL_get_abs_pos)GetProcAddress(hDLL,"get_abs_pos");
		get_rel_pos = (LPFNDLL_get_rel_pos)GetProcAddress(hDLL,"get_rel_pos");
		get_encoder = (LPFNDLL_get_encoder)GetProcAddress(hDLL,"get_encoder");
		get_cur_dir = (LPFNDLL_get_cur_dir)GetProcAddress(hDLL,"get_cur_dir");

		//状态查询函数
		check_status = (LPFNDLL_check_status)GetProcAddress(hDLL,"check_status");
		check_done = (LPFNDLL_check_done)GetProcAddress(hDLL,"check_done");
		check_limit = (LPFNDLL_check_limit)GetProcAddress(hDLL,"check_limit");
		check_home = (LPFNDLL_check_home)GetProcAddress(hDLL,"check_home");
		check_SD = (LPFNDLL_check_SD)GetProcAddress(hDLL,"check_SD");
		check_alarm = (LPFNDLL_check_alarm)GetProcAddress(hDLL,"check_alarm");
		get_cmd_counter = (LPFNDLL_get_cmd_counter)GetProcAddress(hDLL,"get_cmd_counter");

		checkin_byte = (LPFNDLL_checkin_byte)GetProcAddress(hDLL,"checkin_byte");
		checkin_bit = (LPFNDLL_checkin_bit)GetProcAddress(hDLL,"checkin_bit");
		outport_bit = (LPFNDLL_outport_bit)GetProcAddress(hDLL,"outport_bit");
		outport_byte = (LPFNDLL_outport_byte)GetProcAddress(hDLL,"outport_byte");
		check_SFR = (LPFNDLL_check_SFR)GetProcAddress(hDLL,"check_SFR");

		//其它函数
		set_backlash = (LPFNDLL_set_backlash)GetProcAddress(hDLL,"set_backlash");
		start_backlash = (LPFNDLL_start_backlash)GetProcAddress(hDLL,"start_backlash");
		end_backlash = (LPFNDLL_end_backlash)GetProcAddress(hDLL,"end_backlash");
		change_speed = (LPFNDLL_change_speed)GetProcAddress(hDLL,"change_speed");
		change_accel = (LPFNDLL_change_accel)GetProcAddress(hDLL,"change_accel");
		Outport = (LPFNDLL_Outport)GetProcAddress(hDLL,"Outport");
		Inport = (LPFNDLL_Inport)GetProcAddress(hDLL,"Inport");
		set_ramp_flag = (LPFNDLL_set_ramp_flag)GetProcAddress(hDLL,"set_ramp_flag");
		get_lib_ver = (LPFNDLL_get_lib_ver)GetProcAddress(hDLL,"get_lib_ver");
		get_sys_ver = (LPFNDLL_get_sys_ver)GetProcAddress(hDLL,"get_sys_ver");
		get_card_ver = (LPFNDLL_get_card_ver)GetProcAddress(hDLL,"get_card_ver");

		enable_io_pos = (LPFNDLL_enable_io_pos)GetProcAddress(hDLL,"enable_io_pos");
		set_io_pos = (LPFNDLL_set_io_pos)GetProcAddress(hDLL,"set_io_pos");
		////////////////////////////////////////////////////////////////////
		//若无法取得函数指针
		if (!auto_set||!init_board)
		{
			// handle the error
			FreeLibrary(hDLL);
			return -1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return -1;
	}
}
