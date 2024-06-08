//pushup project for IoT
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define echoPin 2               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define trigPin 4               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define buzzPin 15    
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

int counter = 0;
long duration, distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  lcd.init();                       // Initialize the LCD
  lcd.backlight();                  // Turn on the backlight
  lcd.clear();                      // Clear the LCD screen
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0, 0);               // Set the cursor to the first column and first row
  lcd.print("    PUSHUP COUNTER   ");     // Print some text
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  String disp = String(distance);

  Serial.print("Distance: ");
  Serial.print(disp);
  Serial.println(" cm");
  

  if (distance <= 15) {
    counter++;
    digitalWrite(buzzPin, HIGH);  // Turn the buzzer on
    delay(100);                   // Wait for 100 milliseconds
    digitalWrite(buzzPin, LOW);   // Turn the buzzer off
    lcd.setCursor(0, 1);          // Move to the second row
    lcd.print("Total = ");
    lcd.print(counter);
    delay(1000);                  // Delay to avoid multiple counts for one pushup
  }
  delay(10);
}
