$mutex = Mutex.new

class MyClass

end

puts "try to initialize"
m = MyClass.new
puts "succeed in initializing"
o = Operation.new
puts "succeed in initializing"

# debugprint('start', 'main_loop')
# while true
#   $mutex.lock()
#   puts o.fixnum_sample
#   $mutex.unlock()
#   sleep 1
#   $mutex.lock()
#   puts o.string_sample
#   $mutex.unlock()
#   sleep 1
#   $mutex.lock()
#   puts o.array_sample
#   $mutex.unlock()
# end

