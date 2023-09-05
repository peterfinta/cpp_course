#pragma once

// own classes
#include "Amoeba.h"
#include "DeadCell.h"
#include "Bacterium.h"
#include "Virus.h"

// STL classes
#include <vector>

double random_value(double difficulty = 1.0) {
  return (double((std::rand() % 800) + 100) / 1000.0) * difficulty; // [0.1 .. 0.899] * difficulty
}

bool combat(Amoeba *player, Food *enemy) {
  std::cout << "\n+++++++++++++++++++++++++ new round ++++++++++++++++++++++++\n"
            << std::endl; 

  unsigned int turn = 0;
  
  bool player_won{false};

  if (player && enemy) {
    // print enemy and player information
    enemy->print_header();
    enemy->print();
    player->print_header();
    player->print();

    // fight until either player or enemy lost
    while (player->is_alive() && enemy->is_alive()) {
      turn++;
      
      // player attacks first
      enemy->attacked([player]
                      (double &health, double defence)
                      {
                        double damage = random_value() * player->get_power() 
                         - random_value() * defence;
                        if(damage > 0) health -= damage;
                      }
                      ); // Your Code here

      // enemy attacks second
      player->attacked([enemy]
                      (double &health, double defence)
                      {
                        double damage = random_value() * enemy->get_power() 
                         - random_value() * defence;
                        if(damage > 0) health -= damage;i
                      }
                      ); // Your Code here

      // print enemy and player information for this turn
      std::cout << "---------- turn: " << turn << " -----------" << std::endl;
      enemy->print_header();
      enemy->print();
      player->print_header();
      player->print();
    }

    player_won = (player->is_alive() && !enemy->is_alive());

    if (player_won)
    {
      player->eat(enemy->get_health_gain(), enemy->get_dna_gain());
    }
  }

  std::cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"
            << std::endl; 

  return player_won;
}

void engine()
{
  std::cout << "Start game!" << std::endl;

  double difficulty{1.0};

  // create the player  
  Amoeba player; // Your Code here

  // while player is still alive: fight!
  while (player.is_alive()) {
    std::cout << "Difficulty: " << difficulty << std::endl;

    // define a vector with distinct enemies (DeadCell, Bacterium, ...) which are the competitors and available to fight in this round
    std::vector<Food *> all_enemies;

    double mult = random_value(difficulty);
    DeadCell  deadcell(10.0 * mult, 0.0, 0.0);
    Bacterium bacterium(200.0 * mult, 10.0 * mult, 50.0 * mult);
    Virus     virus(500.0 * mult, 25.0 * mult, 25.0 * mult);

    all_enemies.push_back(&deadcell);
    all_enemies.push_back(&bacterium);
    all_enemies.push_back(&virus);
    if(all_enemies.empty()) return;

    player.print_header();
    player.print();
    std::cout << "\n";

    // deep copy (one to three) random competitor the player can fight in this round. Duplicates are allowed.
    std::vector<Food *> enemy;

    for(int i = std::rand() % 3; i >= 0; i--)
      enemy.push_back(all_enemies.at(std::rand() % 3)->clone());

    // print number of enemies selected for this round
    std::cout << std::setw(10) << "Select" << " : ";
    enemy[0]->print_header(); // only print header of first entry to reduce output in InfoMark
    for (size_t i = 0; i < enemy.size(); i++) {
      std::cout << std::setw(10) << i << " : ";
      enemy[i]->print();
    }
    std::cout << "Choose your enemy (0-" << enemy.size() - 1 << "): ";

    unsigned int selection;
    std::cin >> selection;

    selection = selection % enemy.size();

    combat(&player, enemy[selection]);

    difficulty += 1.0;
    
    // Your Code here
    // Hint: don't forget to free dynamically allocated objects!
    all_enemies.clear();
    enemy.clear();
  }
	std::cout << "Player reached difficulty level (round): " << difficulty << std::endl;
}
