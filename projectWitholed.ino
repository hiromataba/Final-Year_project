#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal.h>
 
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
#define laser 12


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
 
double temp_amb;
double temp_obj;
//Normal Variables 

int ledRed = 7;
int ledGreen = 8;
int buzzer = 9;
 
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  mlx.begin();         //Initialize MLX90614
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)

  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen,OUTPUT);
  pinMode(buzzer,OUTPUT);
  
  Serial.println("Temperature Sensor MLX90614");
 
  pinMode(laser, OUTPUT);     // Connect LASER
 
  digitalWrite(laser, LOW);
 
  display.clearDisplay();
  display.setCursor(25,15);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" Thermometer");
  display.setCursor(25,35);
  display.setTextSize(1);
  display.print("Initializing");
  display.display();
  delay(5000);
}
 
void loop()
{
  //Reading room temperature and object temp
  //for reading Fahrenheit values, use
  //mlx.readAmbientTempF() , mlx.readObjectTempF() )
  temp_amb = mlx.readAmbientTempC();
  temp_obj = mlx.readObjectTempC();
  digitalWrite(laser, HIGH);
 
  //Serial Monitor
  Serial.print("Room Temp = ");
  Serial.println(temp_amb);
  Serial.print("Object temp = ");
  Serial.println(temp_obj);
 
  display.clearDisplay();
  display.setCursor(25,10);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println(" Temperature");
  display.setCursor(25,30);
  display.setTextSize(2);
  display.print(temp_obj);
  display.print((char)247);
  display.print("C");
  display.display();
  lcd.setCursor(0, 0);
  lcd.print("Room 1 Temp is: ");
  lcd.setCursor(0, 1);
  lcd.print(temp_obj);
  lcd.setCursor(5, 1);
  lcd.print("Deg Celcius"); 

  digitalWrite(buzzer,LOW); 
  digitalWrite(ledGreen,HIGH);
  digitalWrite(ledRed,LOW);
  if(temp_obj > 38 || temp_obj < 27){
    digitalWrite(buzzer,HIGH);    
    digitalWrite(ledGreen,LOW);
    digitalWrite(ledRed,HIGH);
  }
  
 
  delay(1000);
}
