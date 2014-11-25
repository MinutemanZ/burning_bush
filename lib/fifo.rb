require 'fifo/daemon'
require 'fifo'
require 'fileutils'

module Fifo
  PATH = File.expand_path('../exec/fifo', File.dirname(__FILE__))

  class PipeCreationError < StandardError; end

  class <<self
    # Wrapper method for File.mkfifo.  Does not raise an error if FIFO exists
    def create_fifo!
      File.mkfifo PATH
    # This exception is usually raised when the fifo already exists
    rescue Exception => e
      if File.exists?(PATH) && File.ftype(PATH) != "fifo"
        raise PipeCreationError, "Could not create named pipe"
      end
    end

    # Creates a FIFO if needed
    def create_fifo
      FileUtils.mkdir_p File.dirname(PATH)
      if File.exists? PATH
        if File.ftype(PATH) != "fifo"
          File.unlink PATH
          self.create_fifo!
        end
      else
        self.create_fifo!
      end
    end
  end
end
