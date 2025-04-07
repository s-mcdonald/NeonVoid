#pragma once

namespace Neon
{
    class AudioComponent final
        : public Component
        , public AudioSystem
    {
        public:
            explicit AudioComponent(std::string);
            ~AudioComponent() override;

            void OnInit() override;
            void OnUpdate() override;
            void TriggerPlayOnce();
            void TriggerPlayRepeat();
            void SetVolume(const Volume&) override;
            void OnDestroy() override;

        private:
            std::string m_filename;
            bool m_repeats;
    };
}
