/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Homework/HW07
g++ -g -Wall -std=c++11 -o main.out *.cpp
./main.out
~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- ./main.out
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
#include <list>
#include <vector>
#include <map>
#include <random>
#include <cassert>


// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef unsigned int unint;
typedef std::map< std::string , unint > CT_MAP;
typedef std::map< std::string , CT_MAP > MY_MAP;
typedef std::map< std::string , MY_MAP > MY_MAP_2L;

//Used as placeholder string if reading frame was set to 2
std::string null = "NULL:WINDOW_2";


// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
        // break words at whitespace
        return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
        istr.get(c);
        word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this is an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking at a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}


// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP_2L &data, const std::string &filename,
                    int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }


  //
  // ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
  
  // Strings to hold used words, list to hold
  //  reading frame, and counter to note first
  //  words
  std::string word, curr, next, next2;
  std::list<std::string> rdLst;
  int counter = 1;

  if (ignore_punctuation) {
    // If reading frame is 2...
    if (window==2) {
      // Read all words in file
      while (ReadNextWord(istr,word)) {
        if (word == "\"") {continue;}

        // 1st word pushed back w/out operations
        if (counter==1) {rdLst.push_back(word); counter+=1;}

        else {
          // Add 2nd word, set itrs to look at words
          rdLst.push_back(word);
          std::list<std::string>::iterator itr1 = rdLst.begin(),
                                          itr2 = rdLst.begin();
          ++itr2;
          curr = (*itr1); next = (*itr2);

          // Only fill in 2nd + 3rd levels of map;
          //  1st level is "null" and not used
          MY_MAP miniData;
          data.insert(std::make_pair(null, miniData));

          MY_MAP::iterator mmItr = data[null].find(curr);
          // If not in map, add entire chain of words
          if (mmItr==data[null].end()) {
            CT_MAP miniminiData;
            ++miniminiData[next];
            data[null].insert(std::make_pair(curr, miniminiData));
          }
          // Else if in map, simply add to existing next word
          else {
            ++data[null][curr][next];
          }
          // Remove 1st word to change reading frame
          rdLst.pop_front();
        }
      }
    }

    // If reading frame is 3...
    else if (window==3) {
      while (ReadNextWord(istr,word)) {
        if (word == "\"") {continue;}

        // 1st words pushed back w/out operations
        if (counter<3) {rdLst.push_back(word); counter+=1;}

        else {
          // Add 3rd word, set itrs to look at words
          rdLst.push_back(word);
          std::list<std::string>::iterator itr1 = rdLst.begin(),
                                          itr2 = rdLst.begin(),
                                          itr3 = rdLst.begin();
          ++itr2; ++itr3; ++itr3;
          curr = (*itr1); next = (*itr2); next2 = (*itr3);

          MY_MAP_2L::iterator mm2Itr = data.find(curr);
          // If not in map, add entire chain of words
          if (mm2Itr==data.end()) {
            MY_MAP miniData;
            data.insert(std::make_pair(curr, miniData));
            CT_MAP miniminiData;
            ++miniminiData[next2];
            data[curr].insert(std::make_pair(next, miniminiData));
          }
          // Else if in map...
          else {
            MY_MAP::iterator mmItr = data[curr].find(next);
            // If not in inner map, add rest of chain of words
            if (mmItr==data[curr].end()) {
              CT_MAP miniminiData;
              ++miniminiData[next2];
              data[curr].insert(std::make_pair(next, miniminiData));
            }
            else {
              // Else if in inner map, simply add to existing next word
              ++data[curr][next][next2];
            }
          }
          // remove 1st word to change reading frame
          rdLst.pop_front();
        }
      }
    }
  }
}



int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP_2L data;

  // Parse each command
  std::string command;    
  while (std::cin >> command) {
    assert(command=="load" || command=="print"
        || command=="generate" || command=="quit");

    // load the sample text file
    if (command == "load") {
      data.clear();
      std::string filename;
      int window;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;

      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      
      LoadSampleText(data, filename, window, parse_method);
      std::cout<<"Loaded "<<filename
                <<" with window = "<<window
                <<" and parse method = "<<parse_method
                <<std::endl<<std::endl;
    }

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);

      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE

      // If one word given...
      if (sentence.size()==1) {
        // Check if initial reading frame was
        //  2 or 3 by checking if map has "null"
        MY_MAP_2L::iterator mm2Itr = data.find(null);
        
        // If reading frame was 2 (null is in map)...
        if (mm2Itr!=data.end()) {
          int count = 0;
          // Iterate through entire inner map to get total count
          MY_MAP::iterator mmItr = data[null].begin();
          while (mmItr!=data[null].end()) {
            // If 1st word found in inner map, enter inner-inner map
            if (mmItr->first==sentence[0]) {
              CT_MAP::iterator ctItr = data[null][mmItr->first].begin();
              while (ctItr!=data[null][mmItr->first].end()) {
                // Add to count - if blank space, don't advance itr
                if (ctItr->first=="") {count+=1; continue;} //---------OVER HERE---------
                count+=(ctItr->second);
                ++ctItr;
              }
            }
            ++mmItr;
          }
          std::cout<<sentence[0]<<" ("<<count<<")"<<std::endl;
          // Repeat same iteration to print entries
          mmItr = data[null].begin();
          while (mmItr!=data[null].end()) {
            if (mmItr->first==sentence[0]) {
              CT_MAP::iterator ctItr = data[null][mmItr->first].begin();
              while (ctItr!=data[null][mmItr->first].end()) {
                std::cout<<mmItr->first<<" "<<ctItr->first
                        <<" ("<<ctItr->second<<")"<<std::endl;
                ++ctItr;
              }
            }
            ++mmItr;
          }
          std::cout<<std::endl;
        }

        // Else if reading frame was 3 (null is not in map)...
        else if (mm2Itr==data.end()) {
          int count = 0;
          // Iterate through entire inner map to get total count
          MY_MAP_2L::iterator mm2Itr = data.begin();
          while (mm2Itr!=data.end()) {
            // If 1st word found in map, enter inner map
            if (mm2Itr->first==sentence[0]) {
              MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
              while (mmItr!=data[mm2Itr->first].end()) {
                // Add all instances in each inner-inner map to count
                int sum = 0;
                CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                while (ctItr!=data[mm2Itr->first][mmItr->first].end()) {
                  sum+=(ctItr->second);
                  ++ctItr;
                }
                count+=sum;
                ++mmItr;
              }
            }
            ++mm2Itr;
          }
          std::cout<<sentence[0]<<" ("<<count<<")"<<std::endl;
          // Repeat iteration to print entries
          mm2Itr = data.begin();
          while (mm2Itr!=data.end()) {
            if (mm2Itr->first==sentence[0]) {
              MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
              while (mmItr!=data[mm2Itr->first].end()) {
                int sum = 0;
                CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                while (ctItr!=data[mm2Itr->first][mmItr->first].end()) {
                  sum+=ctItr->second;
                  ++ctItr;
                }
                std::cout<<mm2Itr->first<<" "<<mmItr->first
                        <<" ("<<sum<<")"<<std::endl;
                ++mmItr;
              }
            }
            ++mm2Itr;
          }
          std::cout<<std::endl;
        }
      }

      // If two words given...
      else if (sentence.size()==2) {
        int count = 0;
        // Iterate through entire map to get total count
        MY_MAP_2L::iterator mm2Itr = data.begin();
        while (mm2Itr!=data.end()) {
          // If 1st word found in map, enter inner map
          if (mm2Itr->first==sentence[0]) {
            MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
            while (mmItr!=data[mm2Itr->first].end()) {
              // If 2nd word found in inner map, enter inner-inner map
              if (mmItr->first==sentence[1]) {
                CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                while (ctItr!=data[mm2Itr->first][mmItr->first].end()) {
                  // Add to count - if blank space, don't advance itr
                  if (ctItr->first=="") {count+=1; continue;} //---------OVER HERE---------
                  count+=(ctItr->second);
                  ++ctItr;
                }
              }
              ++mmItr;
            }
          }
          ++mm2Itr;
        }
        std::cout<<sentence[0]<<" "<<sentence[1]<<" ("<<count<<")"<<std::endl;
        // Repeat iteration to print
        mm2Itr = data.begin();
        while (mm2Itr!=data.end()) {
          if (mm2Itr->first==sentence[0]) {
            MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
            while (mmItr!=data[mm2Itr->first].end()) {
              if (mmItr->first==sentence[1]) {
                CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                while (ctItr!=data[mm2Itr->first][mmItr->first].end()) {
                  std::cout<<mm2Itr->first<<" "<<mmItr->first<<" "<<ctItr->first
                          <<" ("<<ctItr->second<<")"<<std::endl;
                  ++ctItr;
                }
              }
              ++mmItr;
            }
          }
          ++mm2Itr;
        }
        std::cout<<std::endl;
      }

    }

    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
        random_flag = true;
      } else {
        assert (selection_method == "most_common");
        random_flag = false;
      }


      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      
      // str for final output, lst + itrs to
      //  words-in-use (WsiU), and int to keep
      //  track of highest freq. count
      std::string output = "";
      std::list<std::string> WsiU;
      std::list<std::string>:: iterator WsiUItr1, WsiUItr2;
      unint highest = 0;

      // Immediately add sentence vec to output and 
      // set list to be in use
      for (unint i=0 ; i<sentence.size() ; ++i) {
        output+=(sentence[i]+" ");
        WsiU.push_back(sentence[i]);
      }
      WsiUItr1 = WsiU.begin(); WsiUItr2 = WsiU.begin(); ++WsiUItr2;


      // For as long as user dictates...
      for (int i=0 ; i<length ; ++i) {
        
        // If most_common...
        if (!random_flag) {
          
          // If 1 word given...
          if (WsiU.size()==1) {
            // Check if initial reading frame was
            //  2 or 3 by checking if map has "null"
            MY_MAP_2L::iterator mm2Itr = data.find(null);
            
            // If reading frame was 2 (null is in map)...
            if (mm2Itr!=data.end()) {
              // Iterate through inner map and get highest count
              MY_MAP::iterator mmItr = data[null].begin();
              while (mmItr!=data[null].end()) {
                if (mmItr->first==(*WsiUItr1)) {
                  CT_MAP::iterator ctItr = data[null][mmItr->first].begin();
                  // Iterate through all entries for WsiUItr1
                  while (ctItr!=data[null][mmItr->first].end()) {
                    // If higher than highest, set as new high
                    if (ctItr->second>highest) {
                      highest = ctItr->second;
                    }
                    ++ctItr;
                  }
                  break;
                }
                ++mmItr;
              }
              // Repeat iteration to find word w/ highest count
              mmItr = data[null].begin();
              while (mmItr!=data[null].end()) {
                if (mmItr->first==(*WsiUItr1)) {
                  CT_MAP::iterator ctItr = data[null][mmItr->first].begin();
                  while (ctItr!=data[null][mmItr->first].end()) {
                    // If found...
                    if (ctItr->second==highest) {
                      // Add to output
                      if (i!=length-1) {output+=(ctItr->first+" ");}
                      else {output+=(ctItr->first);}
                      // Change reading frame, reset values
                      WsiU.pop_front();
                      WsiU.push_back(ctItr->first);
                      WsiUItr1 = WsiU.begin();
                      highest = 0;
                      break;
                    }
                    ++ctItr;
                  }
                  break;
                }
                ++mmItr;
              }
            }

            // Else if reading frame was 3 (null is not in map)...
            else if (mm2Itr==data.end()) {
              // Iterate through map and get highest count
              MY_MAP_2L::iterator mm2Itr = data.begin();
              while (mm2Itr!=data.end()) {
                if (mm2Itr->first==(*WsiUItr1)) {
                  MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
                  while (mmItr!=data[mm2Itr->first].end()) {
                    // Add all instances in each inner-inner map to check highest
                    unint sum = 0;
                    CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                    while (ctItr!=data[mm2Itr->first][mmItr->first].end()) {
                      sum+=(ctItr->second);
                      ++ctItr;
                    }
                    if (sum>highest) {
                      highest = sum;
                    }
                    ++mmItr;
                  }
                  break;
                }
                ++mm2Itr;
              }
              // Repeat iteration to find word w/ highest count
              mm2Itr = data.begin();
              while (mm2Itr!=data.end()) {
                if (mm2Itr->first==(*WsiUItr1)) {
                  MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
                  while (mmItr!=data[mm2Itr->first].end()) {
                    // Add all instances in each inner-inner map to check highest
                    unint sum = 0;
                    CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                    while (ctItr!=data[mm2Itr->first][mmItr->first].end()) {
                      sum+=(ctItr->second);
                      ++ctItr;
                    }
                    // If found...
                    if (sum==highest) {
                      // Add to output
                      if (i!=length-1) {output+=(mmItr->first+" ");}
                      else {output+=(mmItr->first);}
                      // Change reading frame, reset values
                      WsiU.push_back(mmItr->first);
                      WsiUItr1 = WsiU.begin();
                      WsiUItr2 = WsiU.begin(); ++WsiUItr2;
                      highest = 0;
                      break;
                    }
                    ++mmItr;
                  }
                  break;
                }
                ++mm2Itr;
              }
            }
          }

          // If two words given...
          else if (WsiU.size()==2) {
            // Iterate through map and get highest count
            MY_MAP_2L::iterator mm2Itr = data.begin();
            while (mm2Itr!=data.end()) {
              if (mm2Itr->first==(*WsiUItr1)) {
                MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
                while (mmItr!=data[mm2Itr->first].end()) {
                  if (mmItr->first==(*WsiUItr2)) {
                    CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                    while (ctItr!=data[mm2Itr->first][mmItr->first].end()) {
                      // If higher than highest, set as new high
                      if (ctItr->second>highest) {
                        highest = ctItr->second;
                      }
                      ++ctItr;
                    }
                    break;
                  }
                  ++mmItr;
                }
                break;
              }
              ++mm2Itr;
            }
            // Repeat iteration to find word w/ highest count
            mm2Itr = data.begin();
            while (mm2Itr!=data.end()) {
              if (mm2Itr->first==(*WsiUItr1)) {
                MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
                while (mmItr!=data[mm2Itr->first].end()) {
                  if (mmItr->first==(*WsiUItr2)) {
                    CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                    while (ctItr!=data[mm2Itr->first][mmItr->first].end()) {
                      // If found...
                      if (ctItr->second==highest) {
                        // Add to output
                        if (i!=length-1) {output+=(ctItr->first+" ");}
                        else {output+=(ctItr->first);}
                        // Change reading frame, reset values
                        WsiU.pop_front();
                        WsiU.push_back(ctItr->first);
                        WsiUItr1 = WsiU.begin();  WsiUItr2 = WsiU.begin();  ++WsiUItr2;
                        highest = 0;
                        break;
                      }
                      ++ctItr;
                    }
                    break;
                  }
                  ++mmItr;
                }
                break;
              }
              ++mm2Itr;
            }
          }
        }

        // If random...
        else if (random_flag) {
          // If 1 word given...
          if (WsiU.size()==1) {
            // Check if initial reading frame was
            //  2 or 3 by checking if map has "null"
            MY_MAP_2L::iterator mm2Itr = data.find(null);
            
            // If reading frame was 2 (null is in map)...
            if (mm2Itr!=data.end()) {
              MY_MAP::iterator mmItr = data[null].begin();
              while (mmItr!=data[null].end()) {
                if (mmItr->first==(*WsiUItr1)) {
                  // Store words with corresponding freqs. in vec
                  std::vector<std::string> wrdVec;
                  CT_MAP::iterator ctItr = data[null][mmItr->first].begin();
                  for ( ; ctItr!=data[null][mmItr->first].end() ; ++ctItr) {
                    for (unint i=0 ; i<ctItr->second ; ++i) {
                      wrdVec.push_back(ctItr->first);
                    }
                  }
                  // Use rand to get rand idx to use
                  int randIdx = rand() % wrdVec.size();
                  if (i!=length-1) {output+=(wrdVec[randIdx]+" ");}
                  else {output+=wrdVec[randIdx];}
                  WsiU.pop_front();
                  WsiU.push_back(wrdVec[randIdx]);
                  WsiUItr1 = WsiU.begin();
                  break;
                }
                ++mmItr;
              }
            }

            // Else if reading frame was 3 (null is not in map)...
            else if (mm2Itr==data.end()) {
              MY_MAP_2L::iterator mm2Itr = data.begin();
              while (mm2Itr!=data.end()) {
                if (mm2Itr->first==(*WsiUItr1)) {
                  // Store words with corresponding freqs. in vec
                  std::vector<std::string> wrdVec;
                  MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
                  for ( ; mmItr!=data[mm2Itr->first].end() ; ++mmItr) {
                    CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                    for ( ; ctItr!=data[mm2Itr->first][mmItr->first].end() ; ++ctItr) {
                      for (unint i=0 ; i<ctItr->second ; ++i) {
                        wrdVec.push_back(ctItr->first);
                      }
                    }
                  }
                  // Use rand to get rand idx to use
                  int randIdx = rand() % wrdVec.size();
                  if (i!=length-1) {output+=(wrdVec[randIdx]+" ");}
                  else {output+=wrdVec[randIdx];}
                  // Change reading frame, reset values
                  WsiU.push_back(wrdVec[randIdx]);
                  WsiUItr1 = WsiU.begin();
                  WsiUItr2 = WsiU.begin(); ++WsiUItr2;
                  break;
                }
                ++mm2Itr;
              }
            }
          }

          // If two words given...
          else if (WsiU.size()==2) {
            MY_MAP_2L::iterator mm2Itr = data.begin();
            while (mm2Itr!=data.end()) {
              // If 1st word found in map, enter its inner map
              if (mm2Itr->first==(*WsiUItr1)) {
                MY_MAP::iterator mmItr = data[mm2Itr->first].begin();
                while (mmItr!=data[mm2Itr->first].end()) {
                  // If 2nd word found in inner map, enter its inner-inner map
                  if (mmItr->first==(*WsiUItr2)) {
                    // Store words with corresponding freqs. in vec
                    std::vector<std::string> wrdVec;
                    CT_MAP::iterator ctItr = data[mm2Itr->first][mmItr->first].begin();
                    for ( ; ctItr!=data[mm2Itr->first][mmItr->first].end() ; ++ctItr) {
                      for (unint j=0 ; j<ctItr->second ; ++j) {
                        wrdVec.push_back(ctItr->first);
                      }
                    }
                    // Use rand to get rand idx to use
                    int randIdx = rand() % wrdVec.size();
                    if (i!=length-1) {output+=(wrdVec[randIdx]+" ");}
                    else {output+=wrdVec[randIdx];}
                    WsiU.pop_front();
                    WsiU.push_back(wrdVec[randIdx]);
                    WsiUItr1 = WsiU.begin();  WsiUItr2 = WsiU.begin();  ++WsiUItr2;
                    break;
                  }
                  ++mmItr;
                }
                break;
              }
              ++mm2Itr;
            }
          }
        }
      }
      std::cout<<output<<std::endl<<std::endl;

    } else if (command == "quit") {
      break;
    } else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}