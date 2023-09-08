#include "histogram.h"

#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

Histogram::Histogram(const std::vector<std::string> &words) {
  // TODO 5.1.a) make sure the histogram is normalized when the constructor is done

  double norm = 1.0 / static_cast<double>(words.size()); 
  for(auto it = words.begin(); it != words.end(); it++)
  {
    if(!histogram.count(*it)) histogram[*it] = norm;
    else histogram[*it] += norm;
  }
}

size_t Histogram::size() const {
  // TODO 5.1.a)
  std::map<std::string, double>::const_iterator it;
  size_t count = 0;
  for(it = histogram.begin(); it != histogram.end(); it++)
    count += 1;
  return count;
}

bool Histogram::contains(const std::string &word) const {
  if(histogram.count(word)) return true;
  return false;
}

double Histogram::probability(const std::string &word) const {
  if(histogram.count(word)) return histogram.at(word);
  return 0.0;
}

std::vector<std::pair<double, std::string>> Histogram::most_common_words(unsigned n_words) const
{
  std::multimap<double, std::string> sortedHistogram;
  auto res = new std::vector<std::pair<double, std::string>>{};

  for(std::map<std::string, double>::const_iterator it = histogram.begin();
      it != histogram.end(); it++)
    sortedHistogram.emplace((*it).second, (*it).first);

  for(std::multimap<double, std::string>::reverse_iterator it = sortedHistogram.rbegin();
      it != sortedHistogram.rend() && n_words != 0; it++, n_words--)
    res->push_back(*it);

  return *res;
}




// TODO 5.1.b
// TODO 5.1.c
// TODO 5.1.d
