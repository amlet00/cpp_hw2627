#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Errors.hpp"
#include "Inventory.hpp"
#include "ServiceCenter.hpp"
#include "Things.hpp"
#include "Transport.hpp"

bool parseLine(const std::string& line, ServiceCenter& service_center) {
  std::stringstream line_in(line);

  std::string command;
  line_in >> command;
  if (command == "add") {
    std::string kind;
    line_in >> kind;
    if (kind == "scooter") {
      std::string id, name;
      double energy;
      int score;
      line_in >> id >> name >> energy >> score;

      std::shared_ptr<ModelSpec> model_spec = service_center.getModelSpec(name);
      service_center.addItem(
          std::make_unique<Scooter>(id, name, model_spec, score, energy));
    } else if (kind == "bike") {
      std::string id, name;
      int score;
      line_in >> id >> name >> score;

      std::shared_ptr<ModelSpec> model_spec = service_center.getModelSpec(name);
      service_center.addItem(
          std::make_unique<Bike>(id, name, model_spec, score));

    } else if (kind == "ebike") {
      std::string id, name;
      double energy;
      int score;
      line_in >> id >> name >> energy >> score;

      std::shared_ptr<ModelSpec> model_spec = service_center.getModelSpec(name);
      service_center.addItem(
          std::make_unique<Ebike>(id, name, model_spec, score, energy));
    } else if (kind == "roller_skates") {
      std::string id, name;
      int score;
      line_in >> id >> name >> score;

      std::shared_ptr<ModelSpec> model_spec = service_center.getModelSpec(name);
      service_center.addItem(
          std::make_unique<RollerSkates>(id, name, model_spec, score));
    } else if (kind == "helmet") {
      std::string id, name;
      line_in >> id >> name;

      std::shared_ptr<ModelSpec> model_spec = service_center.getModelSpec(name);
      service_center.addItem(std::make_unique<Helmet>(id, name, model_spec));
    } else if (kind == "dock") {
      std::string id, name;
      double energy;
      line_in >> id >> name >> energy;

      std::shared_ptr<ModelSpec> model_spec = service_center.getModelSpec(name);
      service_center.addItem(
          std::make_unique<Dock>(id, name, model_spec, energy));
    } else if (kind == "roller_skates_gear") {
      std::string id, name;
      line_in >> id >> name;

      std::shared_ptr<ModelSpec> model_spec = service_center.getModelSpec(name);
      service_center.addItem(
          std::make_unique<RollerSkatesGear>(id, name, model_spec));

    } else {
      throw InvalidArgumentError{"invalid kind: " + kind};
    }
  } else if (command == "remove") {
    std::string id;
    line_in >> id;
    service_center.removeItem(id);
  } else if (command == "energy") {
    service_center.energy();
  } else if (command == "max_energy") {
    service_center.maxEnergy();
  } else if (command == "novice") {
    service_center.novice();
  } else if (command == "count_novice") {
    service_center.countNovice();
  } else if (command == "list") {
    service_center.list();
  } else if (command == "count") {
    service_center.count();
  } else if (command == "focus") {
    std::string id;
    line_in >> id;
    service_center.focus(id);
  } else if (command == "show_focus") {
    service_center.showFocus();
  } else if (command == "log") {
    service_center.log();
  } else if (command == "log_energy") {
    service_center.logEnergy();
  } else if (command == "quit") {
    return 0;
  } else {
    throw InvalidCommandError{command};
  }
  return 1;
}

int main() {
  ServiceCenter service_center;

  bool running = true;
  while (running) {
    std::string line;
    std::getline(std::cin, line);

    try {
      running = parseLine(line, service_center);
    } catch (const FleetError& e) {
      std::cout << "error: " << e.what() << '\n';
    }
  }
}
