/**
 * {SourceHeader}
 */

#include <NeonEngine/Scene.hpp>

namespace Neon
{
    Scene::~Scene()
    {
        Destroy();
    }

    bool Scene::IsInitialized() const
    {
        return m_isInitialized;
    }

    void Scene::Init()
    {
#if defined(NEON_DEBUG) && defined(NEON_DEBUG_VERBOSE)
        std::cout << "Scene::Init\n";
#endif

        if (m_isInitialized)
        {
            return;
        }

        // Scene components must be initialized before entity components
        InitRenderable(m_components);
        InitRenderable(m_entities);

        OnInit();

        m_isInitialized = true;
    }

    void Scene::Update()
    {
        // Scene components must be updated before entity components
        UpdateRenderable(m_components);
        UpdateRenderable(m_entities);

        OnUpdate();
    }

    void Scene::Render()
    {
        // Scene components must be rendered before entity components
        RenderRenderable(m_components);
        RenderRenderable(m_entities);

        OnRender();
    }

    void Scene::Destroy()
    {
        // Reverse the order for destruction
        DestroyRenderable(m_entities);
        DestroyRenderable(m_components);

        OnDestroy();
    }

    void Scene::HandleInput(Input* input)
    {
        HandlesInput(m_entities, input);
    }

    void Scene::AddComponent(const std::string& tag, Component* component)
    {
        // what do we do if it already exists?
        m_components[tag] = component;
    }

    Component* Scene::GetComponent(const std::string& tag)
    {
        if (auto it = m_components.find(tag); it != m_components.end())
        {
            auto& [key, component] = *it;

            return component;
        }

        return nullptr;
    }

    SceneType Scene::GetSceneType() const
    {
        return m_sceneType;
    }

    template <typename T>
    void Scene::InitRenderable(const T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnInit();
        }
    }

    template <typename T>
    void Scene::UpdateRenderable(const T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnUpdate();
        }
    }

    template <typename T>
    void Scene::RenderRenderable(const T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnRender();
        }
    }

    template <typename T>
    void Scene::DestroyRenderable(const T& t)
    {
        for (auto& [key, value] : t)
        {
            value->OnDestroy();

            delete value;
        }
    }

    template <typename T>
    void Scene::HandlesInput(const T& t, Input* input)
    {
        for (auto& [key, value] : t)
        {
            value->HandleInput(input);
        }
    }
}
