#ifndef _ROC_RENDERABLE_INTERFACE_H_
#define _ROC_RENDERABLE_INTERFACE_H_

#include <vector>

struct IRenderable
{
    virtual void Render() = 0;
};

namespace Renderable {
    extern std::vector<IRenderable*> m_renderables;

    void Render();
};

#endif