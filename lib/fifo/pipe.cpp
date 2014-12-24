#include <algorithm>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstring>

#include "fifo/pipe.h"

namespace BurningBush {
  namespace Fifo {

    Pipe::Pipe()
    : file_h(fopen(get_path(), "r"))
    {}

    Pipe::~Pipe() {
      fclose(file_h);
    }

    void Pipe::evaluate_stream() {
      std::cout << "eof:" << feof(file_h) << std::endl;
      std::cout << "fail:" << ferror(file_h) << std::endl;
    }

    bool parse_string(char *zone_pos, char *state_pos, int &zone, bool &on) {
      int zone_test = atoi(zone_pos);
      if(zone_test < 0 || zone_test > 15) {
        std::cerr << "zone must be between 0 and 15 inclusive\n";
        return false;
      }
      for(char *current = state_pos; *current != '\0'; ++current) {
        *current = tolower(*current);
      }
      on = (strncmp(state_pos, "on", 2) == 0);
      zone = zone_test;
      return true;
    }

    /*
    Reads the input buffer and extracts the zone and state information
    */
    bool Pipe::get_command(int &zone, bool &on) {
      int state = BEFORE_ZONE;
      char buffer[1001];
      char *current = buffer;
      char *zone_pos = NULL;
      char *state_pos = NULL;
      char *buffer_end = buffer + sizeof(buffer) - 1;
      while(current < buffer_end && !feof(file_h)) {
        // Just read one character at a time.  It's already buffered
        fread(current, 1, 1, file_h);
        switch(state) {
        case BEFORE_ZONE:
          if('0' <= *current && *current <= '9') {
            zone_pos = current;
            ++state;
          }
          break;
        case WITHIN_ZONE:
          if('0' <= *current && *current <= '9') {
            break;
          }
          ++state;
        // Falls through to next state
        case BEFORE_STATE:
          if(('a' <= *current && *current <= 'z')
            || ('A' <= *current && *current <= 'Z')) {

            state_pos = current;
            ++state;
            break;
          }
          break;
        case WITHIN_STATE:
          if(('a' <= *current && *current <= 'z')
            || ('A' <= *current && *current <= 'Z')) {

            break;
          }
          // We've read enough.  Parse the bits that we care about.
          *current = '\0';
          return parse_string(zone_pos, state_pos, zone, on);
        default:
          std::cerr << "Error parsing command\n";
          return false;
        }
        ++current;
      }

      return false;
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
