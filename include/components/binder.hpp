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

#ifndef COMPONENT_BINDER_HPP
#define COMPONENT_BINDER_HPP

#include "core/types.hpp"

namespace Hydrogine
{

// forward declarations
namespace System
{
class SystemsInterface;
class ComponentBinderInterface;
}

// interface implemented by base class to support registering components
class EntityRegistrarInterface
{
private:
  friend class System::ComponentBinderInterface;
  EntityID registerIntoSystem(System::SystemsInterface& system)
  {
    return this->registerIntoSystem_(system);
  }

protected:
  EntityRegistrarInterface() {}
  EntityRegistrarInterface(EntityRegistrarInterface&) = delete;
  EntityRegistrarInterface& operator=(EntityRegistrarInterface&) = delete;
  virtual ~EntityRegistrarInterface() {}

  // add one more component to the entity
  virtual EntityID registerIntoSystem_(System::SystemsInterface& system) = 0;
};

namespace System
{

// interface used to provide access to register a component to an entity and into its system
class ComponentBinderInterface
{
public:
  virtual ~ComponentBinderInterface() {}
  virtual ErrorCode toEntity(EntityRegistrarInterface* er) = 0;

protected:
  EntityID registerIntoSystem_(SystemsInterface* sys, EntityRegistrarInterface* er)
  {
    if(sys != nullptr && er != nullptr)
    {
      return er->registerIntoSystem(*sys);
    }
    return InvalidID;
  }
};

// template concrete class to provide binders to each system
// systems will return the resolved template pointing to their own data types
template < class Resource, class Container >
class ComponentBinder : public ComponentBinderInterface
{
public:
  // virtual dtor
  virtual ~ComponentBinder() {}
  // Constructor
  ComponentBinder(SystemsInterface* system, Resource* resource, Container* components);

  // bind this resource to entity
  virtual ErrorCode toEntity(EntityRegistrarInterface* er);

private:
  ComponentBinder() = delete;
  ComponentBinder(const ComponentBinder&) = delete;
  ComponentBinder& operator=(ComponentBinder&) = delete;

  // data
  SystemsInterface* system_;
  Resource* resource_;
  Container* components_;
};

template < class Resource, class Container >
ComponentBinder< Resource, Container >::ComponentBinder(SystemsInterface* system,
                                                        Resource* resource,
                                                        Container* components)
    : system_{system}
    , resource_{resource}
    , components_{components}
{
}

template < class Resource, class Container >
ErrorCode ComponentBinder< Resource, Container >::toEntity(EntityRegistrarInterface* er)
{
  if(system_ != nullptr && er != nullptr)
  {
    EntityID id = this->registerIntoSystem_(system_, er);

    auto it = this->components_->find(id);
    if(it != this->components_->end())
    {
      it->second.resource = resource_;
      return NO_ERROR;
    }
  }
  return UNKNOWN_ERROR;
}

using ComponentBinderPtr = SharedPtr< ComponentBinderInterface >;

} // end namespace System

} // end namespace Hydrogine

#endif // COMPONENT_BINDER_HPP
