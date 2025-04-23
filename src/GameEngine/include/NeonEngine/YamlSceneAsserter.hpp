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

#pragma once

#include <fkYAML/node.hpp>

namespace Neon
{
    class YamlSceneAsserter
    {
        public:
            static void AssertValidYaml(const fkyaml::node& node);

        protected:
            static void AssertSceneTypeYaml(const fkyaml::basic_node<>& value);
            static void AssertEntityTypeYaml(const fkyaml::basic_node<>& value);
            static void AssertGamePlayYaml(const fkyaml::basic_node<>& value);
            static void AssertFontsYaml(const fkyaml::basic_node<>& value);
            static void AssertComponentsSeqYaml(const fkyaml::basic_node<>& value);
            static void AssertSceneEntitiesYaml(const fkyaml::basic_node<>& value);

            static void AssertValidateComponentTypeAudio(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypePosition(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypeMovement(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypeShader(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypeText(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypeScript(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypeCollision(const fkyaml::basic_node<>& value);
            static void AssertValidateComponentTypeTimer(const fkyaml::basic_node<>& value);
    };
}
