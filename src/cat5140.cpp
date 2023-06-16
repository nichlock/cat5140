#include "cat5140.h"

CAT5140::CAT5140(uint8_t addr, TwoWire *twc) {
  this->addr = addr;
  this->twc = twc;
}

bool CAT5140::pollForWriteCompletion(unsigned long timeout_ms) {
  unsigned long end = millis() + timeout_ms;
  uint8_t result = 1;

  do {
    this->twc->beginTransmission(this->addr);
    this->twc->write((uint8_t)(CAT5140_REG_VR));
    // Device will NACK the address if the write is not complete.
    result = this->twc->endTransmission(true);
  } while ((end > millis()) && (result != 0));

  return result == 0;
}

bool CAT5140::writeWiper(uint8_t value, bool save) {
  if (save) {
    this->_writeRegister8(CAT5140_REG_ACR, CAT5140_ACR::CAT5140_ACR_SAVE);
    this->_writeRegister8(CAT5140_REG_VR, value);
    return this->pollForWriteCompletion();
  } else {
    this->_writeRegister8(CAT5140_REG_ACR, CAT5140_ACR::CAT5140_ACR_NO_SAVE);
    this->_writeRegister8(CAT5140_REG_VR, value);
    // No need to poll for write completion if not saving
    return true;
  }
}

uint8_t CAT5140::readWiper() {
  return this->_readRegister8(CAT5140_REG_VR);
}

void CAT5140::_writeRegister8(uint8_t reg, uint8_t data) {
  this->twc->beginTransmission(this->addr);
  this->twc->write(reg);
  this->twc->write(data);
  this->twc->endTransmission(true);
}

uint8_t CAT5140::_readRegister8(uint8_t reg) {
  this->twc->beginTransmission(this->addr);
  this->twc->write(reg);
  this->twc->endTransmission(true);

  this->twc->requestFrom(this->addr, (uint8_t)1);
  return this->twc->read();
}
