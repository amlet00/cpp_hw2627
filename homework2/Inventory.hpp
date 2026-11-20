#pragma once

#include <iostream>
#include <memory>
#include <string>

class ModelSpec {
 private:
  std::string _name;
  std::string _info;

 public:
  ModelSpec(const std::string& name, const std::string& info);
};

class InventoryItem {
 protected:
  std::string _id;
  std::string _name;

  std::shared_ptr<ModelSpec> _model_spec;

 public:
  InventoryItem(const std::string& id, const std::string& name,
                std::shared_ptr<ModelSpec> model_spec);
  virtual ~InventoryItem() = default;

  virtual std::string inventoryId() const = 0;
  virtual std::string name() const = 0;
  virtual std::string describe() const = 0;

  bool operator<(const InventoryItem& o) const;
  bool operator==(const InventoryItem& o) const;
};

class EnergyConsumer {
 protected:
  double _energy;

 public:
  EnergyConsumer(double energy);
  virtual ~EnergyConsumer() = default;

  virtual double dailyEnergy() const = 0;
};

std::ostream& operator<<(std::ostream& out,
                         const InventoryItem& inventory_item);
