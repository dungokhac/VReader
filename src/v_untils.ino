void caidatthietbi(String s){
	// add_to_serial("cai dat"+s);
	// serial_out();
	if (s.startsWith("id_"))// luu id thiet bi
	{  	
		s.remove(0,3);
		my_id=s.substring(0,5).toInt();
		if (my_id < soluongthietbi && my_id > 0){
			save_id();
		    bipok1();
		    udp_out_ip("106TBC011", hangdoi_Front());
		}else{
			my_id=0;
			save_id();
			biper1();
		}
	}
	else if (s.startsWith("cfg_"))
	{	s.remove(0,4);
		save_cfg(s);
		bipok1();
		udp_out_ip("106TBC011", hangdoi_Front());

	}
	//nam
	else if(s.startsWith("dsChoThanhToan_")) 
	{
		TrangThaiThanhToan = true;
		s.remove(0,14);
	}
	else if(s.startsWith("thongbaotrangthai_"))
	{
		s.remove(0,17);
		udp_out_ip("106TBCSV_"+s, hangdoi_Front());
	}
 
 	else if(s.startsWith("showPass_"))
	{
		s.remove(0,9);
		idDelaySend[0] = s;
		yeu_cau_nhapmk();
	}
	else if(s.startsWith("iplocalw_"))
	{
		s.remove(0,9);
		save_iplocal(s);
		bipok1();
		udp_out_ip("106TBC011", hangdoi_Front());
	}
	else if(s.startsWith("serialId_"))
	{
		s.remove(0,9);
		save_TBTTId(s);
		bipok1();
		udp_out_ip("106TBC011", hangdoi_Front());
	}
	else if (s.startsWith("wifiw_"))
	{	
		s.remove(0,6);
		if(s.length() > 10)
		{
			save_ssid(s);
			bipok1();
			udp_out_ip("106TBC011", hangdoi_Front());
		}
	}
	// ======
	else if (s.startsWith("wifir"))
	{	s="wifir";
		for (int i=0;i<8;i++)
		{	s += str_name[i]+"_"+str_pass[i]+"_";
		}
		if(v_cfg.media==https_media)	{}
		else if(v_cfg.media==rs485_media){} //add_to_serial(msg_send(s));
	}
	else if (s.startsWith("gett_"))
	{	//add_to_serial(msg_send(time_string()));
	}
	else if (s.startsWith("sett_"))
	{  	new_time(s);
	}
	else if (s.startsWith("ramcl_"))
	{  	
	}
	else if (s.startsWith("ramrd_"))
	{  	s.remove(0,6);
		ram_rd(s);
	}
	else if(s.startsWith("dichvumaytram_"))
	{
		s.remove(0,14);
		DichVuMayTram = true;
		strdichvumaytram = s;
	}
	else if (s.startsWith("door_open")){	
		mocua();
	}
	else if (s.startsWith("door_close")){	
		//dong cua
		door_close;
		biper1();
	}
}

String str_idtb(int a){
	String b;
	b = fix_len(String(a),5);
	return b;
}

String tinhCKS(String s)
{
	int32 bcc=0;	
	for (int i=0;i<s.length();i++)
	{
		bcc += (uint8)s.charAt(i);
	}
	return fix_len(String(bcc),3);
}

String fix_len_n_str(String s,int16 len) // số không đặt cuối
{	
	if (s.length() > len)	s=s.substring(s.length()-len,s.length());
	while (s.length() < len)	{	s = s+"0";}
	return s;
}
bool check_limit(int a,int low,int hi){
	if( a > hi && a < low){
		return true;
	}else{
		return false;
	}
}
