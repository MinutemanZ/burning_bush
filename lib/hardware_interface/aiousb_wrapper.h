#ifndef __BURNING_BUSH_AIOUSB_H__
#define __BURNING_BUSH_AIOUSB_H__

#include <array>
#include <stdexcept>

namespace BurningBush {
  namespace HardwareInterface {
    class AiousbWrapper {
    public:
      AiousbWrapper();
      ~AiousbWrapper();
      void set_zone(int zone, bool on);

      class Exception : public std::runtime_error {
        // using necessary because of explicit keywords in contstructors
        using std::runtime_error::runtime_error;
      };
    private:
      void set_buffer(int zone, bool on);
      void set_hardware();

      std::array<unsigned char,4> buffer;
    };
    void check_aiousb_result(unsigned long result);
  }
}


#endif
