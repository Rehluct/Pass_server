#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <list>
#include <vector>
#include <cstdlib>
#include <iostream> 
#include <utility>
#include <algorithm>
#include <fstream>
// max_prime is used by the helpful functions provided
// to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity 
// of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 11;


namespace cop4530{
template <typename K, typename V>
class HashTable{
	
	public:
		HashTable(size_t size = 101);
		~HashTable();
		bool contains(const K & k);
		bool match(const std::pair<K, V> &kv);
		bool insert(const std::pair<K, V> & kv);
		bool insert (std::pair<K,V> && kv);
		bool remove(const K & k);
		void clear();
		bool load(const char *filename);
		void dump();
		bool write_to_file(const char *filename);
		int getsize();
	
	private:
		
		void makeEmpty();
		void rehash();
		bool containsValue(const std::pair<K, V> & kv);
		size_t myhash(const K &k);
		std::vector < std::list< std::pair<K,V> > > table;
		int sizeVector;
		
		unsigned long prime_below (unsigned long);
		void setPrimes(std::vector<unsigned long>&);
		int currentSize;
		
	
};
#include "hashtable.hpp"

}
 
#endif
