#include "Bacterium.h"
//TODO: task c)
Bacterium::Bacterium(double health_, double power_, double defence_)
  : Food::Food(health_, power_, defence_, 10.0, 200.0)
{
  name = "Bacterium";
}

Bacterium::~Bacterium() {}
//TODO: task k)
Food *Bacterium::clone() const {
  Bacterium *copy = new Bacterium(health, power, defence);
  return copy;
}
