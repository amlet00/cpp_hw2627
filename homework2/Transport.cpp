#include "Transport.hpp"

#include "Errors.hpp"

Transport::Transport(const std::string& id, const std::string& name,
                     std::shared_ptr<ModelSpec> model_spec, int score)
    : InventoryItem{id, name, model_spec}, _score{score} {
  if (_score < 1 || _score > 10) {
    throw InvalidArgumentError{"score must be in 1...10"};
  }
};
bool Transport::isNovice() const { return _score >= 6; }

Scooter::Scooter(const std::string& id, const std::string& name,
                 std::shared_ptr<ModelSpec> model_spec, int score,
                 double energy)
    : Transport{id, name, model_spec, score}, EnergyConsumer{energy} {};
std::string Scooter::inventoryId() const { return _id; }
std::string Scooter::name() const { return _name; }
std::string Scooter::describe() const { return _id + " " + _name; }
double Scooter::dailyEnergy() const { return _energy; }

Bike::Bike(const std::string& id, const std::string& name,
           std::shared_ptr<ModelSpec> model_spec, int score)
    : Transport{id, name, model_spec, score} {};
std::string Bike::inventoryId() const { return _id; }
std::string Bike::name() const { return _name; }
std::string Bike::describe() const { return _id + " " + _name; }

Ebike::Ebike(const std::string& id, const std::string& name,
             std::shared_ptr<ModelSpec> model_spec, int score, double energy)
    : Transport{id, name, model_spec, score}, EnergyConsumer{energy} {};
std::string Ebike::inventoryId() const { return _id; }
std::string Ebike::name() const { return _name; }
std::string Ebike::describe() const { return _id + " " + _name; }
double Ebike::dailyEnergy() const { return _energy; }

RollerSkates::RollerSkates(const std::string& id, const std::string& name,
                           std::shared_ptr<ModelSpec> model_spec, int score)
    : Transport{id, name, model_spec, score} {};
std::string RollerSkates::inventoryId() const { return _id; }
std::string RollerSkates::name() const { return _name; }
std::string RollerSkates::describe() const { return _id + " " + _name; }
