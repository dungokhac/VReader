// bipset
//độ ngân 1: 75; 2:150; 3:350; 4:500

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
void setbip(int n)
{
    switch (n)
    {
    case Cham_the:
        bip(1, 2);
        break;
    case Nhac_the:
        bip(2, 1);
        break;
    case Cham_van_tay:
        bip(1, 3);
        break;
    case Thanh_Cong:
        bip(2, 1);
        break;
    case Loi:
        bip(3, 1);
        break;
    }
}

void bip(int len, int type)
{
    //
    for (int i = 0; i < len; i++)
    {
        coi_on;
        delay(75 * type);
        coi_off;
        delay(75 * type);
    }
}

void led_test()
{
	led_cnt &= 0x1f;
	if (led_cnt <= 0)
	{
		led1_on = 0;
		if (wifi_on)
			led1_on++;
		if (pc_ip_cnt)
			led1_on = 2;
		if (fs01_on)
			led1_on += 2;
		led_cnt = led1_on * 2 + 2;
	}
	else if ((--led_cnt & 1) && led1_on)
	{
		led1_on--;
		on_led1;
	}
	else
	{
		off_led1;
	}
	if (led_reset)
	{
		led_reset--;
		on_led1;
	}
}


void bipok1()
{
	coi_on;
	delay(150);
	coi_off;
	delay(150);
}
void bipok2()
{
	bipok1();
	bipok1();
}
void biper1()
{
	coi_on;
	delay(500);
	coi_off;
	delay(500);
}
void biper2()
{
	biper1();
	biper1();
}

void bip4_no_internet()
{
	coi_on;
	delay(300);
	coi_off;
	delay(300);
	coi_on;
	delay(300);
	coi_off;
	delay(300);
}
