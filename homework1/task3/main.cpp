#include <iostream>

const size_t cRows{5};
const size_t cCols{10};

size_t GetLength(const char*);
bool CompareStrings(const char*, const char*);

void Clear(char[cRows][cCols]);
bool Put(char[cRows][cCols], int, int, char);
bool Text(char[cRows][cCols], int, int, const char*);
void Print(const char[cRows][cCols]);
bool ValidBorders(int, int);

void PrintError();

int main() {
  char tablo[cRows][cCols];
  Clear(tablo);

  char command_name[256];
  do {
    std::cin >> command_name;
    if (CompareStrings(command_name, "clear")) {
      Clear(tablo);
    } else if (CompareStrings(command_name, "put")) {
      int x, y;
      char c;
      std::cin >> x >> y >> c;

      if (!Put(tablo, x, y, c)) {
        PrintError();
      }
    } else if (CompareStrings(command_name, "text")) {
      int x, y;
      char string[256];
      std::cin >> x >> y >> string;

      if (!Text(tablo, x, y, string)) {
        PrintError();
      }
    } else if (CompareStrings(command_name, "print")) {
      Print(tablo);
    }
  } while (!CompareStrings(command_name, "quit"));
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

void Clear(char tablo[cRows][cCols]) {
  for (size_t i{}; i < cRows; i++) {
    for (size_t j{}; j < cCols; j++) {
      tablo[i][j] = ' ';
    }
  }
}

bool Put(char tablo[cRows][cCols], int x, int y, char c) {
  if (!ValidBorders(x, y)) {
    return false;
  }
  tablo[y][x] = c;
  return true;
}

bool Text(char tablo[cRows][cCols], int x, int y, const char* message) {
  size_t message_length = GetLength(message);
  int end_x = x + static_cast<int>(message_length) - 1;

  if (!ValidBorders(x, y) || !ValidBorders(end_x, y)) {
    return false;
  }
  for (size_t i{}; i < message_length; i++) {
    Put(tablo, x + static_cast<int>(i), y, message[i]);
  }
  return true;
}

void Print(const char tablo[cRows][cCols]) {
  for (size_t i{}; i < cRows; i++) {
    for (size_t j{}; j < cCols; j++) {
      std::cout << tablo[i][j];
    }
    std::cout << '\n';
  }
}

bool ValidBorders(int x, int y) {
  if (0 <= x && x < static_cast<int>(cCols) && 0 <= y &&
      y < static_cast<int>(cRows)) {
    return true;
  }
  return false;
}

void PrintError() {
  std::cout << "error\n";
}
