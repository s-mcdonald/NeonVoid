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

        public:
        void OnInit() override;
        void OnUpdate() override;

        public:
        void TriggerPlayOnce();
        void TriggerPlayRepeat();

        public:
        void SetVolume(const Volume&) override;
        void OnDestroy() override;

        private:
        std::string m_filename;
        bool m_repeats;
    };
}
