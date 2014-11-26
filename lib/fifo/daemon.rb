require 'fifo/utils'
require 'hardware_interface/selector'

module Fifo
  class Daemon

    class << self
      def start
        self.new.start
      end
    end

    def initialize
    end

    def start
      Fifo.create_fifo
      File.open(Fifo::PATH, 'r') do |pipe|
        self.read(pipe)
      end
    end

    def interface
      @interface ||= HardwareInterface::Selector.get_instance
    end

    def read(pipe)
      pipe.each_line do |line|
        match = /^(\d+) +(\d+)$/.match(line)
        if match
          zone, value = "1 1".split.map{|n| n.to_i}
          interface.set_zone(zone, value)
        else
          logger.warn "\"#{line}\" received.  Expected \"zone value\" where" \
            "zone and value are integers."
        end
      end
    end
  end
end
