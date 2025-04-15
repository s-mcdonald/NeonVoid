/**
 * {SourceHeader}
 */

#include <NeonEngine/Components/Components.hpp>

namespace Neon 
{
    PositionComponent::PositionComponent(const float x = 0.0f, const float y = 0.0f)
        : Component()
        , m_position(x,y)
    {
        // ...
    }

    void PositionComponent::OnDestroy()
    {
        // ...
    }

    Point PositionComponent::GetPoint() const
    {
        return m_position;
    }

    void PositionComponent::UpdateData(Point p)
    {
        m_position = p;
    }
}
