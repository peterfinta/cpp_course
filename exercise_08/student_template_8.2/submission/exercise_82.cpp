#include "exercise_82.h"
#include "point.h"
#include <algorithm>
#include <vector>
#include <cstdint>

std::vector<Point> sort_x(const std::vector<Point> &points) {
  std::vector<Point> tmpVec = points;
  std::sort(tmpVec.begin(), tmpVec.end(),
            [](Point a, Point b){
              if(a.x == b.x) return a.y < b.y;
              else return a.x < b.x;});
  return tmpVec;
}

std::vector<Point> sort_y(const std::vector<Point> &points) {
  std::vector<Point> tmpVec = points;
  std::sort(tmpVec.begin(), tmpVec.end(),
            [](Point a, Point b){
              if(a.y == b.y) return a.x < b.x;
              else return a.y < b.y;});
  return tmpVec;
}

Point median(const std::vector<Point> &points) {
  size_t size = points.size();
  std::vector<Point> xSorted = sort_x(points);
  std::vector<Point> ySorted = sort_y(points);
  if(size % 2) return Point(xSorted.at(size/2).x,
                            ySorted.at(size/2).y);
  else return Point((xSorted.at(size/2).x + xSorted.at(size/2 - 1).x) / 2.0f,
                    (xSorted.at(size/2).y + xSorted.at(size/2 - 1).y) / 2.0f);
}
