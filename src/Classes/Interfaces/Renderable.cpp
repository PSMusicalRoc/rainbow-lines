#include "Classes/Interfaces/Renderable.hpp"

std::vector<IRenderable*> Renderable::m_renderables;

void Renderable::Render()
{
    for (IRenderable* r : m_renderables)
        r->Render();
}