require 'fifo'

namespace :fifo do
  namespace :daemon do
    task :start do
      Fifo::Daemon.start
    end
  end
end
