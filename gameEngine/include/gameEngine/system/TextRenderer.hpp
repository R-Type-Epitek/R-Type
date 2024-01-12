//
// Created by edouard on 12/22/23.
//

#pragma once

#include "gameEngine/gfx/IRenderer.hpp"
#include "gameEngine/gfx/sfml/Renderer.hpp"
#include "gameEngine/component/Text.hpp"
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/system/System.hpp"

namespace GameEngine::System
{

  class TextRenderer : public GameEngine::ECS::System {
   public:
    void update(GameEngine::ECS::Registry& registry, Gfx::IRenderer& renderer)
    {
      auto& componentManager = registry.getComponentManager();

      //        TODO: use only Rtype game engine gfx objects (not SFML)
      if (auto* sfmlRenderer = dynamic_cast<Gfx::Sfml::Renderer*>(&renderer)) {
        for (auto const& entity : m_entities) {
          auto& textC = componentManager->getComponent<ComponentRType::Text>(entity);
          textC.text.setFont(*textC.text.getFont());
          sfmlRenderer->draw(textC.text);
        }
      } else {
        throw std::runtime_error("System::TextRenderer::update: text renderer is not compatible");
      }
    }
  };

} // namespace GameEngine::System