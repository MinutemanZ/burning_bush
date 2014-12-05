#include <iostream>
#include <cstring>
#include "aiousb.h"

int main(int /*argc*/, char **/*argv*/) {
  char buffer[4];

  std::cout << "Hello World" << std::endl;

  memset(buffer, 0, 4);
  AIOUSB::DIO_WriteAll(AIOUSB::diFirst, buffer);

  return 0;
}
