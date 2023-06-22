#include "Interfaces/ModularObject.hpp"

void IModularObject::DeleteAll()
{
    for (IObject* obj : m_objects)
        delete obj;
    m_objects.clear();
}

void IModularObject::Render()
{
    for (IObject* obj : m_objects)
        obj->Render();
}