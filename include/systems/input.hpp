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
  *
  *
  */

#ifndef SYSTEM_INPUT_HPP
#define SYSTEM_INPUT_HPP

#include "components/input.hpp"
#include "systems/interface.hpp"

namespace Hydrogine
{

namespace System
{

// FIXME: this system needs to support multiple componts per entity!!!
// TODO: can the other system support more than one component as well???
using InputComponents = HashMap< EntityID, Component::InputPod >;
using InputResourcePtr = SharedPtr< Component::InputInterface >;
using InputResources = HashMap< ResourceID, InputResourcePtr >;

class Input : public SystemsInterface
{
public:
  Input();
  explicit Input(const char* name);
  Input(Input& other) = delete;
  virtual ~Input();

  template < class ComponentType >
  ResourceID loadComponent();

protected:
  virtual void insert(Component::EntityPod& entity) override;
  virtual void remove(const Component::EntityPod& entity) override;
  virtual void tick(TimeDim delta) override;
  virtual ComponentBinderPtr getComponentBinder(ResourceID resourceId) override;

  InputComponents components_;
  InputResources resources_;
};

template < typename ComponentType >
ResourceID Input::loadComponent()
{
  ResourceID resCounter = seqId();
  this->resources_.emplace(resCounter, std::make_shared< ComponentType >());

  return resCounter;
}

} // end namespace System

} // end namespace Hydrogine

#endif // SYSTEM_INPUT_HPP
