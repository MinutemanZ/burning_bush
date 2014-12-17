#include <iostream>
#include "hardware_interface/aiousb_wrapper.h"

void terminate(unsigned long result=0);

int main(int argc, char **argv) {
  BurningBush::HardwareInterface::AiousbWrapper interface;

  if(argc < 2) {
    std::cerr << "Usage: " << argv[0] << " ZONE {0|1}";
  }
  interface.set_zone(atoi(argv[1]), atoi(argv[2]));

  return 0;
}
