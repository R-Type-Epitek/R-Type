//
// Created by raphael on 12/20/23.
//

#pragma once

#include "IScene.hpp"
#include <map>
#include <memory>
#include <string>

namespace GameEngine::Scene
{
  /**
     * @brief A container class for managing scenes.
     *
     * The `SceneContainer` class allows adding, deleting, and retrieving scenes.
     * It also provides iterators for iterating over the stored scenes.
     */
  class SceneContainer {
   public:
    /**
         * @brief Constructor for SceneContainer.
         */
    SceneContainer();

    /**
         * @brief Adds a scene to the container.
         *
         * @param name The name of the scene.
         * @param scene A unique pointer to the scene.
         * @throw std::invalid_argument if a scene with the same name already exists.
         */
    void addScene(std::string name, std::unique_ptr<IScene> scene);

    /**
         * @brief Deletes a scene from the container.
         *
         * @param name The name of the scene to be deleted.
         * @throw std::invalid_argument if the scene with the specified name doesn't exist.
         */
    void deleteScene(const std::string& name);

    /**
         * @brief Gets a reference to a scene by name.
         *
         * @param name The name of the scene.
         * @return A reference to the specified scene.
         * @throw std::out_of_range if the scene with the specified name is not found.
         */
    IScene& getScene(const std::string& name);

    /**
         * @brief Finds a scene by name.
         *
         * @param name The name of the scene to find.
         * @return A reference to the found scene.
         * @throw std::out_of_range if the scene with the specified name is not found.
         */
    IScene& find(const std::string& name);

    /**
         * @brief Checks if a scene with a given name exists.
         *
         * @param name The name of the scene to check.
         * @return true if the scene exists, false otherwise.
         */
    bool exist(const std::string& name);

    /**
         * @brief Returns an iterator to the beginning of the scenes.
         *
         * @return An iterator to the beginning.
         */
    typename std::map<std::string, std::unique_ptr<IScene>>::iterator begin();

    /**
         * @brief Returns an iterator to the end of the scenes.
         *
         * @return An iterator to the end.
         */
    typename std::map<std::string, std::unique_ptr<IScene>>::iterator end();

   private:
    std::map<std::string, std::unique_ptr<IScene>> m_scenes;
  };

} // namespace GameEngine::Scene
