#include "Amoeba.h"
//TODO: task f)
Amoeba::Amoeba() 
  : Food(1000.0, 50.0, 50.0, 0.0, 0.0) // Your code here
    {
      dna_level_th = 100.0; 
      name = "Amoeba";
    };

Amoeba::Amoeba(double health_
              ,double power_
              ,double defence_
              ,double dna_level_th)
    : Food(health_, power_, defence_, 0.0, 0.0)
    // Your code here
    {
      this->dna_level_th = dna_level_th;
      name = "Amoeba";
    };

void Amoeba::print_header() 
{
  std::cout << std::setw(10) << "name" << " | ";
  std::cout << std::setw(10) << "health" << " | ";
  std::cout << std::setw(10) << "power" << " | ";
  std::cout << std::setw(10) << "defence" << " | ";
  std::cout << std::setw(10) << "dna_level" << " | ";
  std::cout << std::setw(10) << "dna_lvl_th" << std::endl;
}

void Amoeba::print()
{
  std::cout << std::setw(10) << name << " | ";
  std::cout << std::setw(10) << health << " | ";
  std::cout << std::setw(10) << power << " | ";
  std::cout << std::setw(10) << defence << " | ";
  std::cout << std::setw(10) << dna_level << " | ";
  std::cout << std::setw(10) << dna_level_th << std::endl;
}

Amoeba::~Amoeba(){};
//TODO: task k)
Food *Amoeba::clone() const {
  Amoeba *copy = new Amoeba(health, power, defence, dna_level_th);
  return copy;
}
//TODO: task h)
void Amoeba::eat(double health, double dna) {
  this->health += health; 
  dna_level += dna;
  if(dna_level > dna_level_th) dna_level_th *= 2;
}
