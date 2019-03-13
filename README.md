Time switch device
==================
This ArduinoDevice turns on and off another device depending on the time you can configure.

For example:
  1. 09:00 - 12:00 - on
  2. 16:30 - 18:00 - on
  3. 20:00 - 22:00 - on

# Connection:
1. Encoder:
* CLK - 2,
* DT - 3,
* SW - 4,
2. LCD 1602:
* SCL - A5,
* SDA - A4,
3. DS1302:
* CLK - 13,
* DAT - 12,
* RST - 1
