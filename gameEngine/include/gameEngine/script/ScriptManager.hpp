//
// Created by raphael on 1/14/24.
//

#pragma once
#include "gameEngine/ecs/entity/Entity.hpp"
#include "IScript.hpp"
#include <unordered_map>
#include <string>
#include <memory>

namespace GameEngine::Script
{

  /**
   * @brief Manager for handling scripts and their bindings.
   */
  class ScriptManager {
   public:
    /**
     * @brief Destructor.
     */
    virtual ~ScriptManager() = default;

    /**
     * @brief Register a script with a given name.
     *
     * @param scriptName The name of the script.
     * @param script The script to be registered.
     * @throw std::runtime_error If a script with the same name is already registered.
     */
    void registerScript(const std::string &scriptName, std::shared_ptr<GameEngine::Script::IScript> script);

    /**
     * @brief Add a script binding.
     *
     * @param scriptName The name of the script to bind.
     * @param baseScriptName The name of the base script to which the given script is bound.
     * @throw std::runtime_error If the script to bind does not exist or the base script is not found.
     */
    void addScriptBinding(const std::string &scriptName, const std::string &baseScriptName);

    /**
     * @brief Get the script associated with a given name.
     *
     * @param scriptName The name of the script to retrieve.
     * @return A shared pointer to the script.
     * @throw std::runtime_error If the script or its binding is not found.
     */
    std::shared_ptr<GameEngine::Script::IScript> getScript(const std::string &scriptName);

   private:
    std::unordered_map<std::string, std::shared_ptr<GameEngine::Script::IScript>> m_scriptsRegistered;
    std::unordered_map<std::string, std::string> m_scriptsBindings;
  };

} // namespace GameEngine::Script
