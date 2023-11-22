#include <Wire.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
int mea = 0;
#define alcohol A0
float alcohol_value = 0;  
const unsigned long measurementDuration = 30000; 
// 알코올 관련 
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128
#define SCLK_PIN 2
#define MOSI_PIN 3
#define DC_PIN   4
#define CS_PIN   5
#define RST_PIN  6
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF
Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);  
// 점등 관련 
Servo servo;
#define servopin1 9
int pos = 0;
int breaker = 0;
//차단기(servo) 관련
#define t 13
#define e 12
//초음파 관련
// #define buz 8
void paas_display()
{
  tft.fillScreen(GREEN);
  tft.setTextSize(18);
  tft.setCursor(20,-18);
  tft.setTextColor(BLACK);  
  tft.println("o");
  delay(5000);
  tft.fillScreen(BLACK);
}
void npaas_display()
{
  tft.fillScreen(RED);
  tft.setTextSize(18);
  tft.setCursor(20,-18);
  tft.setTextColor(BLACK);  
  tft.println("x");
  delay(5000);
  tft.fillScreen(BLACK);
}
void tft_al(float alva)
{
  tft.fillScreen(YELLOW);
  tft.setTextSize(3);
  tft.setCursor(0,10);
  tft.setTextColor(BLACK);  
  tft.println("alcohol value");
  tft.setCursor(10,80);
  tft.println(alva);
  delay(5000);
  tft.fillScreen(BLACK);
}
int alcohol_30()
{
  unsigned long startTime = millis();
  unsigned long currentTime;
  unsigned long elapsedTime = 0;
  while (elapsedTime < measurementDuration) 
  {
    alcohol_value = analogRead(alcohol);
    tft_al(alcohol_value);
    if(alcohol_value > 800) //음주단속이 걸렸을때 
    {
      Serial.println(alcohol_value);
      return 1;
    }
    else if(alcohol_value < 500)
    {
      Serial.println(alcohol_value);
      return 2;
    }
    else
      return 0;
    currentTime = millis();
    elapsedTime = currentTime - startTime;
  }
}

void determine(int mea)
{
  if(mea == 1 || mea == 0) //음주단속 걸렸을때
  {
    Serial.println("red");
    npaas_display();
  }
  else if(mea == 2) //음주단속 안걸렸을때// 알코올 수치는 따로 변경
  {
    Serial.println("green");
    breaker = 1;
    paas_display();
    servo.write(pos-90);
    delay(5000);
    servo.write(pos+90);
    breaker = 0;
  }
  mea=0;
}
void setup() 
{
  Serial.begin(9600);
  tft.begin();
  servo.attach(servopin1);
  pinMode(e,INPUT);
  pinMode(t, OUTPUT);
  pinMode(alcohol, INPUT);
  tft.fillScreen(BLACK);
}
void loop() 
{
  int f=0;
  int set=0;
  float dur, dis;
  digitalWrite(t,LOW);
  delayMicroseconds(2);
  digitalWrite(t,HIGH);
  delayMicroseconds(10);
  digitalWrite(t,LOW);
  dur=pulseIn(e,HIGH);
  dis=((float)(340*dur)/10000)/2;
  if(dis<20)
  {
    delay(10000); 
    set = alcohol_30(); //알코올 측정
    determine(set);
  }  
}

