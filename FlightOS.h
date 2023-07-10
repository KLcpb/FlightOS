#pragma once
#include<Arduino.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
#define g 9.81

template< uint16_t N>//n дл€ функций с периодом; k дл€ функций выполн€ющихс€ каждый раз
class FlightOS {
private:
	bool On[N] = { 0 };
	int v;
	unsigned long prev[N];
	unsigned long prev_mpu
	int interval[N];
	int interval_mpu;
	void (*f[N])();
	struct InertialData
	{
		int aX, aY, aZ;
		int gX, gY, gZ;
	};
	InertialData IDATA;
	void updateMPU() {
		mpu6050.update();
		IDATA.aX = mpu6050.getAccX() * 100
		IDATA.aY = mpu6050.getAccY() * 100
		IDATA.aZ = mpu6050.getAccZ() * 100

		IDATA.gX = mpu6050.getGyroX() * 100
		IDATA.gY = mpu6050.getGyroY() * 100
		IDATA.gZ = mpu6050.getGyroZ() * 100
	}
public:
	
	FlightOS() {
		Wire.begin();
		mpu6050.begin();
	}
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
			if ((millis() - prev_mpu) > interval_mpu) {
				updateMPU();
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
		mpu6050.writeMPU6050(MPU6050_ACCEL_CONFIG, 0x18);
		writeMPU6050(MPU6050_GYRO_CONFIG, 0x08);///////////////////////////
	}
};