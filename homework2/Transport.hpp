#pragma once

#include "Inventory.hpp"

class Transport : public InventoryItem {
 private:
  int _score;

 public:
  Transport(const std::string& id, const std::string& name,
            std::shared_ptr<ModelSpec> model_spec, int score);

  bool isNovice() const;
};

class Scooter : public Transport, public EnergyConsumer {
 public:
  Scooter(const std::string& id, const std::string& name,
          std::shared_ptr<ModelSpec> model_spec, int score, double energy);

  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;
  double dailyEnergy() const override;
};

class Bike : public Transport {
 public:
  Bike(const std::string& id, const std::string& name,
       std::shared_ptr<ModelSpec> model_spec, int score);

  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;
};

class Ebike : public Transport, public EnergyConsumer {
 public:
  Ebike(const std::string& id, const std::string& name,
        std::shared_ptr<ModelSpec> model_spec, int score, double energy);

  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;
  double dailyEnergy() const override;
};

class RollerSkates : public Transport {
 public:
  RollerSkates(const std::string& id, const std::string& name,
               std::shared_ptr<ModelSpec> model_spec, int score);

  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;
};
