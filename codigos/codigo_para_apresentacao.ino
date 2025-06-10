#include <LiquidCrystal_I2C.h>

int sensor = 7;
int timer = 1000;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

	Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.print("Distancia (cm):");
}

void loop() {
  long duracao;
  float distancia_cm;

  pinMode(sensor, OUTPUT);
	digitalWrite(sensor, LOW);
	delayMicroseconds(2);
	digitalWrite(sensor, HIGH);
	delayMicroseconds(5);
	digitalWrite(sensor, LOW);

	pinMode(sensor, INPUT);
	duracao = pulseIn(sensor, HIGH);

  distancia_cm = (duracao / 2.0) / 29.1;

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  if (distancia_cm >= 0) {
    lcd.print(distancia_cm, 1);
    lcd.print(" cm");
  } else {
    lcd.print("Erro de leitura");
  }

  Serial.print("{\"distancia_cm\":");
  Serial.print(distancia_cm, 1);
  Serial.println("}");


  delay(timer);
}
