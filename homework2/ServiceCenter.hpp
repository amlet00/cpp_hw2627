#pragma once

#include <unordered_map>

#include "Inventory.hpp"
#include "Registry.hpp"

class ServiceCenter {
 private:
  std::vector<std::shared_ptr<InventoryItem>> _items;
  std::unordered_map<std::string, std::shared_ptr<ModelSpec>> _model_specs;
  Registry<std::string, 1000> _registry_items;
  Registry<double, 1000> _registry_energy;
  std::weak_ptr<InventoryItem> _focus;

  bool isBroken(const std::string& name);
  void fixModelSpecs(const std::string& name);

 public:
  ServiceCenter();

  std::shared_ptr<ModelSpec> getModelSpec(const std::string& name);

  void addItem(std::unique_ptr<InventoryItem> item);
  void removeItem(const std::string& id);

  void energy();
  void maxEnergy();

  void novice();
  void countNovice();

  void list();
  void count();

  void focus(const std::string& id);
  void showFocus();

  void log();
  void logEnergy();
};
