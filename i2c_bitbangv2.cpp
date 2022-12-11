#include "i2c_bitbangv2.h"


void starti2c(byte clockpin, byte datapin)
{
  pinMode(clockpin, OUTPUT);
  digitalWrite(clockpin, HIGH);
  pinMode(datapin, INPUT);
}

  // Send one bit at a time, MSB gets sent first
void sendByte(byte data, byte clockpin, byte datapin)
{
  byte currentBit;
  for(byte iter = 0; iter < 8; iter++)
  {
    currentBit = bitRead(data, 7-iter);
    sendBit(currentBit, clockpin, datapin);
  }
}

// Send one bit at a time, MSB gets sent first, Read or Write bit wont be sent with this
void sendAddress(byte address, byte clockpin, byte datapin)
{
  byte currentBit;
  for(byte iter = 0; iter < 7; iter++)
  {
    currentBit = bitRead(address, 6-iter);
    sendBit(currentBit, clockpin, datapin);
  }
}


// After setting up to read a register this listens to the i2c slave data and returns it.
byte getByte(byte clockpin, byte datapin)
{
  pinMode(datapin, INPUT);
  byte currentBit;
  byte finalByte;
  for(byte iter = 0; iter < 8; iter++)
  {
    digitalWrite(clockpin, HIGH);
    currentBit = digitalRead(datapin);
    digitalWrite(clockpin, LOW);
    finalByte |= (currentBit << (7 -iter));
  }
  return finalByte;
}

// Sends a single bit, includes a clock
void sendBit(byte bit, byte clockpin, byte datapin)
{
  if(bit)
  {
    sendOne(clockpin, datapin, 0);
  }
  else
  {
    sendZero(clockpin, datapin, 0);
  }
}

// Sends the Read bit
void sendRead(byte clockpin, byte datapin)
{
  sendOne(clockpin, datapin, 4);
}

// Sends the Write Bit
void sendWrite(byte clockpin, byte datapin)
{
  sendZero(clockpin, datapin, 4);
}

// Checks if the I2C slave was addressed to correctly
// Looks up if the data line was pulled low by the slave
boolean checkAck(byte clockpin, byte datapin)
{
  digitalWrite(clockpin, LOW);
  pinMode(datapin, INPUT);
  digitalWrite(clockpin, HIGH);
  if(digitalRead(datapin) == LOW)
  {
    digitalWrite(clockpin, LOW);
    return true;
  }
  else
  {
    digitalWrite(clockpin, LOW);
    return false;
  }
}

// After receiving data this needs to be sent to let the slave know 
// you received it successfully
boolean sendAck(byte clockpin, byte datapin)
{
  pinMode(datapin, OUTPUT);
  digitalWrite(datapin, LOW);
  digitalWrite(clockpin, HIGH);
  digitalWrite(clockpin, LOW);
}

// Used for sendBit, sends a one
void sendOne(byte clockpin, byte datapin, byte microDelay)
{
  pinMode(datapin, OUTPUT);
  digitalWrite(clockpin, LOW);
  digitalWrite(datapin, HIGH);
  digitalWrite(clockpin, HIGH);
  delayMicroseconds(microDelay);
}

// Used for sendBit, sends a zero
void sendZero(byte clockpin, byte datapin, byte microDelay)
{
  pinMode(datapin, OUTPUT);
  digitalWrite(clockpin, LOW);
  digitalWrite(datapin, LOW);
  digitalWrite(clockpin, HIGH);
  delayMicroseconds(microDelay);
  
}

// Sends the start condition
void startcond(byte clockpin, byte datapin) 
{
  digitalWrite(clockpin, LOW);
  pinMode(datapin, OUTPUT);
  digitalWrite(datapin, HIGH);
  digitalWrite(clockpin, HIGH);
  digitalWrite(datapin, LOW);
}

// Sends the stop condition
void stopcond(byte clockpin, byte datapin)
{
  digitalWrite(clockpin, LOW);
  pinMode(datapin, OUTPUT);
  digitalWrite(datapin, LOW);
  digitalWrite(clockpin, HIGH);
  digitalWrite(datapin, HIGH);
}
