#include "DeadCell.h"
//TODO: task c)
DeadCell::DeadCell(double health_, double power_, double defence_)
  : Food::Food(health_, power_, defence_, 10.0, 100.0)
{
  name = "DeadCell";
}

DeadCell::~DeadCell() {}
//TODO: task k)
Food *DeadCell::clone() const {
  DeadCell *copy = new DeadCell(health, power, defence);
  return copy;
}
