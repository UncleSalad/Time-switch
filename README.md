Time switch device v1.0
==================
This ArduinoDevice turns on and off another device depending on the time you can configure.

For example:
  1. 09:00 - 12:00 - on
  2. 16:30 - 18:00 - on
  3. 20:00 - 22:00 - on
***
Connection:
===
*if the settings are standard*
1. Encoder:
* clk - 2
* dt - 3
* sw - 4
2. LCD 1602:
* scl - A5
* sda - A4
3. DS1302:
* clk - 13
* dat - 12
* rst - 10
4. Relay/MOSFET
* in - 7
***
Setting:
===
1. Encoder:
* 9.byte clk = 2;
*	10.byte dat = 3;
*	11.byte swt = 4;
2. LCD 1602:
* *The display connects via i2c, so A4(SDA) and A5(SCL) are standard for i2c :)*
* Well, except that the address:
* 43.LiquidCrystal_I2C lsd(0x3f(address), 16, 2);
3. DS1302:
* 44.iarduino_RTC time(RTC_DS1302, 10(RST), 13(CLK), 12(DAT);
4. Relay/MOSFET:
* 15.byte relay_pin = 7;
