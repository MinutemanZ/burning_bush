require 'fifo/utils'

module Fifo
  class Writer
    def self.set_zone(zone,value)
      Fifo.create_fifo
      File.open(Fifo::PATH, 'w') do |pipe|
        pipe.puts "#{zone} #{value}"
      end
    end
  end
end
