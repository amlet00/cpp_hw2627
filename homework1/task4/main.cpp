/*
 * Задача: система управления "умной многоэтажной парковкой"
 *
 * 1) Зачем здесь int***:
 *  парковка имеет три измерения: этаж, ряд и парковочное место
 *  размеры задаются динамически, поэтому нужен 3D-массив
 *
 * 2) Зачем здесь void*:
 *  очередь событий принимает сигналы от разных систем
 *  тип 1: датчик передает указатель на место (int*)
 *  тип 2: система безопасности передает текст (char*)
 *  массив void* позволяет хранить указатели на разные типы в одном массиве
 */
#include <iostream>

int main() {
  size_t floors{2};
  size_t rows{3};
  size_t places{5};

  int*** parking{new int**[floors]};
  for (size_t f{}; f < floors; f++) {
    parking[f] = new int*[rows];
    for (size_t r{}; r < rows; r++) {
      parking[f][r] = new int[places];
      for (size_t s{}; s < places; s++) {
        parking[f][r][s] = 0;
      }
    }
  }

  parking[1][0][4] = 777;

  int event_types[]{2, 1, 2};
  void* event_queue[3];

  char error_msg[]{"Ошибка подключения камеры."};
  event_queue[0] = error_msg;

  event_queue[1] = &parking[0][2][1];

  char info_msg[]{"Новая машина заехала."};
  event_queue[2] = info_msg;

  size_t amount_of_events{3};
  for (size_t i{}; i < amount_of_events; i++) {
    if (event_types[i] == 1) {
      int* target_spot{static_cast<int*>(event_queue[i])};
      *target_spot = 999;
    } else if (event_types[i] == 2) {
      char* text{static_cast<char*>(event_queue[i])};
      std::cout << text << '\n';
    }
  }

  std::cout << parking[0][2][1] << '\n';
  std::cout << parking[1][0][4] << '\n';

  for (size_t f{}; f < floors; f++) {
    for (size_t r{}; r < rows; r++) {
      delete[] parking[f][r];
    }
    delete[] parking[f];
  }
  delete[] parking;
}
