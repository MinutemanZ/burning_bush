require 'mkfifo'

module Fifo
  class Daemon

    class << self
      def start
        self.new.start
      end
    end

    def start
      Fifo.create_fifo
    end
  end
end
