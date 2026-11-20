#include "Things.hpp"

Thing::Thing(const std::string& id, const std::string& name,
             std::shared_ptr<ModelSpec> model_spec)
    : InventoryItem{id, name, model_spec} {};

Helmet::Helmet(const std::string& id, const std::string& name,
               std::shared_ptr<ModelSpec> model_spec)
    : Thing{id, name, model_spec} {};
std::string Helmet::inventoryId() const { return _id; }
std::string Helmet::name() const { return _name; }
std::string Helmet::describe() const { return _id + " " + _name; }

Dock::Dock(const std::string& id, const std::string& name,
           std::shared_ptr<ModelSpec> model_spec, double energy)
    : Thing{id, name, model_spec}, EnergyConsumer{energy} {};
std::string Dock::inventoryId() const { return _id; }
std::string Dock::name() const { return _name; }
std::string Dock::describe() const { return _id + " " + _name; }
double Dock::dailyEnergy() const { return _energy; }

RollerSkatesGear::RollerSkatesGear(const std::string& id,
                                   const std::string& name,
                                   std::shared_ptr<ModelSpec> model_spec)
    : Thing{id, name, model_spec} {};
std::string RollerSkatesGear::inventoryId() const { return _id; }
std::string RollerSkatesGear::name() const { return _name; }
std::string RollerSkatesGear::describe() const { return _id + " " + _name; }
