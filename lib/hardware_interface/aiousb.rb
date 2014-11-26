require 'hardware_interface/base'
require 'AIOUSB'

module HardwareInterface
  class Aiousb < HardwareInterface::Base

    class BadDrivers < StandardError; end

    def initialize(**options)
      @name = options[:name] || ""
      @serial_number = options[:serial_number] || 0
      @index = options[:index] || 0
      @num_dio_bytes = options[:num_dio_bytes] || 0
      @num_counters = options[:num_counters] || 0
      @product_id = options[:product_id] || 0
    end

    def set_zone(zone,value)
      super
      self.get_lock
      aiousb_value = value ? AIOUSB::AIOUSB_TRUE : AIOUSB::AIOUSB_FALSE
      AIOUSB.DIO_Write1(self.index, zone, aiousb_value)
      self.release_lock
    end

    def get_lock
    end

    def release_lock
    end
  end
end
