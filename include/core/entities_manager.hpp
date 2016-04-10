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
  * entities are just containers to components
  *
  */

#ifndef CORE_ENTITIES_MANAGER_HPP
#define CORE_ENTITIES_MANAGER_HPP

#include <memory>

#include "core/entity_base.hpp"

namespace Hydrogine
{

class EntitiesManager
{
public:
  CLASS_METHOD EntitiesManager* instance();
  int count();

  // entity related methods
  template < class EntityType = EntityBase >
  EntityID createEntity(const char* name);
  EntityRegistrarInterface* registrar(EntityID entityId);
  // const String * lookUpEntityName(EntityID entityId);
  EntityID lookUpEntityId(const String& name);
  int refreshEntities();

protected:
  enum
  {
    MAXENTITIES_AMOUNT_ = 99999
  };

  // CTOR
  EntitiesManager()
      : count_{0}
      , entities_{}
      , lookUp_{}
  {
  }

  // private type defs
  using IEntityPtr = SharedPtr< EntityBase >;
  using Entities = HashMap< EntityID, IEntityPtr >;
  using EntitiesLookUp = HashMap< String, EntityID >;

  // data
  int count_;
  Entities entities_;
  EntitiesLookUp lookUp_;
};

template < class EntityType >
inline EntityID EntitiesManager::createEntity(const char* name)
{
  EntityID id = rndId();
  EntityType* entity = new EntityType(id);
  entity->setUpComponents();
  this->entities_[id].reset(entity);
  this->lookUp_[name] = id;
  this->refreshEntities();
  return id;
}

inline int EntitiesManager::count() { return this->count_; }

} // end namespace Hydrogine

#endif // CORE_ENTITIES_MANAGER_HPP
