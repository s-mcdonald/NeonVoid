/**
 * {SourceHeader}
 */

#pragma once

namespace Neon
{
    class Game;

    class Platform
    {
        public:
        Platform() = default;
        virtual ~Platform() = default;

        public:
        virtual bool Initialize(int width, int height, const char* title) = 0;
        virtual void Run(Game* game) = 0;
    };
}