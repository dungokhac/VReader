void showOpenDoor(String s)
{
	door_open;
	door_cnt = 1;
	bipok1();
	// add_to_serial("mo cua1---");
	// serial_out();
	xuLyDanhSachThe(s);
}

void showCloseDoor(String s)
{
	door_close;
	door_cnt = 0;
	biper1();
	// add_to_serial("dong cua1---");
	// serial_out();
}

void resetDoorStatus()
{
	str_door = "";
	v_stat = fx_waiting;
}

void xuLyDanhSachThe(String s)
{
	if (s.length() > 12)
	{
		s.remove(0, 12);
	}
	if (s.length() > 10)
	{
		String deviceId = "";
		if (s.startsWith("_"))
		{
			s.remove(0, 1);
		}
		int n = s.indexOf("_");
		deviceId = s.substring(0, n);
		s.remove(0, n);
		// -----ghi cache the
		save_cardOpenDoorOffline(s);
		// ----confirm
		confirmSaveCardOffline(deviceId);
	}
}

void checkOfflineCardOpenDoor(String s)
{
	if (s.startsWith("35_"))
	{
		s = https_decode(s);
		int n = s.indexOf("_");
		String funcId = s.substring(0, n);
		s.remove(0, n);
		if (s.startsWith("_"))
		{
			s.remove(0, 1);
		}

		// 	add_to_serial(" funcId :" + funcId);
		// serial_out();

		n = s.indexOf("_");
		String uid = s.substring(0, n);
		s.remove(0, n);
		if (s.startsWith("_"))
		{
			s.remove(0, 1);
		}
		n = s.indexOf("_");
		String tbttId = s.substring(0, n);
		s.remove(0, n);
		if (s.startsWith("_"))
		{
			s.remove(0, 1);
		}

		n = s.indexOf("_");
		String cks1 = s.substring(0, n);
		s.remove(0, n);
		if (s.startsWith("_"))
		{
			s.remove(0, 1);
		}

		n = s.indexOf("_");
		String cks2 = s.substring(0, n);
		s.remove(0, n);
		if (s.startsWith("_"))
		{
			s.remove(0, 1);
		}

		n = s.indexOf("_");
		String cks3 = s.substring(0, n);
		s.remove(0, n);
		if (s.startsWith("_"))
		{
			s.remove(0, 1);
		}

		n = s.indexOf("_");
		String vidInput = s.substring(0, n);
		s.remove(0, n);
		if (s.startsWith("_"))
		{
			s.remove(0, 1);
		}

		vidInput.replace(" ", "");
		vidInput.replace("%20", "");

		TrangThaiCacheCard = false;
		checkCardOffline(vidInput);

		if (TrangThaiCacheCard)
		{
			showOpenDoor("");
		}
		else
		{
			showCloseDoor("");
		}
	}
}

void dongcua()
{
	REG_CLR_BIT(RTC_IO_PAD_DAC1_REG, RTC_IO_PDAC1_XPD_DAC);
	REG_SET_BIT(RTC_IO_PAD_DAC1_REG, RTC_IO_PDAC1_DAC_XPD_FORCE);
	pinMode(door_gate, OUTPUT);
	bipok2();
	digitalWrite(door_gate, 1);
	Serial.println("cua dong\n");
	delay(1000);
}
void mocua()
{
	REG_CLR_BIT(RTC_IO_PAD_DAC1_REG, RTC_IO_PDAC1_XPD_DAC);
	REG_SET_BIT(RTC_IO_PAD_DAC1_REG, RTC_IO_PDAC1_DAC_XPD_FORCE);
	pinMode(door_gate, OUTPUT);
	bipok1();
	digitalWrite(door_gate, 0);
	Serial.println("cua mo\n");
	delay(1000);
	digitalWrite(door_gate, 1);
	Serial.println("cua dong\n");
}
void mocuaUDP()
{
	play_audio(xin_cam_on, sizeof(xin_cam_on));
	REG_CLR_BIT(RTC_IO_PAD_DAC1_REG, RTC_IO_PDAC1_XPD_DAC);
	REG_SET_BIT(RTC_IO_PAD_DAC1_REG, RTC_IO_PDAC1_DAC_XPD_FORCE);
	pinMode(door_gate, OUTPUT);
	// bipok1();

	digitalWrite(door_gate, 0);

	Serial.println("cua mo\n");
	delay(1000);
	digitalWrite(door_gate, 1);
	Serial.println("cua dong\n");
}