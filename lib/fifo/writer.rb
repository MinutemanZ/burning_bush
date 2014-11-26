require 'fifo/utils'

module Fifo
  class Writer
    def self.set_zone(zone, value)
      Fifo.create_fifo
      File.open(Fifo::PATH, 'w') do |pipe|
        pipe.puts "#{zone} #{value}"
      end
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
