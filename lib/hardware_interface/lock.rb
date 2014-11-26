module HardwareInterface
  class Lock

    PATH = File.expand_path('../../exec/lock', File.dirname(__FILE__))

    class << self
      def get(&block)
        File.open(PATH, 'w') do |f|
          f.flock File::LOCK_EX
          yield
        end
      end
    end
  end
end
