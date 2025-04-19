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

                if (comp.component != nullptr)
                {
                    delete comp.component;
                }
            }


            // auto& runtimeApi = RuntimeApi::GetInstance();
            // for (auto& shaders : m_sceneConfig.shaders)
            // {
            //     std::vector<float> circle_vertices = runtimeApi.GenerateCircleVertices(1.0f, 100);
            //
            //     auto vertexPath = shaders.dir + shaders.vertexShader;
            //     auto fragPath = shaders.dir + shaders.fragShader;
            //
            //     std::cout << vertexPath << std::endl;
            //     std::cout << fragPath << std::endl;
            //
            //     auto circle_shader = runtimeApi.CreateShader(vertexPath,fragPath);
            //
            //     auto* circle_component = new ShaderComponent(circle_vertices, circle_shader);
            //     scene->AddComponent(shaders.id, circle_component);
            //
            //
            //     // auto* mainPlayer = new MoveablePlayerEntity();
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
