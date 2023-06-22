#ifndef _ROC_MODULAR_OBJECT_GL_HPP_
#define _ROC_MODULAR_OBJECT_GL_HPP_

#include <vector>
#include "Interfaces/Object.hpp"

class IModularObject : public IObject
{
protected:
    std::vector<IObject*> m_objects;

public:
    void AddObject(IObject* obj) {m_objects.push_back(obj); }
    void DeleteAll();
    void Render() override;
};

#endif