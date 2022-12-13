#ifndef I2C_BITBANGV2_H
#define I2C_BITBANGV2_H
#include <Arduino.h>

void sendByte(byte data, byte clockpin, byte datapin);
void sendAddress(byte address, byte clockpin, byte datapin);
byte getByte(byte clockpin, byte datapin);
void sendBit(byte bit, byte clockpin, byte datapin);
void sendRead(byte clockpin, byte datapin);
void sendWrite(byte clockpin, byte datapin);
boolean checkAck(byte clockpin, byte datapin);
boolean sendAck(byte clockpin, byte datapin);
void sendOne(byte clockpin, byte datapin, byte microDelay);
void sendZero(byte clockpin, byte datapin, byte microDelay);
void startcond(byte clockpin, byte datapin);
void stopcond(byte clockpin, byte datapin);
void starti2c(byte clockpin, byte datapin);
void sendManyBytesHex(String data, byte clockpin, byte datapin);
#endif
