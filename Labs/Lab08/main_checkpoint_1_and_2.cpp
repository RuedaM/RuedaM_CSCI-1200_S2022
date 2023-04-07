/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab08
g++ -g -Wall -std=c++11 -o main_checkpoint_1_and_2.out *.cpp
./main_checkpoint_1_and_2.out
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- main_checkpoint_1_and_2.out
*/

#include <string>
#include <iostream>
#include <sstream>
#include <cassert>

#include "superhero.h"


int main() {

  // -------------------------------------------------------
  // IMPORTANT: DO NOT MODIFY ANY OF THE PROVIDED TEST CASES
  // -------------------------------------------------------

  // CHECKPOINT 1

  // create a bunch of superheroes
  Superhero a("Elastigirl", "Zoe", "Flexible");
  Superhero b("Falcon", "Roland", "Flying");
  Superhero c("Shadow", "Violet", "Invisible");
  Superhero d("Gazerbeam", "Pierce", "Laser");
  Superhero e("Flame", "Fiona", "Fire");
  Superhero f("Lumberman", "Jack", "Wood");
  Superhero g("Aquawoman", "Marie", "Water");
  Superhero h("Dash", "Aaron", "Speed");
  
  // access information about the superheroes
  assert (a.getName() == "Elastigirl");
  assert (b.getPower() == "Flying");
  assert (c.getName() == "Shadow");
  assert (d.getPower() == "Laser");
  
  // test superhero output
  // should print:
  // "Superhero Elastigirl has power Flexible"
  // "Superhero Falcon has power Flying"
  std::cout << a << b;

  // there is no public accessor for a superhero's true identity
  // but we can try to guess a superheroe's true identity
  assert (a == "Zoe");
  assert (!(b == "Bob"));
  assert (c != "Lilly");
  assert (!(d != "Pierce"));

  // -------------------------------------------------------
  
  // CHECKPOINT 2 (uncomment when you're ready)

  //

  // superheroes start out good, but can be corrupted (negated)
  -b;
  -c;
  -c;
  assert (a.isGood());
  assert (!b.isGood());
  assert (c.isGood());

  // test superhero output
  // should print:
  // "Supervillain Falcon has power Flying"
  // "Superhero Shadow has power Invisible"
  std::cout << b << c;

  // superhero powers can be compared.  note that this property is *not* transitive!
  assert (e > f);  // fire beats wood
  assert (f > g);  // wood beats water
  assert (g > e);  // water beats fire

  //
  // add your own comparison tests here!
  //
  assert (d > c);  // laser beats invisible
  assert (c > b);  // invisible beats flying
  assert (b > d);  // flying beats laser
  assert (a > h);  // flexible beats speed
  assert (!(h > a));  // speed beats anything except speed and flexible
  assert (h > b);
  assert (h > c);
  assert (h > d);
  assert (h > e);
  assert (h > f);
  assert (h > g);
  assert (!(h > h));

  //

  // -------------------------------------------------------

  std::cout << "Passed all test cases." << std::endl;
  return 0;
}
