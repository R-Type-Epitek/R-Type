//
// Created by edouard on 12/21/23.
//

#pragma once
#include "gameEngine/ecs/Registry.hpp"
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/scene/IScene.hpp"
#include "network/Network.hpp"

#include <memory>
#include <vector>

namespace Client
{
    class WelcomeScene : public GameEngine::Scene::IScene {
    public:
        WelcomeScene(Network& network);

        void initRegistry() final;

        void initEntities() final;

        GameEngine::ECS::Registry& getECS() final;

        GameEngine::Entity::EntityFactory& getEntityFactory() final;

    protected:
        void initCustomSystem();

    private:
        std::vector<GameEngine::ECS::Entity> m_entities;
        std::unique_ptr<GameEngine::ECS::Registry> m_registry;
        std::unique_ptr<GameEngine::Entity::EntityFactory> m_entityFactory;
        Network& m_network;
    };
} // namespace Client
