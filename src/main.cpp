#include <Arduino.h>
#include <Time.h>
#include <DS1307RTC.h>

void setup()  {
  Serial.begin(115200);
  while (!Serial) ; // Только для платы Leonardo
  setSyncProvider(RTC.get);   // получаем время с RTC
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC"); //синхронизация не удаласть
  else
    Serial.println("RTC has set the system time");
  //установим вручную 16.02.2016 12:53
  TimeElements te;
  te.Second = 0; //секунды
  te.Minute = 3; //минуты
  te.Hour = 0; //часы
  te.Day = 3; //день
  te.Month = 12; // месяц
  te.Year = 2018 - 1970; //год в библиотеке отсчитывается с 1970
  time_t timeVal = makeTime(te);
  RTC.set(timeVal);
  setTime(timeVal);
}

void printDigits(int digits) {
  //выводим время через ":"
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void digitalClockDisplay() {
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();
}

void loop()
{
  digitalClockDisplay(); //вывод времени
  delay(1000);
}
