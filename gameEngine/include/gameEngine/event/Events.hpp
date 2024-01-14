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
    explicit EntityCollision(ECS::Entity entityA, ECS::Entity entityB, int maskA = -1, int maskB = -1)
      : entityA(entityA)
      , entityB(entityB)
      , maskA(maskA)
      , maskB(maskB) {};

    ECS::Entity entityA;
    ECS::Entity entityB;
    int maskA;
    int maskB;
  };

  struct KeyboardInput : public IEvent {
    KeyboardInput() = default;
    explicit KeyboardInput(Keybinds key, ECS::Entity entity = -1)
      : key(key)
      , entity {entity} {};

    Keybinds key = Keybinds::Unknown;
    ECS::Entity entity = -1;
  };

  struct MouseButtonPressed : public IEvent {
    MouseButtonPressed() = default;
    explicit MouseButtonPressed(int x, int y)
      : x {x}
      , y {y} {};

    int x;
    int y;
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

  struct PlayerShoot : public IEvent {
    PlayerShoot() = default;
    explicit PlayerShoot(std::string entityTypeName, ECS::Entity entityActor, float x, float y)
      : entityTypeName(entityTypeName)
      , entityActor(entityActor)
      , x(x)
      , y(y) {};

    std::string entityTypeName;
    ECS::Entity entityActor;
    float x;
    float y;
  };

  struct DisconnectedPlayer : public IEvent {
    DisconnectedPlayer() = default;
    explicit DisconnectedPlayer(size_t id)
      : id(id) {};

    size_t id;
  };

  struct DestroyEntity : public IEvent {
    explicit DestroyEntity(ECS::Entity entity)
      : entity(entity) {};

    ECS::Entity entity = -1;
  };

} // namespace GameEngine::Event
