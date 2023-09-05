#include "Virus.h"
//TODO: task c)
Virus::Virus(double health_, double power_, double defence_)
  : Food::Food(health_, power_, defence_, 400.0, 400.0)
{
  name = "Virus";
}

Virus::~Virus() {}
//TODO: task k)
Food *Virus::clone() const {
  Virus *copy = new Virus(health, power, defence);
  return copy;
}
