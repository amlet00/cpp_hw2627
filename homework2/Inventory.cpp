#include "Inventory.hpp"

#include "Errors.hpp"

ModelSpec::ModelSpec(const std::string& name, const std::string& info)
    : _name{name}, _info{info} {};

InventoryItem::InventoryItem(const std::string& id, const std::string& name,
                             std::shared_ptr<ModelSpec> model_spec)
    : _id{id}, _name{name}, _model_spec{model_spec} {};

bool InventoryItem::operator<(const InventoryItem& o) const {
  return _id < o._id;
}

bool InventoryItem::operator==(const InventoryItem& o) const {
  return _id == o._id;
}

EnergyConsumer::EnergyConsumer(double energy) : _energy{energy} {
  if (_energy < 0) {
    throw InvalidArgumentError{"energy must be non-negative"};
  }
};

std::ostream& operator<<(std::ostream& out,
                         const InventoryItem& inventory_item) {
  return out << inventory_item.describe();
}
