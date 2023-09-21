#include "vimass.h"

bool write_buf(String f_name, uint8 *buf, int16 len)
{
  // timer_init(false);
  File f = SPIFFS.open(f_name, "w");
  while (f.available())
  {
    f.write(buf, len);
    f.close();
    return true;
  }
  return false;
}

bool read_buf(String f_name)
{
  // timer_init(false);

  File f = SPIFFS.open(f_name, "r");
  while (f.available())
  {
    voice_len = f.size();
    f.read(ima_buf, voice_len);
    f.close();
    return true;
  }
  return false;
}
bool rename(String s_src, String s_dst)
{
  return SPIFFS.rename(s_src, s_dst);
}
bool remove(String fname)
{
  return SPIFFS.remove(fname);
}
String list_file()
{
  String s = "file list:\n", name;
  File f;
  for (int i = 0; i < 16; i++)
  {
    name = "/a_" + String(i) + ".wav";
    if (SPIFFS.exists(name))
    {
      s += name;
      s += ":";
      f = SPIFFS.open(name, "r");
      s += String(f.size() * 4) + "\n";
      f.close();
    }
  }
  return s;
}
void read_ssid()
{
  String s[16];
  int k;
  for (k = 0; k < 4; k++)
  {
    str_name[k] = str_pass[k] = "";
  }
  k = 0;
  File f = SPIFFS.open("/ssid.txt", "r");
  while ((f.available()) && (k < 8))
  {
    s[k] = f.readStringUntil(',');
    if (k)
      s[k].remove(0, 1);
    if (s[k].startsWith(","))
      s[k].remove(0, 1);
    if (s[k].endsWith(","))
      s[k].remove(s[k].length() - 1, 1);
    k++;
  }
  for (k = 0; k < 4; k++)
  {
    str_name[k] = s[k * 2];
    str_pass[k] = s[k * 2 + 1];
  }
  f.close();
}
void save_ssid(String s)
{
  File f = SPIFFS.open("/ssid.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void read_TBTTId()
{
  String s[16];
  int k = 0;
  tbttid[0] = "262626";
  File f = SPIFFS.open("/tbttid.txt", "r");
  while ((f.available()) && (k < 8))
  {
    s[k] = f.readStringUntil('_');
    // add_to_serial("\rread_TBTTId:s[k]"+ s[k]);
    tbttid[0] = s[k];
    k++;
  }

  // add_to_serial("\nend read_TBTTId");
  f.close();
}

void read_iplocal()
{
  String s[16];
  int k = 0;
  iplocal[0] = "";
  File f = SPIFFS.open("/iplocal.txt", "r");

  while ((f.available()) && (k < 8))
  {
    s[k] = f.readStringUntil('_');
    // add_to_serial("\read_iplocal:s[k]"+ s[k]);
    // serial_out();
    iplocal[0] = s[k];
    k++;
  }

  // add_to_serial("\nend read_iplocal");
  f.close();
}

void save_TBTTId(String s)
{
  File f = SPIFFS.open("/tbttid.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void ghimatbi(String s)
{
  File f = SPIFFS.open("/hello.txt", "w");
  if (f)
    f.print(s);
  f.close();
}

void docmatbi()
{
  File f = SPIFFS.open("/hello.txt", FILE_READ);
  while (f.available())
  {
    ma_tbi = f.read();
    f.close();
    uart0.println("..." + f.read());
    return;
  }
}

void save_iplocal(String s)
{
  File f = SPIFFS.open("/iplocal.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void save_cfg(String s)
{
  File f = SPIFFS.open("/cfg.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void save_id()
{
  // my_id=check_lim(my_id,0,soluongthietbi);
  File f = SPIFFS.open("/id.txt", "w");
  if (f)
  {
    f.print(String(my_id));
  }
  f.close();
  led_reset = 15;
}

void checkCardOffline(String cardInput)
{
  TrangThaiCacheCard = false;
  File f = SPIFFS.open("/cardOpenDoorOffline.txt", "r");
  String card = "";

  // add_to_serial("checkCardOffline 1:--" + cardInput + "--\n");
  // serial_out();

  while ((f.available()))
  {
    card = f.readStringUntil('_');

    // add_to_serial("checkCardOffline 2:--" + card + "--\n");
    // serial_out();
    if (card.equals(cardInput))
    {
      TrangThaiCacheCard = true;
      break;
    }
  }
  f.close();
}

void save_cardOpenDoorOffline(String s)
{
  File f = SPIFFS.open("/cardOpenDoorOffline.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
  //  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("− failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    Serial.println("− file written");
  }
  else
  {
    Serial.println("− frite failed");
  }
}

// String dec_to_string(int a)
// {
//   String str = "01234567890000000ABCDEF", s = "";
//   s = str.substring(a, a + 1);
//   return s;
// }

void readFile(const char *path)
{
  File file = SPIFFS.open(path);
  if (!file || file.isDirectory())
  {
    //  Serial.println("− failed to open file for reading");
    return;
  }
  ma_tbi = "";
  int n = 0;
  //  Serial.println("− read from file:");
  while (file.available())
  {
    n = file.read();
    ma_tbi += dec_to_string(n - 48);
    // Serial.write(ma_tbi);
  }
  add_to_serial(ma_tbi);
  serial_out();
  //  uart0.println(ma_tbi);
}
