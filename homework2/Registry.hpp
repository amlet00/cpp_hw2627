#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Errors.hpp"

template <typename T, size_t Cap>
class Registry {
 private:
  std::vector<T> _registry;

 public:
  size_t size() const { return _registry.size(); }

  void add(T item) {
    if (size() >= Cap) {
      throw RegistryFullError();
    }
    _registry.push_back(item);
  }

  const T& operator[](size_t index) const {
    if (size() <= index) {
      throw InvalidArgumentError("index out of range");
    }
    return _registry[index];
  }
};

template <typename T, size_t Cap>
std::ostream& operator<<(std::ostream& out, const Registry<T, Cap>& registry) {
  for (size_t i{}; i < registry.size(); i++) {
    out << registry[i] << '\n';
  }
  return out;
}

template <size_t Cap>
class Registry<std::string, Cap> {
 private:
  std::vector<std::string> _registry;

 public:
  size_t size() const { return _registry.size(); }

  void add(std::string item) {
    if (size() >= Cap) {
      throw RegistryFullError();
    }
    _registry.push_back(std::to_string(size()) + ") " + item);
  }

  const std::string& operator[](size_t index) const {
    if (size() <= index) {
      throw InvalidArgumentError("index out of range");
    }
    return _registry[index];
  }
};
