/**
 * {SourceHeader}
 */

#include <deque>

#include <fkYAML/node.hpp>

#include <NeonEngine/Types.hpp>
#include <NeonEngine/Application.hpp>

namespace Neon 
{
    Application::~Application()
    {
        for (const auto s : m_scenes)
        {
            delete s;
        }

        auto cleanupComponent = [](YComponent& comp)
        {
            switch(comp.configType)
            {
                case ConfigType::Shader:
                    delete comp.shaderConfig;
                    break;
                case ConfigType::Audio:
                    delete comp.audioConfig;
                    break;
                case ConfigType::Position:
                    delete comp.posConfig;
                    break;
                case ConfigType::None:
                case ConfigType::Movement:
                    break;
            }
        };

        for (auto& comp : m_sceneConfig.components)
        {
            cleanupComponent(comp);
        }

        for (auto& entity : m_sceneConfig.entities)
        {
            for (auto& comp : entity.components)
            {
                cleanupComponent(comp);
            }
        }

        if (m_currentScene)
        {
            m_currentScene = nullptr;
        }
    }

    bool Application::Initialize(const WindowDimension width, const WindowDimension height, const char* title)
    {
        if (m_runtime.Initialize(width, height, title))
        {
            m_yamlReader.Read(m_sceneYamlPath);

            // @todo: we need to validate this data
            m_sceneConfig = m_yamlReader.Init();

            auto* scene = new Scene(m_sceneConfig.sceneType);

            std::unordered_map<std::string, Component*> componentsForScene  = CollectComponents(m_sceneConfig.components);

            for (auto [name, comp] : componentsForScene)
            {
                scene->AddComponent(name, comp);
            }

            for (auto& entity : m_sceneConfig.entities)
            {
                auto* entityToAdd = new Entity(1);

                std::unordered_map<std::string, Component*> componentsForEntity = CollectComponents(entity.components);

                for (auto [name, comp] : componentsForEntity)
                {
                    entityToAdd->AddComponent(comp);
                }

                scene->AddEntity(entityToAdd->GetId(), entityToAdd);
            }

            // we need to be able to load multiple scenes.
            // either multiple yaml scene files or a game yaml with all scenes.
            AddScene(scene);

            return true;
        }

        return false;
    }

    std::unordered_map<std::string, Component*> Application::CollectComponents(std::vector<YComponent> components)
    {
        std::unordered_map<std::string, Component*> componentsForScene;

        for (auto& comp : components)
        {
            if (comp.type == "audio")
            {
                auto* theComponent = new AudioComponent(comp.audioConfig->path);
                Volume v(comp.audioConfig->volume);
                theComponent->SetVolume(v);
                if (comp.audioConfig->loop)
                {
                    theComponent->TriggerPlayRepeat();
                }
                else
                {
                    theComponent->TriggerPlayOnce();
                }

                componentsForScene.emplace(comp.name, theComponent);
            }

            if (comp.type == "position")
            {
                // @todo, make PosComp accept point so we can pass initial
                auto* theComponent = new PositionComponent();
                componentsForScene.emplace(comp.name, theComponent);
            }

            if (comp.type == "movement")
            {
                // @todo, add data: key bindings
                auto* theComponent = new MovementComponent();
                componentsForScene.emplace(comp.name, theComponent);
            }

            if (comp.type == "shader")
            {
                std::vector<float> circle_vertices = RuntimeApi::GetInstance().GenerateCircleVertices(1.0f, 100);

                auto vertexPath = comp.shaderConfig->dir + comp.shaderConfig->vertexShader;
                auto fragPath = comp.shaderConfig->dir + comp.shaderConfig->fragShader;

                auto shaderPgm = RuntimeApi::GetInstance().CreateShader(vertexPath,fragPath);

                // @todo, make PosComp accept point so we can pass initial
                auto* theComponent = new ShaderComponent(circle_vertices, shaderPgm);

                componentsForScene.emplace(comp.name, theComponent);
            }
        }

        return componentsForScene;
    }

    void Application::Run()
    {
        m_runtime.Run(this);
    }

    void Application::SetSceneYaml(const std::string& sceneName)
    {
        m_sceneYamlPath = sceneName;
    }

    std::string Application::GetSceneYaml() const
    {
        return m_sceneYamlPath;
    }

    void Application::AddScene(Scene* scene)
    {
        m_scenes.push_back(scene);
    }

    Scene* Application::GetCurrentScene()
    {
        if (m_currentScene == nullptr)
        {
            SwitchScene();
        }

        return m_currentScene;
    }

    void Application::SwitchScene()
    {
        if (m_currentScene == nullptr && !m_scenes.empty())
        {
            m_currentScene = m_scenes.front();
            m_scenes.pop_front();
            return;
        }

        if (m_currentScene != nullptr && !m_scenes.empty())
        {
            m_currentScene->Destroy();

            m_currentScene = m_scenes.front();
            m_scenes.pop_front();
            return;
        }

        // we must have reached the end of the Application..
        // if (m_scenes.empty())....
    }
}
