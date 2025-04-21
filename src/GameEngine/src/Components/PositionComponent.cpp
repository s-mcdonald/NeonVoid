/**
 *    ███╗   ██╗███████╗ ██████╗ ███╗   ██╗
 *    ████╗  ██║██╔════╝██╔═══██╗████╗  ██║
 *    ██╔██╗ ██║█████╗  ██║   ██║██╔██╗ ██║
 *    ██║╚██╗██║██╔══╝  ██║   ██║██║╚██╗██║
 *    ██║ ╚████║███████╗╚██████╔╝██║ ╚████║
 *    ╚═╝  ╚═══╝╚══════╝ ╚═════╝ ╚═╝  ╚═══╝
 * ========================================
 *                 NeonVoid
 *         A 2D Game Engine in C++
 * ----------------------------------------
 * License: MIT
 * Copyright (c) : 2024 Sam McDonald
 * Repository: https://github.com/s-mcdonald/NeonVoid
 */
#include <iostream>

#include <NeonEngine/Components.hpp>

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

    void PositionComponent::OnUpdate()
    {
        std::cout << "[DEBUG][Movement] : " << m_position.x << "\n";
        std::cout << "[DEBUG][Movement] : " << m_position.y << "\n";
    }

    void PositionComponent::UpdateData(Point p)
    {
        m_position = p;
    }
}
