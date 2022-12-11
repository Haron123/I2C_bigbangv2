# I2C_bigbangv2

An Arduino Libary to Bitbang I2C, is currently being tested by me with various devices to see if it works. so far it works well though.
The Point isnt to use this as a goto Libary for i2c devices but to help you(and especially me) understand I2C in a simpler way.

The Code is still quite messy though and im quite certain breaks rules of the I2C protocl but so far it worked flawless with the SSD1306 and INA219.

# Functions : 

void sendByte(byte data, byte clockpin, byte datapin); // Sends a Byte
void sendAddress(byte address, byte clockpin, byte datapin); // Sends an Address, without Read or Write Bit
byte getByte(byte clockpin, byte datapin); // Receives Byte from slave without sending ack
void sendBit(byte bit, byte clockpin, byte datapin); // Sends a single Bit, bit can be 1 or 0
void sendRead(byte clockpin, byte datapin); // Sends Read Byte
void sendWrite(byte clockpin, byte datapin); // Sends Write Byte
boolean checkAck(byte clockpin, byte datapin); // Checks Acknowledge by Slave
boolean sendAck(byte clockpin, byte datapin); // Sends Acknowledge after read
void sendOne(byte clockpin, byte datapin, byte microDelay); // Sends a One with clock, delay can be included in microseconds
void sendZero(byte clockpin, byte datapin, byte microDelay); // Sends a Zero with clock, delay can be included in microseconds
void startcond(byte clockpin, byte datapin); // Sends a Startcondition
void stopcond(byte clockpin, byte datapin); // Sends a Stop condition
void starti2c(byte clockpin, byte datapin); // Sets the Pins accordingly for the i2c communication to go flawless

Aslong as you understand the basics of the I2C Protocol this is quite Straightforward

# Example Usage : 
Receive the Busvoltage read by the INA219 Sensor with a slave address 0x40

short getBusVoltage()
{
  // Sends Address + Write Bit + Pointer Address
  startcond(sclpin, sdapin);
  sendAddress(0x40, sclpin, sdapin);
  sendWrite(sclpin, sdapin);
  checkAck(sclpin, sdapin);
  sendByte(0x02, sclpin, sdapin);
  checkAck(sclpin, sdapin);

  // Sends Address + Read Bit
  startcond(sclpin, sdapin);
  sendAddress(0x40, sclpin, sdapin);
  sendRead(sclpin, sdapin);
  checkAck(sclpin, sdapin);

  // Gets data by the slave + acknowledged received data(can add condition if needed)
  byte higher = getByte(sclpin, sdapin);
  sendAck(sclpin, sdapin);

  // Gets data by the slave + acknowledged received data(can add condition if needed)
  byte lower = getByte(sclpin, sdapin);
  sendAck(sclpin, sdapin);

  // Stops I2C comm
  stopcond(sclpin, sdapin);

  short data = (((higher << 8) | lower) >> 3);
  return data * 4;
}
