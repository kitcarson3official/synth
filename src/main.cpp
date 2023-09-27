#include <SDL2/SDL.h>
#include <SDL_audio.h>
#include <SDL_stdinc.h>
#include <cmath>
#include <iostream>
#include <optional>

/*******************************************************************************
 * TODO
 * 1. check as macro with ref to __LINE__ and __FILE__
 * 2. cmp-emoji
 */

/*******************************************************************************
 * ✅1. callback func
 * ❌2. SDL_AudioSpec --> define the specs
 * ❌3. Query the system for the specs
 */

// thx shurizzle :)
#define SDL_check(ret, msg)                                                    \
  (ret < 0)                                                                    \
      ? (SDL_Log("%s:%d: ERROR: %s\n", __FILE__, __LINE__, (msg)), exit(1), 0) \
      : (ret)

namespace synth {
using std::optional;
/*******************************************************************************
 * CONSTANTS
 */
const float LA_FREQ = 440.;
const int SAMPLING_RATE = 44'100;
const float sample_time = 1. / 44'100.;

void synth_callback([[__maybe_unused__]] void *userdata, unsigned char *_buffer,
                    int len) {
  auto buffer = reinterpret_cast<float *>(_buffer);
  const unsigned int N = len / sizeof(float);
  for (unsigned int i = 0; i < N; ++i) {
    buffer[i] = 100. * sinf(2 * M_PI * LA_FREQ * sample_time * (float)i);
  }
}

optional<SDL_AudioDeviceID> synth_init_audio_device() {
  SDL_AudioSpec want, have;
  SDL_zero(want);
  SDL_zero(have);
  want.freq = SAMPLING_RATE;
  want.channels = 1;
  want.format = AUDIO_F32;
  want.samples = 4096;
  want.callback = synth_callback;

  SDL_AudioDeviceID adi =
      SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_ANY_CHANGE);
  return adi > 0 ? std::optional(adi) : std::nullopt;
}

} // namespace synth

int main([[__maybe_unused__]] int argc, [[__maybe_unused__]] char **argv) {
  using namespace synth;
  SDL_check(SDL_Init(SDL_INIT_AUDIO), "Init audio");
  auto adi = synth_init_audio_device();
  if (adi.has_value()) {
    SDL_PauseAudioDevice(adi.value(), 0);
  } else {
    SDL_Log("adi failed\n");
    exit(1);
  }
  while (true)
    ;
  return 0;
}
