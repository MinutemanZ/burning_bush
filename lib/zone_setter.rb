require 'hardware_interface/lock'
require 'hardware_interface/selector'

class ZoneSetter

  class InvalidInput < StandardError; end

  class << self
    def set_zone(zone,value)
      unless /^\d+$/.match(zone) && /^\d+$/.match(value)
        raise InvalidInput, "[#{zone},#{value}] received.  " \
          "Expected [zone value] where zone and value are integers."
      end
      zone = zone.to_i
      value = value != "0"
      unless 0 <= zone && zone < 16
        raise InvalidInput,
          "zone must be between 0-15 inclusive. #{zone} received."
      end

      self.new.set_zone(zone,value)
    end
  end

  def set_zone(zone,value)
    HardwareInterface::Lock.get do
      self.interface.set_zone(zone, value)
    end
  end

  def interface
    @interface ||= HardwareInterface::Selector.get_instance
  end
end
