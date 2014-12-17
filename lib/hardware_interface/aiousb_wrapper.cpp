#include <iostream>
#include <sstream>
#include <iomanip>

#include "aiousb.h"
#include "hardware_interface/aiousb_wrapper.h"

namespace BurningBush {
  namespace HardwareInterface {
    AiousbWrapper::AiousbWrapper() {
      buffer.fill(0xff);
      check_aiousb_result(AIOUSB::AIOUSB_Init());
    }

    AiousbWrapper::~AiousbWrapper() {
      AIOUSB::AIOUSB_Exit();
    }

    void AiousbWrapper::set_zone(int zone, bool on) {
      std::cout << "zone " << zone << (on?" on":" off") << std::endl;
      set_buffer(zone, on);
      set_hardware();
    }

    //***************************************************************
    //*************************** Private ***************************
    //***************************************************************

    void AiousbWrapper::set_buffer(int zone, bool on) {
      unsigned char bit = (1 << zone%8);
      unsigned char &octet = buffer[zone/8];
      if(on) {
        octet &= ~bit; // Set the bit in question to 0
      } else {
        octet |= bit;  // Set the bit in question to 1
      }
    }

    void AiousbWrapper::set_hardware() {
      std::cout << "Setting hardware to "
        << std::hex << std::setfill('0') << std::setw(2)
        << std::hex << (static_cast<int>(buffer[1]))
        << (static_cast<int>(buffer[0])) << std::endl;
      unsigned char *data = buffer.data();
      unsigned long result = AIOUSB::DIO_WriteAll(AIOUSB::diFirst, data);
      if(result != AIOUSB::AIOUSB_SUCCESS) {
        std::cerr << AIOUSB::AIOUSB_GetResultCodeAsString(result) << std::endl;
      }
    }

    /*
     * Checks the standard return codes from AIOUSB calls.  Terminates
     * exection with an appropriate error code
     */
    void check_aiousb_result(unsigned long result) {
      if(result == AIOUSB::AIOUSB_SUCCESS) {
        return;
      }
      std::stringstream message;
      message << AIOUSB::AIOUSB_GetResultCodeAsString(result) << std::endl;
      switch(result) {
        case AIOUSB::AIOUSB_SUCCESS:
          return;
        case AIOUSB::AIOUSB_ERROR_DEVICE_NOT_CONNECTED:
          message << "The internal handle to the device is not valid. "
            "This can occur if AIOUSB has not been properly initialized. "
            "On Linux this can occur because libusb fails to return a valid "
            "handle.";
          break;
        case AIOUSB::AIOUSB_ERROR_DUP_NAME:
          message << "More than one device was found on the bus when diOnly was "
            "specified as a device index.";
          break;
        case AIOUSB::AIOUSB_ERROR_FILE_NOT_FOUND:
          message << "May mean multiple things. May mean that the attempt to "
            "load the A/D calibration table in ADC_SetCal() failed because the "
            "specified file does not exist or cannot be read. May also mean that "
            "the attempt to save the A/D calibration table to a file in "
            "ADC_SetCal() failed because the file could not be created. May also "
            "mean that no device was found on the bus when diFirst or diOnly were "
            "specified as a device index.";
          break;
        case AIOUSB::AIOUSB_ERROR_INVALID_DATA:
          message << "Data retrieved from the device is not valid. May mean "
            "that the data is corrupt or that an incorrect amount of data was "
            "transferred";
          break;
        case AIOUSB::AIOUSB_ERROR_INVALID_INDEX:
          message << "The device index passed to an function is invalid.";
          break;
        case AIOUSB::AIOUSB_ERROR_INVALID_MUTEX:
          message << "An internal mutex is invalid. This usually means the "
            "library was unable to initialize the mutex.";
          break;
        case AIOUSB::AIOUSB_ERROR_INVALID_PARAMETER:
          message << "One or more parameters passed to a function are invalid, "
            "such as outside the allowed range or null pointers.";
          break;
        case AIOUSB::AIOUSB_ERROR_INVALID_THREAD:
          message << "An internal thread is invalid. This usually means the "
            "library was unable to initialize the thread.";
          break;
        case AIOUSB::AIOUSB_ERROR_NOT_ENOUGH_MEMORY:
          message << "A function was unable to allocate sufficient dynamic "
            "memory.";
          break;
        case AIOUSB::AIOUSB_ERROR_NOT_SUPPORTED:
          message << "The function is not supported for the device specified, "
            "for example, trying to perform A/D operations on a device that "
            "doesn't have an A/D.";
          break;
        case AIOUSB::AIOUSB_ERROR_OPEN_FAILED:
          message << "Typically means that a streaming device is already open "
            "for streaming and cannot be opened again until it's closed.";
          break;
        case AIOUSB::AIOUSB_ERROR_LIBUSB: default:
          break;
      }
      message << std::endl;
      std::string message_string = message.str();
      // throw std::runtime_error(message_string);
      throw AiousbWrapper::Exception(message_string);
    }
  }
}
