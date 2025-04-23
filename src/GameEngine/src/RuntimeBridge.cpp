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

#include <NeonRuntime/ExtRuntime.hpp>
#include <NeonEngine/RuntimeBridge.hpp>

namespace Neon
{
    RuntimeBridge::RuntimeBridge() : mx_platform(nullptr)
    {
        mx_platform = RuntimeApi::GetInstance().GetPlatform();
    }

    RuntimeBridge::~RuntimeBridge()
    {
        //
    }

    bool RuntimeBridge::Initialize(const int width, const int height, const char* title) const
    {
        return mx_platform->Initialize(width, height,title);
    }

    void RuntimeBridge::Run(Application* application) const
    {
        mx_platform->Run(application);
    }

    IPlatform* RuntimeBridge::GetPlatform() const
    {
        return mx_platform;
    }

    IShader* RuntimeBridge::CreateShader(const std::string& vertexPath, const std::string& fragmentPath) const
    {
        return mx_platform->CreateShader(vertexPath, fragmentPath);
    }
}
