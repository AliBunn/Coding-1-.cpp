#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef struct _player {
  int health;
  int gold;
} PLAYER;

PLAYER player;

string askYesNo(string question) {
  string response;
  do {
    cout << question << " (yes/no): ";
    cin >> response;
  } while (response != "yes" && response != "no");
  return response;
}

int DiceRoll(int sides = 6) {
  if (sides < 1) {
    sides = 2;
  }
  if (sides > 100) {
    sides = 100;
  }

  return rand() % sides + 1;
}

void EndGame() {
  if (player.health > 0) {
    cout << "You are still alive\n";
    if (player.health < 5)
      cout << "Your current health is " << player.health << '.'
           << "You probably should go see a doctor.\n";
    cout << "Your current gold is " << player.gold
         << " which you can use to cover your medical costs. :) \n";
  } else
    cout << "Well your dead and you have " << player.gold
         << " gold laying next to your corpse. ";
  if (player.gold > 0)
    cout << "Enjoy!\n";
  else
    cout << '\n';

  exit(0);
}

int main(void) {
  int turns = 0;
  string adventure;
  int orcAttack = 0;
  int playerBlock = 0;

  player.health = 10; // PLAYER STARTING HEALTH.
  player.gold = 0;

  srand(time(0));

  do {
    adventure = askYesNo("Would you like to go adventuring?");

    if ("yes" == adventure) {
      turns++;
      cout << "An Orc attacks you.\n";
      orcAttack = DiceRoll();
      playerBlock = DiceRoll();

      if (playerBlock < orcAttack) { // Player block unsuccessful!
        player.health -= orcAttack;
        cout << "The orc wins the fight and you lost " << orcAttack
             << " health points.\n";
        cout << "Your current health is " << player.health << '\n';
      } else { // Player block successful! This means the block is >= orcAttack.
               // <--SEE
        int gold = DiceRoll() + 1;
        player.health--;
        player.gold += gold;

        cout << "You blocked the attack successfully but your exercion still "
                "cost you 1 health point. You found "
             << gold << " gold.\n";
        cout << "Your current health is " << player.health << '\n';
      }

      if (player.health < 1)
        EndGame();
    } else {
      EndGame();
    }
  } while (1);

  return 0;
}