#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int screen = 0;
int total_screens = 4;

unsigned long lastinfo = 0;
unsigned long lastswitch = 0;

const int timeswitch = 5000;    
const int timetimeout = 7000;   

int pos = 0;
unsigned long lastscroll = 0;

void cpuLCD(float cpu, float temp, bool high_temp){
  lcd.setCursor(0, 0);
  lcd.print("CPU:");
  lcd.print((int)cpu);
  lcd.print("% | ");
  lcd.print((int)temp);
  lcd.print("C");

  lcd.setCursor(0, 1);
      
  if(high_temp){
    lcd.print("TEMP ALERT!");
  }
}

void ramLCD(float ram, float memory_total, float memory_used){
  lcd.setCursor(0, 0);
  lcd.print("RAM:");
  lcd.print((int)ram);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print((float)memory_used);
  lcd.print("/");
  lcd.print((float)memory_total);
  lcd.print("GB");
}

void diskLCD(float disk, float disk_total, float disk_used){
  lcd.setCursor(0, 0);
  lcd.print("DISK:");
  lcd.print((int)disk);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print((float)disk_used);
  lcd.print("/");
  lcd.print((float)disk_total);
  lcd.print("GB");
}

void musicLCD(String musica, String atual_min, String atual_sec, String total_min, String total_sec){
  lcd.setCursor(0,0);

  if (musica.length() <= 16) {
    lcd.print(musica);
  }
  else{
    String scroll = musica + "    " + musica + "    ";
    
    if (millis() - lastscroll >= 300) {
      lastscroll = millis();

      lcd.setCursor(0, 0);
      lcd.print(scroll.substring(pos, pos + 16));

      pos++;
      if (pos > scroll.length() - 16) {
        pos = 0;
      }
    }
  }

  lcd.setCursor(0, 1);
  lcd.print(atual_min);
  lcd.print(":");
  lcd.print(atual_sec);
  lcd.print(" - ");
  lcd.print(total_min);
  lcd.print(":");
  lcd.print(total_sec);
}

void idleLCD(){
  lcd.setCursor(0, 0);
  lcd.print("No connection.  ");
  lcd.setCursor(0, 1);
  lcd.print("Check PC. :(    ");
}

void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    pinMode(8, OUTPUT);
}

void loop() {
  if (Serial.available() > 0) {
    lastinfo = millis();

    String data = Serial.readStringUntil('\n');

    int p1 = data.indexOf(',');
    int p2 = data.indexOf(',', p1 + 1);
    int p3 = data.indexOf(',', p2 + 1);
    int p4 = data.indexOf(',', p3 + 1);
    int p5 = data.indexOf(',', p4 + 1);
    int p6 = data.indexOf(',', p5 + 1);
    int p7 = data.indexOf(',', p6 + 1);
    int p8 = data.indexOf(',', p7 + 1);
    int p9 = data.indexOf(',', p8 + 1);
    int p10 = data.indexOf(',', p9 + 1);
    int p11 = data.indexOf(',', p10 + 1);
    int p12 = data.indexOf(',', p11 + 1);
    int p13 = data.indexOf(',', p12 + 1);
    
    String s_cpu = data.substring(0, p1);
    String s_temp = data.substring(p1 + 1, p2);
    String s_ram = data.substring(p2 + 1, p3);
    bool high_temp = data.substring(p3 + 1, p4).toInt();
    String ram_total = data.substring(p4 + 1, p5);
    String ram_used = data.substring(p5 + 1, p6);
    String s_disk = data.substring(p6 + 1, p7);
    String disk_total = data.substring(p7 + 1, p8);
    String disk_used = data.substring(p8 + 1, p9);
    String musica = data.substring(p9 + 1, p10);
    String atual_min = data.substring(p10 + 1, p11);
    String atual_sec = data.substring(p11 + 1, p12);
    String total_min = data.substring(p12 + 1, p13);
    String total_sec = data.substring(p13 + 1);

    float cpu = s_cpu.toFloat();
    float temp = s_temp.toFloat();
    float ram = s_ram.toFloat();
    float memory_total = ram_total.toFloat();
    float memory_used = ram_used.toFloat();
    float disk = s_disk.toFloat();
    float disk_total_f = disk_total.toFloat();
    float disk_used_f = disk_used.toFloat();

    if(high_temp){
      digitalWrite(8, HIGH);
    }
    else{
      digitalWrite(8, LOW);
    }
    
    lcd.clear();

    if (millis() - lastswitch >= timeswitch) {
     lastswitch = millis();

      screen++;
      if (screen > total_screens - 1){
        screen = 0;
      }  
    }
    
    if (millis() - lastinfo >= timetimeout) {
      idleLCD();
    }

    if(screen == 0){
      cpuLCD(cpu, temp, high_temp);
    }

    else if(screen == 1){
      ramLCD(ram, memory_total, memory_used);
    }
    else if(screen == 2){
      diskLCD(disk, disk_total_f, disk_used_f);
    }
    else if(screen == 3){
      musicLCD(musica, atual_min, atual_sec, total_min, total_sec);
    }
  }
  else{
    if (millis() - lastinfo >= timetimeout) {
      idleLCD();
    }
  }
}