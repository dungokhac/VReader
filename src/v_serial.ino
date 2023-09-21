int16 fs_01_cks(uint8 *buf, int16 len, int16 k)
{
	int16 cks = 0;
	for (int i = 0; i < len - 2; i++)
	{
		cks += buf[i];
	}
	if (k)
	{
		memcpy(&buf[len - 2], &cks, 2);
	}
	return cks;
}

void fp_lock()
{
	if (++fp_fail > 5)
	{
		fp_off = fp_off_max;
		fp_fail = 0;
	}
}
void serial_test()
{
	while (uart1.available())
	{
		int16 n;
		while (uart1.available())
		{
			n = uart1.read();
			if (n != -1)
			{
				rx_buf[rx_cnt++] = n & 0xff;

				rx_cnt &= rx_max - 1;
				if (!hd_ok && (rx_cnt >= 2))
				{
					memcpy(&n_prefix, rx_buf, 2);
					if ((n_prefix == cmd_response_prefix) || (n_prefix == data_response_prefix))
					{
						hd_ok = 1;
						rx_pkt_len = -1;
					}
					else
					{
						rx_cnt = 0;
					}
				}
				if (hd_ok)
				{

					if (rx_cnt >= 6)
					{
						if (rx_pkt_len == -1)
						{
							memcpy(&rx_pkt_len, &rx_buf[4], 2);
						}
					}
					if (n_prefix == cmd_response_prefix)
					{

						if (rx_cnt == 24)
						{
							// FS01_RES("FS01_cmd");
							memcpy(cmd_rx.prefix, rx_buf, sizeof(cmd_rx));

							ret = cmd_rx.data[0];
							ret_code = cmd_rx.data[1];
							// uart0.println("cmd_rx.data[0]"+ String(cmd_rx.data[0]));
							// uart0.println("cmd_rx.data[1]"+ String(cmd_rx.data[1]));
							// uart0.println("cmd_rx.data[2]"+ String(cmd_rx.data[2]));
							memcpy(udp_tx.cmd_rx.prefix, cmd_rx.prefix, sizeof(cmd_rx));
							if (ret == 0)
							{
								switch (cmd_rx.rcm)
								{
								case Test_Connection:
									fs01_on = 1;
									break;
								case Verify_Feature:
									// fp_auto_off=500;
									cmd_send(Verify_Feature, 498, 0);
									uart1.write(data_tx.prefix, 498 + 8);
									break;
								case Read_Page:
									break;

								case Identify:
									// uart0.println("index FP"+ String(fp_index));
									if (ret_code == -12)
										break;
									if (ret_code > 0)
									{
										// Play_voice(Xin_cam_on);
										play_audio(xin_cam_on, sizeof(xin_cam_on));
										mocua();
										// readFile(SPIFFS, "/hello.txt");
										String page = String(ret_code);
										uart0.println("ma_vt" + page);
										data_chamcong = "getAccessDoor?fpIndex=" + page + "&&readercode=" + ma_tbi;
										// data_chamcong = "010202060532" + ma_tbi + "11" + fix_len(String(page.length()), 2) + page;
										// get_vantay(data_chamcong);
									}
									break;
								case Enroll_RAM:
									// ghivantay=1;//du them
									// uart0.println("layvantay");
									// uart0.println("cmd_rx.data[0]"+ String(cmd_rx.data[0]));
									// uart0.println("cmd_rx.data[1]"+ String(cmd_rx.data[1]));
									// uart0.println("cmd_rx.data[2]"+ String(cmd_rx.data[2]));

									if (ret_code == -15 || ret_code == -13)
									{
										delay(1000);
										// Play_voice(Moi_dat_van_tay);
									}
									if (ret_code == 0)
									{
										// fp_auto_off=500;
										// if (ghivantay == 1)
										// 	reset_7462("2x6");
										cmd_send(Get_Enroll, 0, 0);
										uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
									}
									break;
								case Enroll_1:
									// uart0.println("cmd_rx.data[0]" + String(cmd_rx.data[0]));
									// uart0.println("cmd_rx.data[1]" + String(cmd_rx.data[1]));
									// if (ret_code > 0)
									// {
									// 	Play_voice(Thanh_cong);
									// }
									break;
									// delay(500);

								case Enroll_3:
									if (ret_code == -13)
									{
										delay(1000);
										// Play_voice(Moi_dat_van_tay);
									}
									if (ret_code > 0)
									{
										delay(1000);
										// Play_voice(Thanh_cong);
									}

									break;
								}
							}
							else
							{

								// uart0.println("cmd_rx.data[1]"+ String(cmd_rx.data[1]));
								switch (cmd_rx.rcm)
								{
								case Test_Connection:
									fs01_on = 1;
									break;
								case Verify_Feature:

									break;
								case Read_Page:
									break;

								case Identify:

									break;
								case Enroll_RAM:

									break;

								case Enroll_1:
									if (cmd_rx.data[1] > 1)
										break;
									// Play_voice(Khong_thanh_cong);
									break;
								}
							}
							hd_ok = rx_cnt = 0;
							udp_tx.pkt_type = FS01_CMD;
							uni_send(&udp_tx.bcc, sizeof(udp_tx));
						}
					}
					else if (n_prefix == data_response_prefix)
					{

						if (rx_cnt == (6 + rx_pkt_len + 2))
						{
							// FS01_RES("FS01_data");
							memcpy(data_rx.prefix, rx_buf, sizeof(data_rx));
							ret = rx_buf[9];
							ret_code = data_rx.data[1];
							memcpy(udp_tx.data_rx.prefix, data_rx.prefix, sizeof(data_rx));
							// ducmt
							//  uart0.println("data_rx.data[0]" + String(data_rx.data[0]));
							//  uart0.println("data_rx.data[1]" + String(data_rx.data[1]));
							//  uart0.println("data_rx.rcm" + String(data_rx.rcm));
							//  uart0.println("ret" + String(ret));

							if (data_rx.rcm == Read_Page)
							{
								if (ret == 0)
								{
									String sss = "";
									uint8 n8, n;
									for (int i = 0; i < 498; i++)
									{
										// datavantay[i] = rx_buf[i + 8];
										n8 = rx_buf[i + 10];
										n = (n8 >> 4) & 0xf;
										sss += s_hex.substring(n, n + 1);
										n = n8 & 0xf;
										sss += s_hex.substring(n, n + 1);
									}
									uart0.println("Read_Page:" + sss);
								}
							}

							if (ret > 0)
							{
								// uart0.println("ret:0");
								if (data_rx.rcm == Get_Enroll)
								{
									String sss = "";
									uint8 n8, n;
									for (int i = 0; i < 498; i++)
									{
										// datavantay[i] = rx_buf[i + 8];
										n8 = rx_buf[i + 8];
										n = (n8 >> 4) & 0xf;
										sss += s_hex.substring(n, n + 1);
										n = n8 & 0xf;
										sss += s_hex.substring(n, n + 1);
									}
									if (vantay1.length() == 0)
									{
										vantay1 = sss + "0000";
										uart0.println(String(vantay1.length()));
										// writedatatoesp32(vantay1);
									}
									// else
									// {
									// 	vantay2 = sss + "0000";
									// 	uart0.println(String(vantay2.length()));
									// }
									// if (vantay1.length() == 1000 )
									// {
									// 	udp_out_ip(vantay1, "192168000103");
									// }
									// if (vantay2.length() == 1000)
									// {
									// 	udp_out_ip(vantay2, "192168000103");
									// }
									if (vantay1.length() == 1000)
									{
										ghivantay = 1;
										// Play_voice(Moi_dat_the);

										ghivantayvaothe(vantay1); // hamghivantayvaothe
										reset_7462("2x6");
									}
								}
							}
							else
							{
								// uart0.println("ret:!=0");
							}
							hd_ok = rx_cnt = 0;
							udp_tx.pkt_type = FS01_DATA;
							uni_send(&udp_tx.bcc, sizeof(udp_tx));
						}
					}
				}
			}
		}
	}
}

void serial2_test()
{
	if (Serial2.available())
	{
		String s;
		int n;
		while (Serial2.available())
		{
			n = Serial2.read();

			if (n != -1)
			{
				serial2_in += (char)(n & 0xff);
				//in ra
				if (serial2_in.endsWith("***"))
				{
					// uart0.print(serial2_in);
					add_to_serial("7462 nhan: " + hextostr(serial2_in));
					serial_out();
				}
				if (xacthucvantay == 1)
				{
					if (serial2_in.endsWith("!"))
					{
						if (serial2_in.startsWith("^135"))
						{
							vantay = "";
							serial2_in = "";
							// reset_7462("2xx2");tạm cmt
						}
						if (serial2_in.startsWith("^6"))
						{
							serial2_in = serial2_in;
						}
						else
						{
							serial2_in = "";
						}
					}
					else if (serial2_in.endsWith("***"))
					{

						serial2_in.remove(serial2_in.length() - 3, 3); // remove ***
						if (serial2_in.substring(0, 1) == "!")
							serial2_in.remove(0, 1);

						// add_to_serial("7462 nhan" + hextostr(serial2_in));
						// serial_out();

						if (serial2_in.startsWith("^6") && xacthucvantay == 1)
						{
							serial2_in.remove(0, 2);
							vantay += serial2_in;
							serial2_in = "";
							if (vantay.length() == 1000)
							{
								// for (int i = 0; i < 498; i++)
								// {
								// 	datavantay1 += vantay.charAt(i);
								// }
								// for (int i = 500; i < 998; i++)
								// {
								// 	datavantay2 += vantay.charAt(i);
								// }
								// for (int i = 1; i < 250; i++)
								// {
								// 	vt1.data[i] = (datavantay1.charAt(2 * i - 1) << 8) + (datavantay1.charAt(2 * i - 2));
								// }
								// uart0.println();
								// fp_func_write_template(vt1, 998);
								// for (int i = 1; i < 250; i++)
								// {
								// 	vt2.data[i] = (datavantay2.charAt(2 * i - 1) << 8) + (datavantay2.charAt(2 * i - 2));
								// }
								// fp_func_write_template(vt2, 999);
								// uart0.println();
								// for (int i = 0; i < 250; i++)
								// {
								// 	vt1.data[i] = 0;
								// 	vt2.data[i] = 0;
								// }
								datavantay1 = datavantay2 = "";
								// play_audio(thanh_cong, sizeof(thanh_cong));
								vantay = "";
								xacthucvantay = 0;
							}
						}
					}
				}
				else
				{
					if (serial2_in.endsWith("!"))
					{
						serial2_in = "";
					}

					else if (serial2_in.endsWith("#"))
					{

						serial2_in.remove(serial2_in.length() - 1, 1); // remove #

						// add_to_serial("7462 nhan#" + hextostr(serial2_in));
						// serial_out();

						if (serial2_in.startsWith("^1"))
						{
							if (ghivantay == 1)
							{
								reset_7462("2x6");
							}
							if (serial2_in.startsWith("^135"))
							{
								uid_the = serial2_in.substring(5, 19);
								vid_the = serial2_in.substring(76, 83);
								vid_the.replace(" ", "");
								// uart0.println(vid_the);
								if (ghi_ma_tbi == 1)
								{
									ma_tbi = serial2_in.substring(20, 53);
									add_to_serial("ma_tbi:" + ma_tbi);
									serial_out();
									ghimatbi(ma_tbi);
									ghi_ma_tbi = 0;
								}
								data_chamcong = "getAccessDoorByCard?vid=" + vid_the + "&readercode=" + ma_tbi;
								// getms(data_chamcong); // chamcong, đang tạm cmt
							}

							TrangThaiThanhToan = false;
							magiaodich = "";
							String s = serial2_in;
							s.remove(0, 2);
							if (s.startsWith("cfs"))
							{
								s.remove(0, 3);
								if (wifi_on)
									confirm_service(s);
							}
							else
							{

								// gốc
								reset_7462("2x3");
								delay(1000);
								if (wifi_on)
									send_https(s);
							}
						}
						else if (serial2_in.startsWith("^5"))
						{
							// add_to_serial("7462 nhan" + hextostr(serial2_in));
							// serial_out();
						}
						else if (serial2_in.startsWith("^6"))
						{
							if (demghi == 0)
								break;

							if (demghi == 5)
							{
								String ghilaivitri = "";
								for (int i = 0; i < 12; i++)
								{
									if (offset_wfp[i] == 0)
									{
										offset_wfp[i] = 3;
										break;
									}
								}
								for (int i = 0; i < 12; i++)
								{
									ghilaivitri += "0" + String(offset_wfp[i]);
								}
								serial2_out = "!^2" + uid_the + "$1130000" + ghilaivitri + "$" + tinhCKS_Du("2" + uid_the + "$1130000" + ghilaivitri, 5) + "#";
								uart0.println("ghi lan, " + String(demghi) + "," + serial2_out);
							}
							else
							{
								serial2_out = "!^2" + uid_the + "$113" + String(offset_write) + fp_save[demghi] + "$" + tinhCKS_Du("2" + uid_the + "$113" + String(offset_write) + fp_save[demghi], 5) + "#";
								uart0.println("ghi lan, " + String(demghi) + "," + serial2_out);
							}

							demghi++;

							if (demghi == 6)
							{
								demghi = 0;
								ghivantay = 0;
								vantay1 = "";
								vantay2 = "";
								offset_write = 0;
								// uid_the = "";
							}
						}
						else if (serial2_in.startsWith("^7"))
						{
							int offset = 12;
							offset_fp = hextostr(serial2_in);
							// ghilaivitri=offset_fp;
							offset_fp.remove(0, 4);
							// uart0.println("offset_fp2 " + offset_fp);
							for (int i = 0; i < 12; i++)
							{
								offset_wfp[i] = offset_fp.substring(0, 2).toInt();
								// uart0.println("offset_wfp["+String(i)+"] = "+String(offset_wfp[i]));
								offset_fp.remove(0, 2);
								// uart0.println("offset_fp22 " + offset_fp);
							}
							offset_fp = "";
							int n = 0, m = 0;
							for (int i = 0; i < 12; i++)
							{

								if (offset_wfp[i] == 1 )
								{
									offset +=  1040;
								}
								if (offset_wfp[i] == 3 )
								{
									offset += 520;
								}
							}
							// offset_write +=12; // vị trí lưu

							uart0.println(offset_write);
							// uart0.println(convertDecToHexString(offset_write));
							// decimalToHex(offset_write);
							// StringtoInt();
							// hexadecimalToDecimal("0FFF");
							offset_write=offset;
						}
						else if (serial2_in.startsWith("^4"))
						{
							// String sout = "";
							uart0.print("ghi thanh coong");
							offset_write=0;
							setbip(Thanh_Cong);

							serial2_in.remove(0, 3);
							if (duong_ra == ra_udp && hangdoi_Front() != "")
							{
								udp_out_ip("100" + serial2_in + "#", hangdoi_Front());
							}
						}
						serial2_in = "";
					}
				}
				if (serial2_in.length() > rx_max)
					serial2_in.clear();
			}
		}
	}
}

void serial2_out_test()
{
	int len;
	if (uart2.availableForWrite() >= 127)
	{
		ms5 &= 7;
		if (ms5)
		{
			if (--ms5 == 0)
			{
				String s = "";
				if (serial2_out.length() > 123)
				{
					s = serial2_out.substring(0, 124);

					serial2_out.remove(0, 124);
				}
				else if (serial2_out.length())
				{
					s = serial2_out;
					serial2_out = "";
					len = (s.length() & 0x7c) + 4;
					if (len > 124)
						len = 124;
					while (s.length() < len)
					{
						s += "0";
					}
				}
				if (s.length())
				{
					uart2.print(s);
					ms5 = 4;
				}
			}
		}
		else if (serial2_out.length())
		{
			ms5 = 4;
		}
	}
}
// ghi van tay vao file7

void char_buf_to_ev2()
{
	String s = "", snew, snew1 = "2" + uid_the + "$114000";
	uint8 n8, n;
	for (int i = 0; i < char_buf_len; i++)
	{
		n8 = char_buf[i];
		n = (n8 >> 4) & 0xf;
		s += s_hex.substring(n, n + 1);
		n = n8 & 0xf;
		s += s_hex.substring(n, n + 1);
	}
	s += "0000";
	// uart0.println(s);
	for (int i = 1; i < 5; i++)
	{
		fp_save[i] = s.substring(0, 250);
		s.remove(0, 250);
	}

	serial2_out = "!^" + snew1 + fp_save[1] + "$" + tinhCKS_Du(snew1 + fp_save[1], 5) + "#";
	// uart0.println(serial2_out);
}

uint8 hex_to_byte(String s)
{
	s.toUpperCase();
	uint8 n8;
	int n;
	n = s_hex.indexOf(s.substring(0, 1));
	n8 = (n != -1) ? n : 0;
	n8 <<= 4;
	n = s_hex.indexOf(s.substring(1, 2));
	n8 |= (n != -1) ? n : 0;
	return n8;
}

String tinhCKS_Du(String s, int n)
{
	int32 bcc = 0;
	for (int i = 0; i < s.length(); i++)
	{
		bcc += (uint8)s.charAt(i);
	}
	return fix_len(String(bcc), n);
}

void XTvanTay(String strvt)
{
	if (strvt.length() == char_buf_len)
	{
		bipok1();
		for (int i = 0; i < char_buf_len; i++)
		{
			char_buf[i] = (int)strvt.charAt(i);
		}
		uart0.println("Vao xt vantay:");
		cmd_send(Verify_Feature, 498, 0);
		uart1.write(data_tx.prefix, 498 + 8);
		// Play_voice(Moi_dat_van_tay);
		led_reset = 5;
	}
}

String hextostr(String s1)
{
	String s = "";
	uint8 n8, n;
	for (int i = 0; i < s1.length(); i++)
	{
		n8 = s1.charAt(i);
		n = (n8 >> 4) & 0xf;
		s += s_hex.substring(n, n + 1);
		n = n8 & 0xf;
		s += s_hex.substring(n, n + 1);
	}
	return s;
}

void ghivantayvaothe(String vantay)
{
	// reset_7462("2x7");// bat dau ghi xac thuc
	setbip(Cham_the);
	// delay(1000);
	// Play_voice(Moi_dat_the);
	// delay(500);
	// String s1 = ;
	uart0.println(vantay);
	for (int i = 1; i < 5; i++)
	{
		fp_save[i] = vantay.substring(0, 250);
		vantay.remove(0, 250);
	}
	demghi = 1;
}

void FS01_RES(String s1)
{
	String sss = "";
	uint8 n8, n;
	for (int i = 0; i < rx_cnt; i++)
	{
		// datavantay[i] = rx_buf[i + 8];
		n8 = cmd_rx.prefix[i];
		n = (n8 >> 4) & 0xf;
		sss += s_hex.substring(n, n + 1);
		n = n8 & 0xf;
		sss += s_hex.substring(n, n + 1);
	}
	// uart0.println(s1 + sss); // Thông báo đặt thẻ ghi vân tay
}
String dec_to_string(int a)
{
	String str = "01234567890000000ABCDEF", s = "";
	s = str.substring(a, a + 1);
	return s;
}

void reset_7462(String a)
{
	uart0.println("reset_7462:" + a);
	String s = "", serialto7462 = "!^" + a + "#";
	while (serialto7462.length())
	{

		if (serialto7462.length() > 123)
		{
			s = serial2_out.substring(0, 124);
			serial2_out.remove(0, 124);
		}
		else if (serialto7462.length())
		{
			s = serialto7462;
			serialto7462 = "";
			ms5 = (s.length() & 0x7c) + 4;
			while (s.length() < ms5)
			{
				s += "0";
			}
			ms5 = 0;
		}
		if (s.length())
		{
			Serial2.print(s);
			ms5 = 4;
		}
		delay(5);
	}
}