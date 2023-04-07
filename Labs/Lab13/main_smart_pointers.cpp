/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab13
g++ -g -Wall -std=c++11 main_smart_pointers.cpp -o smart_pointers.out
./smart_pointers.out
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- ./smart_pointers.out
*/

#include <iostream>
#include <cassert>
#include <string>
#include <set>

// simple homemade smart pointers
#include "ds_smart_pointers.h"


// ====================================================
// BALLOON: a toy class with dynamically allocated memory
// ====================================================

#define MAX_NUM_ROPES 10

class Balloon {
public:
  // CONSTRUCTOR & DESTRUCTOR
  Balloon(const std::string& name_) : name(name_) {
    std::cout << "Balloon constructor " << name << std::endl;
    num_ropes = 0;
    ropes = new Balloon*[MAX_NUM_ROPES];
  }
  ~Balloon() {
    std::cout << "Balloon destructor " << name << std::endl;
    // don't try to destroy attached balloons, just delete array
    delete [] ropes;
  }

  // ACCESSORS
  const std::string& getName() const { return name; }
  int numRopes() const { return num_ropes; }
  Balloon* getRope(int i) const { return ropes[i]; }

  // print the balloons we are attached to
  void print() { 
    std::cout << "Balloon " << name << " is connected to: ";
    for (int i = 0; i < num_ropes; i++) {
      std::cout << ropes[i]->name << " ";
    }
    if (num_ropes == 0) std::cout << "nothing";
    std::cout << std::endl;
  }
  // add a rope connecting this balloon to another
  void addRope(Balloon* b) { 
    assert (num_ropes < MAX_NUM_ROPES);
    ropes[num_ropes] = b;
    num_ropes++;
  }
  // detach a rope connecting this balloon to another
  void removeRope(Balloon* b) { 
    for (int i = 0; i < MAX_NUM_ROPES; i++) {
      if (ropes[i] == b) { ropes[i] = ropes[num_ropes-1]; num_ropes--; break; }
    }
  }

private:
  std::string name;
  int num_ropes;
  // a dynamically allocated C-style array of ropes connecting to other Balloons
  Balloon** ropes; 
};

// Extra Code
class Balloon2 {
    public:
    // Constructor + Destructor
    Balloon2( const std::string& name_) : name(name_) {
        std::cout << "Balloon Constructor " << name << std::endl;
        num_ropes = 0;
        ropes = new dsSharedPtr<Balloon2>[MAX_NUM_ROPES];
    }
    ~Balloon2() {
        std::cout << "Balloon Destructor " << name << std::endl;
        delete [] ropes;
    }
    // Accessors
    const std::string& getName() const {return name;}
    int numRopes() const {return num_ropes; }
    const dsSharedPtr<Balloon2> getRope(int i) const { return ropes[i]; }

    

    void addRope (const dsSharedPtr<Balloon2> &b) {
        assert (num_ropes < MAX_NUM_ROPES);
        ropes[num_ropes] = b;
        num_ropes++;
    }

    void removeRope(Balloon2* b) {
        for (int i = 0; i < MAX_NUM_ROPES; i++) {
            if (ropes[i] == b) {
                ropes[i] = ropes[num_ropes - 1];
                num_ropes--;
                break;
            }
        }
    }
  // print the balloons we are attached to
    void print() { 
      std::cout << "Balloon " << name << " is connected to: ";
      for (int i = 0; i < num_ropes; i++) {
        std::cout << ropes[i]->name << " ";
      }
      if (num_ropes == 0) std::cout << "nothing";
      std::cout << std::endl;
    }

    private:
        std::string name;
        int num_ropes;
        dsSharedPtr<Balloon2>* ropes; 

};

/*
void deleteAll(Balloon* j) {
  std::set<Balloon*> balloon_set;
  balloon_set.insert(j);
  Balloon* start = j;
  Balloon* new_start = NULL;
  while(true) {
    //go through the array of this balloon
    for(int i = 0; i < start->numRopes(); i++){
      //get the ith balloon
      new_start = start->getRope(i);
      if(new_start==j && i==start->numRopes()-1)
          break; //if we get the first

      if (balloon_set.insert(new_start).second) { //find the new balloon
        start = new_start;
        break;
      } else {
        if(i==start->numRopes()-1)
          continue;
      }
      if(new_start==j && i ==start->numRopes()-1)
        break;
    }
    // if(new_start==j && i ==start->numRopes()-1) break;
  }
  for (std::set<Balloon*>::const_iterator i = balloon_set.begin(); i != balloon_set.end() ; ++i) {
    delete *i;
  }
}
*/
void deleteAll(Balloon* j, std::set<Balloon*>& balloon_set){
  if(balloon_set.find(j)==balloon_set.end()) {balloon_set.insert(j);}
  else {return;}

  for (int i = 0; i < j->numRopes(); i++) {
    deleteAll(j->getRope(i), balloon_set);
    //j->getRope(i), balloon_set
  }
  delete j;
}
void deleteAll(Balloon *j) {
  std::set<Balloon*> balloon_set;
  deleteAll(j, balloon_set);
}
//


// ====================================================
// ====================================================

int main() {

  std::cout << "start of main" << std::endl;
  
  // ====================================================
  // SINGLE OWNER SMART POINTERS
  // ====================================================

  // first, without smart pointers!
  Balloon* alice(new Balloon("Hello Kitty"));
  
  // now, with our homemade single owner smart pointer
  dsAutoPtr<Balloon> bob(new Balloon("Spiderman"));

  // both alice & bob work like regular pointers...
  alice->print();
  bob->print();



  //
  // CHECKPOINT 2A: INSERT NECESSARY EXPLICIT DEALLOCATION
  delete alice;
  
  // ====================================================
  // SIMPLE SHARED POINTERS
  // ====================================================

  // first, without smart pointers
  Balloon* cathy(new Balloon("Buzz Lightyear"));  
  Balloon* daniel(cathy);
  Balloon* elaine(new Balloon("Pokemon"));
  Balloon* fred(elaine);
  daniel = fred;
  fred = NULL;
  elaine = cathy;
  cathy = NULL;
  


  //
  // CHECKPOINT 2B: INSERT NECESSARY EXPLICIT DEALLOCATION
  delete daniel; delete elaine;

  daniel = NULL;
  elaine = NULL;
  

  // now, with our homemade shared pointer
  dsSharedPtr<Balloon> cathy2(new Balloon("Buzz Lightyear2"));
  dsSharedPtr<Balloon> daniel2(cathy2);
  dsSharedPtr<Balloon> elaine2(new Balloon("Pokemon2"));
  dsSharedPtr<Balloon> fred2(elaine2);
  daniel2 = fred2;
  fred2 = NULL;
  elaine2 = cathy2;
  cathy2 = NULL;
   // NOTE:  no explicit destruction required!
  daniel2 = NULL;
  elaine2 = NULL;


  // ====================================================
  // SHARED POINTERS WITH INTERCONNECTED STRUCTURES
  // ====================================================

  // Balloon* georgette(new Balloon("Mr Potato Head"));
  // Balloon* henry(new Balloon("Snoopy"));

  // georgette->addRope(henry);
  // henry = new Balloon("Tigger");
  // georgette->addRope(henry);
  // georgette->print();
  // henry->print();
  
  // Balloon* isabelle(new Balloon("Shrek"));
  // henry->addRope(isabelle);
  // isabelle = new Balloon("Barney the Purple Dinosaur");
  // georgette->addRope(isabelle);

  // henry->print();
  // georgette->print();
  // isabelle->print();


  //
  // CHECKPOINT 2C: REWRITE THE ABOVE EXAMPLE TO USE SHARED POINTERS
  dsSharedPtr<Balloon2> geo(new Balloon2("Mr Potato Head"));
  dsSharedPtr<Balloon2> hen(new Balloon2("Snoopy"));
  geo->addRope(hen);
  hen = new Balloon2("Trigger");
  geo->addRope(hen);
  geo->print();
  hen->print();

  dsSharedPtr<Balloon2> isa(new Balloon2("Shrek"));
  hen->addRope(isa);
  isa = new Balloon2("Barney the Purple Dinosaur");
  geo->addRope(isa);

  hen->print();
  geo->print();
  isa->print();



  // ====================================================
  // CYCLIC STRUCTURES
  // ====================================================


  // FOR CHECKPOINT 3


  //
  Balloon* jacob(new Balloon("Dora the Explorer"));
  Balloon* katherine(new Balloon("Kung Fu Panda"));
  Balloon* larry(new Balloon("Scooby Doo"));
  Balloon* miranda(new Balloon("SpongeBob SquarePants"));
  Balloon* nicole(new Balloon("Papa Smurf"));

  jacob->addRope(katherine);
  katherine->addRope(larry);
  larry->addRope(jacob);
  miranda->addRope(jacob);
  nicole->addRope(miranda);
  larry->addRope(nicole);

  katherine = NULL;
  larry = NULL;
  miranda = NULL;
  nicole = NULL;

  // jacob points to a cyclic structure!

  // to cleanup this structure:
  deleteAll(jacob);
  
  jacob = NULL;
  //



  std::cout << "end of main" << std::endl;
  return 0;

  //
  // NOTE: when smart pointers go out of scope, the destructors for
  //       those objects will be called automatically
  //
}

// ====================================================
