#ifndef __BURNING_BUSH_PIPE_H__
#define __BURNING_BUSH_PIPE_H__

#include <ext/stdio_filebuf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

namespace BurningBush {
  namespace Fifo {
    class Pipe {
    public:
      Pipe();
      ~Pipe();

      bool get_command(int &zone, bool &on);

      class Exception : public std::runtime_error {
        // using necessary because of explicit keywords in contstructors
        using std::runtime_error::runtime_error;
      };
    private:
      size_t parse_position;
      // Order matters.  Need input_handle to construct input_buffer,
      // which is needed to construct input_stream
      FILE *input_handle;
      __gnu_cxx::stdio_filebuf<char> input_buffer;
      std::istream input_stream;
    };
    const char *get_path();
    void make_fifo(std::string path);
  }
}

#endif
