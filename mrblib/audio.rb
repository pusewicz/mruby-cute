module Cute
  class Audio
    def inspect
      "#<Cute::Audio:#{sprintf("0x%x", (object_id << 1))} channels:#{channel_count} samples:#{sample_count} rate:#{sample_rate}>"
    end
  end

  class Sound
    def inspect
      "#<Cute::Sound:#{sprintf("0x%x", (object_id << 1))} active:#{active?} looped:#{looped?} paused:#{paused?} volume:#{volume} pitch:#{pitch}>"
    end
  end
end