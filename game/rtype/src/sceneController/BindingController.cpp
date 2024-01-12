//
// Created by raphael on 1/12/24.
//

#include "sceneController/BindingController.hpp"
#include "spdlog/spdlog.h"

#include <utility>

namespace Rtype::Controller
{

  void BindingController::addBinding(std::string name, std::function<void()> binding)
  {
    m_bindings[name] = std::move(binding);
  }

  std::function<void()> BindingController::getBinding(std::string name)
  {
    auto it = m_bindings.find(name);
    if (it != m_bindings.end()) {
      return it->second;
    } else {
      spdlog::error("[Rtype::Controller::Binding]Binding with ID '{}' not found.", name);
      return [name]() { spdlog::error(" Invalid Binding with ID '{}' not found.", name); };
    }
  }

} // namespace Rtype::Controller