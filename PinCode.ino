#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

//constants for LEDs
int Green = 12;
int Red = 13;

//set our code
char* Pin = "1234";
int currentPosition = 0;

//define the keypad
const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[rows] = {11,10,9,8};
byte colPins[cols] = {7,6,5,4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  lcd.init();             
  
  
  // Print a message to the LCD.
  lcd.backlight();
  
  EnterPin();
  
  //setup and turn off both LEDs
  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  digitalWrite(Red, LOW);
  digitalWrite(Green, LOW);
  
}

void loop()
{
  
  int l;
  
  char key = keypad.getKey();
  
  if (int(key) != 0) {
    lcd.setCursor(10,1);
    lcd.print("      ");
    lcd.setCursor(10,1);
    
    for (l=0; l<=currentPosition; ++l)
    {
      lcd.print("*");
    }
    
    if (key == Pin[currentPosition])
      {
        ++currentPosition;
        if (currentPosition == 4)
        {
          Correct();
          currentPosition = 0;
        }
      } else {
        Incorrect();
        currentPosition = 0;
      }
    
    
  }
}

void Incorrect()
{
  clearScreen();
  digitalWrite(Red, HIGH);
  clearScreen();
  lcd.setCursor(0,0);
  lcd.print(" Access Denied");
  lcd.setCursor(0,1);
  lcd.print(" Incorrect Pin");
  
  delay(5000);
  digitalWrite(Red, LOW);
  clearScreen();
  EnterPin();
}

void Correct()
{
  digitalWrite(Green, HIGH);
  clearScreen();
  
  lcd.setCursor(0,0);
  lcd.print("  Pin Correct");
  lcd.setCursor(0,1);
  lcd.print("   Door Open");
  delay(5000);
  digitalWrite(Green, LOW);
  clearScreen();
  EnterPin();
}

void EnterPin()
{
  clearScreen();
  
  lcd.setCursor(0,0);
  lcd.print("Enter Pin:");
}

void clearScreen()
{
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
}


