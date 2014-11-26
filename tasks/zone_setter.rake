require 'zone_setter'
require 'burning_bush_logger'

namespace :zone_setter do
  task :write, [:zone, :value] do |t, args|
    hash_args = args.to_hash
    ZoneSetter.set_zone(hash_args.fetch(:zone), hash_args.fetch(:value))
  end
end
