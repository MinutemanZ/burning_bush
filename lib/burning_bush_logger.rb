require 'logging'
require 'socket'

include Logging.globally

module Logging::Layouts
  class Logstash < Logging::Layout
    def initialize opts = {}
      super
      @created_at = Time.now
    end

    def format event
      h = {
        '@timestamp'    => iso8601_format(event.time),
        '@message'      => format_obj(event.data),
        '@source_host'  =>  Socket.gethostname,
        '@version'      => '1',
        '@fields'       => {
          :log_name       => event.logger,
          :level          => ::Logging::LNAMES[event.level],
          :file           => event.file,
          :line           => event.line,
          :method         => event.method,
          :pid            => Process.pid,
          :env            => ENV.fetch('ENV_NAME')
        }
      }
      MultiJson.encode(h)
    end

    # Public: Take a given object and convert it into a format suitable for
    # inclusion as a log message. The conversion allows the object to be more
    # easily expressed in YAML or JSON form.
    #
    # If the object is an Exception, then this method will return a Hash
    # containing the exception class name, message, and backtrace (if any).
    #
    # obj - The Object to format
    #
    # Returns the formatted Object.
    #
    def format_obj( obj )
      case obj
      when Exception
        h = { :class   => obj.class.name,
              :message => obj.message }
        h[:backtrace] = obj.backtrace if @backtrace && !obj.backtrace.nil?
        h
      when Time
        iso8601_format(obj)
      else
        obj
      end
    end

    private
      # Convert the given time _value_ into an ISO8601 formatted time string.
      #
      def iso8601_format( value )
        str = value.strftime('%Y-%m-%dT%H:%M:%S')
        str << ('.%06d' % value.usec)

        offset = value.gmt_offset.abs
        return str << 'Z' if offset == 0

        offset = sprintf('%02d:%02d', offset / 3600, offset % 3600 / 60)
        return str << (value.gmt_offset < 0 ? '-' : '+') << offset
      end
  end
end

Logging.logger.root.level = :debug
Logging.logger.root.add_appenders(
  Logging.appenders.stdout(
    :layout => Logging.layouts.pattern(:pattern => '[%d] %-5l: %m\n')
  )
)
if ENV['ENV_NAME'] == 'production'
  Logging.logger.root.level = :info
end
