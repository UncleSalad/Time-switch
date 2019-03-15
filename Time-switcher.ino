//Libraries//
	#include <Wire.h>
	#include "Arduino-LiquidCrystal-I2C-library-master/LiquidCrystal_I2C.h"
	#include "EEWrap-master/EEWrap.h"
	#include <EEPROM.h>
	#include <iarduino_RTC.h>
//EEPROM//
	//Encoder//
		byte clk = 2;
		byte dat = 3;
		byte swt = 4;
		bool encoder_A, encoder_B, encoder_A_prev;
		long lastTime, loopTime;
	//Relay//
		byte relay_pin = 7;
	//Text Variables
		char* textMonth[12] = {
			"Jan", "Feb",
			"Mar", "Apr", "May",
			"Jun", "Jul", "Aug",
			"Sep", "Oct", "Nov", "Dec"
		};
		char* textWeekday[7] = {
			"Mon", "Tue", "Wed",
			"Thu", "Fri", "Sat", "Sun"
		};
	//Choice Variables
		int choiceLevel;            //1 - choice Timer/ 2 - choice startTimer or end Time/ 3 - choice hour/minute/second 4 - change selected value
		int choiceTimer;          //1 - 1th timer/ 2 - 2th timer/ 3 - 3th timer
		int choiceHMS;            //1 - hour/ 2 - minute/ 3 - second
		bool choiceStartOrEnd; //true - start/ false - end
	//Real Time
		int realTime[3];
		int realDate[4];
		long realTimeDelay;
	//Timers
		int32_e hour[6];
		int32_e minute[6];
		int32_e second[6];
		int FTimer_s_sec, STimer_s_sec, TTimer_s_sec;
		int FTimer_e_sec, STimer_e_sec, TTimer_e_sec;
//Begins//
	LiquidCrystal_I2C lsd(0x3f, 16, 2);
	iarduino_RTC time(RTC_DS1302, 10, 13, 12);

void setup() {
	//Initialization//
		pinMode(clk , INPUT);
		pinMode(dat, INPUT);
		pinMode(swt, INPUT_PULLUP);
		pinMode(relay_pin, OUTPUT);
		Serial.begin(9600);
		time.begin();
		lsd.begin();
	//Others//
		//time.settime(30, 59, 9, 1, 1, 1, 1);
		lsd.backlight();
		lastTime = millis();
		loopTime = lastTime;
}

void loop() {
	//Workout encoder//
	lastTime = millis();
	if (lastTime >= (loopTime + 50)) {
		encoder_A = digitalRead(clk);
		encoder_B = digitalRead(dat);
		if ((!encoder_A) && (encoder_A_prev)) {
			if (encoder_B) {
				//encoder rotated to the left and holded//	
				if (!digitalRead(swt)) {
					choiceLevel++;
				}
				//encoder rotated to the left//
				else {
					switch (choiceLevel) {
					case 1: choiceTimer++;
						break;
					case 2: choiceStartOrEnd = false;
						break;
					case 3: choiceHMS++;
						break;
					case 4:
						switch (choiceTimer) {
						case 1:
							switch (choiceStartOrEnd) {
							case true:
								switch (choiceHMS) {
								case 1: hour[1]++;
									if (hour[1] >= 24) hour[1] = 23;
									break;
								case 2: minute[1]++;
									if (minute[1] >= 60) minute[1] = 59;
									break;
								case 3: second[1]++;
									if (second[1] >= 60) second[1] = 59;
									break;
								}
							break;
							case false:
								switch (choiceHMS) {
								case 1: hour[2]++;
									if (hour[2] >= 24) hour[2] = 23;
									break;
								case 2: minute[2]++;
									if (minute[2] >= 60) minute[2] = 59;
									break;
								case 3: second[2]++;
									if (second[2] >= 60) second[2] = 59;
									break;
								}
							}
							break;
						case 2:
							switch (choiceStartOrEnd) {
							case true:
								switch (choiceHMS) {
								case 1: hour[3]++;
									if (hour[3] >= 24) hour[3] = 23;
									break;
								case 2: minute[3]++;
									if (minute[3] >= 60) minute[3] = 59;
									break;
								case 3: second[3]++;
									if (second[3] >= 60) second[3] = 59;
									break;
								}
							break;
							case false:
								switch (choiceHMS) {
								case 1: hour[4]++;
									if (hour[4] >= 24) hour[4] = 23;
									break;
								case 2: minute[4]++;
									if (minute[4] >= 60) minute[4] = 59;
									break;
								case 3: second[4]++;
									if (second[4] >= 60) second[4] = 59;
									break;
								}
							}
							break;
						case 3:
							switch (choiceStartOrEnd) {
							case true:
								switch (choiceHMS) {
								case 1: hour[5]++;
									if (hour[5] >= 24) hour[5] = 23;
									break;
								case 2: minute[5]++;
									if (minute[5] >= 60) minute[5] = 59;
									break;
								case 3: second[5]++;
									if (second[5] >= 60) second[5] = 59;
									break;
								}
							break;
							case false:
								switch (choiceHMS) {
								case 1: hour[6]++;
									if (hour[6] >= 24) hour[6] = 23;
									break;
								case 2: minute[6]++;
									if (minute[6] >= 60) minute[6] = 59;
									break;
								case 3: second[6]++;
									if (second[6] >= 60) second[6] = 59;
									break;
								}
							}
							break;
						}
					}
				}
			}
			else {
				//encoder rotated to the right and holded//
				if (!digitalRead(swt)) {
					choiceLevel--;
				}
				//encoder rotated to the right//
				else {
					switch (choiceLevel) {
					case 1: choiceTimer--;
						break;
					case 2: choiceStartOrEnd = true;
						break;
					case 3: choiceHMS--;
						break;
					case 4:
						switch (choiceTimer) {
						case 1:
							switch (choiceStartOrEnd) {
							case true:
								switch (choiceHMS) {
								case 1: hour[1]--;
									if (hour[1] <= -1) hour[1] = 0;
									break;
								case 2: minute[1]--;
									if (minute[1] <= -1) minute[1] = 0;
									break;
								case 3: second[1]--;
									if (second[1] <= -1) second[1] = 0;
									break;
								}
							break;
							case false:
								switch (choiceHMS) {
								case 1: hour[2]--;
									if (hour[2] <= -1) hour[2] = 0;
									break;
								case 2: minute[2]--;
									if (minute[2] <= -1) minute[2] = 0;
									break;
								case 3: second[2]--;
									if (second[2] <= -1) second[2] = 0;
									break;
								}
							}
							break;
						case 2:
							switch (choiceStartOrEnd) {
							case true:
								switch (choiceHMS) {
								case 1: hour[3]--;
									if (hour[3] <= -1) hour[3] = 0;
									break;
								case 2: minute[3]--;
									if (minute[3] <= -1) minute[3] = 0;
									break;
								case 3: second[3]--;
									if (second[3] <= -1) second[3] = 0;
									break;
								}
							break;
							case false:
								switch (choiceHMS) {
								case 1: hour[4]--;
									if (hour[4] <= -1) hour[4] = 0;
									break;
								case 2: minute[4]--;
									if (minute[4] <= -1) minute[4] = 0;
									break;
								case 3: second[4]--;
									if (second[4] <= -1) second[4] = 0;
									break;
								}
							}
							break;
						case 3:
							switch (choiceStartOrEnd) {
							case true:
								switch (choiceHMS) {
								case 1: hour[5]--;
									if (hour[5] <= -1) hour[5] = 0;
									break;
								case 2: minute[5]--;
									if (minute[5] <= -1) minute[5] = 0;
									break;
								case 3: second[5]--;
									if (second[5] <= -1) second[5] = 0;
									break;
								}
							break;
							case false:
								switch (choiceHMS) {
								case 1: hour[6]--;
									if (hour[6] <= -1) hour[6] = 0;
									break;
								case 2: minute[6]--;
									if (minute[6] <= -1) minute[6] = 0;
									break;
								case 3: second[6]--;
									if (second[6] <= -1) second[6] = 0;
									break;
								}
								break;
							}
							break;
						}
					}
				}
			}
		}
		encoder_A_prev = encoder_A;
		loopTime = lastTime;
	}
	//YEAAAAAAAHHHH, 223 LINES!!!!
	//Workout RTC
		time.gettime();
	//Workout LSD Display
		if (choiceLevel == 0) {
			printTime(4, 0);
			printDate(0, 1);
		}
		else {
			switch (choiceTimer) {
			case 1:
				printTimer(0, 0, hour[1], minute[1], second[1]);
				printTimer(8, 0, hour[2], minute[2], second[2]);
				break;
			case 2:
				printTimer(0, 0, hour[3], minute[3], second[3]);
				printTimer(8, 0, hour[4], minute[4], second[4]);
				break;
			case 3:
				printTimer(0, 0, hour[5], minute[5], second[5]);
				printTimer(8, 0, hour[6], minute[6], second[6]);
				break;
			}
			switch (choiceLevel) {
			case 1:
				switch (choiceTimer) {
				case 1:
					printLine(0, 1, "     Timer1     ");
					break;
				case 2:
					printLine(0, 1, "     Timer2     ");
					break;
				case 3:
					printLine(0, 1, "     Timer3     ");
					break;
				}
				break;
			case 2:
				switch (choiceStartOrEnd) {
				case 0:
					printLine(0, 1, "        |end   |");
					break;
				case 1:
					printLine(0, 1, "| start|        ");
					break;
				}
				break;
			case 3:
				switch (choiceStartOrEnd) {
				case 0:
					switch (choiceHMS) {
					case 1: printLine(0, 1, "        | hour |");
						break;
					case 2: printLine(0, 1, "        |minute|");
						break;
					case 3: printLine(0, 1, "        |second|");
						break;
					}
					break;
				case 1:
					switch (choiceHMS) {
					case 1: printLine(0, 1, "| hour |       ");
						break;
					case 2: printLine(0, 1, "|minute|        ");
						break;
					case 3: printLine(0, 1, "|second|        ");
						break;
					}
					break;
				}
				break;
			case 4:
				printLine(0, 1, "     Change!    ");
				break;
			} 
		}
	//Operation with massives|variables//
		//Constrain massives|variables
			choiceTimer = constrain(choiceTimer, 1, 3);
			choiceHMS = constrain(choiceHMS, 1, 3);
			choiceLevel = constrain(choiceLevel, 0, 4);
			realTime[1] = constrain(realTime[1], 0, 23);
			realTime[2] = constrain(realTime[2], 0, 59);
			realTime[3] = constrain(realTime[3], 0, 59);
			realDate[1] = constrain(realDate[1], 1, 31);
			realDate[2] = constrain(realDate[2], 0, 11);
			realDate[4] = constrain(realDate[4], 0, 6);
		//Real time variables assignment//
			realTime[1] = time.Hours;
			realTime[2] = time.minutes;
			realTime[3] = time.seconds;
			realDate[1] = time.day;
			realDate[2] = time.month;
			realDate[3] = time.year;
			realDate[4] = time.weekday;
	//Workout Relay//
			if ((time_in_sec(hour[1], minute[1], second[1]) <= time_in_sec(realTime[1], realTime[2], realTime[3]))
				&&
				(time_in_sec(realTime[1], realTime[2], realTime[3]) <= time_in_sec(hour[2], minute[2], second[2]))) digitalWrite(relay_pin, HIGH);
			else if ((time_in_sec(hour[3], minute[3], second[3]) <= time_in_sec(realTime[1], realTime[2], realTime[3]))
				&&
				(time_in_sec(realTime[1], realTime[2], realTime[3]) <= time_in_sec(hour[4], minute[4], second[4]))) digitalWrite(relay_pin, HIGH);
			else if ((time_in_sec(hour[5], minute[5], second[5]) <= time_in_sec(realTime[1], realTime[2], realTime[3]))
				&&
				(time_in_sec(realTime[1], realTime[2], realTime[3]) <= time_in_sec(hour[6], minute[6], second[6]))) digitalWrite(relay_pin, HIGH);
			else digitalWrite(relay_pin, LOW);

}
void printTime(int x, int y) {
	for (int i = 0; i < x; i++) {
		lsd.setCursor(i, y);
		lsd	.print(" ");
	}
	printNum(realTime[1], x, y);
	lsd.setCursor(x + 2, y);
	lsd.print(":");
	printNum(realTime[2], x + 3, y);
	lsd.setCursor(x + 5, y);
	lsd.print(":");
	printNum(realTime[3], x + 6, y);
	for (int i = x+8; i < 16; i++) {
		lsd.setCursor(i, y);
		lsd.print(" ");
	}
}
void printDate(int x, int y) {
	lsd.setCursor(x, y);
	lsd.print(realDate[1]);
	lsd.print(" ");
	lsd.print(textMonth[realDate[2]]);
	lsd.print(" ");
	lsd.print("20");
	printNum(realDate[3], 8, 1);
	lsd.print(", ");
	lsd.print(textWeekday[realDate[4]]);
}
void printLine(int x, int y, String text) {
	lsd.setCursor(x, y);
	lsd.print(text);
}
void printLineWithVar(int x, int y, String text, int var) {
	lsd.setCursor(x, y);
	lsd.print(text);
	lsd.print(var);
}
void printTimer(int x, int y, int hour, int minute, int second) {
	printNum(hour, x, y);
	lsd.print(":");
	printNum(minute, x + 3, y);
	lsd.print(":");
	printNum(second, x + 6, y);
}
void printNum(int var, int x, int y) {
	if (var < 10) {
		lsd.setCursor(x, y);
		lsd.print("0");
		lsd.print(var);
	}
	else {
		lsd.setCursor(x, y);
		lsd.print(var);
	}
}
int time_in_sec(int hour, int minute, int second) {
	return (hour * 3600) + (minute * 60) + second;
}
