#include <iostream>
#include <iterator>

using MoneyFunction = void (*)(unsigned long long&);

struct Command {
  const char* name;
  const MoneyFunction money_function;
};

size_t GetLength(const char*);
bool CompareStrings(const char*, const char*);

void Deposit(unsigned long long&);
void Withdraw(unsigned long long&);
void Balance(unsigned long long&);
void Reset(unsigned long long&);
void Invest(unsigned long long&);

void PrintError();

int main() {
  const Command commands_list[]{{"deposit", Deposit},
                                {"withdraw", Withdraw},
                                {"balance", Balance},
                                {"reset", Reset},
                                {"invest", Invest}};
  const size_t amount_of_commands{std::size(commands_list)};

  unsigned long long money{};

  char command_name[256];
  bool running{true};
  while (running) {
    std::cin >> command_name;

    bool is_command_found{};

    if (CompareStrings(command_name, "stop")) {
      is_command_found = true;
      running = false;
    }

    for (int i{}; i < amount_of_commands; i++) {
      if (CompareStrings(command_name, commands_list[i].name)) {
        commands_list[i].money_function(money);
        is_command_found = true;
        break;
      }
    }

    if (!is_command_found) {
      PrintError();
    }
  };
}

size_t GetLength(const char* string) {
  size_t length{};
  const char* c{string};
  while (*c != '\0') {
    length++;
    c++;
  }
  return length;
}

bool CompareStrings(const char* string1, const char* string2) {
  size_t length1{GetLength(string1)};
  size_t length2{GetLength(string2)};

  if (length1 != length2) {
    return false;
  }

  for (size_t i{}; i < length1; i++) {
    if (string1[i] != string2[i]) {
      return false;
    }
  }
  return true;
}

void Deposit(unsigned long long& money) {
  int k;
  std::cin >> k;
  if (k <= 0) {
    PrintError();
    return;
  }
  money += k;
}

void Withdraw(unsigned long long& money) {
  int k;
  std::cin >> k;
  if (k <= 0 || money < k) {
    PrintError();
    return;
  }
  money -= k;
}

void Balance(unsigned long long& money) {
  std::cout << money << '\n';
}

void Reset(unsigned long long& money) {
  money = 0;
}

void Invest(unsigned long long& money) {
  int k;
  std::cin >> k;
  if (k <= 0 || 100 < k) {
    PrintError();
    return;
  }
  money += (money * k / 100);
}

void PrintError() {
  std::cout << "error\n";
}
