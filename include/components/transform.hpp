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
  * transform data component
  */

#ifndef COMPONENT_TRANSFORM_HPP
#define COMPONENT_TRANSFORM_HPP

#include "core/types.hpp"

namespace Hydrogine
{

namespace Component
{

struct TransformPod
{

  // position
  // absolute in pixels (float values)
  // can contain z-order for 2d spaces
  Vector3 position;

  // rotation
  // values between 0.0 - 1.0  (= 0 - 360)
  Rotation3 rotation;

  // scales
  // <1.0 = smaller | > 1.0 = larger
  // <0.0 = mirror
  // this attribure is shared by physics and
  // graphics, and might have application
  // to the entity behaviour as well
  Vector3 scale;

  // just for compatibility with the binder mechanisms
  void* resource;
};

} // namespace Component

} // end namespace Hydrogine

#endif // COMPONENT_TRANSFORM_HPP
