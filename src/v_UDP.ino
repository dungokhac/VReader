
void udp_out(String s, uint8 bcast)
{
  uint8 buf[s.length()], *ptr;
  ptr = buf;
  for (int i = 0; i < (int)sizeof(buf); i++)
  {
    *ptr++ = s.charAt(i);
  }
  if (bcast)
    myUDP.beginPacket(bcast_IP, 6000); // 08/12/20
  else
    myUDP.beginPacket(pc_IP, 6000); // 08/12/20
  myUDP.write(buf, sizeof(buf));
  myUDP.endPacket();
}
void udp_out_config(String sout)
{
  add_to_serial("send" + sout + "---------" + "ip" + strip);
  serial_out();
  int t[4], i = 0;
  String ipout = strip;

  for (i = 0; i < 4; i++)
  {
    t[i] = ipout.substring(0, 3).toInt();
    ipout.remove(0, 3);
  }

  IPAddress ip(t[0], t[1], t[2], t[3]);
  if (sout.length() > 0)
  {
    uint8 buf[sout.length()], *ptr;
    ptr = buf;
    for (int i = 0; i < (int)sizeof(buf); i++)
    {
      *ptr++ = sout.charAt(i);
    }
    myUDP.beginPacket(ip, 6000); // 08/12/20
    myUDP.write(buf, sizeof(buf));
    myUDP.endPacket();
    sout = "";
  }
}
// void udp_out(String sout)
// {
//   int t[4], i = 0;
//   String ipout = "192168000103";

//   for (i = 0; i < 4; i++)
//   {
//     t[i] = ipout.substring(0, 3).toInt();
//     ipout.remove(0, 3);
//   }

//   IPAddress ip(t[0], t[1], t[2], t[3]);
//   if (sout.length() > 0)
//   {
//     uint8 buf[sout.length()], *ptr;
//     ptr = buf;
//     for (int i = 0; i < (int)sizeof(buf); i++)
//     {
//       *ptr++ = sout.charAt(i);
//     }
//     myUDP.beginPacket(ip, 6000); // 08/12/20
//     myUDP.write(buf, sizeof(buf));
//     myUDP.endPacket();
//     sout = "";
//   }
// }
void UDP_control(String s)
{
  int malenhint;
  String out = "", ipnhan = "", s1 = "";
  add_to_serial("UDP11");
  serial_out();

  add_to_serial("strip" + strip + ",pc_IP" + pc_IP.toString().c_str());
  serial_out();

  if (!strip.equals(pc_ip_tostring(pc_IP.toString().c_str())))
    return;
  add_to_serial("UDP22");
  serial_out();
  str_lenhtbngoai = "";

  malenhint = s.substring(0, 3).toInt();
  s1 = s;
  s1.replace(" ", "");
  duong_ra = ra_udp;
  if (s1.length() == 0)
  {
    thong_bao_udp("TBC006");
    return;
  }
  s.remove(0, 15);
  // add_to_serial(s);
  // serial_out();
  bipok1();
  if (malenhint == 100)
  {
    reset_7462("2x5");
    if (kiemtraipdanglapviec(strip))
    {
      udp_out_ip("106TBC011", hangdoi_Front());
    }
    else
    {
      thong_bao_udp("TBC007");
      strip = "";
    }
  }
  else if (malenhint == 101)
  {
    gui_id_thietbi();
  }
  else if (malenhint == 102)
  {
    reset_7462("2x5");
    str_door = "12";
  }
  else if (malenhint == 103)
  {
    add_to_serial("lenh 103");
    serial_out();
    EnQueue(strip);
  }
  else if (malenhint == 104)
  {
    if (vitrihangdoi(strip) > 0)
    {
      thong_bao_udp("TBC003_1");
    }
    else
    {
      thong_bao_udp("TBC008");
    }
  }
  else if (malenhint == 105)
  {
    DeQueue(strip);
  }
  else if (malenhint == 106) // Hủy lệnh chuyển tiền
  {
    str_lenhtbngoai = "";
    udp_out_ip("106TBC013", hangdoi_Front());
  }
  else if (malenhint == 200)
  {
    if (s.indexOf("MO CUA") != -1)
    {
      mocuaUDP();
      return;
    }

    if (!kiemtraipdanglapviec(strip))
      return;
    strip = "";
    str_lenhtbngoai = s + "#";

    if (str_lenhtbngoai.indexOf("PASS") != -1 && idDelaySend[0] != "")
    {
      send_https("");
      str_lenhtbngoai = "";
      return;
    }
    else
    {
      udp_out_ip("106TBC009", hangdoi_Front());
    }
  }
  else if (malenhint == 999)
  {
    caidatthietbi(s);
  }
  else if (malenhint == 300)
  {
    // add_to_serial(s);
    // serial_out();
    khoitao_ghixacthuc(s);
    // if(!kiemtraipdanglapviec(strip)) return;
    // strip="";
  }
  else if (malenhint == 301)
  {

    Docxacthuc5();
  }
  else if (malenhint == 302)
  {

    Docxacthuc6();
  }
}
void gui_id_thietbi()
{
  String out1 = "";
  out1 = str_idtb(my_id) + "^101TB" + str_idtb(my_id) + bcc_check_step("101TB" + str_idtb(my_id), 6) + "#";
  udp_out_config(out1);
}
void yeu_cau_nhapmk()
{

  biper1();

  udp_out_ip("105", hangdoi_Front());
}
void thong_bao_udp(String s)
{
  String s11 = str_idtb(my_id) + "^106" + s + "_" + bcc_check_step("106" + s + "_", 6) + "#";
  udp_out_config(s11);
}
// void udp_out_ip(String sout, String ipout)
// {
//   add_to_serial(sout);
//   serial_out();
//   sout = str_idtb(my_id) + "^" + sout + "_" + bcc_check_step(sout, 6);
//   udp_time = 0;
//   int t[4], i = 0;
//   for (i = 0; i < 4; i++)
//   {
//     t[i] = ipout.substring(0, 3).toInt();
//     ipout.remove(0, 3);
//   }
//   IPAddress ip(t[0], t[1], t[2], t[3]);
//   if (sout.length())
//   {
//     uint8 buf[sout.length()], *ptr;
//     ptr = buf;
//     for (int i = 0; i < (int)sizeof(buf); i++)
//     {
//       *ptr++ = sout.charAt(i);
//     }
//     myUDP.beginPacket(ip, 6000); // 08/12/20
//     myUDP.write(buf, sizeof(buf));
//     myUDP.endPacket();
//     sout = "";
//   }
// }

void UDP_msg(String s)
{

  int s_len = s.length();
  String ipthietbivao = "";
  if (s.indexOf("^") == 5)
  {
    int dst = s.substring(0, 5).toInt();

    strip = s.substring(9, 21);
    int malenhvao = s.substring(6, 9).toInt();
    if (dst == 0 && malenhvao == 101)
    { // tra ve ten thiet bi
      gui_id_thietbi();
      return;
    }

    if (dst != my_id || dst > soluongthietbi)
      return;

    String s_bcc = s.substring(s_len - 4, s_len);

    if (!s_bcc.equals(bcc_check_step(s.substring(6, s_len - 4), 6)))
      return; // kiem tra checksum du lieu

    s = s.substring(6, s_len - 4);
    pc_IP = myUDP.remoteIP();
    // pc_IP.toString().c_str()

    UDP_control(s); // re nhanh lenh
  }
}
bool kiemtraipdanglapviec(String s)
{

  // add_to_serial("--"+hangdoi_Front()+"--"+s+"--");
  // serial_out();
  if (hangdoi_Front() == s)
    return true;
  else
    return false;
}

String pc_ip_tostring(String s)
{
  String s2 = "", s1 = "";
  s1 = s.substring(0, s.indexOf("."));
  s2 += fix_len(s1, 3);
  s.remove(0, s.indexOf(".") + 1);
  s1 = s.substring(0, s.indexOf("."));
  s2 += fix_len(s1, 3);
  s.remove(0, s.indexOf(".") + 1);
  s1 = s.substring(0, s.indexOf("."));
  s2 += fix_len(s1, 3);
  s.remove(0, s.indexOf(".") + 1);

  s2 += fix_len(s, 3);
  uart0.println("s2" + s2);
  return s2;
}

void bcast_out()
{
	String s = s_log + " " + String(fp_on_max) + " " + String(fp_detect_cnt) + " " + String(fp_auto_off);
	uint8 buf[s.length()];
	udp_tx.pkt_type = FS01_BCAST;
	udp_tx.data_rx.rcm = WiFi.RSSI();
	udp_tx.data_rx.len = s.length();
	udp_tx.cmd_rx.data[0] = my_ip[3];
	udp_tx.cmd_rx.data[0] <<= 8;
	udp_tx.cmd_rx.data[0] |= my_ip[3];
	udp_tx.cmd_rx.data[1] = digitalRead(master_in);
	for (int i = 0; i < udp_tx.data_rx.len; i++)
	{
		buf[i] = s.charAt(i);
	}
	memcpy(udp_tx.data_rx.data, buf, sizeof(buf));
	bcast_send(&udp_tx.bcc, sizeof(udp_tx));
}