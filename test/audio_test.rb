def within_app(&block)
  Cute.cf_make_app("Audio Test App", 0, 10, 10, 800, 600, 0, "audio_test_app")
  Cute.cf_app_update
  block.call
  Cute.cf_app_update
  Cute.cf_app_destroy
end

within_app do
  assert("Cute::Audio class exists") do
    assert_kind_of(Class, Cute::Audio)
  end

  assert("Cute::Sound class exists") do
    assert_kind_of(Class, Cute::Sound)
  end

  # Test audio loading functions exist
  assert("Cute.cf_audio_load_ogg exists") do
    assert_respond_to(Cute, :cf_audio_load_ogg)
  end

  assert("Cute.cf_audio_load_wav exists") do
    assert_respond_to(Cute, :cf_audio_load_wav)
  end

  assert("Cute.cf_audio_load_ogg_from_memory exists") do
    assert_respond_to(Cute, :cf_audio_load_ogg_from_memory)
  end

  assert("Cute.cf_audio_load_wav_from_memory exists") do
    assert_respond_to(Cute, :cf_audio_load_wav_from_memory)
  end

  # Test global audio functions exist
  assert("Cute.cf_audio_set_global_volume exists") do
    assert_respond_to(Cute, :cf_audio_set_global_volume)
  end

  assert("Cute.cf_audio_set_pan exists") do
    assert_respond_to(Cute, :cf_audio_set_pan)
  end

  assert("Cute.cf_audio_set_pause exists") do
    assert_respond_to(Cute, :cf_audio_set_pause)
  end

  assert("Cute.cf_audio_set_sound_volume exists") do
    assert_respond_to(Cute, :cf_audio_set_sound_volume)
  end

  assert("Cute.cf_audio_cull_duplicates exists") do
    assert_respond_to(Cute, :cf_audio_cull_duplicates)
  end

  assert("Cute.cf_play_sound exists") do
    assert_respond_to(Cute, :cf_play_sound)
  end

  assert("Cute.cf_sound_params_defaults exists") do
    assert_respond_to(Cute, :cf_sound_params_defaults)
  end

  # Test music functions exist
  assert("Cute.cf_music_crossfade exists") do
    assert_respond_to(Cute, :cf_music_crossfade)
  end

  assert("Cute.cf_music_get_sample_index exists") do
    assert_respond_to(Cute, :cf_music_get_sample_index)
  end

  assert("Cute.cf_music_pause exists") do
    assert_respond_to(Cute, :cf_music_pause)
  end

  assert("Cute.cf_music_play exists") do
    assert_respond_to(Cute, :cf_music_play)
  end

  assert("Cute.cf_music_resume exists") do
    assert_respond_to(Cute, :cf_music_resume)
  end

  assert("Cute.cf_music_set_loop exists") do
    assert_respond_to(Cute, :cf_music_set_loop)
  end

  assert("Cute.cf_music_set_pitch exists") do
    assert_respond_to(Cute, :cf_music_set_pitch)
  end

  assert("Cute.cf_music_set_sample_index exists") do
    assert_respond_to(Cute, :cf_music_set_sample_index)
  end

  assert("Cute.cf_music_set_volume exists") do
    assert_respond_to(Cute, :cf_music_set_volume)
  end

  assert("Cute.cf_music_stop exists") do
    assert_respond_to(Cute, :cf_music_stop)
  end

  assert("Cute.cf_music_switch_to exists") do
    assert_respond_to(Cute, :cf_music_switch_to)
  end

  # Test global audio controls work without files
  assert("Cute.cf_audio_set_global_volume works") do
    result = Cute.cf_audio_set_global_volume(0.5)
    assert_equal(0.5, result)
  end

  assert("Cute.cf_audio_set_pan works") do
    result = Cute.cf_audio_set_pan(0.0)
    assert_equal(0.0, result)
  end

  assert("Cute.cf_audio_set_pause works") do
    result = Cute.cf_audio_set_pause(false)
    assert_equal(false, result)
  end

  assert("Cute.cf_audio_set_sound_volume works") do
    result = Cute.cf_audio_set_sound_volume(1.0)
    assert_equal(1.0, result)
  end

  assert("Cute.cf_audio_cull_duplicates works") do
    assert_nil(Cute.cf_audio_cull_duplicates)
  end

  assert("Cute.cf_music_get_sample_index works") do
    result = Cute.cf_music_get_sample_index
    assert_kind_of(Integer, result)
  end

  assert("Cute.cf_music_pause works") do
    assert_nil(Cute.cf_music_pause)
  end

  assert("Cute.cf_music_resume works") do
    assert_nil(Cute.cf_music_resume)
  end

  assert("Cute.cf_music_set_loop works") do
    result = Cute.cf_music_set_loop(true)
    assert_equal(true, result)
  end

  assert("Cute.cf_music_set_pitch works") do
    result = Cute.cf_music_set_pitch(1.0)
    assert_equal(1.0, result)
  end

  assert("Cute.cf_music_set_sample_index works") do
    result = Cute.cf_music_set_sample_index(0)
    assert_equal(0, result)
  end

  assert("Cute.cf_music_set_volume works") do
    result = Cute.cf_music_set_volume(1.0)
    assert_equal(1.0, result)
  end

  assert("Cute.cf_music_stop works") do
    assert_nil(Cute.cf_music_stop)
  end

  # Note: Testing actual audio loading and playing would require audio files,
  # which are not available in the test environment. The above tests verify
  # that all the binding functions exist and basic parameter-free functions work.
end