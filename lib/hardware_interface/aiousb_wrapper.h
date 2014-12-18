#ifndef __BURNING_BUSH_AIOUSB_WRAPPER_H__
#define __BURNING_BUSH_AIOUSB_WRAPPER_H__

#include <stdexcept>

namespace BurningBush {
  namespace HardwareInterface {
    class AiousbWrapper {
    public:
      AiousbWrapper();
      ~AiousbWrapper();

      class Exception : public std::runtime_error {
      public:
        // using necessary because of explicit keywords in contstructors
        explicit Exception(const std::string& what_arg)
        :std::runtime_error(what_arg)
        {}
      };
      void set_buffer(int zone, bool on);
      void write_zones();

    private:
      unsigned char buffer[4];
    };
    void check_aiousb_result(unsigned long result);
  }
}


#endif
