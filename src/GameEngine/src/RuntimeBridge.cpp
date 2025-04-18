/**
 * {SourceHeader}
 */

#include <../../Runtime/include/NeonRuntime/ExtRuntime.hpp>
#include <NeonEngine/RuntimeBridge.hpp>

namespace Neon
{
    RuntimeBridge::RuntimeBridge() : m_platform(nullptr)
    {
        m_platform = RuntimeApi::CreatePlatform();
    }

    RuntimeBridge::~RuntimeBridge()
    {
        delete m_platform;
    }

    bool RuntimeBridge::Initialize(const int width, const int height, const char* title) const
    {
        return m_platform->Initialize(width, height,title);
    }

    void RuntimeBridge::Run(Application* application) const
    {
        m_platform->Run(application);
    }

    IPlatform* RuntimeBridge::GetPlatform() const
    {
        return m_platform;
    }
}
