#ifndef __BURNING_BUSH_PIPE_H__
#define __BURNING_BUSH_PIPE_H__

#include <ext/stdio_filebuf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <stdexcept>

namespace BurningBush {
  namespace Fifo {
    class Pipe {
    public:
      Pipe();
      ~Pipe();

      bool get_command(int &zone, bool &on);
      void evaluate_stream();

      class Exception : public std::runtime_error {
      public:
        explicit Exception(const std::string& what_arg)
        :std::runtime_error(what_arg)
        {}
      };
    private:
      size_t parse_position;
      std::ifstream input_stream;
    };
    const char *get_path();
    void make_fifo(std::string path);
  }
}

#endif
