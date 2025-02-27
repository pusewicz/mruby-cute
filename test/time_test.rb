assert("CF_DELTA_TIME") do
  dt = Cute.CF_DELTA_TIME
  assert_true dt >= 0
  assert_kind_of Float, dt
end

assert("CF_DELTA_TIME_FIXED") do
  dt = Cute.CF_DELTA_TIME_FIXED
  assert_true dt >= 0
  assert_kind_of Float, dt
end

assert("CF_DELTA_TIME_INTERPOLANT") do
  dt = Cute.CF_DELTA_TIME_INTERPOLANT
  assert_true dt >= 0
  assert_kind_of Float, dt
end

assert("CF_SECONDS") do
  secs = Cute.CF_SECONDS
  assert_true secs >= 0
  assert_kind_of Float, secs
end

assert("CF_PREV_SECONDS") do
  secs = Cute.CF_PREV_SECONDS
  assert_true secs >= 0
  assert_kind_of Float, secs
end

assert("CF_TICKS") do
  ticks = Cute.CF_TICKS
  assert_true ticks >= 0
  assert_kind_of Integer, ticks
end

assert("CF_PREV_TICKS") do
  ticks = Cute.CF_PREV_TICKS
  assert_true ticks >= 0
  assert_kind_of Integer, ticks
end

assert("CF_PAUSE_TIME_LEFT") do
  time = Cute.CF_PAUSE_TIME_LEFT
  assert_true time >= 0
  assert_kind_of Float, time
end
