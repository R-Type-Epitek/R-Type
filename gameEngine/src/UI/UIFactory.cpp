//
// Created by raphael on 1/12/24.
//

#include "gameEngine/UI/UIFactory.hpp"
#include "gameEngine/asset/AssetManager.hpp"
#include "gameEngine/component/Position.hpp"
#include "gameEngine/component/Displayable.hpp"
#include "gameEngine/component/Text.hpp"
#include "gameEngine/component/UiElement.hpp"
#include "gameEngine/component/Clickable.hpp"
#include "spdlog/spdlog.h"
#include <fstream>

namespace GameEngine::UI
{
  void UIFactory::loadUIFromJSON(const std::string& jsonFilePath)
  {
    std::ifstream file(jsonFilePath);
    if (!file.is_open()) {
      spdlog::error("Could not open file {}", jsonFilePath);
      throw std::runtime_error("Could not open file " + jsonFilePath);
    }

    try {
      json uiJson;
      file >> uiJson;

      if (uiJson.contains("ui") && uiJson["ui"].is_array()) {
        for (const auto& element : uiJson["ui"]) {
          createUIEntity(element);
        }
      }
    } catch (const std::exception& e) {
      spdlog::error("Error parsing JSON: {}", jsonFilePath);
      std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
  }

  void UIFactory::createUIEntity(const json& config)
  {
    auto entity = m_registry.createEntity();
    m_entities.push_back(entity);
    try {
      std::string id = config["name"];
      m_uiElements[id] = entity;

      parseUIElement(entity, config);
      parsePosition(entity, config);

      std::string elementType = config.value("type", "");
      if (elementType == "Text") {
        parseText(entity, config);
      } else if (elementType == "Button") {
        parseDisplayable(entity, config);
        parseClickable(entity, config);
      } else if (elementType == "Image") {
        parseDisplayable(entity, config);
      } else {
        spdlog::error("Unknown UI element type {}", elementType);
      }
    } catch (const std::exception& e) {
      spdlog::error("Error parsing JSON");
      std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
  }

  void UIFactory::parseDisplayable(const GameEngine::ECS::Entity& entity, const json& config)
  {
    std::string path = config.value("assetPath", AssetManager::defaultTextureId);
    auto displayableComponent = ComponentRType::Displayable(AssetManager::getInstance().getTexture(path));
    m_registry.addComponent(entity, displayableComponent);
  }

  void UIFactory::parseText(const GameEngine::ECS::Entity& entity, const json& config)
  {
    std::string text = config.value("text", "");
    int size = config.value("fontSize", 24);
    std::string path = config.value("fontPath", AssetManager::defaultFontId);
    auto textComponent = ComponentRType::Text(text, size, AssetManager::getInstance().getFont(path));
    m_registry.addComponent(entity, textComponent);
  }

  void UIFactory::parsePosition(const GameEngine::ECS::Entity& entity, const json& config)
  {
    auto positionComponent = ComponentRType::Position(config["position"]["x"], config["position"]["y"]);
    m_registry.addComponent(entity, positionComponent);
  }

  void UIFactory::parseClickable(const GameEngine::ECS::Entity& entity, const json& config)
  {
    (void)config;
    auto clickableComponent = ComponentRType::Clickable();
    m_registry.addComponent(entity, clickableComponent);
  }

  void UIFactory::parseUIElement(const GameEngine::ECS::Entity& entity, const json& config)
  {
    std::string id = config["name"];
    std::string callbackValue = config.value("callbackValue", "");

    auto uiElementComponent = ComponentRType::UIElement(id, callbackValue);
    m_registry.addComponent(entity, uiElementComponent);

    auto& elem = m_registry.getComponentManager()->getComponent<ComponentRType::UIElement>(entity);
    elem.callBackValue = callbackValue;
  }
}
