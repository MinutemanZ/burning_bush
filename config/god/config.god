PROJECT_ROOT = File.join(File.dirname(__FILE__), '..', '..')

God.watch do |w|
  w.name = "ddclient"
  w.pid_file = '/var/run/ddclient.pid'
  w.keepalive
  w.start = 'ddclient -daemon=1'
  w.behavior(:clean_pid_file)
end

God.watch do |w|
  # Environment variables
  w.env = {
    'BURNING_BUSH_ROOT' => PROJECT_ROOT
  }
  w.env['BURNING_BUSH_LIB'] = w.env['BURNING_BUSH_ROOT'] + "/lib"

  w.name = "burning-bush"
  w.log = PROJECT_ROOT + "/exec/log.txt"
  w.keepalive
  w.start = "su -l pi -c #{PROJECT_ROOT}/burning_bush_daemon"
  puts "logging to #{w.log}"
end
