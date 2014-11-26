module HardwareInterface
  class Base
    def set_zone(zone,value)
      logger.info "Setting zone #{zone} to #{!!value}"
    end
  end
end
