/*
Wifi secure connection example for ESP32
Running on TLS 1.2 using mbedTLS
Suporting the following chipersuites:
"TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384","TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384","TLS_DHE_RSA_WITH_AES_256_GCM_SHA384","TLS_ECDHE_ECDSA_WITH_AES_256_CCM","TLS_DHE_RSA_WITH_AES_256_CCM","TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384","TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384","TLS_DHE_RSA_WITH_AES_256_CBC_SHA256","TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA","TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA","TLS_DHE_RSA_WITH_AES_256_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8","TLS_DHE_RSA_WITH_AES_256_CCM_8","TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256","TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256","TLS_DHE_RSA_WITH_AES_128_GCM_SHA256","TLS_ECDHE_ECDSA_WITH_AES_128_CCM","TLS_DHE_RSA_WITH_AES_128_CCM","TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256","TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256","TLS_DHE_RSA_WITH_AES_128_CBC_SHA256","TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA","TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA","TLS_DHE_RSA_WITH_AES_128_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8","TLS_DHE_RSA_WITH_AES_128_CCM_8","TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA","TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA","TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA","TLS_DHE_PSK_WITH_AES_256_GCM_SHA384","TLS_DHE_PSK_WITH_AES_256_CCM","TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384","TLS_DHE_PSK_WITH_AES_256_CBC_SHA384","TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA","TLS_DHE_PSK_WITH_AES_256_CBC_SHA","TLS_DHE_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_DHE_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_PSK_DHE_WITH_AES_256_CCM_8","TLS_DHE_PSK_WITH_AES_128_GCM_SHA256","TLS_DHE_PSK_WITH_AES_128_CCM","TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256","TLS_DHE_PSK_WITH_AES_128_CBC_SHA256","TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA","TLS_DHE_PSK_WITH_AES_128_CBC_SHA","TLS_DHE_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_DHE_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDHE_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_PSK_DHE_WITH_AES_128_CCM_8","TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA","TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA","TLS_RSA_WITH_AES_256_GCM_SHA384","TLS_RSA_WITH_AES_256_CCM","TLS_RSA_WITH_AES_256_CBC_SHA256","TLS_RSA_WITH_AES_256_CBC_SHA","TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384","TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384","TLS_ECDH_RSA_WITH_AES_256_CBC_SHA","TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384","TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384","TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA","TLS_RSA_WITH_AES_256_CCM_8","TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256","TLS_RSA_WITH_CAMELLIA_256_CBC_SHA","TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_RSA_WITH_AES_128_GCM_SHA256","TLS_RSA_WITH_AES_128_CCM","TLS_RSA_WITH_AES_128_CBC_SHA256","TLS_RSA_WITH_AES_128_CBC_SHA","TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256","TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256","TLS_ECDH_RSA_WITH_AES_128_CBC_SHA","TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256","TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256","TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA","TLS_RSA_WITH_AES_128_CCM_8","TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_WITH_CAMELLIA_128_CBC_SHA","TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA","TLS_RSA_PSK_WITH_AES_256_GCM_SHA384","TLS_RSA_PSK_WITH_AES_256_CBC_SHA384","TLS_RSA_PSK_WITH_AES_256_CBC_SHA","TLS_RSA_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_RSA_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_RSA_PSK_WITH_AES_128_GCM_SHA256","TLS_RSA_PSK_WITH_AES_128_CBC_SHA256","TLS_RSA_PSK_WITH_AES_128_CBC_SHA","TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_RSA_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA","TLS_PSK_WITH_AES_256_GCM_SHA384","TLS_PSK_WITH_AES_256_CCM","TLS_PSK_WITH_AES_256_CBC_SHA384","TLS_PSK_WITH_AES_256_CBC_SHA","TLS_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_PSK_WITH_AES_256_CCM_8","TLS_PSK_WITH_AES_128_GCM_SHA256","TLS_PSK_WITH_AES_128_CCM","TLS_PSK_WITH_AES_128_CBC_SHA256","TLS_PSK_WITH_AES_128_CBC_SHA","TLS_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_PSK_WITH_AES_128_CCM_8","TLS_PSK_WITH_3DES_EDE_CBC_SHA","TLS_EMPTY_RENEGOTIATION_INFO_SCSV"]
2017 - Evandro Copercini - Apache 2.0 License.
*/

// https://vimass.vn/vmbank/services/TBTTService/requestComand?param=xxx root certificate authority, to verify the server

// You can use x.509 client certificates if you want
// const char* test_client_key = ""; //to verify the client
// const char* test_client_cert = ""; //to verify the client

// * - . _
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

WiFiClientSecure client;
HTTPClient httpMC;
const char *server = "www.vimass.vn";		   // Server URL
const char *status_open_door = "^6*door_open"; // Server URL

void send_https(String s)
{
	s = https_encode(s);
	if (str_door.startsWith("12_") || str_door.startsWith("13"))
	{
		xuLyGuiThongTinLienQuanDenDoor(s);
	}
	else
	{
		// if(str_lenhtbngoai.length() == 0) return;
		String param = "";
		if (str_lenhtbngoai.indexOf("PASS") != -1)
		{
			str_lenhtbngoai.remove(0, 5);
			str_lenhtbngoai = https_encode(str_lenhtbngoai);
			param = "51_" + idDelaySend[0] + str_lenhtbngoai;
			resetServicesStatus();
		}
		else if (str_lenhtbngoai.indexOf("YEU CAU THANH TOAN") != -1)
		{
			param = "2244_";
		}
		else if (str_lenhtbngoai != "")
		{
			str_lenhtbngoai = https_encode(str_lenhtbngoai);
			param = "50_99_dv_" + str_lenhtbngoai;
		}
		else if (idDelaySend[0] != "" && str_lenhtbngoai.indexOf("PASS") == -1 && solannhapmk < 3)
		{
			solannhapmk++;
			if (solannhapmk < 3)
			{
				udp_out_ip("105", hangdoi_Front());
			}
			else
			{
				resetServicesStatus();
			}
			return;
		}
		solannhapmk = 0;
		str_lenhtbngoai = "";
		add_to_serial("param:" + param + s);
		serial_out();
		httpMC.setReuse(true);
		httpMC.begin("http://124.158.4.173:8080/vmbank/services/TBTTService/requestComand?param=" + param + s);

		int httpCode = httpMC.GET();
		httpMC.setConnectTimeout(5000);

		if (httpCode > 0)
		{									  // Check the returning code
			String sout = httpMC.getString(); // Get the request response payload
			add_to_serial("server ve:" + sout + "---");
			serial_out();
			if (sout.indexOf("2x1") != -1)
			{
				udp_out_ip("106TBC010", hangdoi_Front());
			}
			// nam==============
			//  add_to_serial("server ve:"+sout);
			//  serial_out();
			//===============
			if (v_stat == dv_F1)
			{
				xuLyYeuCauDichVuSauKetNoiLan1(sout);
			}
			else if (sout.startsWith("^2x1") && vuaNhapPassConfirm == 1)
			{
				vuaNhapPassConfirm = 0;
			}
			else
			{
				// thong bao
				sout = https_decode(sout);
				if (sout.indexOf("$112") > 0 || sout.indexOf("$113") > 0)
				{
					khoitao_ghixacthuc(sout);
				}
				else
				{
					new_cmd(sout, https_src);
				}
			}
			// resetServicesStatus();
		}
		else
		{
			resetServicesStatus();
			// if(param.length() == 0)
			// {
			// 	new_cmd("^2x1^",https_src);
			// }
			// wifi_setup();
			new_cmd("^2x1^", https_src);
		}
		httpMC.end(); // Close connection
	}
}
String https_decode(String s)
{
	String s0 = "";
	int16 n;
	while (s.length())
	{
		if (s.substring(0, 1) != "%")
		{
			s0 += s.substring(0, 1);
			s.remove(0, 1);
		}
		else
		{
			n = strtol(s.substring(1, 3).c_str(), NULL, 16);
			s0 += char(n & 0x7f);
			s.remove(0, 3);
		}
	}
	return s0;
}

String ctrl_char = " !#$%&()+,/:;<=>?[]^{}|~";
String https_encode(String s)
{
	String s1, s0 = "";
	while (s.length())
	{
		s1 = s.substring(0, 1);
		s.remove(0, 1);
		if (ctrl_char.indexOf(s1) >= 0)
		{
			s0 += "%" + fix_len(String(s1.charAt(0), HEX), 2);
		}
		else
		{
			s0 += s1;
		}
	}
	return s0;
}
void confirm_service(String s)
{

	if (s.startsWith("000"))
	{
		if (idDelayConfirm[0].length() > 0)
		{
			delay(100);
			httpMC.setReuse(true);
			s = https_encode(s);
			httpMC.begin("http://124.158.4.173:8080/vmbank/services/TBTTService/requestComand?param=" + idDelayConfirm[0]);
			httpMC.setConnectTimeout(5000);
			int httpCode = httpMC.GET();

			idDelayConfirm[0] = "";
			if (httpCode <= 0)
			{
				wifi_setup();
			}
			else
			{
				String sout = httpMC.getString(); // Get the request response payload
				sout = https_decode(sout);
				// add_to_serial("ket qua sau cf --"+sout+"--");
				// serial_out();
				new_cmd(sout, https_src);
			}
		}
	}
	else
	{
		s = https_encode(s);
		idDelayConfirm[0] = idDelayConfirm[0] + "_" + s;
	}

	httpMC.end(); // Close connection
}

void xuLyGuiThongTinLienQuanDenDoor(String s)
{
	String param = "";
	boolean openThuong = false;
	if (str_door.startsWith("13"))
	{
		String temp = tinhCKS(passDelaySend[0]);
		param = "51_" + idDelaySend[0] + "_" + temp;
	}
	else
	{
		openThuong = true;
	}
	resetDoorStatus();
	httpMC.setReuse(true);
	httpMC.begin("http://" + iplocal[0] + ":8080/ApiPkiWeb/services/DichVuMayTram/openGate?input=" + param + s);
	httpMC.setConnectTimeout(1000);
	int httpCode = httpMC.GET();

	if (httpCode > 0)
	{										 // Check the returning code
		String payload = httpMC.getString(); // Get the request response payload
		// add_to_serial("nhap mat khau"+payload);
		// serial_out();
		if (payload.startsWith(status_open_door))
		{
			showOpenDoor(payload);
		}
		else if (payload.startsWith("^6*showPass_openDoor_"))
		{

			v_stat = dv_PASS;
			str_door = "13";
			payload.remove(0, 21);
			idDelaySend[0] = payload;
			// str_idtb(my_id) gui ra tb nhap mat khau
			yeu_cau_nhapmk();
		}
		else
		{
			if (openThuong)
			{
				checkOfflineCardOpenDoor(s);
			}
			else
			{
				showCloseDoor(payload);
			}
		}
	}
	else
	{
		//  add_to_serial("xuLyGuiThongTinLienQuanDenDoor 3 code:" + httpCode);
		// serial_out();
		// check offline
		if (openThuong)
		{
			checkOfflineCardOpenDoor(s);
		}
	}
	httpMC.end(); // Close connection
}

void confirmSaveCardOffline(String s)
{
	httpMC.setReuse(true);
	httpMC.begin("http://" + iplocal[0] + ":8080/ApiPkiWeb/services/DichVuMayTram/confirmListCardDoor?input=" + s);
	httpMC.setConnectTimeout(5000);
	int httpCode = httpMC.GET();
	if (httpCode > 0)
	{
	}
	// else
	// {
	// 	wifi_setup();
	// }
	httpMC.end(); // Close connection
}

void door_service(String s)
{
}

void xuLyYeuCauDichVuSauKetNoiLan1(String payload)
{
	if (payload.startsWith("^2x1"))
	{
		// cho thong bao ket qua
	}
	else if (payload.startsWith("^6*showPass_"))
	{
		v_stat = dv_PASS;
		str_door = "15";
		payload.remove(0, 12);
		idDelaySend[0] = payload;
		yeu_cau_nhapmk();
	}
	else
	{
		resetServicesStatus();
		new_cmd(payload, https_src);
	}
}

void payment_confirmation(String s)
{
	magiaodich = "";
	httpMC.setReuse(true);
	s = https_encode(s);
	httpMC.begin("http://124.158.4.173:8080/vmbank/services/TBTTService/requestComand?param=" + s);
	httpMC.setConnectTimeout(5000);
	int httpCode = httpMC.GET();
	idDelayConfirm[0] = "";
	httpMC.end(); // Close connection
}

void get_vantay(String data)
{
	String uid1 = "1";
	if (WiFi.status() == WL_CONNECTED)
	{
		httpMC.setReuse(true);
		httpMC.begin("http://210.245.8.7:12317/api/" + data);
		// Serial.println(data);
		int httpCode = httpMC.GET();
		httpMC.setConnectTimeout(5000);
		if (httpCode > 0)
		{									  // Check the returning code
			String sout = httpMC.getString(); // Get the request response payload
			Serial.println("http out:" + sout);
			if (sout.equals(uid1) == 1)
			{
				// bipok1();
				// mocua();
			}
			else
			{
				bipok2();
			}
		}
		httpMC.end();
	}
	else
	{
		bip4_no_internet();
		// mocua();
		wifi_setup();
	}
}
void getms(String data)
{
	String uid1 = "1";
	if (WiFi.status() == WL_CONNECTED)
	{
		httpMC.setReuse(true);
		// data = https_encode(data);
		httpMC.begin("http://210.245.8.7:12317/api/" + data);
		// Serial.println(data);
		int httpCode = httpMC.GET();
		httpMC.setConnectTimeout(5000);
		uart0.println(httpCode);
		if (httpCode > 0)
		{									  // Check the returning code
			String sout = httpMC.getString(); // Get the request response payload
			Serial.println("http out:" + sout);
			if (sout.equals(uid1) == 1)
			{
				play_audio(xin_cam_on, sizeof(xin_cam_on));
				mocua();
			}
			else
			{
				if (sout.equals("err4"))
				{
					mocua();
				}
				else
				{play_audio(khong_thanh_cong, sizeof(khong_thanh_cong));
					
					dongcua();
				}
			}
		}
		else
		{
			mocua();
		}
		httpMC.end();
	}
	else
	{
		bip4_no_internet();
		mocua();
		wifi_setup();
	}
}

void CallSV(String s)
{
	String uid1 = "1";
	if (WiFi.status() == WL_CONNECTED)
	{
		httpMC.setReuse(true);
		// data = https_encode(data);
		httpMC.begin("http://192.168.55.108:5555/api/lenRequest?param=" + s);
		// Serial.println(data);
		int httpCode = httpMC.GET();
		httpMC.setConnectTimeout(5000);
		uart0.println(httpCode);
		if (httpCode > 0)
		{									  // Check the returning code
			String sout = httpMC.getString(); // Get the request response payload
			Serial.println("http out:" + sout);
		}
		else
		{
			// mocua();
		}
		httpMC.end();
	}
}