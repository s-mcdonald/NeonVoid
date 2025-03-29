/**
 *
 */

#include "Runtime/Runtime.hpp"

#include "Entity/Entity.hpp"

namespace Neon 
{
   template <typename T>
   void ComponentManager::AddComponent(Entity& entity, T* component)
   {
      entity.AddComponent(component);
   }

   template <typename T>
   T* ComponentManager::GetComponent(const Entity& entity)
   {
      return entity.GetComponent<T>();
   }
}

