/**
 * {SourceHeader}
 */

#include <deque>

#include <NeonEngine/Application.hpp>
#include <fkYAML/node.hpp>

namespace Neon 
{
    Application::~Application()
    {
        for (const auto s : m_scenes)
        {
            delete s;
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

            for (auto& comp : m_sceneConfig.components)
            {
                if (comp.type == "audio")
                {
                    auto* introMusic = new AudioComponent(comp.audioConfig->path);
                    scene->AddComponent(comp.name, introMusic);

                    if (comp.audioConfig->loop)
                    {
                        introMusic->TriggerPlayRepeat();
                    }
                    else
                    {
                        introMusic->TriggerPlayOnce();
                    }

                    // cleanup
                    delete comp.audioConfig;
                }

                if (comp.type == "position")
                {
                    // @todo, make PosComp accept point so we can pass initial
                    auto* positionComp = new PositionComponent();
                    scene->AddComponent(comp.name, positionComp);

                    // cleanup
                    delete comp.posConfig;
                }

                if (comp.type == "movement")
                {
                    // @todo, add data: key bindings
                    auto* movementComp = new MovementComponent();
                    scene->AddComponent(comp.name, movementComp);
                }

                if (comp.type == "shader")
                {
                    std::vector<float> circle_vertices = RuntimeApi::GetInstance().GenerateCircleVertices(1.0f, 100);

                    auto vertexPath = comp.shaderConfig->dir + comp.shaderConfig->vertexShader;
                    auto fragPath = comp.shaderConfig->dir + comp.shaderConfig->fragShader;

                    auto shaderPgm = RuntimeApi::GetInstance().CreateShader(vertexPath,fragPath);

                    // @todo, make PosComp accept point so we can pass initial
                    auto* shaderComp = new ShaderComponent(circle_vertices, shaderPgm);

                    scene->AddComponent(comp.name, shaderComp);

                    // cleanup
                    delete comp.shaderConfig;
                }
            }

            // auto& runtimeApi = RuntimeApi::GetInstance();
            // for (auto& shaders : m_sceneConfig.shaders)
            // {
            //
            //
            //     // auto* mainPlayer = new Entity();
            //     // m_entities[mainPlayer->GetId()] = mainPlayer;
            //     // scene->AddEntity();
            // }

            AddScene(scene);

            return true;
        }

        return false;
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
