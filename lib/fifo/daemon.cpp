#include <iostream>
#include <cstdlib>
#include <string>

#include "hardware_interface/aiousb_wrapper.h"
#include "fifo/pipe.h"

void test_fifo();

int main(int /*argc*/, char **/*argv*/) {
  BurningBush::HardwareInterface::AiousbWrapper interface;

  int zone;
  bool status;
  while(true) {
    BurningBush::Fifo::Pipe pipe;
    while(pipe.get_command(zone, status)) {
      std::cout << "Zone " << zone << (status ? " on" : " off") << std::endl;
      interface.set_buffer(zone,status);
    }
    interface.write_zones();
  }

  return 0;
}

void print_fifo_status(FILE *file_h) {
  std::cout << "Error: " << ferror(file_h) << std::endl;
  std::cout << "eof: " << feof(file_h) << std::endl;
}

void test_fifo() {
  while(true) {
    std::cout << "Opening pipe" << std::endl;
    FILE *file_h = fopen("exec/fifo", "r");

    print_fifo_status(file_h);
    char buffer[101];
    fgets(buffer, 2, file_h);
    std::cout << buffer << std::endl;
    while(!feof(file_h)) {
      fgets(buffer, 101, file_h);
    }
    print_fifo_status(file_h);

    fclose(file_h);
  }
}
