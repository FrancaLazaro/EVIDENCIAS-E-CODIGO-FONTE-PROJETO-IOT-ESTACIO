#include <LiquidCrystal_I2C.h>

int sensor = 7;
int timer = 1000;

const float alturaCaixa = 61.0;
const float sensorTopo = 17.0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Nivel da Agua:");
}

void loop() {
  long duracao;
  float distancia;
  int nivelAgua ;

  pinMode(sensor, OUTPUT);
  digitalWrite(sensor, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor, HIGH);
  delayMicroseconds(5);
  digitalWrite(sensor, LOW);

  pinMode(sensor, INPUT);
  duracao = pulseIn(sensor, HIGH);

  distancia = (duracao / 2.0) / 29.1;

  nivelAgua = converterParaPorcentagem(distancia);

  if (nivelAgua > 100) nivelAgua = 100;
  if (nivelAgua < 0) nivelAgua = 0;

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(nivelAgua);
  lcd.print("%");

  Serial.print("Nivel da Agua: ");
  Serial.print(nivelAgua);
  Serial.println("%");

  delay(timer);
}

int converterParaPorcentagem(float d) {
  float fundoSensor = alturaCaixa + sensorTopo;
  float nivel = fundoSensor - d;

  return (nivel / alturaCaixa) * 100;
}