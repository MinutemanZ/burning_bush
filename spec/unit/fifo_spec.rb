require 'spec_helper'

require 'fifo'

describe Fifo do
  before :each do
    stub_const("Fifo::PATH", File.expand_path('../../test/fifo', File.dirname(__FILE__)))
    @fifo_dir = File.dirname(Fifo::PATH)
  end

  after :each do
    FileUtils.rm_r @fifo_dir if File.exists?(@fifo_dir)
  end

  context :create_fifo! do
    before :each do
      Dir.mkdir @fifo_dir
    end

    it 'creates a fifo' do
      Fifo.create_fifo!

      expect(File.ftype(Fifo::PATH)).to eq "fifo"
    end

    it 'does not rase an error if the fifo already exists' do
      File.mkfifo Fifo::PATH

      expect{Fifo.create_fifo!}.to_not raise_error
    end

    it 'raises an error if some other type of file exists' do
      File.open(Fifo::PATH, 'w') {|f| f.write "foo\n"}

      expect{Fifo.create_fifo!}.to raise_error(Fifo::PipeCreationError)
    end
  end

  context :create_fifo do
    it 'does nothing if a FIFO already exists' do
      Dir.mkdir @fifo_dir
      File.mkfifo Fifo::PATH
      expect(Fifo).to receive(:create_fifo!).never

      Fifo.create_fifo
    end

    it 'creates a fifo if no file exists' do
      Dir.mkdir @fifo_dir
      expect(Fifo).to receive(:create_fifo!)

      Fifo.create_fifo
    end

    it 'deletes a non-fifo file if some other file exists' do
      Dir.mkdir @fifo_dir
      File.open(Fifo::PATH, 'w') {|f| f.write "foo\n"}
      expect(Fifo).to receive(:create_fifo!)

      Fifo.create_fifo
    end
  end
end
