module Cute
  class Audio
    # Returns the number of audio channels (1 for mono, 2 for stereo)
    # @return [Integer] the number of channels
    def channel_count
    end

    # Returns the total number of audio samples
    # @return [Integer] the number of samples
    def sample_count
    end

    # Returns the sample rate in Hz (e.g., 44100)
    # @return [Integer] the sample rate
    def sample_rate
    end
  end

  class Sound
    # Returns whether the sound is set to loop
    # @return [Boolean] true if looping, false otherwise
    def looped?
    end

    # Sets whether the sound should loop
    # @param value [Boolean] true to loop, false to play once
    # @return [Boolean] the new loop setting
    def looped=(value)
    end

    # Returns whether the sound is currently paused
    # @return [Boolean] true if paused, false otherwise
    def paused?
    end

    # Sets whether the sound is paused
    # @param value [Boolean] true to pause, false to unpause
    # @return [Boolean] the new pause setting
    def paused=(value)
    end

    # Returns the current pitch multiplier (1.0 is normal speed)
    # @return [Float] the pitch multiplier
    def pitch
    end

    # Sets the pitch multiplier (1.0 is normal speed, 2.0 is double speed, 0.5 is half speed)
    # @param value [Float] the new pitch multiplier
    # @return [Float] the new pitch value
    def pitch=(value)
    end

    # Returns the current sample index (position in the audio)
    # @return [Integer] the sample index
    def sample_index
    end

    # Sets the current sample index (seeks to position in the audio)
    # @param value [Integer] the new sample index
    # @return [Integer] the new sample index
    def sample_index=(value)
    end

    # Returns the current volume (0.0 to 1.0)
    # @return [Float] the volume level
    def volume
    end

    # Sets the volume (0.0 to 1.0)
    # @param value [Float] the new volume level
    # @return [Float] the new volume value
    def volume=(value)
    end

    # Returns whether the sound is currently playing
    # @return [Boolean] true if active/playing, false otherwise
    def active?
    end

    # Stops the sound playback
    # @return nil
    def stop
    end
  end

  # Loads an OGG audio file
  # @param path [String] path to the OGG file
  # @return [Audio] the loaded audio object
  def self.cf_audio_load_ogg(path)
  end

  # Loads an OGG audio file from memory
  # @param data [String] binary data of the OGG file
  # @param size [Integer] size of the data in bytes
  # @return [Audio] the loaded audio object
  def self.cf_audio_load_ogg_from_memory(data, size)
  end

  # Loads a WAV audio file
  # @param path [String] path to the WAV file
  # @return [Audio] the loaded audio object
  def self.cf_audio_load_wav(path)
  end

  # Loads a WAV audio file from memory
  # @param data [String] binary data of the WAV file
  # @param size [Integer] size of the data in bytes
  # @return [Audio] the loaded audio object
  def self.cf_audio_load_wav_from_memory(data, size)
  end

  # Sets the global audio volume
  # @param volume [Float] volume level (0.0 to 1.0)
  # @return [Float] the volume value
  def self.cf_audio_set_global_volume(volume)
  end

  # Sets the global audio pan (-1.0 left, 0.0 center, 1.0 right)
  # @param pan [Float] pan value (-1.0 to 1.0)
  # @return [Float] the pan value
  def self.cf_audio_set_pan(pan)
  end

  # Pauses or unpauses all audio
  # @param paused [Boolean] true to pause, false to unpause
  # @return [Boolean] the pause state
  def self.cf_audio_set_pause(paused)
  end

  # Sets the global sound effects volume
  # @param volume [Float] volume level (0.0 to 1.0)
  # @return [Float] the volume value
  def self.cf_audio_set_sound_volume(volume)
  end

  # Removes duplicate sounds to save memory
  # @return nil
  def self.cf_audio_cull_duplicates
  end

  # Plays an audio clip as a sound effect
  # @param audio [Audio] the audio to play
  # @return [Sound] the playing sound object
  def self.cf_play_sound(audio)
  end

  # Returns default sound parameters
  # @return [Object] default sound parameters (implementation pending)
  def self.cf_sound_params_defaults
  end

  # Crossfades between two music tracks
  # @param audio_a [Audio] the first audio track
  # @param audio_b [Audio] the second audio track
  # @param fade_out_time [Float] time to fade out first track
  # @param fade_in_time [Float] time to fade in second track
  # @return nil
  def self.cf_music_crossfade(audio_a, audio_b, fade_out_time, fade_in_time)
  end

  # Gets the current sample index of the playing music
  # @return [Integer] the current sample index
  def self.cf_music_get_sample_index
  end

  # Pauses the currently playing music
  # @return nil
  def self.cf_music_pause
  end

  # Plays music from an audio object
  # @param audio [Audio] the audio to play as music
  # @return nil
  def self.cf_music_play(audio)
  end

  # Resumes paused music
  # @return nil
  def self.cf_music_resume
  end

  # Sets whether music should loop
  # @param loop [Boolean] true to loop, false to play once
  # @return [Boolean] the loop setting
  def self.cf_music_set_loop(loop)
  end

  # Sets the music pitch
  # @param pitch [Float] pitch multiplier (1.0 is normal)
  # @return [Float] the pitch value
  def self.cf_music_set_pitch(pitch)
  end

  # Sets the current sample index of the music (seeks)
  # @param index [Integer] the sample index to seek to
  # @return [Integer] the sample index
  def self.cf_music_set_sample_index(index)
  end

  # Sets the music volume
  # @param volume [Float] volume level (0.0 to 1.0)
  # @return [Float] the volume value
  def self.cf_music_set_volume(volume)
  end

  # Stops the currently playing music
  # @return nil
  def self.cf_music_stop
  end

  # Switches to a different music track
  # @param audio [Audio] the new audio to play as music
  # @return nil
  def self.cf_music_switch_to(audio)
  end
end