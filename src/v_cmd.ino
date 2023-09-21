void new_cmd(String s0, uint8 src)
{
	// s0 = "^2x1^";
	int k;
	String s, s1;
	while (s0.startsWith("^"))
	{
		s0.remove(0, 1);	 // s0 =2x1^
		k = s0.indexOf("^"); // k=3
		if (k >= 0)
		{
			s1 = s0.substring(0, k); // s1=2x1
			s0.remove(0, k);		 // s0=""
			k = s1.charAt(0);
			s1.remove(0, 1);
			switch (k)
			{
			case pc_to_lcd:
				if (s1.length())
				{
				}
			case nfc_to_lcd:
				if (s1.length())
				{
				}
				break;
			case wifi_reset:
				WiFi.disconnect(true);
				delay(2000);
				ESP.restart();
				break;
			case rs485_query:
				// add_to_serial(s1);
				// serial_out();
				break;
			case pc_to_nfc:
				resetServicesStatus();

				serial2_out += "!^2" + s1 + "#";
				// serial2_out="!^2xx3#";//ducmt
				// serial2_out="!^2x7#";//ducmt
				uart0.println("7462 out:" + serial2_out);
				break;
			case pc_to_https:
				// send_https(https_encode(s1));
				send_https(s1);
				break;
			case ram_write:
				ram_wr(s1);
				break;
			case wifi_write:
				save_ssid(s1);
				break;
			case pc_to_esp:
				while (s1.startsWith("*"))
				{
					s1.remove(0, 1);
					k = s1.indexOf("*");
					if (k >= 0)
					{
						s = s1.substring(0, k);
						s1.remove(0, k);
						// add_to_serial("from may tram--"+s+"--");
						// 	serial_out();
						caidatthietbi(s);
					}
					else
					{
						s1 = "";
					}
				}
				break;
			}
		}
		else
		{
			s0 = "";
		}
	}
	// serial_out();
}

void resetServicesStatus()
{
	// nam
	Validate = false;
	// TrangThaiThanhToan = false;
	// magiaodich="";
	//======
	str_door = "";
	v_stat = fx_waiting;
	dataServices[0] = "";
	strdvtt = "";
	str_lenhtbngoai = "";
	idDelaySend[0] = "";
	solannhapmk = 0;
}

void ram_rd(String s)
{
	for (int i = 0; i < v_fx.dv_index_max; i++)
	{
		if (s.length() < 3500)
			s += "dv" + n_fix_len(i, 2) + dv_td[i] + "_";
	}
	// add_to_serial(s);
	for (int i = 0; i < v_fx.ds_index_max; i++)
	{
		s += "ds" + n_fix_len(i, 2) + "_";
		for (int j = 0; j < v_fx.sub_ds_index_max[i]; j++)
		{
			if (s.length() < 3500)
				s += ds_name[i][j] + "_";
		}
	}
	// add_to_serial(s);
}

void new_time(String s)
{
	s.remove(0, 5);
	if (s.length() > 5)
	{
		ms64 = millis();
		n_time[0] = n_time[3] = s.substring(0, 2).toInt();
		s.remove(0, 2);
		n_time[1] = n_time[4] = s.substring(0, 2).toInt();
		s.remove(0, 2);
		n_time[2] = n_time[5] = s.substring(0, 2).toInt();
	}
}
String n_fix_len(int16 n, int16 len)
{
	return fix_len(String(n), len);
}

String fix_len(String s, int16 len)
{
	if (s.length() > len)
		s = s.substring(s.length() - len, s.length());
	while (s.length() < len)
	{
		s = "0" + s;
	}
	return s;
}

void ram_wr(String s)
{
	String s0;
	int k;
	while (s.startsWith("*"))
	{
		s.remove(0, 1);
		k = s.indexOf("*");
		if (k >= 0)
		{
			s0 = s.substring(0, k);
			s.remove(0, k);
		}
		else
		{
			s = "";
		}
	}
	v_stat = dv_selecting;
	// lcd.clear();
	// lcd.print(String(v_fx.dv_index_max));
}
String bcc_check_len(String s, int a)
{
	int32 bcc = 0;
	for (int i = 0; i < s.length(); i++)
	{
		bcc += (uint8)s.charAt(i);
	}
	return fix_len(String(bcc), a);
}
String bcc_check_step(String s, int step)
{
	int32 bcc = 0;
	int32 tong = 0;
	int i = 0;
	for (i = 0; i < s.length(); i++)
	{
		bcc = (uint8)s.charAt(i);
		if (i % step == 0)
			bcc = bcc + (i / step) + 3;
		tong += bcc;
	}
	return fix_len(String(tong), 4);
}

void add_to_serial(String s)
{
	serial_rs485 = s;
}
void serial_out()
{
	if (serial_rs485.length())
	{
		rs485_tx_out = 127;
		rs485_out;
		Serial.print(serial_rs485);
		serial_rs485 = "";
	}
}

void khoitao_ghixacthuc(String s)
{

	dau_dlxacthuc = s.substring(1, 20);
	s.remove(0, 20);
	dulieughixacthuc = s;
	s = "";
	trangthailenhtumaytinh = 1;
	// reset_7462("2x7");// bat dau ghi xac thuc
}

void Docxacthuc5()
{ // doc xac thuc fi5
	bipok1();
	reset_7462("2xx1");
}
void Docxacthuc6()
{ // doc xac thuc fi6
	bipok1();
	reset_7462("2xx2");
}

//-------encode-decode
// key key.txt
// tạo mảng node
// chuyển char -> số
// chuyển hex string thanh số
// số thành hex string
// hex string thanh mang hex ok
/*
void
*/
uint8_t convertHexStrToDec(String s)
{
	int length = s.length();
	size_t digitCount = 0;
	uint16_t dataIndex = 0;
	uint8_t dataHex = 0;
	for (size_t i = 0; i < length; i++)
	{
		// int8 n = (uint8)s.charAt(i) ;
		char digit = s[i];
		byte nybble = 99;
		if (digit >= '0' && digit <= '9')
		{
			nybble = digit - '0';
		}
		else if (digit >= 'A' && digit <= 'F')
		{
			nybble = digit - 'A' + 10;
		}
		else if (digit >= 'a' && digit <= 'f')
		{
			nybble = digit - 'a' + 10;
		}
		else
			nybble = 99;

		if (nybble != 99)
		{
			dataHex <<= 4; // số thấp
			dataHex += nybble;
			digitCount++;
			// if (digitCount == 2)
			// {
			// 	// This byte is full
			// 	dataIndex++;
			// 	dataHex = 0;
			// 	digitCount = 0;
			// }
		}
	}
	return dataHex;
}

String convertDecToHexString(uint8_t n8)
{
	String s = "";
	uint8 n;
	n = (n8 >> 4) & 0xf;
	s += s_hex.substring(n, n + 1);
	n = n8 & 0xf;
	s += s_hex.substring(n, n + 1);
	return s;
}
void decimalToHex(int decimalNumber)
{
	char hexString[5]; // Chuỗi hex có 4 ký tự và 1 ký tự kết thúc chuỗi ('\0')

	// Chuyển hệ 10 thành chuỗi hex
	snprintf(hexString, sizeof(hexString), "%04X", decimalNumber);

	// In chuỗi hex
	printf("Chuỗi hex signed 2's complement: %s\n", hexString);
}
// void StringtoInt (){
// 	char str[] = "12345"; // Chuỗi cần chuyển
//     int number = atoi(str); // Chuyển chuỗi sang int
//     printf("Số nguyên: %d\n", number);

// }

void StringtoInt()
{
	char str[] = "";
	char string_Int_In[] = "1132048";
	for (int i = 0; i < 4; i++)
	{
		str[i] = string_Int_In[i + 3];
	}
	int number = atoi(str); // Chuyển chuỗi sang int
	printf("Số nguyên: %d\n", number);
}

int hexadecimalToDecimal(char hexVal[])
{
	int len = strlen(hexVal);
	int base = 1;
	int dec_val = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (hexVal[i] >= '0' && hexVal[i] <= '9')
		{
			dec_val += (hexVal[i] - 48) * base;
			base = base * 16;
		}
		else if (hexVal[i] >= 'A' && hexVal[i] <= 'F')
		{
			dec_val += (hexVal[i] - 55) * base;
			base = base * 16;
		}
	}
	printf("Số nguyên1: %d\n", dec_val);
	return dec_val;
}
uint8_t *getArrKey(String key)
{
	uint8_t len = key.length();
	uint8_t *numArr = (uint8_t *)malloc(4);
	uint8_t *numArr1 = (uint8_t *)malloc(4);
	int n = 0, j = 0;
	for (size_t i = 0; i < len; i += 8)
	{
		numArr1[0] = convertHexStrToDec(key.substring(i, i + 2));
		numArr1[1] = convertHexStrToDec(key.substring(i + 2, i + 4));
		numArr1[2] = convertHexStrToDec(key.substring(i + 4, i + 6));
		numArr1[3] = convertHexStrToDec(key.substring(i + 6, i + 8));
		if (i % 8 == 0)
		{
			n = numArr1[0] - numArr1[1] + numArr1[2] - numArr1[3];
			numArr[i / 8] = n;
		}
	}

	return numArr;
}

String enCodeConvert(String str)
{
	String strHex = "";
	uint8_t *numArrKey;
	uint8_t n;
	numArrKey = getArrKey("327F640C7769978EF160028B89700F19");

	for (size_t i = 0; i < str.length(); i++)
	{
		uint8_t digit = str.charAt(i);
		// uart0.println("digit"+digit);
		n = (digit - numArrKey[i % 4]) * 2;
		strHex += convertDecToHexString(n);
	}
	return strHex;
}

String deCodeConvert(String str)
{
	String str1 = "";
	uint8_t *numArrKey;
	uint8_t n;
	numArrKey = getArrKey("327F640C7769978EF160028B89700F19");
	for (size_t i = 0; i < str.length(); i += 2)
	{
		uint8_t digit = convertHexStrToDec(str.substring(i, i + 2));
		n = (digit / 2) + numArrKey[i / 2 % 4];
		char ch = (char)n;
		str1 += ch;
	}
	return str1;
}
