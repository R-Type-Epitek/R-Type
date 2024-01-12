//
// Created by raphael on 1/12/24.
//

#pragma once
namespace ComponentRType
{

  /// \brief A component representing if a entity is an ui element.
  struct UIElement {
    UIElement() = default;
    explicit UIElement(std::string id, std::string callBackValue = "")
      : id(id)
      , callBackValue(callBackValue)
    {
    }

    std::string id;
    std::string callBackValue;
  };

} // namespace ComponentRType
