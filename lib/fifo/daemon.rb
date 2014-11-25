require 'Fifo'

module Fifo
  class Daemon

    attr_reader :pins

    class << self
      def start
        self.new.start
      end
    end

    def initialize
      @pins = 0x0
    end

    def start
      Fifo.create_fifo
      self.read_pins
    end
  end
end
