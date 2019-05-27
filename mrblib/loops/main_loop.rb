$mutex = Mutex.new

puts "before Operation.new"
o = Operation.new
puts "after Operation.new"

debugprint('start', 'main_loop')

while true
  $mutex.lock()
  puts o.fixnum_sample
  $mutex.unlock()
  sleep 1
  $mutex.lock()
  puts o.string_sample
  $mutex.unlock()
  sleep 1
  $mutex.lock()
  puts o.array_sample
  $mutex.unlock()
end

