#ifndef __BURNING_BUSH_AIOUSB_WRAPPER_H__
#define __BURNING_BUSH_AIOUSB_WRAPPER_H__

#include <array>
#include <stdexcept>

namespace BurningBush {
  namespace HardwareInterface {
    class AiousbWrapper {
    public:
      AiousbWrapper();
      ~AiousbWrapper();

      class Exception : public std::runtime_error {
        // using necessary because of explicit keywords in contstructors
        using std::runtime_error::runtime_error;
      };
      void set_buffer(int zone, bool on);
      void write_zones();

    private:
      std::array<unsigned char,4> buffer;
    };
    void check_aiousb_result(unsigned long result);
  }
}


#endif
