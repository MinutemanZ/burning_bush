#include <iostream>
#include <cstring>
#include "aiousb.h"

void check_aiousb_result(unsigned long result);
void terminate(unsigned long result=0);

int main(int /*argc*/, char **/*argv*/) {
  char buffer[4];
  memset(buffer, 0, 4);

  unsigned long result = AIOUSB::AIOUSB_Init();
  check_aiousb_result(result);

  result = AIOUSB::DIO_WriteAll(AIOUSB::diFirst, buffer);
  check_aiousb_result(result);

  std::cout << "Wrote ";
  for(int i=3; i>=0; i-=2) {
    std::cout << std::hex << buffer[i] << std::hex << buffer[i-1] << ' ';
  }
  std::cout << "successfully!" << std::endl;

  terminate();
}

void terminate(unsigned long result) {
  AIOUSB::AIOUSB_Exit();
  exit(result);  
}

/*
 * Checks the standard return codes from AIOUSB calls.  Terminates
 * exection with an appropriate error code
 */
void check_aiousb_result(unsigned long result) {
  if(result == AIOUSB::AIOUSB_SUCCESS) {
    return;
  }
  std::cout << AIOUSB::AIOUSB_GetResultCodeAsString(result) << std::endl;
  switch(result) {
    case AIOUSB::AIOUSB_SUCCESS:
      return;
    case AIOUSB::AIOUSB_ERROR_DEVICE_NOT_CONNECTED:
      std::cout << "The internal handle to the device is not valid. "
        "This can occur if AIOUSB has not been properly initialized. "
        "On Linux this can occur because libusb fails to return a valid "
        "handle.";
      break;
    case AIOUSB::AIOUSB_ERROR_DUP_NAME:
      std::cout << "More than one device was found on the bus when diOnly was "
        "specified as a device index.";
      break;
    case AIOUSB::AIOUSB_ERROR_FILE_NOT_FOUND:
      std::cout << "May mean multiple things. May mean that the attempt to "
        "load the A/D calibration table in ADC_SetCal() failed because the "
        "specified file does not exist or cannot be read. May also mean that "
        "the attempt to save the A/D calibration table to a file in "
        "ADC_SetCal() failed because the file could not be created. May also "
        "mean that no device was found on the bus when diFirst or diOnly were "
        "specified as a device index.";
      break;
    case AIOUSB::AIOUSB_ERROR_INVALID_DATA:
      std::cout << "Data retrieved from the device is not valid. May mean "
        "that the data is corrupt or that an incorrect amount of data was "
        "transferred";
      break;
    case AIOUSB::AIOUSB_ERROR_INVALID_INDEX:
      std::cout << "The device index passed to an function is invalid.";
      break;
    case AIOUSB::AIOUSB_ERROR_INVALID_MUTEX:
      std::cout << "An internal mutex is invalid. This usually means the "
        "library was unable to initialize the mutex.";
      break;
    case AIOUSB::AIOUSB_ERROR_INVALID_PARAMETER:
      std::cout << "One or more parameters passed to a function are invalid, "
        "such as outside the allowed range or null pointers.";
      break;
    case AIOUSB::AIOUSB_ERROR_INVALID_THREAD:
      std::cout << "An internal thread is invalid. This usually means the "
        "library was unable to initialize the thread.";
      break;
    case AIOUSB::AIOUSB_ERROR_NOT_ENOUGH_MEMORY:
      std::cout << "A function was unable to allocate sufficient dynamic "
        "memory.";
      break;
    case AIOUSB::AIOUSB_ERROR_NOT_SUPPORTED:
      std::cout << "The function is not supported for the device specified, "
        "for example, trying to perform A/D operations on a device that "
        "doesn't have an A/D.";
      break;
    case AIOUSB::AIOUSB_ERROR_OPEN_FAILED:
      std::cout << "Typically means that a streaming device is already open "
        "for streaming and cannot be opened again until it's closed.";
      break;
    case AIOUSB::AIOUSB_ERROR_LIBUSB: default:
      break;
  }
  std::cout << std::endl;
  terminate(result);
}