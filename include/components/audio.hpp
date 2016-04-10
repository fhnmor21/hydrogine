/**
The MIT License (MIT)

Copyright (c) 2016 Flavio Moreira

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
  * structs containing component data
  *
  */

#ifndef COMPONENT_AUDIO_HPP
#define COMPONENT_AUDIO_HPP

#include "core/types.hpp"

namespace Hydrogyne
{

namespace Component
{

enum eAudioState
{
  PLAYING,
  PAUSED,
  STOPED,
};

// forward declaration
class AudioInterface;
class MusicData;
class SoundFxData;

struct AudioPod
{
  MusicData* music;
  float musicVolume; // values between 0.0 - 1.0
  eAudioState musicState;
  SoundFxData* soundFx;
  float soundFxVolume; // values between 0.0 - 1.0
  eAudioState soundFxState;

  AudioInterface* resource;
};

class AudioInterface
{
public:
  AudioInterface() {}
  virtual ~AudioInterface() {}
  virtual void play(const AudioPod& component) = 0;
};

} // namespace Component

} // end namespace Hydrogyne

#endif // COMPONENT_AUDIO_HPP
