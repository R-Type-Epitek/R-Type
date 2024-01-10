//
// Created by lsg on 12/12/23.
//

#pragma once

namespace GameEngine::Gfx
{
  class IRenderer {
   public:
    virtual ~IRenderer() = default;

    virtual void clear() = 0;

    virtual void display() = 0;

    virtual bool isActive() = 0;

    virtual void setFramerateLimit(unsigned int limit) = 0;

    virtual IRenderer& getRenderer() = 0;
  };
} // namespace GameEngine::Gfx