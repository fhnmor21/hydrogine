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

#ifndef GRAPHIC_SYSTEMS_HPP
#define GRAPHIC_SYSTEMS_HPP

// #include "utils_colour.hpp"
#include "components/graphic.hpp"
#include "components/transform.hpp"
#include "core/display_interface.hpp"
#include "systems/interface.hpp"

namespace Hydrogine
{

namespace System
{

using DisplayHandler = SharedPtr< DisplayInterface >;
using GraphicComponents = HashMap< EntityID, Component::GraphicPod >;
using GraphicResourcePtr = SharedPtr< Component::GraphicInterface >;
using GraphicResources = HashMap< ResourceID, GraphicResourcePtr >;

class Graphics : public SystemsInterface
{
public:
  DisplayHandler display;

  Graphics();
  explicit Graphics(const char* name);
  Graphics(Graphics& other) = delete;
  virtual ~Graphics();

  // FIXME: replace this by a centralized resource manager... possibly reuse something ready!
  // methods specific to the graphic system
  DisplayHandler createDisplay(const BoxBoundXYWH& rect, Flags flags = 0);

  template < typename T >
  ResourceID loadResourceFromFile(const String& filepath);
  // TODO:
  // ResourceID loadResourceFromAtlas(const ImageAtlas & atlas);
  // ResourceID loadResourceFromNet(const NetworkResource & netRes)

  // camera set
  ErrorCode setCameraTransform(Component::TransformPod& transformData);

protected:
  // this methods override the base class to create the specific graphic system behaviour
  virtual void insert(Component::EntityPod& entity) override;
  virtual void remove(const Component::EntityPod& entity) override;
  virtual void tick(TimeDim delta) override;
  virtual ComponentBinderPtr getComponentBinder(ResourceID resourceId) override;

  // data
  Component::TransformPod camera_;
  GraphicComponents components_;
  GraphicResources resources_;
};

template < typename ResourceType >
ResourceID Graphics::loadResourceFromFile(const String& filepath)
{
  ResourceID resCounter = seqId();
  this->resources_.emplace(resCounter, std::make_shared< ResourceType >(filepath));

  return resCounter;
}

} // end namespace System

} // end namespace Hydrogine

#endif // GRAPHIC_SYSTEMS_HPP
