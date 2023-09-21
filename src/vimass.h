#ifndef V_H_
#define V_H_
#include "fs_01.h"
#define rx_max 1024
#define fx_waiting 0
#define dv_selecting 1
#define dv_inputing 2
#define dv_d_Button 3
#define dv_PASS 4
#define dv_PASS_DOOR 5
#define dv_F1 6
#define ra_udp 1
#define LED1 15// vr1 la 25 va 26
#define LED2 2
#define COI 33//vr1 la 23
#define https_src	1
#define  coi_on digitalWrite(COI,1)
#define  coi_off digitalWrite(COI,0)

#define  off_led1 digitalWrite(LED1, 1)
#define  on_led1 digitalWrite(LED1, 0)

#define  off_led2 digitalWrite(LED2, 1)
#define  on_led2 digitalWrite(LED2, 0)

#define rs485_media	0
#define https_media 1
#define dv_max 32
#define ds_max 32
#define sub_ds_max 64
#define FS01_STRING                  0x0
#define FS01_BCAST                   0x1
#define FS01_CMD                     0x2
#define FS01_DATA                    0x3
#define FS01_02                      0x4
#define PC_BCAST                     0x10
#define PC_01                        0x11
#define PC_02                        0x12
#define FS02_STRING                  0x20
#define FS02_BCAST                   0x21
#define FS02_CMD                     0x22
#define FS02_DATA                    0x23
#define FS02_01                      0x24
#define nfc_to_pc 0x31
#define pc_to_nfc 0x32
#define pc_to_lcd 0x33
#define nfc_to_lcd 0x34
#define esp_to_pc 0x35
#define pc_to_esp 0x36
#define pc_to_https 0x37
#define rs485_query 0x38
#define wifi_reset 0x39
#define ram_write 0x41
#define wifi_write 0x42
#define pwm_ch 0
#define freq  78125
#define pwm_bit  9
#define zero_level 256
#define ima_seg_max 32
#define ima_seg_len 1024        
#define ima_buf_max 32768        
#define fp_serial Serial1
#define pkt_cmd 1
#define pkt_data 0

#define cmd_buf_max 16
#define total_page_len 200
const int16 sin8[]={0, 180, 255, 180, 0, -180, -255, -180};
const String s_hex="0123456789ABCDEF";

#define uart0   Serial
#define uart1   Serial1
#define uart2   Serial2

#define pin_tx1   27
#define pin_rx1   14

// #define buzze_ctrl 23
#define rs485_ctrl 32
#define door_gate 25

#define pwm_pin 26      // 34
#define fp_detect_pin 4 //36
#define master_in 36
#define door_open digitalWrite(door_gate,1)
#define door_close digitalWrite(door_gate,0)
#define rs485_out digitalWrite(rs485_ctrl,1)
#define rs485_in digitalWrite(rs485_ctrl,0)
// #define buzze_on digitalWrite(buzze_ctrl,1)
// #define buzze_off digitalWrite(buzze_ctrl,0)


/* coi thong bao
1. chạm thẻ
2. nhấc thẻ
3. chạm vân tay
4. Thành công
5. lỗi.
#define Cham_the 1
#define Nhac_the 2
#define Cham_van_tay 3
#define Thanh_Cong 4
#define Loi 5
*/
#define Cham_the 1
#define Nhac_the 2
#define Cham_van_tay 3
#define Thanh_Cong 4
#define Loi 5
#endif


// iiik^.....ssss#
// iii id : 0-999
// k : key_code (1-20) = ascii(k) - 0x40
// ssss check sum

// ^6ramwr_dv00_CHUYEN DEN DT_SO TIEN=_SO DIEN THOAI=_ _MK THE=_*dv01_  	*
// ^6ramwr_nt00_Ngan hang A Chau_Ngan hang Phuong Nam_ ...*nt01_ 			*
// ^3cl*li0_This line 1*li1_This line 2*csccr*
// ^3pa0_line 1_line 2_line 3_line 4*pa1_line 1_line 2_line 3_line 4*pa2_line 1_line 2_line 3_line 4_*