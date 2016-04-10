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

#ifndef COMPONENT_INPUT_HPP
#define COMPONENT_INPUT_HPP

#include "core/types.hpp"

namespace Hydrogine
{

namespace Component
{

struct Event
{
  u32 type;
  u32 value;
};

// forward declaration
class InputInterface;

struct InputPod
{
  // values between -1.0 and +1.0
  f32 axis[6];

  // values bitmask of up to 16 buttons
  u16 buttons;

  // keyboard buffer
  char keysBuffer[32];

  // graphic element data pointer
  InputInterface* resource;
};

class InputInterface
{
public:
  InputInterface() {}
  virtual ~InputInterface() {}
  virtual void poll(const Event& event, InputPod& component) = 0;
};

class WasdInput : public InputInterface
{
public:
  WasdInput() {}
  virtual ~WasdInput() {}
  virtual void poll(const Event& event, InputPod& component) override;
};

class ArrowsInput : public InputInterface
{
public:
  ArrowsInput() {}
  virtual ~ArrowsInput() {}
  virtual void poll(const Event& event, InputPod& component) override;
};

class XInput : public InputInterface
{
public:
  XInput() {}
  virtual ~XInput() {}
  virtual void poll(const Event& event, InputPod& component) override;
};

class NumPadInput : public InputInterface
{
public:
  NumPadInput() {}
  virtual ~NumPadInput() {}
  virtual void poll(const Event& event, InputPod& component) override;
};

} // namespace Component

} // end namespace Hydrogine

#endif // COMPONENT_INPUT_HPP
