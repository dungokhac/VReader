#include "vimass.h"

void fp_set_cks_cmd(cmd_packet &cmd_packet)
{
    uint8 *ptr;
    uint16 cks = 0;
    ptr = cmd_packet.prefix;
    for (int i = 0; i < 22; i++) // CKS : Carry out the arithmetic and operation from PREFIX to DATA by byte (0 to 21), take the lower result of 2byte data
    {
        cks += *ptr++;
    }
    cmd_packet.cks = cks;
}

void get_tx_cks(int16 len)
{
    uint8 *ptr;
    uint16 cks = 0,nn=0;
    if (len <= 2)
    {
        ptr = cmd_tx.prefix;
        for (int i = 0; i < (int)(sizeof(cmd_tx)) - 2; i++)
        {
            cks += *ptr++;
        }
        cmd_tx.cks = cks;
    }
    else if (len == 498)
    {
        ptr = data_tx.prefix;
        for (int i = 0; i < 6 + len; i++)
        {
            nn = *ptr++;
            cks += nn;
        }
        data_tx.data[len >> 1] = cks;
    }
}

int16 get_rx_cks(int16 len)
{
    int16 cks = 0;
    uint8 *ptr;
    if (len <= 2)
    {
        ptr = cmd_rx.prefix;
        for (int i = 0; i < (int)(sizeof(cmd_rx)) - 2; i++)
        {
            cks += *ptr++;
        }
        return (cmd_rx.cks == cks);
    }
    else
    {
        ptr = data_rx.prefix;
        for (int i = 0; i < 6 + len; i++)
        {
            cks += *ptr++;
        }
        return (cks == data_tx.data[len >> 1]);
    }
}

int16 get_cmd_len(int16 cmd)
{
    for (int i = 0; i < 38; i++)
    {
        if (cmd_len[i * 2] == cmd)
        {
            return cmd_len[i * 2 + 1];
        }
    }
    return 0;
}
void cmd_send(int16 cmd, int16 len, int16 page_id)
{
    switch (cmd)
    {
    case Verify:
    case Identify:
    case Enroll_3:
    case Enroll_1:
    case Get_Feature:
    case Verify_Feature:
    case Enroll_RAM:
    // case Set_Security:
    // case Get_Security:
    case Identify_Feature:
        fp_auto_off = 250;
        break;
    default:
        break;
    }
    switch (len)
    {
    case 0:
    case 2:
        cmd_tx.prefix[0] = cmd_prefix & 0xff;
        cmd_tx.prefix[1] = (cmd_prefix >> 8) & 0xff;
        cmd_tx.cmd = cmd;
        cmd_tx.len = len;
        memset(cmd_tx.data, 0, sizeof(cmd_tx.data));
        if (cmd == Verify_Feature)
        {
            cmd_tx.data[0] = 498;
            memcpy(char_buf, udp_rx.data, char_buf_len);
        }
        else if (cmd == Set_Security)
        {
            cmd_tx.data[0] = 2;
            cmd_tx.data[1] = 0;
            // memset(cmd_tx.data, 0, sizeof(cmd_tx.data));
        }
        else if (cmd == Get_Security)
        {
            cmd_tx.data[0] = 0;
            cmd_tx.data[1] = 0;
            // memset(cmd_tx.data, 0, sizeof(cmd_tx.data));
        }
        else if (len)
        {
            cmd_tx.data[0] = page_id;
        }
        get_tx_cks(len);
    case 14:
        break;
    case 498:
        data_tx.prefix[0] = data_prefix & 0xff;
        data_tx.prefix[1] = (data_prefix >> 8) & 0xff;
        data_tx.cmd = cmd;
        data_tx.len = len;
        memcpy(data_tx.data, char_buf, char_buf_len);
        get_tx_cks(len);
        break;
    }
      if (cmd ==  Enroll_1 || cmd == Enroll_3)
      {
        delay(1000);
        // Play_voice(Moi_dat_van_tay);
        // delay(1000);
      }
}
bool cmd_found(int16 cmd)
{
    bool b = false;
    for (int i = 0; i < sizeof(cmd_len) / 4; i++)
    {
        if (cmd == cmd_len[i * 2])
        {
            b = true;
            i = sizeof(cmd_len);
        }
    }
    return b;
}
void cmd_switch()
{
    rx_cnt = 0;
    // String sss = "";
    // for (int i = 0; i < sizeof(udp_in_buf); i++)
    // {
    //     sss += udp_in_buf[i];

    // }
    // uart0.println("udp_rx.cmd:"+String(udp_rx.cmd));
    String s = "";
    int16 len = 0;
    // if(cmd_found(udp_rx.cmd)){

    if ((udp_rx.cmd > 0x100) && (udp_rx.cmd < 0x151))
    {
        cmd_send(udp_rx.cmd, udp_rx.len, udp_rx.page_id);
        uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
        led_reset = 5;
        return;
    }
    switch (udp_rx.cmd)
    {
    case voice_download:

        break;
    case voice_play:


        break;
    case file_rename:
        break;
    case file_list:
        // string_send(list_file());
        reset_7462("2xx3"); // kiểm tra vị trí lưu vân tay
        break;
    case set_bip_on:
        xacthucvantay = 1; 
        reset_7462("2xx2"); // du dang lam
        break;
    case send_ev2:
        memcpy(char_buf, udp_rx.data, char_buf_len);
        char_buf_to_ev2();

        break;
    case add_ssid:
        String fl ;
 
        for (int i = 0; i < 10; i++)
        {
            fl = "/a_"+String(i)+".wav";
            if (remove(fl))
            {
                uart0.println("Xoa"+fl+" thanh cong");
            }else{
                uart0.println("Xoa "+fl+"  khong thanh cong");
            }
        }
        
        break;
    }
}
void save_data_block(res_data_packet &res_data_packet, uint8_t *res_data)
{
    res_data_packet.prefix[0] = res_data[0];
    res_data_packet.prefix[1] = res_data[1];
    res_data_packet.rcm = (res_data[3] << 8) + res_data[2];
    res_data_packet.len = (res_data[5] << 8) + res_data[4];
    res_data_packet.ret = (res_data[7] << 8) + res_data[6];
    for (int i = 0; i < (int)(res_data_packet.len / 2 - 1); i++)
    {
        res_data_packet.data[i] = (res_data[2 * i + 9] << 8) + res_data[2 * i + 8];
    }
    res_data_packet.cks = (res_data[res_data_packet.len + 9] << 8) + res_data[res_data_packet.len + 8];
}

void fp_func_write_template(res_data_packet res_data_packet_in, int16_t id)
{
    cmd_packet fp_cmd;
    cmd_data_packet fp_data;
    res_packet res_packet1;
    res_packet res_packet2;
    res_packet res_packet3;
    res_packet res_packet4;
    res_packet res_packet5;
    res_packet res_packet;
    res_data_packet res_data_packet;

    fp_set_cmd_packet(fp_cmd, fp_write_template, 2, 498);
    fp_send_cmd(fp_cmd);
    fp_cmd_res(res_packet1, res_packet2, res_packet3, res_packet4, res_packet5, 3000);
    if ((res_packet1.rcm == fp_write_template) && (res_packet1.ret == fp_ERR_SUCCESS))
        Serial.println("Bat dau ghi van tay");
    else
    {
        Serial.println("Ghi van tay that bai");
        play_audio(khong_thanh_cong, sizeof(khong_thanh_cong));
        return;
    }
    fp_set_cmd_data_packet_id(fp_data, fp_write_template, fp_len_write_template, res_data_packet_in.data, id);
    fp_send_data(fp_data);
    fp_data_res(res_packet, res_data_packet, 1000);
    if ((res_data_packet.rcm == fp_write_template) && (res_data_packet.ret == fp_ERR_SUCCESS))
    {
        Serial.println("Ghi van tay thanh cong");
        // play_audio(thanh_cong, sizeof(thanh_cong));
    }
    else
    {
        Serial.println("Ghi van tay that bai");
        // play_audio(khong_thanh_cong, sizeof(khong_thanh_cong));
        return;
    }
}
void fp_set_cks_data(cmd_data_packet &cmd_data_packet)
{
    uint8 *ptr;
    uint16 cks = 0;
    ptr = cmd_data_packet.prefix;
    for (int i = 0; i < 6 + cmd_data_packet.len; i++) // CKS : Carry out the arithmetic and operation from PREFIX to DATA by byte (0 to 6 + len DATA), take the lower result of 2byte data
    {
        cks += *ptr++;
    }
    cmd_data_packet.cks = cks;
}

void fp_set_cmd_packet(cmd_packet &cmd_packet, int16_t cmd, int16_t len, int16_t data)
{
    cmd_packet.prefix[0] = fp_cmd_prefix & 0xff;
    cmd_packet.prefix[1] = (fp_cmd_prefix >> 8) & 0xff;
    cmd_packet.cmd = cmd;
    cmd_packet.len = len;
    memset(cmd_packet.data, 0, sizeof(cmd_packet.data));
    cmd_packet.data[0] = data;
    fp_set_cks_cmd(cmd_packet);
}

void fp_send_cmd(cmd_packet cmd_packet)
{
    uint8_t cmd[24];
    cmd[0] = cmd_packet.prefix[0];
    cmd[1] = cmd_packet.prefix[1];
    cmd[2] = cmd_packet.cmd & 0xff;
    cmd[3] = (cmd_packet.cmd >> 8) & 0xff;
    cmd[4] = cmd_packet.len & 0xff;
    cmd[5] = (cmd_packet.len >> 8) & 0xff;
    for (int i = 0; i < 8; i++)
    {
        cmd[2 * i + 6] = cmd_packet.data[i] & 0xff;
        cmd[2 * i + 7] = (cmd_packet.data[i] >> 8) & 0xff;
    }
    cmd[22] = cmd_packet.cks & 0xff;
    cmd[23] = (cmd_packet.cks >> 8) & 0xff;
    fp_serial.write(cmd_packet.prefix, sizeof(cmd_packet));
    for (int i = 0; i < 24; i++)
    {
        Serial.print(cmd[i], HEX);
    }
    Serial.println();
}
void save_block(res_packet &block, uint8_t *res_data)
{
    block.prefix[0] = res_data[0];
    block.prefix[1] = res_data[1];
    block.rcm = (res_data[3] << 8) + res_data[2];
    block.len = (res_data[5] << 8) + res_data[4];
    block.ret = (res_data[7] << 8) + res_data[6];
    for (int i = 0; i < 7; i++)
    {
        block.data[i] = (res_data[2 * i + 9] << 8) + res_data[2 * i + 8];
    }
    block.cks = (res_data[23] << 8) + res_data[22];
}
void fp_cmd_res(res_packet &block1, res_packet &block2, res_packet &block3, res_packet &block4, res_packet &block5, const int timeout)
{
    uint8_t res_data[120];
    uint8_t data_block1[24], data_block2[24], data_block3[24], data_block4[24], data_block5[24];
    int index = 0;
    long int times = millis();
    while ((times + timeout) > millis())
    {
        while (fp_serial.available())
        {
            res_data[index++] = fp_serial.read() & 0xff;
        }
    }
    Serial.println(index);
    if (index == 24)
    {
        for (int i = 0; i < 24; i++)
        {
            data_block1[i] = res_data[i];
        }
        save_block(block1, data_block1);
    }
    else if (index == 48)
    {
        for (int i = 0; i < 24; i++)
        {
            data_block1[i] = res_data[i];
        }
        for (int i = 24; i < 48; i++)
        {
            data_block2[i - 24] = res_data[i];
        }
        save_block(block1, data_block1);
        save_block(block2, data_block2);
    }
    else if (index == 96)
    {
        for (int i = 0; i < 24; i++)
        {
            data_block1[i] = res_data[i];
        }
        for (int i = 24; i < 48; i++)
        {
            data_block2[i - 24] = res_data[i];
        }
        for (int i = 48; i < 72; i++)
        {
            data_block3[i - 48] = res_data[i];
        }
        for (int i = 72; i < 96; i++)
        {
            data_block4[i - 72] = res_data[i];
        }
        save_block(block1, data_block1);
        save_block(block2, data_block2);
        save_block(block3, data_block3);
        save_block(block4, data_block4);
    }
    else if (index == 120)
    {
        for (int i = 0; i < 24; i++)
        {
            data_block1[i] = res_data[i];
        }
        for (int i = 24; i < 48; i++)
        {
            data_block2[i - 24] = res_data[i];
        }
        for (int i = 48; i < 72; i++)
        {
            data_block3[i - 48] = res_data[i];
        }
        for (int i = 72; i < 96; i++)
        {
            data_block4[i - 72] = res_data[i];
        }
        for (int i = 96; i < 120; i++)
        {
            data_block5[i - 96] = res_data[i];
        }
        save_block(block1, data_block1);
        save_block(block2, data_block2);
        save_block(block3, data_block3);
        save_block(block4, data_block4);
        save_block(block5, data_block5);
    }
    else if (index == 0)
    {
        for (int i = 0; i < 24; i++)
        {
            data_block1[i] = 0;
            data_block2[i] = 0;
            data_block3[i] = 0;
            data_block4[i] = 0;
            data_block5[i] = 0;
        }
        save_block(block1, data_block1);
        save_block(block2, data_block2);
        save_block(block3, data_block3);
        save_block(block4, data_block4);
        save_block(block5, data_block5);
    }
}
void fp_set_cmd_data_packet_id(cmd_data_packet &cmd_data_packet, int16_t cmd, int16_t len, int16_t *data, int16_t id)
{
    cmd_data_packet.prefix[0] = fp_data_prefix & 0xff;
    cmd_data_packet.prefix[1] = (fp_data_prefix >> 8) & 0xff;
    cmd_data_packet.cmd = cmd;
    cmd_data_packet.len = len;
    memcpy(cmd_data_packet.data, data, sizeof(cmd_data_packet.data));
    cmd_data_packet.data[0] = id;
    fp_set_cks_data(cmd_data_packet);
}

void fp_send_data(cmd_data_packet cmd_data_packet)
{
    uint8_t cmd_data[cmd_data_packet.len + 8];
    cmd_data[0] = cmd_data_packet.prefix[0];
    cmd_data[1] = cmd_data_packet.prefix[1];
    cmd_data[2] = cmd_data_packet.cmd & 0xff;
    cmd_data[3] = (cmd_data_packet.cmd >> 8) & 0xff;
    cmd_data[4] = cmd_data_packet.len & 0xff;
    cmd_data[5] = (cmd_data_packet.len >> 8) & 0xff;
    for (int i = 0; i < (int)(cmd_data_packet.len / 2); i++)
    {
        cmd_data[2 * i + 6] = cmd_data_packet.data[i] & 0xff;
        cmd_data[2 * i + 7] = (cmd_data_packet.data[i] >> 8) & 0xff;
    }
    cmd_data[cmd_data_packet.len + 6] = cmd_data_packet.cks & 0xff;
    cmd_data[cmd_data_packet.len + 7] = (cmd_data_packet.cks >> 8) & 0xff;
    fp_serial.write(cmd_data, sizeof(cmd_data));
    // for(int i =0; i<cmd_data_packet.len + 8; i++){
    //     Serial.print(cmd_data[i], HEX);
    // }
    // Serial.println();
}

void fp_data_res(res_packet &res_packet, res_data_packet &res_data_packet, const int timeout)
{
    uint8_t res_data[800];
    uint8_t res_data1[800];
    int index = 0, i = 0;
    long int times = millis();
    uint8_t data_block1[24];
    while ((times + timeout) > millis())
    {
        while (fp_serial.available())
        {
            res_data[index++] = fp_serial.read() & 0xff;
        }
    }

    for (i = 0; i < index - 24; i++)
    {
        uint8_t n = res_data[i + 24];
        res_data1[i] = n;
    }
    Serial.println(index);
    uint8_t data_block2[index];
    if (index == 12)
    {
        for (int i = 0; i < index; i++)
        {
            data_block2[i] = res_data[i];
        }
        save_data_block(res_data_packet, data_block2);
    }
    else if (index == 24)
    {
        for (int i = 0; i < 24; i++)
        {
            data_block1[i] = res_data[i];
        }
        save_block(res_packet, data_block1);
    }
    else if (index > 24)
    {
        for (int i = 0; i < 24; i++)
        {
            data_block1[i] = res_data[i];
        }
        save_block(res_packet, data_block1);
        // for (int i = 24; i < index; i++)
        // {
        //     data_block2[i - 24] = res_data[i];
        // }
        save_data_block(res_data_packet, res_data1);
    }
}