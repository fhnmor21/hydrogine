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
  * base system interface
  * other systems will inherity from this class
  *
  */

#ifndef SYSTEM_INTERFACE_HPP
#define SYSTEM_INTERFACE_HPP

#include "components/binder.hpp"
#include "core/entities_manager.hpp"

namespace Hydrogine
{

namespace System
{

class SystemsInterface
{
public:
  SystemsInterface() = delete;
  SystemsInterface(SystemsInterface& other) = delete;
  explicit SystemsInterface(const char* name)
      : name_(name)
  {
    bool succeded = false;
    SystemsInterface::systemRegistrar(succeded, this, name, REGISTER);
    assert(succeded);
  }

  virtual ~SystemsInterface()
  {
    bool succeded = false;
    SystemsInterface::systemRegistrar(succeded, this, name_.c_str(), UNREGISTER);
    assert(succeded);
  }

  // get system name
  const String& getName() { return this->name_; }
  // perform one step in the system
  void update(TimeDim delta);

  // public class's methods
  // get system by name
  CLASS_METHOD SystemsInterface* getSystem(const String& name);
  // check if the pointer actually points to a system
  CLASS_METHOD bool isValid(SystemsInterface& system);

  // entity related methods
  void insertEntity(Component::EntityPod& entity);
  void removeEntity(const Component::EntityPod& entity);
  ComponentBinderPtr bindComponent(ResourceID resourceId);

protected:
  enum eRegistrar
  {
    REGISTER,
    UNREGISTER,
    VERIFY,
  };

  // must be overriden in each system (impl. NVI)
  virtual void tick(TimeDim delta) {}
  virtual void insert(Component::EntityPod& entity) {}
  virtual void remove(const Component::EntityPod& entity) {}
  virtual ComponentBinderPtr getComponentBinder(ResourceID resourceId)
  {
    return ComponentBinderPtr(nullptr);
  }

  // class methods
  CLASS_METHOD SystemsInterface* systemRegistrar(bool& retValue,
                                                 SystemsInterface* system,
                                                 const char* name = nullptr,
                                                 eRegistrar op = VERIFY);

  // data
  String name_;
};

} // end namespace System

} // end namespace Hydrogine

#endif // SYSTEM_INTERFACE_HPP
