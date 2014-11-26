require 'fifo'
require 'burning_bush_logger'

namespace :fifo do
  namespace :daemon do
    task :start do
      Fifo::Daemon.start
    end
  end

  task :write, [:zone, :value] do |t, args|
    hash_args = args.to_hash
    Fifo::Writer.set_zone(
      hash_args.fetch(:zone), hash_args.fetch(:value)
    )
  end
end
