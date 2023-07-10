#pragma once
#include<Arduino.h>

#define g 9.81
template< uint16_t N>//n дл€ функций с периодом; k дл€ функций выполн€ющихс€ каждый раз
class FlightOS {
public:
  bool On[N] = { 0 };
  int v;
  unsigned long prev[N];
  int interval[N];
  void (*f[N])();
  void attach(int num, void (*func)(void), int intrvl) {
    interval[num] = intrvl;
    prev[num] = millis();
    f[num] = *func;
    On[num] = 0;
  }
  void tick() {
  for (int i = 0; i < N; i++) {
      if (((millis() - prev[i]) > interval[i]) && On[i] == 1) {
        f[i]();
        prev[i] = millis();
      }
    }
  }
  void turnOn(int num) {
    On[num] = 1;
  }
  void turnOff(int num) {
    On[num] = 0;
  }
	void setMpu(int interval) {
		interval_mpu = interval;
  }
};