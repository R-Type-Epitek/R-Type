//
// Created by raphael on 1/12/24.
//

#pragma once
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/component/NetworkedEntity.hpp"
#include "gameEngine/asset/AssetManager.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Text.hpp"
#include "gameEngine/component/UiElement.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

namespace GameEngine::UI
{
  using json = nlohmann::json;

  class UIFactory {
   public:
    UIFactory(std::vector<GameEngine::ECS::Entity> &entities, GameEngine::ECS::Registry &registry)
      : m_entities(entities)
      , m_registry(registry) {};
    ~UIFactory() = default;

    void loadUIFromJSON(const std::string &jsonFilePath);
    void createUIEntity(const json &config);
    std::map<std::string, ECS::Entity> getUIElements();

    void parseDisplayable(const GameEngine::ECS::Entity &entity, const json &config);
    void parseText(const GameEngine::ECS::Entity &entity, const json &config);
    void parsePosition(const GameEngine::ECS::Entity &entity, const json &config);
    void parseClickable(const GameEngine::ECS::Entity &entity, const json &config);
    void parseUIElement(const GameEngine::ECS::Entity &entity, const json &config);

   private:
    using AssetManager = GameEngine::Asset::AssetManager;

    std::map<std::string, GameEngine::ECS::Entity> m_uiElements;
    std::vector<GameEngine::ECS::Entity> &m_entities; ///< Vector of entities in the Factory context.
    GameEngine::ECS::Registry &m_registry;            ///< Reference to the ECS registry.
  };

} // namespace UI
