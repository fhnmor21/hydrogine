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

#ifndef CORE_DISPLAY_INTERFACE_HPP
#define CORE_DISPLAY_INTERFACE_HPP

#include "core/colour.hpp"

namespace Hydrogine
{

class DisplayInterface
{
public:
  virtual ~DisplayInterface(){};

  // rendering
  virtual void render() = 0;
  virtual void clear() = 0;
  virtual void clear(const Colour& c) = 0;

  // reseting the viewport
  virtual void setColour(const Colour& c) = 0;
  virtual const Colour& getColour() const = 0;
  virtual void setResolution(Dimension2& res) = 0;
  virtual const Dimension2& getResolution() const = 0;
  virtual void setViewRect(const BoxBoundXYWH& rect) = 0;
  virtual const BoxBoundXYWH& getViewRect() const = 0;
  virtual void setTitle(const String& title) = 0;
  virtual const char* getTitle() const = 0;
  virtual void setFullscreen(bool fs) = 0;
  virtual const bool isFullscreen() const = 0;
};

} // end namespace Hydrogine

#endif // CORE_DISPLAY_INTERFACE_HPP
