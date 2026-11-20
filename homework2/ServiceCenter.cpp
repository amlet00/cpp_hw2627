#include "ServiceCenter.hpp"

#include <algorithm>
#include <memory>

#include "Errors.hpp"
#include "Inventory.hpp"
#include "Transport.hpp"

bool ServiceCenter::isBroken(const std::string& name) {
  std::string lower{};
  for (size_t i{}; i < name.length(); i++) {
    lower.push_back(std::tolower(name[i]));
  }

  return lower.find("broken") < name.size();
}

void ServiceCenter::fixModelSpecs(const std::string& name) {
  if (_model_specs.find(name) != _model_specs.end() &&
      _model_specs[name].use_count() == 1) {
    _model_specs.erase(name);
  }
}

ServiceCenter::ServiceCenter() {};

std::shared_ptr<ModelSpec> ServiceCenter::getModelSpec(
    const std::string& name) {
  if (_model_specs.find(name) == _model_specs.end()) {
    _model_specs[name] = std::make_shared<ModelSpec>(name, "very good " + name);
  }
  return _model_specs[name];
}

void ServiceCenter::addItem(std::unique_ptr<InventoryItem> item) {
  for (size_t i{}; i < _items.size(); i++) {
    if (*_items[i] == *item) {
      throw InvalidArgumentError{"item is alredy exist"};
    }
  }

  Transport* transport{dynamic_cast<Transport*>(item.get())};
  if (transport != nullptr && isBroken(transport->name())) {
    fixModelSpecs(transport->name());
    throw InspectionRejectedError{};
  }

  _registry_items.add("added: " + item->describe());
  _items.push_back(std::move(item));
}

void ServiceCenter::removeItem(const std::string& id) {
  for (size_t i{}; i < _items.size(); i++) {
    if (_items[i]->inventoryId() == id) {
      std::string name = _items[i]->name();
      _registry_items.add("removed: " + _items[i]->describe());
      std::swap(_items[i], _items.back());
      _items.pop_back();
      fixModelSpecs(name);
      return;
    }
  }
  throw InvalidArgumentError{"item doesn't exist"};
}

void ServiceCenter::energy() {
  double sum{};
  for (size_t i{}; i < _items.size(); i++) {
    EnergyConsumer* energy_consumer{
        dynamic_cast<EnergyConsumer*>(_items[i].get())};
    if (energy_consumer != nullptr) {
      sum += energy_consumer->dailyEnergy();
    }
  }
  _registry_energy.add(sum);

  std::cout << std::fixed;
  std::cout.precision(1);
  std::cout << sum << '\n';
}

void ServiceCenter::maxEnergy() {
  double max{};
  for (size_t i{}; i < _items.size(); i++) {
    EnergyConsumer* energy_consumer{
        dynamic_cast<EnergyConsumer*>(_items[i].get())};
    if (energy_consumer != nullptr) {
      max = std::max(max, energy_consumer->dailyEnergy());
    }
  }
  std::cout << std::fixed;
  std::cout.precision(1);
  std::cout << max << '\n';
}

void ServiceCenter::novice() {
  for (size_t i{}; i < _items.size(); i++) {
    Transport* transport{dynamic_cast<Transport*>(_items[i].get())};
    if (transport != nullptr && transport->isNovice()) {
      std::cout << *transport << '\n';
    }
  }
}

void ServiceCenter::countNovice() {
  int count{};
  for (size_t i{}; i < _items.size(); i++) {
    Transport* transport{dynamic_cast<Transport*>(_items[i].get())};
    if (transport != nullptr && transport->isNovice()) {
      count++;
    }
  }
  std::cout << count << '\n';
}

void ServiceCenter::list() {
  std::sort(_items.begin(), _items.end(),
            [](std::shared_ptr<InventoryItem> l,
               std::shared_ptr<InventoryItem> r) { return *l < *r; });
  for (size_t i{}; i < _items.size(); i++) {
    std::cout << *_items[i] << '\n';
  }
}

void ServiceCenter::count() { std::cout << _items.size() << '\n'; }

void ServiceCenter::focus(const std::string& id) {
  for (size_t i{}; i < _items.size(); i++) {
    if (_items[i]->inventoryId() == id) {
      _focus = _items[i];
      return;
    }
  }
  throw InvalidArgumentError{"item doesn't exist"};
}

void ServiceCenter::showFocus() {
  if (_focus.expired()) {
    std::cout << "removed\n";
    return;
  }
  std::cout << *_focus.lock() << '\n';
}

void ServiceCenter::log() { std::cout << _registry_items; }

void ServiceCenter::logEnergy() { std::cout << _registry_energy; }
