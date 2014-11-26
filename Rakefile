$:.unshift ENV.fetch('AIO_RUBY_DIR')
$:.unshift File.join(File.dirname(__FILE__), "lib")

require 'rubygems'
require 'bundler'
require 'rdoc/task'

Bundler.require

RDoc::Task.new do |rdoc|
  rdoc.rdoc_files.include('lib', 'app')
  rdoc.rdoc_dir = 'doc'
end

Dir['tasks/*.rake'].each { |r| import r }
