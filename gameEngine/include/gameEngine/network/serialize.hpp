//
// Created by raphael on 12/23/23.
//

#pragma once
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace GameEngine::Serialize
{

  template<typename T, typename = void>
  struct hasSerializeMethod : std::false_type {};

  template<typename T>
  struct hasSerializeMethod<
    T,
    decltype(std::declval<T>().serialize(std::declval<void*>(), std::declval<unsigned int>()), void())>
    : std::true_type {};

  template<typename T>
  std::string serialize(T const& object)
  {
    if constexpr (hasSerializeMethod<T>::value) {
      return trySerialize(object);
    } else {
      throw std::runtime_error("Serialization not supported for this type.");
    }
  }

  template<typename T>
  void deserialize(std::string const& serializedData, T& deserializedObject)
  {
    if constexpr (hasSerializeMethod<T>::value) {
      tryDeserialize(serializedData, deserializedObject);
    } else {
      throw std::runtime_error("Deserialization not supported for this type.");
    }
  }

  template<typename T>
  std::string trySerialize(T const& object)
  {
    try {
      std::ostringstream outputStream;

      boost::archive::text_oarchive const archive(outputStream);
      archive << object;
      return outputStream.str();
    } catch (std::exception const& e) {
      throw std::runtime_error(
        "Serialization failed: " + std::string(e.what()));
    }
  }

  template<typename T>
  void tryDeserialize(std::string const& serializedData, T& deserializedObject)
  {
    try {
      std::istringstream inputStream(serializedData);
      boost::archive::text_iarchive const archive(inputStream);
      archive >> deserializedObject;
    } catch (std::exception const& e) {
      throw std::runtime_error(
        "Deserialization failed: " + std::string(e.what()));
    }
  }

} // namespace GameEngine::Serialize
