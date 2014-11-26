require 'hardware_interface/base'
require 'hardware_interface/aiousb'
require 'AIOUSB'

module HardwareInterface
  class Selector
    class << self
      def get_instance
        result = AIOUSB.AIOUSB_Init()
        if result != AIOUSB::AIOUSB_SUCCESS
          raise BadDrivers("Unable to initialize USB devices")
        end
        deviceMask = AIOUSB.GetDevices()
        index = 0

        while deviceMask > 0
          if (deviceMask & 1 ) != 0
            obj = AIOUSB.GetDeviceInfo( index )
            if obj.PID == AIOUSB::USB_IIRO_16 || obj.PID == AIOUSB::USB_IDIO_16
              return HardwareInterface::Aiousb.new(
                :index => index,
                :product_id => obj.PID,
                :num_dio_bytes => obj.DIOBytes,
                :num_counters => obj.Counters
              )
            end
          end
          index += 1
          deviceMask >>= 1
        end

        logger.warn("No AcdessIO devices found.  Using mocked interface")
        HardwareInterface::Base.new
      end
    end
  end
end
