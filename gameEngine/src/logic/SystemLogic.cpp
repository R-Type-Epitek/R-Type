//
// Created by Alexandre Decobert on 17/12/2023.
//

#include "logic/SystemLogic.hpp"
#include "ecs/Mediator.hpp"
#include <vector>
#include <iostream>
#include <memory>

SystemLogic::SystemLogic()
{
}

SystemLogic::~SystemLogic()
{
}

void SystemLogic::launchSystem(std::shared_ptr<Mediator>& mediator, std::vector<Entity> entities, Entity& player)
{
  //std::unordered_map<const char*, std::shared_ptr<System>> systems = mediator->getSystems();
}