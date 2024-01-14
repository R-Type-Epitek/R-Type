//
// Created by raphael on 1/14/24.
//

#include "gameEngine/script/ScriptManager.hpp"
#include "gameEngine/script/IScript.hpp"
#include "spdlog/spdlog.h"
#include <stdexcept>

namespace GameEngine::Script
{
  void ScriptManager::registerScript(const std::string &scriptName, std::shared_ptr<IScript> script)
  {
    if (m_scriptsRegistered.find(scriptName) != m_scriptsRegistered.end()) {
      spdlog::error("Script with name '{}' is already registered.", scriptName);
      throw std::runtime_error("Script with name '" + scriptName + "' is already registered.");
    }

    m_scriptsRegistered[scriptName] = std::move(script);
  }

  void ScriptManager::addScriptBinding(const std::string &scriptName, const std::string &baseScriptName)
  {
    if (m_scriptsRegistered.find(scriptName) == m_scriptsRegistered.end()) {
      spdlog::error("Script with name '{}' does not exist.", scriptName);
      throw std::runtime_error("Script with name '" + scriptName + "' does not exist.");
    }

    m_scriptsBindings[scriptName] = baseScriptName;
  }

  std::shared_ptr<IScript> ScriptManager::getScript(const std::string &scriptName)
  {
    auto it = m_scriptsBindings.find(scriptName);
    if (it == m_scriptsBindings.end()) {
      spdlog::error("Script Binding not found for script '{}'.", scriptName);
      throw std::runtime_error("Script binding not found for script '" + scriptName + "'.");
    }

    auto scriptIt = m_scriptsRegistered.find(it->second);
    if (scriptIt == m_scriptsRegistered.end()) {
      spdlog::error("Base script with name '{}' not found.", it->second);
      throw std::runtime_error("Base script with name '" + it->second + "' not found.");
    }

    return scriptIt->second;
  }
} // namespace GameEngine::Script
