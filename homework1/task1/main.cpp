#include <iostream>

struct MinMax {
  int min;
  int max;
};

double CalculateMean(const int*, size_t);
MinMax FindMinMax(const int*, size_t);
unsigned CountNegative(const int*, size_t);

int main() {
  size_t N;
  std::cin >> N;

  int* temperature_data{new int[N]};
  for (size_t i{}; i < N; i++) {
    std::cin >> temperature_data[i];
  }

  double mean{CalculateMean(temperature_data, N)};
  MinMax min_max{FindMinMax(temperature_data, N)};
  unsigned days_below_zero{CountNegative(temperature_data, N)};

  std::cout << std::fixed;
  std::cout.precision(1);

  std::cout << mean << '\n';
  std::cout << min_max.min << ' ' << min_max.max << '\n';
  std::cout << days_below_zero << '\n';

  delete[] temperature_data;
}

double CalculateMean(const int* array, size_t n) {
  long long sum{};
  for (size_t i{}; i < n; i++) {
    sum += array[i];
  }
  return static_cast<double>(sum) / n;
}

MinMax FindMinMax(const int* array, size_t n) {
  MinMax min_max{array[0], array[0]};
  for (size_t i{1}; i < n; i++) {
    if (array[i] < min_max.min) {
      min_max.min = array[i];
    }
    if (min_max.max < array[i]) {
      min_max.max = array[i];
    }
  }
  return min_max;
}

unsigned CountNegative(const int* array, size_t n) {
  unsigned result{};
  for (size_t i{}; i < n; i++) {
    if (array[i] < 0) {
      result++;
    }
  }
  return result;
}
