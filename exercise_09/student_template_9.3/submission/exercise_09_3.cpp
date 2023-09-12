#include "exercise_09_3.h"

#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using namespace std;

vector<double> get_vector_of_random_numbers() {
  // First create an instance of an engine.
  random_device rnd_device;
  // Specify the engine and distribution.
  mt19937 mersenne_engine{rnd_device()}; // Generates random integers
  uniform_int_distribution<int> dist{0, 1000000};

  auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };

  vector<double> vec(1e6);
  generate(begin(vec), end(vec), gen);
  return vec;
}

vector<double> sequential_sort(vector<double> &data) {
  // TODO STUDENT
  return data;
}

vector<double> parallel_sort(vector<double> &data) {
  // TODO STUDEN
  return data;
}

vector<double> sequential_transform(vector<double> &data,
                                    double (*function)(double)) {
  // TODO STUDENT
  return data;
}

vector<double> parallel_transform(vector<double> &data,
                                    double (*function)(double)) {
  // TODO STUDENT
    return data;
}
