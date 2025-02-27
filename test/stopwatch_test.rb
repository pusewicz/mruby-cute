assert("Stopwatch#new") do
  stopwatch = Cute::Stopwatch.new
  assert_true(stopwatch.is_a?(Cute::Stopwatch))
end

assert("Stopwatch#seconds") do
  stopwatch = Cute::Stopwatch.new
  assert_equal(0, stopwatch.seconds)
  assert_kind_of(Integer, stopwatch.seconds)
end

assert("Stopwatch#milliseconds") do
  stopwatch = Cute::Stopwatch.new
  assert_equal(0, stopwatch.milliseconds)
  assert_kind_of(Integer, stopwatch.milliseconds)
end

assert("Stopwatch#microseconds") do
  stopwatch = Cute::Stopwatch.new
  assert_equal(0, stopwatch.microseconds)
  assert_kind_of(Integer, stopwatch.microseconds)
end
