PROJECT_ROOT = File.join(File.dirname(__FILE__), '..')

God.watch do |w|
  w.name = "ddclient"
  w.pid_file = '/var/run/ddclient.pid'
  w.keepalive
  w.start = 'ddclient -daemon=1'
  w.behavior(:clean_pid_file)
end
