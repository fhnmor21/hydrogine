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
  * base entities data component
  */

#ifndef COMPONENT_GRAPHIC_HPP
#define COMPONENT_GRAPHIC_HPP

#include "core/colour.hpp"

namespace Hydrogine
{

namespace Component
{
// forward declaration
class GraphicInterface;
struct TransformPod;

struct GraphicPod
{

  // defines the anchor within the boudaries
  // values between 0.0 - 1.0 (in relation to entity size | UV)
  Vector3 anchor = CENTER;

  // colour parameters
  Colour colourTint = Colours::WHITE;
  ColourComp alphaMode = 1.0f;
  eBlendMode blendingMode = BLENDMODEALPHA_;

  // whether to show the entity or not
  bool isVisible = true;

  // reference to transform data component
  TransformPod* transformData = nullptr;

  // graphic component data pointer
  GraphicInterface* resource = nullptr;
};

class GraphicInterface
{
public:
  GraphicInterface() {}
  virtual ~GraphicInterface() {}
  virtual void paint(const GraphicPod& component, const TransformPod& transformData) = 0;
};

template < typename T >
class Image : public GraphicInterface
{
public:
  Image(Image& other) = delete;
  Image();
  explicit Image(const String& filepath);
  // TODO:
  // Image(const ImageAtlas & atlas, vector<AtlasKey> keys);
  // Image(const NetworkResource & netRes);
  virtual ~Image();

  bool isLoaded();
  ErrorCode loadFromFile(const String& filepath);
  // TODO:
  // ErrorCode loadFromAtlas(const ImageAtlas & atlas);
  // ErrorCode loadFromNet(const NetworkResource & netRes);

  virtual void paint(const GraphicPod& component, const TransformPod& transformData) override;
  // virtual bool setParameter(
  //     const char * paramName,
  //     const float & paramValue = 0.0f) override;

protected:
  using HANDLER_ = T;
  UniquePtr< HANDLER_ > data_;

  // size - between 0.0 - 1.0 (in relation to viewport size)
  Dimension2 textureSize_;
};

} // namespace Component

} // end namespace Hydrogine

#endif // COMPONENT_GRAPHIC_HPP
