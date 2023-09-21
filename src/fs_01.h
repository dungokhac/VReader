#ifndef FS01_
#define FS01_
#define int8 int8_t
#define uint8 uint8_t
#define int16 int16_t
#define uint16 uint16_t
#define int32 int32_t
#define uint32 uint32_t
#define int64 int64_t
#define uint64 uint64_t

#define cmd_prefix 0xaa55
#define cmd_response_prefix 0x55aa
#define data_prefix 0xa55a
#define data_response_prefix 0x5aa5
#define char_buf_len 498
#define fp_cmd_prefix	                                    0xaa55
#define fp_cmd_response_prefix	                            0x55aa
#define fp_data_prefix	                                    0xa55a
#define fp_data_response_prefix	                            0x5aa5
struct cmd_tx_struct
{
    uint8 prefix[2];
    int16 cmd;
    int16 len;
    int16 data[8];
    int16 cks;
};
struct data_tx_struct
{
    uint8 prefix[2];
    int16 cmd;
    int16 len;
    int16 data[252];
};
struct cmd_rx_struct
{
    uint8 prefix[2];
    int16 rcm; // last cmd
    int16 len;
    int16 data[8];
    int16 cks;
};
struct data_rx_struct
{
    uint8 prefix[2];
    int16 rcm; // last cmd
    int16 len;
    int16 data[252];
};
struct udp_rx_header
{
    uint8 bcc;
    uint8 pkt_type;
    int16 cmd;
    int16 len;
    int16 page_id;
    int16 app_id;
    int16 seg_type;
    int16 seg_len;
    int16 data[512];
};
struct udp_tx_header
{
    uint8 bcc;
    uint8 pkt_type;
    int16 app_id;
    cmd_rx_struct cmd_rx;
    data_rx_struct data_rx;
};

enum fs01_code
{ // cũ
    Verify = 0x101,
    Identify,
    Enroll_3,
    Enroll_1,
    Delete_Page,
    Empty,
    Get_Empty_ID,
    Get_Page_Sta,
    Get_Broken_Page,
    Read_Page,
    Write_Page,
    Set_Security,
    Get_Security,
    Set_Time_Out,
    Get_Time_Out,
    Set_Device_ID,
    Get_Device_ID,
    Get_FW_Version,
    Finger_Detect,
    Set_BaudRate,
    Set_Dup_Check,
    Get_Dup_Check,
    Stadby_Mode,
    Enroll_RAM,
    Get_Enroll,
    Get_Feature,
    Verify_Feature,
    Identify_Feature,
    Get_Device_Name,
    LED_Control = 0x124,
    Identify_Free,
    Set_Psw,
    Verify_Psw,
    Get_Enroll_Count,
    Change_Page,
    FP_Cancel = 0x130,
    Test_Connection = 0x150,
    Incorrect_Command = 0x160
};

// enum fs01_code{ // mới
//     Verify=0x101,
//     Identify, Enroll_3, Enroll_1, Delete_Page,
//     Empty, Get_Empty_ID, Get_Page_Sta, Get_Broken_Page, Read_Page,
//     Write_Page, Set_Security, Get_Security, Set_Time_Out, Get_Time_Out,
//     Set_Device_ID, Get_Device_ID, Get_FW_Version, Finger_Detect, Set_BaudRate,
//     Set_Dup_Check, Get_Dup_Check, Stadby_Mode, wwwww, Get_Enroll,
//     Get_Feature, wwwww2, Identify_Feature, Get_Device_Name,
//     LED_Control=0x124,
//     Identify_Free, Set_Psw, Verify_Psw, Get_Enroll_Count, Change_Page,
//     FP_Cancel=0x130,
//     Enroll_RAM = 0x138,
//     Verify_Feature=0x13b,
//     Test_Connection=0x150,
//     Incorrect_Command=0x160
// };
const int16 cmd_len[] = {
    Verify, 2, Identify, 0, Enroll_3, 2, Enroll_1, 2, Delete_Page, 2,
    Empty, 0, Get_Empty_ID, 0, Get_Page_Sta, 2, Get_Broken_Page, 0, Read_Page, 2,
    Write_Page, 2, Set_Security, 2, Get_Security, 0, Set_Time_Out, 2, Get_Time_Out, 0,
    Set_Device_ID, 2, Get_Device_ID, 0, Get_FW_Version, 0, Finger_Detect, 0, Set_BaudRate, 2,
    Set_Dup_Check, 2, Get_Dup_Check, 0, Stadby_Mode, 0, Enroll_RAM, 0, Get_Enroll, 0,
    Get_Feature, 0, Verify_Feature, 2, Identify_Feature, 2, Get_Device_Name, 0, LED_Control, 2,
    Identify_Free, 0, Set_Psw, 14, Verify_Psw, 14, Get_Enroll_Count, 0, Change_Page, 2,
    FP_Cancel, 0, Test_Connection, 0, Incorrect_Command, 0};
enum
{
    Moi_dat_van_tay,
    Xin_cam_on,
    Moi_dat_the,
    Thanh_cong,
    Khong_thanh_cong
};
enum
{
    seg_begin,
    seg_append,
    seg_save
};
enum
{
    voice_download,
    voice_play,
    file_rename,
    file_list,
    set_bip_on,
    send_ev2,
    add_ssid
};

#define ERR_TMPL_EMPTY 0x13
#define ERR_TMPL_NOT_EMPTY 0x14
#define ERR_ALL_TMPL_EMPTY 0x15
#define ERR_EMPTY_ID_NOEXIST 0x16
#define ERR_BROKEN_ID_NOEXIST 0x17
#define ERR_INVALID_TMPL_DATA 0x18
#define ERR_DUPLICATION_ID 0x19
#define ERR_BAD_QUALITY 0x21
#define ERR_TIME_OUT 0x23
#define ERR_NOT_AUTHORIZED 0x24
#define ERR_GENERALIZE 0x30
#define ERR_FP_CANCEL 0x41
#define ERR_INTERNAL 0x50
#define ERR_EXCEPTION 0x51
#define ERR_INVALID_TMPL_NO 0x60
#define ERR_INVALID_SEC_VAL 0x61
#define ERR_INVALID_TIME_OUT 0x62
#define ERR_INVALID_BAUDRATE 0x63
#define ERR_INVALID_DUP_VAL 0x65
#define ERR_INVALID_PARAM 0x70
#define ERR_NO_RELEASE 0x71
#define GD_DOWNLOAD_SUCCESS 0xA1
#define GD_NEED_FIRST_SWEEP 0xFFF1
#define GD_NEED_SECOND_SWEEP 0xFFF2
#define GD_NEED_THIRD_SWEEP 0xFFF3
#define GD_NEED_RELEASE_FINGER 0xFFF4
#define GD_TEMPLATE_NOT_EMPTY 0x01
#define GD_TEMPLATE_EMPTY 0x00
#define ERR_SUCCESS 0x0
#define ERR_FAIL 0x1
#define fp_write_template 0x010b
#define fp_ERR_SUCCESS                                      0x0
#define fp_ERR_FAIL                                         0x1
#define fp_len_write_template                               500

struct cmd_packet
{
    uint8_t prefix[2];
    int16_t cmd;
    int16_t len;
    int16_t data[8];
    int16_t cks;
};

struct res_packet
{
    uint8_t prefix[2];
    int16_t rcm; // responsive code
    int16_t len;
    int16_t ret;
    int16_t data[7];
    int16_t cks;
};

struct cmd_data_packet
{
    uint8_t prefix[2];
    int16_t cmd;
    int16_t len;
    int16_t data[256];
    int16_t cks;
};

struct res_data_packet
{
    uint8_t prefix[2];
    int16_t rcm; // responsive code
    int16_t len;
    int16_t ret;
    int16_t data[256];
    int16_t cks;
};

struct fp_backup
{
    String idReader = "3";
    String idGetDataBackup = "3";
    String id7462;
    String Template;
    String index;
    int FPCount = 1000;
    int FPStatus;
    int FPIndexNow = -1;
};




#endif