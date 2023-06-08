#include "Classes/Interfaces/Object.hpp"

std::vector<IObject*> Objects::m_objects;

void Objects::DeleteAll()
{
    for (IObject* obj : m_objects)
        delete obj;
    m_objects.clear();
}

void Objects::AddObject(IObject* obj)
{
    m_objects.emplace_back(obj);
}

IObject* Objects::FindObject()
{
    return nullptr;
}

void Objects::Render()
{
    for (IObject* obj : m_objects)
        obj->Render();
}
