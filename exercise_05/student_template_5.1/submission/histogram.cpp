#include "histogram.h"

#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cmath>

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

// TODO 5.1.b
std::vector<std::pair<double, std::string>> Histogram::most_common_words(unsigned n_words) const
{
  std::multimap<double, std::string> sortedHistogram;
  std::vector<std::pair<double, std::string>> res{};

  for(std::map<std::string, double>::const_iterator it = histogram.begin();
      it != histogram.end(); it++)
    sortedHistogram.emplace((*it).second, (*it).first);

  for(std::multimap<double, std::string>::reverse_iterator it = sortedHistogram.rbegin();
      it != sortedHistogram.rend() && n_words != 0; it++, n_words--)
    res.push_back(*it);

  return res;
}

// TODO 5.1.c
double Histogram::dissimilarity(const Histogram &other) const
{
  double acc = 0.0; 
  size_t count = 0;
  for(auto it = histogram.begin(); it != histogram.end(); it++)
  {
    if(other.contains((*it).first)) 
    {
      count += 1;
      acc += std::abs(probability((*it).first) 
                       - other.probability((*it).first));
    }
  }

  double A = static_cast<double>(size());
  double B = static_cast<double>(other.size());
  double S = static_cast<double>(count);

  return (1.0 - (S / A)) + (1.0 - (S / B)) + acc;
}

// TODO 5.1.d
size_t Histogram::closest(const std::vector<Histogram> &candidates) const
{
  std::multimap<double, size_t> orderedCandidates;
  size_t idx = 0;
  for(auto it = candidates.begin(); it != candidates.end(); it++, idx++)
  {
    orderedCandidates.emplace(dissimilarity(*it), idx);
  }
  return orderedCandidates.begin()->second;
}

