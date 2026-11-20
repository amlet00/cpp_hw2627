#pragma once

#include <exception>
#include <string>

class FleetError : public std::exception {
 private:
  std::string _message;

 public:
  FleetError(const std::string& message) : _message{message} {}
  const char* what() const noexcept override { return _message.c_str(); }
};

class InspectionRejectedError : public FleetError {
 public:
  InspectionRejectedError() : FleetError{"inspection rejected"} {}
};

class InvalidCommandError : public FleetError {
 public:
  InvalidCommandError(const std::string& command)
      : FleetError{"invalid command: " + command} {}
};

class InvalidArgumentError : public FleetError {
 public:
  InvalidArgumentError(const std::string& message)
      : FleetError{"invalid argument: " + message} {}
};

class RegistryFullError : public FleetError {
 public:
  RegistryFullError() : FleetError{"registry is full"} {}
};
