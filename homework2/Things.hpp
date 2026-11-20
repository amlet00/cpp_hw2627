#pragma once

#include "Inventory.hpp"

class Thing : public InventoryItem {
 public:
  Thing(const std::string& id, const std::string& name,
        std::shared_ptr<ModelSpec> model_spec);
};

class Helmet : public Thing {
 public:
  Helmet(const std::string& id, const std::string& name,
         std::shared_ptr<ModelSpec> model_spec);

  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;
};

class Dock : public Thing, public EnergyConsumer {
 public:
  Dock(const std::string& id, const std::string& name,
       std::shared_ptr<ModelSpec> model_spec, double energy);

  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;
  double dailyEnergy() const override;
};

class RollerSkatesGear : public Thing {
 public:
  RollerSkatesGear(const std::string& id, const std::string& name,
                   std::shared_ptr<ModelSpec> model_spec);

  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;
};
