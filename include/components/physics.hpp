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

#ifndef COMPONENT_PHYSICS_HPP
#define COMPONENT_PHYSICS_HPP

#include "core/types.hpp"

namespace Hydrogine
{

namespace Component
{

// forward declaration
class PhysicsInterface;
struct TransformPod;

struct PhysicsPod
{
  // values between 0.0 - 1.0 (in relation to world size) / t / t
  Vector3 linVelocity;
  Vector3 linAcceleration;
  Rotation3 angVelocity;
  Rotation3 angAcceleration;

  // body
  Bound bodyContour;

  // defines the center of the body
  // values between 0.0 - 1.0 (in relation to entity Contour)
  Vector3 centerOfMass;

  // arbritary value in relation to other entities
  f32 mass;

  // values between 0.0 - 1.0
  f32 elasticity;

  // reference to transform data component
  TransformPod* transformData = nullptr;

  // physics component data pointer
  PhysicsInterface* resource = nullptr;
};

class PhysicsInterface
{
public:
  PhysicsInterface() {}
  virtual ~PhysicsInterface() {}
  virtual void step(const PhysicsPod& component, const TransformPod& transformData) = 0;
};

} // namespace Component

} // end namespace Hydrogine

#endif // COMPONENT_PHYSICS_HPP
