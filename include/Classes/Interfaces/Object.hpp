#ifndef _ROC_OBJECT_GL_HPP_
#define _ROC_OBJECT_GL_HPP_

#include <vector>
#include <functional>

struct IObject
{
public:
    IObject() {}
    virtual ~IObject() {};
    virtual void Render() = 0;
};

class Objects
{
private:
    static std::vector<IObject*> m_objects;

public:
    static void DeleteAll();
    static void AddObject(IObject* obj);
    static IObject* FindObject();

    static void Render();
};

template <typename InterfaceType, typename Implementation, class... Args>
struct IStaticCreation
{
    static Implementation* Create(Args... args)
    {
        Implementation* obj = Implementation::CreateInternal(args...);
        Objects::AddObject(obj);
        return obj;
    }
};

#endif