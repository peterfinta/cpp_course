#include "shortest_paths.h"
#include <algorithm>
#include <utility>
#include <iostream>
#include <cmath>
#include <limits>

size_t ShortestPaths::getNodeIdByName(const std::string& name) const {
    // NOTE: if you like, you can make this more efficient by caching the mapping in a mutable hash map that gets reset when calling non-const functions
    const auto it = std::find_if(adjacency_matrix.begin(), adjacency_matrix.end(), [=](const Location& row) -> bool { return row.name == name; });
    if (it == adjacency_matrix.end())
        throw std::runtime_error("Location "+name+" not found");
    return static_cast<size_t>(std::distance(adjacency_matrix.begin(), it));
}

std::vector<size_t> ShortestPaths::compute_shortest_path(size_t from, size_t to) const
{
    /// your result path
    std::vector<size_t> result;
    float  inf   = std::numeric_limits<float>::max();
    size_t undef = std::numeric_limits<size_t>::max();
    /// increment this for every node that you pop from the queue
    size_t num_visited = 0;

    std::vector<float>  dist(size());
    std::vector<size_t> prev(size());
    std::vector<size_t> queue(size());

    for(size_t i = 0; i < size(); i++)
    {
      dist[i]  = inf;
      prev[i]  = undef;
      queue[i] = i;
    }
    dist[from] = 0.0f;

    while(num_visited != size())
    {
      size_t nextId = undef;
      float  nextDist = inf;
      for(size_t i = 0; i < size(); i++)
      {
        if(queue[i] != undef)
        {
          if(dist[i] < nextDist) 
          {
            nextId = i;
            nextDist = dist[i];
          }
        }
      }
      num_visited++;
      queue[nextId] = undef;
      if(nextId == to) break;

      nextDist = 0.0f;
      for(size_t i = 0; i < size(); i++)
      {
        std::optional<float> maybe = adjacency_matrix[nextId][i];
        if(maybe && queue[i] != undef)
        {
          nextDist = dist[nextId] + maybe.value();
          if(nextDist < dist[nextId]) 
          {
            dist[i] = nextDist;
            prev[i] = nextId;
          }
        }
      }
    }

    size_t nextId = to;
    if(prev[nextId] != undef || nextId == from)
    {
      while(prev[nextId] != undef)
      {
        result.push_back(nextId);
        nextId = prev[nextId];
      }
    }

    std::cout << "Nodes visited: " << num_visited << std::endl;

    return result;
}
