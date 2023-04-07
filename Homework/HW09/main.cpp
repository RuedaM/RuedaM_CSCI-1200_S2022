/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW09
g++ -g -Wall -std=c++11 main.cpp -o main.out
./main.out < small_example_input.txt
./main.out < top250_example_input.txt
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- ./main.out < small_example_input.txt
*/

// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map> // Includes pair
#include <cassert>

#include "movie_data.h"
#include "HW9_ds_hashset.h"


typedef unsigned int unint;
typedef std::map<std::string, std::string> actMap;

// Forward declaration for typedef
class hash_string_obj;
typedef ds_hashset< std::pair< QUERY, std::list<MOVIE_DATA*> > , hash_string_obj > HASHTBL_TYPE;


// ==========================
// HELPER CLASSES + FUNCTIONS

class hash_string_obj {
	public:
	  unsigned int operator() (const std::string& key) const {
	  	//  (Note: hash function pulled from class)
	    //  This implementation comes from 
	    //  http://www.partow.net/programming/hashfunctions/
	    //  This is a general-purpose, very good hash function for strings
	    unsigned int hash = 1315423911;
	    for (unsigned int i = 0; i < key.length(); i++)
	      {hash ^= ((hash<<5) + key[i] + (hash>>2));}
	    return hash;
	  }
};

// (Note: Mostly copied from given code)
void permute_filters(int pos, std::vector<std::vector<int>>& filters, std::vector<int> filter) {
	if (pos == 6) {
		filters.push_back(filter);
		return;
	}
	filter.push_back(0);
	std::vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos+1, filters, filter_new);
	permute_filters(pos+1, filters, filter);
}
// Driver function
std::vector<std::vector<int>> permute_filters() {
	std::vector<std::vector<int>> retVec;
	std::vector<int> filterVec;
	permute_filters(0, retVec, filterVec);
	return retVec;
}

void SetMovies(const std::string& inFileStr, std::list<MOVIE_DATA>& movieVec, HASHTBL_TYPE& hash_table) {
	// open file stream
	std::ifstream inFile(inFileStr); assert(inFile);

	// While still strings to read, add to hash table
	std::string title, genStr;
	int year, runtime, GenreCount, ActorCount, RoleCount;
	std::vector<std::string> GenreList, ActorList, RoleList;
	
	while (inFile>>title) {
		// Cursor moves with every read
		inFile>>year; inFile>>runtime;
		inFile>>GenreCount;
		for (int i=0 ; i<GenreCount ; ++i) {
			inFile>>genStr;
			GenreList.push_back(genStr);
		}
		inFile>>ActorCount;
		for (int i=0 ; i<ActorCount ; ++i) {
			inFile>>genStr;
			ActorList.push_back(genStr);
		}
		inFile>>RoleCount;
		for (int i=0 ; i<RoleCount ; ++i) {
			inFile>>genStr;
			RoleList.push_back(genStr);
		}

		/*
		std::cout<<std::endl;
		std::cout<<"Acquired movie:"<<std::endl;
		std::cout<<title<<", "<<year<<", "<<runtime<<std::endl;
		std::cout<<GenreCount<<": ";
		for (int i=0 ; i<GenreCount ; ++i) {std::cout<<GenreList[i]<<" ";} std::cout<<std::endl;
		std::cout<<ActorCount<<": ";
		for (int i=0 ; i<ActorCount ; ++i) {std::cout<<ActorList[i]<<" ";} std::cout<<std::endl;
		std::cout<<RoleCount<<": ";
		for (int i=0 ; i<RoleCount ; ++i) {std::cout<<RoleList[i]<<" ";} std::cout<<std::endl;
		*/

		MOVIE_DATA movie(title, year, runtime, GenreCount, GenreList, ActorCount,ActorList, RoleCount, RoleList);
		movieVec.push_back(movie);
		MOVIE_DATA* movieptr = &movieVec.back();
		

		// Use permute_filters() to get all possibilities
		std::vector<std::vector<int>> possibilities = permute_filters();
		QUERY q;
		for (unint i=0 ; i<possibilities.size() ; ++i) {
			q = "|";
			if (possibilities[i][0]==1) {q=q+title+"|";}
			if (possibilities[i][1]==1) {q=q+std::to_string(year)+"|";}
			if (possibilities[i][2]==1) {q=q+std::to_string(runtime)+"|";}
			if (possibilities[i][3]==1) {
				q=q+std::to_string(GenreCount)+" ";
				for (unint j=0 ; j<GenreList.size() ; ++j) {
					q=q+GenreList[j]+" ";
				}
				q+="|";
			}
			if (possibilities[i][4]==1) {
				q=q+std::to_string(ActorCount)+" ";
				for (unint j=0 ; j<ActorList.size() ; ++j) {
					q=q+ActorList[j]+" ";
				}
				q+="|";
			}
			if (possibilities[i][5]==1) {
				q=q+std::to_string(RoleCount)+" ";
				for (unint j=0 ; j<RoleList.size() ; ++j) {
					q=q+RoleList[j]+" ";
				}
				q+="|";
			}
			//std::cout<<"Current query to be added: "<<q<<std::endl;
			hash_table.insert(q, movieptr);
		}

		GenreList.clear(); ActorList.clear(); RoleList.clear();
	}
}

void SetActors(const std::string& inFileStr, actMap& actorMap) {
	// open file stream
	std::ifstream inFile(inFileStr);
	assert(inFile);

	// While still strings to read, add to map
	std::string code, name;
	while (inFile>>code) {
		// (Cursor moves with 2nd read)
		inFile>>name;
		actorMap[code] = name;
	}
}



// =============
// MAIN FUNCTION
int main() {
	HASHTBL_TYPE hash_table;
	actMap actorMap;
	std::list<MOVIE_DATA> movieVec;
	std::vector<std::vector<int>> filters;


	// Continually ask for commands
	std::string command, inFileStr;
	while (std::cin>>command) {

		if (command=="movies") {
			// Immediately set inFileStr
			std::cin>>inFileStr;

			// All file info put into hash_table, returned by ref
			SetMovies(inFileStr, movieVec, hash_table);
		}

		else if (command=="actors") {
			// Immediately set inFileStr
			std::cin>>inFileStr;

			// All file info put into map, returned by ref
			SetActors(inFileStr, actorMap);
		}

		else if (command=="table_size") {
			// Immediately set size
			int size; std::cin>>size;
			HASHTBL_TYPE new_hash_table(size);
			hash_table = new_hash_table;
		}

		else if (command=="occupancy") {
			// Immediately set occupancy
			float occ; std::cin>>occ;
			hash_table.occChange(occ);
		}

		else if (command=="query") {
			std::string title, genStr, year, runtime;
			int GenreCount, ActorCount, RoleCount;
			std::vector<std::string> GenreList, ActorList, RoleList;

			std::cin>>title>>year>>runtime;
			std::cin>>GenreCount;
			for (int i=0 ; i<GenreCount ; ++i) {
				std::cin>>genStr;
				GenreList.push_back(genStr);
			}
			std::cin>>ActorCount;
			for (int i=0 ; i<ActorCount ; ++i) {
				std::cin>>genStr;
				ActorList.push_back(genStr);
			}
			std::cin>>RoleCount;
			for (int i=0 ; i<RoleCount ; ++i) {
				std::cin>>genStr;
				RoleList.push_back(genStr);
			}

			QUERY q = "|";
			if (title!="?") {q=q+title+"|";}
			if (year!="?") {q=q+year+"|";}
			if (runtime!="?") {q=q+runtime+"|";}

			if (GenreCount!=0) {
				q=q+std::to_string(GenreCount)+" ";
				for (unint j=0 ; j<GenreList.size() ; ++j) {q=q+GenreList[j]+" ";}
				q+="|";
				}
			if (ActorCount!=0) {
				q=q+std::to_string(ActorCount)+" ";
				for (unint j=0 ; j<ActorList.size() ; ++j) {q=q+ActorList[j]+" ";}
				q+="|";
				}
			if (RoleCount!=0) {
				q=q+std::to_string(RoleCount)+" ";
				for (unint j=0 ; j<RoleList.size() ; ++j) {q=q+RoleList[j]+" ";}
				q+="|";
			}

			//std::cout<<"Loking for query: "<<q<<std::endl;

			std::pair<std::list<MOVIE_DATA*>,bool> result = hash_table.find(q);
			if (!result.second) {std::cout<<"No results for query."<<std::endl;}
			else {
				std::cout<<"Printing "<<result.first.size()<<" result(s):"<<std::endl;
				std::list<MOVIE_DATA*>::iterator itr = result.first.begin();
				//
				for ( ; itr!=result.first.end() ; ++itr) {
					std::cout<<(*itr)->title<<std::endl;
					std::cout<<(*itr)->year<<std::endl;
					std::cout<<(*itr)->runtime<<std::endl;
					std::cout<<(*itr)->GenreCount;
					for (int j=0 ; j<(*itr)->GenreCount ; ++j) {
						std::cout<<" "<<(*itr)->GenreList[j];
					}
					std::cout<<std::endl;
					std::cout<<(*itr)->ActorCount;
					for (int j=0 ; j<(*itr)->ActorCount ; ++j) {
						std::cout<<" "<<actorMap[(*itr)->ActorList[j]]<<" ("<<(*itr)->RoleList[j]<<")";
					}
					std::cout<<std::endl;
				}
				//
			}
		}

		else if (command=="quit") {break;}
		
		else {std::cout<<"WARNING---UNKNOWN COMMAND: "<<command<<std::endl;}
	}

	return 0;
}