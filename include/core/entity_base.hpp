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
  * entities manager contains all entities
  * entities are just containers for components
  *
  */

#ifndef CORE_ENTITY_BASE_HPP
#define CORE_ENTITY_BASE_HPP

#include "components/binder.hpp"
#include "core/types.hpp"

namespace Hydrogine
{

namespace Component
{

// forward declaration
struct TransformPod;

struct EntityPod
{
  // entity unique identifier
  EntityID entityId;

  // define to what class entity belongs
  TypeID typeId;

  // whether or not this entity is active
  bool isActive;

  // pointer to transform pod
  TransformPod* transform;
};

} // namespace Component

class EntityBase : public EntityRegistrarInterface
{
public:
  friend class EntitiesManager;
  // friend class SystemsInterface;

  // ctors and dtor
  explicit EntityBase(EntityID id);
  EntityBase() = delete;
  EntityBase(EntityBase& other) = delete;
  virtual ~EntityBase();

  ErrorCode suspend();
  ErrorCode resume();
  ErrorCode destroy(bool mustDestroy = true);
  bool willDestroy();
  bool isActive() const;
  // verify if entity has component
  bool containedInSystem(System::SystemsInterface& system);

protected:
  // add one more component to the entity
  virtual EntityID registerIntoSystem_(System::SystemsInterface& system) override;

  // can be used to register components into systems from constructor
  virtual void setUpComponents(){};

  // tear down (de register) components from systems
  void tearDownComponents();

  // set holds the systems to wich this entity was added
  Set< System::SystemsInterface* > componentSystems_;

  // this POD is to be used by the component systems
  Component::EntityPod entityData_;

  // data
  bool destroy_;
};

inline bool EntityBase::isActive() const { return this->entityData_.isActive; }

inline ErrorCode EntityBase::destroy(bool mustDestroy)
{
  this->destroy_ = mustDestroy;
  return (this->destroy_) ? NO_ERROR : UNKNOWN_ERROR;
}

inline bool EntityBase::willDestroy() { return this->destroy_; }

inline bool EntityBase::containedInSystem(System::SystemsInterface& system)
{
  return (0 < this->componentSystems_.count(&system));
}

} // end namespace Hydrogine

#endif // CORE_ENTITY_BASE_HPP
