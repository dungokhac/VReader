
#include "vimass.h"
#include "SPIFFS.h"
#include <Math.h>
#include <dummy.h>
#include <WiFi.h>
#include "esp_attr.h"
#include "HardwareSerial.h"
#include <audio.h>
#include <WiFiMulti.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <MD5.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define hang_doi_tong 3

WiFiMulti wifiMulti;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
IPAddress apIP(192, 168, 2, 2), ap_gateway(192, 168, 2, 1), bcast_ip(192, 168, 2, 255), my_ip, pc_ip, esp2_ip, myIP, pc_IP, bcast_IP, tmp_IP;
WiFiUDP myUDP;
WiFiUDP ntpUDP;
WebServer server1(80);
WiFiUDP Udp; // Creation of wifi Udp instance
NTPClient timeClient(ntpUDP);
int trangthailenhtumaytinh = 0;
int ghivantay = 0;
int play_index = -1;
int soluongthietbi = 50000;
int duong_ra = 0, hang_doi_front = 0, hang_doi_rear = 0, hang_doi_sothietbidangdoi = 0, hang_doi_sothietbidangdoi2 = 0; // phan tu dau, phan tu cuoi

int64_t ms64_0, ms64, delta64;
int32 e_predsample, d_predsample;
String ReplyBuffer = "OK"; // a string to send back

int16 led_cnt, led1_on, led2_on, led_reset = 5, ms200 = 0, ms1000 = 0, pc_ip_cnt = 0;
int16 ms10, pc_on, wifi_status, string_valid_cnt, ms2;
int16 timer_1ms, udp_time = 0;
int16 wifi_on, file_ok, udp_on = 0, serial_on = 0;
int16 new_millis, old_millis, rx2_time_out;
int16 v_stat = 0, msg_type;
int16 my_id, hd_len;
int16 ms5, fp_off = 0, fp_on = 0, fp_detect_cnt = 0, fp_off_delay = 300, fp_mode_delay = 0, fp_fail = 0, fp_off_max = 500;
int16 tx_pkt_len, hd_index, buf_id, match_delay = 0, pulse_width = 300, pulse_max = 3;
int16 page_id;
int16 hd_ok = 0, rx_pkt_len, rx_cnt = 0, pkt_type, check_sum, check_sum_ok;
int16 voice_len, pwm_val, pwm_on = 0, ima_buf_cnt = 0, sin_cnt = 0, ima_haft = 0, pwm_send = 0;
int16 n_prefix, response, ret, ret_code, door_cnt, fp_index = 0;
int16 bip_on = 0, fs01_on = 0, fp_auto_off, fp_on_duration, fp_on_max;
int16 e_index, d_index;
int16 encode_buf[2048];
int16 vtlen = 0, kmlen = 0, cnt_w = 20;
uint16 r_port = 6000, solannhapmk = 0;
int16 rs485_tx_out = 0;
// ========vua nhap pass gui confirm
int16 vuaNhapPassConfirm = 0;
int vt_save = 1000;
int8 demghi = 0;
uint8 udp_in_buf[1400];
uint8 char_buf[char_buf_len];
// uint8 datavantay[500];
uint8 rx_buf[rx_max];
uint8 ima_buf[ima_buf_max];
uint8 pwm_tmp, offset_wfp[12];
int offset_write = 0, demvt = 0;
int8 n_time[6];

char ssid_name[32], ssid_pass[32];

String s_log = "", magiaodich = "", str_door = "", str_lenhtbngoai = "", strdvtt = "", strdichvumaytram = "";
String idDelaySend[1]; // mã giao dịch kèm theo mật khẩu
String my_mac, serial_rs485, dulieughixacthuc = "", dau_dlxacthuc = "";
String iplocal[1];
String fp_save[9];
String strip = "";
String datavantay2[8];
String vantay1 = "", vantay2 = "", datavantay1 = "";
String vantayw = "14141E57A15B866A25BE9E6E4D9D0272A97B0D76B977157A93EF1D7EB3E12582A7C75A0DEF976F032047EF3D4869460977940711E2ACAD086070D57D63FE9F3845B9AFB646682EFAF1C25F60F2618A202F8AF3263E9090EF6910B4DA67CFF2352AFBBC6F43EE6AD2E05660BA784E7042E2526E976234C18A8531CE6A863CD71A067CDC7F49A6A61FF35CA117435B282EAFE854EEE0404606211328D5C1482420195758C000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000014141C59A0538A6A05BEBE6E4D9D0272A97B0D76B977157A93EF1D7EB3E12582A7C75A0DEF97C3366B44AA28826CB3654396F46321B4BF57A658DF49E4DEC6303BB9BA9F19EAAD8EF5415ED2C765AEA6E9861D588380D4EF8E1A31AC0B7F1473665C24276361BB1A785EE23AB0586DF2B4FA53DEF370EBA202F9EB468BC8C0F7DD7FC1C688FA8EC74EE7C1BFE0203F56F26AE816D09914AF364B1CEF0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000249D0000";
String uid_the = "", vid_the = "", ma_tbi = "", data_chamcong = "", datafpreadtoesp32 = ""; // uid cua the
// == ip may chu mang noi bo
String tbttid[1];
// ======tham so confirm
String idDelayConfirm[1];
// ========dich vu F1
String dataServices[1];
// uint8 datavantay[rx_max];
String serial_in, params_str, serial2_out, serial2_in, vantay = "", khuonmat = "";
String ds_name[ds_max][sub_ds_max];
String str_name[4], str_pass[4];
String passDelaySend[1];
String hang_doi[hang_doi_tong];
String ssparam = "", offset_fp = "";

bool Validate = false;
bool TrangThaiThanhToan = false;
bool DichVuMayTram = false;
bool TrangThaiCacheCard = false;
bool xacthucvantay = 0, xacthuckhuonmat = 0, xacthutiengnoi = 0, ghi_ma_tbi = 1;
bool auto_docvt = 1;

cmd_tx_struct cmd_tx;
cmd_rx_struct cmd_rx;
data_tx_struct data_tx;
data_rx_struct data_rx;
udp_rx_header udp_rx;
udp_tx_header udp_tx;

res_data_packet vt1, vt2;

struct struct_max
{
	int16 fx;
	int16 lcd_line;
	int16 dv_line0;
	int16 dv_index;
	int16 dv_index_max;
	int16 dv_td_index;
	int16 dv_td_index_max;
	int16 line_type[8];
	int16 ds_index;
	int16 ds_index_max;
	int16 sub_ds_index;
	int16 sub_ds_index_max[ds_max];
};
struct_max v_fx;

String dv_td[dv_max];

struct cfg_struct
{
	int16 media;
	int16 key_bounce;
	int16 key_inhibit;
	int16 brate0;
	int16 https_timeout;
	int16 page_delay[4];
};
cfg_struct v_cfg;

void setup()
{
	Serial.begin(115200, SERIAL_8N1);
	Serial2.begin(115200, SERIAL_8N1);
	Serial1.begin(115200, SERIAL_8N1, pin_rx1, pin_tx1);
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(COI, OUTPUT);
	coi_off;
	off_led2;
	file_ok = (SPIFFS.begin(true)) ? 1 : 0;
	wifi_setup();
	readFile("/hello.txt"); // đọc mã đầu đọc từ file
	my_id = 10000;			// ip thiết bị
	save_id();				// lưu mã tb vào file
	bipok1();
}

void loop()
{
	millis_1();
}

void millis_1()
{
	new_millis = millis() & 0x3fff;
	if (old_millis == new_millis)
		return;
	old_millis = new_millis;
	serial_test();
	serial2_test();
	serial2_out_test();
	UDP_receive1();

	ms10 &= 0xf;
	if (++ms10 > 9) // vong lap 10ms
	{
		ms10 = 0;
		fp_test();
		int wifi_status = WiFi.status();
		if (wifi_status == WL_CONNECTED)
			wifi_on = 300;
		if (wifi_on)
			wifi_on--;
		else
			ESP.restart();
		if (pc_ip_cnt)
		{
			pc_ip_cnt--;
		}
		else
		{
			pc_ip = bcast_ip;
			r_port = 6000;
		}
		if (fp_auto_off)
			fp_auto_off--;
	}
	ms200 &= 0x1ff;
	if (++ms200 > 200) // vong 200ms kiem tra led
	{
		ms200 = 0;
		led_test();
	}
	ms1000 &= 0xfff;
	if (++ms1000 > 1000)
	{
		ms1000 = 0;
		bcast_out();
	}
}

void fp_test()
{
	if (auto_docvt)
	// if (digitalRead(fp_detect_pin))
	{
		if (fp_detect_cnt < 100)
			fp_detect_cnt++;
		fp_on_duration++;
	}
	else
	{
		if (fp_detect_cnt)
		{
			fp_detect_cnt--;
		}
		else
		{
			if (fp_on_duration)
			{
				fp_on_max = fp_on_duration;
				fp_on_duration = 0;
			}
		}
	}
	if (fp_detect_cnt >= 50)
	{
		fp_detect_cnt = 0;
		if (fp_auto_off == 0)
		{
			cmd_send(Identify, 0, 0);
			uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
		}
	}
}
// void writedatatofs01(int n)
// {
// 	uart0.println(n);
// 	uint8_t FP[498];
// 	for (int i = 0; i < 498; i++)
// 	{
// 		FP[i] = convertHexStrToDec(vantayw.substring(i * 2, i * 2 + 2));
// 		// Serial.print(FP[i] , HEX);
// 	}
// 	for (int i = 1; i < 250; i++)
// 	{
// 		vt1.data[i] = (FP[2 * i - 1] << 8) + (FP[2 * i - 2]);
// 	}

// 	fp_func_write_template(vt1, n);
// }

// void writedatatoesp32(String s)
// {
// 	File f = SPIFFS.open("/datavt1.txt", "w");
// 	if (f)
// 		f.print(s);
// 	f.close();
// 	uart0.println("Ghi vt 1 vao esp");
// }
// void readdatatoesp32(const char *path)
// {

// 	File file = SPIFFS.open(path);
// 	if (!file || file.isDirectory())
// 	{
// 		//  Serial.println("− failed to open file for reading");
// 		return;
// 	}
// 	datafpreadtoesp32 = "";
// 	int n = 0;
// 	//  Serial.println("− read from file:");
// 	while (file.available())
// 	{
// 		n = file.read();
// 		datafpreadtoesp32 += dec_to_string(n - 48);
// 		// Serial.write(ma_tbi);
// 	}
// 	add_to_serial(datafpreadtoesp32);
// 	serial_out();
// 	//  uart0.println(ma_tbi);
// }

// void writedataesp32tofs01()
// {
// 	// uart0.println(n);
// 	uint8_t FP[498];
// 	for (int i = 0; i < 498; i++)
// 	{
// 		FP[i] = convertHexStrToDec(datafpreadtoesp32.substring(i * 2, i * 2 + 2));
// 		// Serial.print(FP[i] , HEX);
// 	}
// 	for (int i = 1; i < 250; i++)
// 	{
// 		vt1.data[i] = (FP[2 * i - 1] << 8) + (FP[2 * i - 2]);
// 	}

// 	fp_func_write_template(vt1, 999);
// }