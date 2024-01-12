//
// Created by raphael on 1/10/24.
//

#pragma once
#include <map>
#include <functional>
#include <string>
#include <stdexcept>

namespace Rtype::Controller
{

  class BindingController {
   public:
    explicit BindingController() = default;

    virtual void initClassBinding() = 0;

    void addBinding(std::string name, std::function<void()> binding);

    std::function<void()> getBinding(std::string name);

   private:
    std::map<std::string, std::function<void()>> m_bindings = {};
  };

} // namespace Rtype::Controller
