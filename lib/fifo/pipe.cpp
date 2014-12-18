#include <algorithm>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>

#include "fifo/pipe.h"

namespace BurningBush {
  namespace Fifo {
    Pipe::Pipe()
    : parse_position(0)
    , input_handle(::fopen(get_path(), "r"))
    , input_buffer(fileno(input_handle), std::ios::in)
    , input_stream(&input_buffer)
    {}

    Pipe::~Pipe() {
      ::fclose(input_handle);
      input_handle = NULL;
    }

    /*
    Reads the input buffer and extracts the zone and state information
    */
    bool Pipe::get_command(int &zone, bool &on) {
      std::string line;
      if(!std::getline(input_stream, line, ',')) {
        std::cerr << "Finished parsing line" << std::endl;
        return false;
      }
      size_t zone_pos = line.find_first_not_of(", \n", parse_position);
      if(zone_pos == std::string::npos) {
        std::cerr << "Couldn't find zone number" << std::endl;
        return false;
      }
      size_t space_pos = line.find_first_of(' ', zone_pos);
      if(space_pos == std::string::npos) {
        std::cerr << "Couldn't find space after zone number" << std::endl;
        return false;
      }
      size_t status_pos = line.find_first_not_of(' ', space_pos);
      if(status_pos == std::string::npos) {
        std::cerr << "Couldn't find status" << std::endl;
        return false;
      }
      size_t end_pos = line.find_first_not_of("onf", status_pos);
      if(end_pos == std::string::npos) {
        end_pos = line.length();
      }

      std::string status = line.substr(status_pos, end_pos-status_pos);
      std::transform(
        status.begin(), status.end(), status.begin(), ::tolower);

      zone = std::strtol(line.c_str() + zone_pos, NULL, 10);
      on = (status == "on");
      return true;
    }

    const char *get_path() {
      const char* env_path = std::getenv("BURNING_BUSH_ROOT");
      if(env_path == NULL) {
        throw Pipe::Exception("Run \"source .env\"");
      }
      std::string fifo_path = env_path;
      fifo_path += "/exec/fifo";

      make_fifo(fifo_path);

      return fifo_path.c_str();
    }

    /* 
    Creates a fifo if it doesn't exist.  Does nothing if it already exists.
    */
    void make_fifo(std::string path) {
      int result = mkfifo(path.c_str(), S_IRUSR | S_IWUSR);
      if(result < 0) {
       struct stat buf;
        if(stat(path.c_str(), &buf) != 0 || !S_ISFIFO(buf.st_mode)) {
          std::cerr << path << " could not be turned into a fifo" << std::endl;
          exit(2);
        }
      }
    }
  }
}
