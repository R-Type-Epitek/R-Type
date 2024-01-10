//
// Created by raphael on 1/8/24.
//

#pragma once
#include "gameEngine/ecs/entity/Entity.hpp"
#include "gameEngine/event/IEvent.hpp"
#include "gameEngine/constants/Keybinds.hpp"

namespace GameEngine::Event
{
  struct EntityCollision : public IEvent {
    explicit EntityCollision(ECS::Entity entityA, ECS::Entity entityB)
      : entityA(entityA)
      , entityB(entityB) {};

    ECS::Entity entityA;
    ECS::Entity entityB;
  };

  struct KeyboardInput : public IEvent {
    KeyboardInput() = default;
    explicit KeyboardInput(Keybinds key)
      : key(key) {};

    Keybinds key = Keybinds::Unknown;
  };

  struct MoveUp : public IEvent {
    MoveUp() = default;
    explicit MoveUp(ECS::Entity entity)
      : entity(entity) {};

    ECS::Entity entity = -1;
  };

  struct Movedown : public IEvent {
    Movedown() = default;
    explicit Movedown(ECS::Entity entity)
      : entity(entity) {};

    ECS::Entity entity = -1;
  };

  struct MoveLeft : public IEvent {
    MoveLeft() = default;
    explicit MoveLeft(ECS::Entity entity)
      : entity(entity) {};

    ECS::Entity entity = -1;
  };

  struct MoveRight : public IEvent {
    MoveRight() = default;
    explicit MoveRight(ECS::Entity entity)
      : entity(entity) {};

    ECS::Entity entity = -1;
  };

  struct PressSpace : public IEvent {
    PressSpace() = default;
    explicit PressSpace(ECS::Entity entity)
      : entity(entity) {};

    ECS::Entity entity = -1;
  };

  struct NewPlayer : public IEvent {
    explicit NewPlayer(size_t id)
      : id(id) {};

    size_t id;
  };

  struct NewProjectile : public IEvent {
    explicit NewProjectile(size_t id, float x, float y)
      : id(id)
      , x(x)
      , y(y) {};

    size_t id;
    int x;
    int y;
  };

  struct NewEnemy : public IEvent {
    NewEnemy() = default;
    explicit NewEnemy(size_t id, float x, float y)
      : id(id)
      , x(x)
      , y(y) {};

    size_t id;
    float x;
    float y;
  };

  struct DisconnectedPlayer : public IEvent {
    DisconnectedPlayer() = default;
    explicit DisconnectedPlayer(size_t id)
      : id(id) {};

    size_t id;
  };

} // namespace GameEngine::Event
