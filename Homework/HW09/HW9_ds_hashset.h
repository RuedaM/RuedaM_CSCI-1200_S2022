#ifndef ds_hashset_h_
#define ds_hashset_h_
// The set class as a hash table instead of a binary search tree.  The
// primary external difference between ds_set and ds_hashset is that
// the iterators do not step through the hashset in any meaningful
// order.  It is just the order imposed by the hash function.
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <utility> // Includes pair
#include <algorithm>

#include "movie_data.h"

typedef std::string QUERY;

// The ds_hashset is templated over both the type of key and the type
// of the hash function, a function object.
template < class KeyType, class HashFunc >
class ds_hashset {
  private:
    typedef typename std::list<MOVIE_DATA*>::iterator hash_list_itr;

  private:
    // =================================================================
    // HASH SET REPRESENTATION
    std::vector<KeyType> m_table;     // actual table
    HashFunc m_hash;                  // hash function
    unsigned int m_size;              // number of keys

  public:
    // =================================================================
    // HASH SET IMPLEMENTATION
    
    // Constructor for the table accepts the size of the table.  Default
    // constructor for the hash function object is implicitly used.
    // As per HW assignment, init_size = 100
    ds_hashset(unsigned int init_size = 100) : m_table(init_size), m_size(0) {
      //std::cerr<<"############################################################"<<std::endl;
    }

    // Copy constructor just uses the member function copy constructors.
    ds_hashset(const ds_hashset<KeyType, HashFunc>& old) {
      m_table = old.m_table;
      m_size = old.m_size;
    }

    ~ds_hashset() {} //=========================================================== MUST BUILD DESTRUCTOR maybe

    ds_hashset& operator=(const ds_hashset<KeyType,HashFunc>& old) {
      if (&old != this) {
        this->m_table = old.m_table;
        this->m_size = old.m_size;
        this->m_hash = old.m_hash;
        this->LOAD_FRACTION_FOR_RESIZE = old.LOAD_FRACTION_FOR_RESIZE;
      }
      return *this;
    }

    unsigned int size() const {return m_size;}

    void occChange(const float occ) {LOAD_FRACTION_FOR_RESIZE = occ;}

    // Insert the key if it is not already there.
    bool insert(QUERY& key, MOVIE_DATA* movieptr) {
      if (m_size >= LOAD_FRACTION_FOR_RESIZE * m_table.size()) {
        this->resize_table(2*m_table.size()+1);
      }

      // 1. If query in table, simply add to list associated w/ key
      // 2. If query not in table, create pair of query and list, add to that list
      // 3. If collision and query in table, linear probe until existing query is found, add to list
      // 4. If collision and query not in table, linear probe to next available space, create pair, add to that list

      // Using key and hash function, find index from hash value, linearly probe
      unsigned int hash_value = m_hash(key);
      unsigned int index = hash_value % m_table.size();
      index = linear_probe(index, hash_value, key);

      // Find if movie already exists in list
      hash_list_itr p = std::find(m_table[index].second.begin(), m_table[index].second.end(), movieptr);

      bool addedNew = false;
      // If found, note as such and add
      if (p==m_table[index].second.end()) {
        addedNew = true;
        m_table[index].first = key;
        m_table[index].second.push_back(movieptr);
      }
      else {
        m_table[index].second.push_back(movieptr);
      }

      //std::cout<<m_table[index].second.back()->title<<std::endl;
      
      return addedNew;
    }

    // Find the key, using hash function, indexing and list find
    std::pair< std::list<MOVIE_DATA*>, bool > find(const QUERY& key) {
      // Using key and hash function, find index from hash value, linearly probe
      unsigned int hash_value = m_hash(key);
      unsigned int index = hash_value % m_table.size();
      index = linear_probe(index, hash_value, key);

      //std::cout<<"Testing if index was got:"<<std::endl;
      //std::cout<<m_table[index].second.back()->title<<std::endl;

      // If given index matches key at index, return list and true - else, return false
      if (m_table[index].first==key) {
        return (make_pair(m_table[index].second, true));
      }
      else {
        return (make_pair(m_table[index].second, false));
      }
    }

    // // Find the first entry in the table and create an associated iterator
    // iterator begin() {
    //   // Go through all indices of hash_table, stop at first "filled" index
    //   int index = 0;
    //   while (index<m_table.size() && m_table[index].second.size()==0) {++index;}
    //   // Return beginning of the list at the hash table index
    //   return m_table[index].second.begin();
    // }

    // // Create an end iterator
    // iterator end() {
    //   iterator p(this);
    //   p.m_index = -1;
    //   return p;
    // }
    
    // A public print utility - MAY NOT NEED BUT KEEP JUST IN CASE
    // void print(std::ostream& ostr) {
    //   for (unsigned int i=0; i<m_table.size(); ++i) {
    //     ostr<<i<<": ";
    //     for (hash_list_itr p = m_table[i].second.begin() ; p!=m_table[i].second.end() ; ++p)
    //       ostr<<' '<<(*p);
    //     ostr<<std::endl;
    //   }
    // }

  private:
    int linear_probe(int index, int hash_value, const QUERY& key) {
      for (int i=0 ; m_table[index].first!=key && m_table[index].second.size()!=0 ; ++i) {
        // If it wraps around and reaches original index, break - maybe implement, but not AS necessary
        if (index>=int(m_table.size())-1) {i = -hash_value;}
        index = (hash_value+i) % m_table.size();
      }
      return index;
    }

    // resize the table with the same values but twice as many buckets
    void resize_table(unsigned int new_size) {
      std::cout<<"resize called"<<std::endl;
      // Create new hash_table to populate with new size
      std::vector< KeyType > new_hash_table(new_size);

      // Iterate through old hash_table and copy values: rehashing
      for (unsigned int i=0 ; i<m_table.size() ; ++i) {
        QUERY key = m_table[i].first;
        unsigned int hash_value = m_hash(key);
        unsigned int index = hash_value % new_size;
        index = linear_probe(index, hash_value, key);

        new_hash_table[index] = m_table[index];
      }
      
      m_table = new_hash_table;
    }


    float LOAD_FRACTION_FOR_RESIZE = 0.5;
};

#endif
