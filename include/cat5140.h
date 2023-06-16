#ifndef CAT5140_H
#define CAT5140_H

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

const static uint8_t CAT5140_REG_ACR = 0x08u;
const static uint8_t CAT5140_REG_DEVID = 0x01u;
const static uint8_t CAT5140_REG_VR = 0x00u;

const static unsigned long CAT5140_POLL_TIME_MS = 10;

enum CAT5140_ACR {
  CAT5140_ACR_SAVE = 0x00,
  CAT5140_ACR_NO_SAVE = 0x80,
};

/**
 * @brief CAT5140 digital potentiometer class.
 *
 * This class provides a simple interface to the CAT5140 digital potentiometer.
 *
 */
class CAT5140 {
 private:
  /// @brief CAT5140 device addresses
  uint8_t addr;

  /// @brief Wire object to use for I2C communication
  TwoWire *twc;

  /**
   * @brief Write a byte to a register.
   *
   * @param reg  CAT5140 internal register address.
   * @param data Byte to write.
   */
  void _writeRegister8(uint8_t reg, uint8_t data);

  /**
   * @brief Read a byte from a register.
   *
   * @param reg CAT5140 internal register address.
   *
   * @return uint8_t Byte read from register.
   */
  uint8_t _readRegister8(uint8_t reg);

  /**
   * @brief Poll the CAT5140 for write completion.
   *
   * @return false If the CAT5140 does not respond within the timeout period.
   */
  bool pollForWriteCompletion(unsigned long timeout_ms = CAT5140_POLL_TIME_MS);

 public:
  /**
   * @brief Construct a new CAT5140 object.
   *
   * @param addr CAT5140 device address.
   * @param twc  Wire object to use for I2C communication (default: Wire).
   */
  CAT5140(uint8_t addr = 0x28, TwoWire *twc = &Wire);

  /**
   * @brief Write a value to the CAT5140.
   *
   * The CAT5140 can be configured to use non-volatile memory to store the
   * wiper setting. In this case, the device will boot to the last saved wiper
   * setting. To take advantage of this, set argument `save` to true.
   *
   * Note that these NVRAM writes will take much longer (up to 10ms).
   *
   * @param value Value to write.
   * @param save  Save the wiper setting to NVRAM (default: false). See
   *              setMemoryMode().
   *
   * @return false If the write fails.
   */
  bool writeWiper(uint8_t value, bool save = false);

  /**
   * @brief Read the device ID of the CAT5140.
   *
   * (The device ID should be 0xD0.)
   *
   * @return uint8_t Device ID.
   */
  uint8_t readDeviceId() { return this->_readRegister8(CAT5140_REG_DEVID); }

  /**
   * @brief Get the current wiper setting of the CAT5140.
   *
   * @return uint8_t Current wiper setting.
   */
  uint8_t readWiper();
};

#endif  // End of include guard