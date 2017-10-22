
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size):table(prime_below(size)),currentSize(0) {
	
	//std::cout << table.capacity()  <<"size "<<std::endl;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv){
	//std::cout << "\n"<< table.size() <<" size "<< currentSize << " currentSize "<<std::endl;
	//std::cout <<" kv.first copy " << kv.first  <<" kv.second " <<kv.second <<std::endl;
	auto & whichList = table[myhash(kv.first)];
	
	if (find(begin(whichList), end(whichList), kv) != end(whichList))
		return false;
	bool breaky = false;
	if (containsValue(kv)){
		for( auto & x : whichList ){
			if(x.first == kv.first &&  x.second != kv.second){
				x = kv;
				currentSize--;
				breaky = true;
				break;
			}
		}
	}
	if(!breaky){
	whichList.push_back(kv);
	//std::cout << "pushing back "<<std::endl;
	}
	//std::cout << "not going "<<currentSize<<std::endl;
	//  rehash, see Section 5.5
	if (currentSize++ > table.size() )
		rehash();

	return true;
}

template <typename K, typename V>
size_t  HashTable<K, V>::myhash(const K &k){
	std::hash<K> hash;
	return hash(k)%table.size() ;
}

template <typename K,typename V>
void HashTable<K, V>::rehash(){
	int sum = ((table.size() / 2)+2) * 2 + 1; 
	//std::cout << " SUM " <<sum <<std::endl;
	std::vector < std::list< std::pair<K,V> > > temp = table;
	table.resize(prime_below(sum)); 
	
	for( auto & thisList : table )
		thisList.clear( );
	
	currentSize =0;
	  
	for( auto & thisList : temp )
		for( auto & x : thisList ){
			insert( std::move( x ) );
		}
	
}

template<typename K,typename V>
bool HashTable<K, V>::containsValue(const std::pair<K, V> & kv){
	
	for( auto & x : table[myhash(kv.first)] ){
		//std::cout << " contains " <<x.first <<" x.second "<<x.second <<" kv.first " << kv.first  <<" kv.second " <<kv.second <<std::endl;
		if(x.first == kv.first &&  x.second != kv.second){
		//	std::cout << " true v" <<std::endl;
			return true;
		}
	}
	//std::cout << " false v" <<std::endl;
	return false;
}

template<typename K,typename V>
bool HashTable<K, V>::contains(const K & k){
	
	for( auto & x : table[myhash(k)] ){
		if(x.first == k){
			//std::cout << " true " <<std::endl;
			return true;
		}
	}
	//std::cout << " false " <<std::endl;
	return false;
}

template<typename K,typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv){
	
	auto & whichList = table[myhash(kv.first)];
	if (find(begin(whichList), end(whichList), kv) != end(whichList))
		return true;
	
		return false;
}


template<typename K,typename V>
bool HashTable<K, V>::insert (std::pair<K,V> && kv){
	//std::cout << "\n"<< table.size() <<" sizem "<< currentSize << " currentSizem "<<std::endl;
	//std::cout <<" kv.first move " << kv.first  <<" kv.second " <<kv.second <<std::endl;
	
	auto & whichList = table[myhash(kv.first)];
	//std::cout << myhash(kv.first) << "  hash "<<std::endl;
	// for (auto & x =whichList.begin(); x != whichList.end(); ++x)
    //std::cout << ' ' << (*x).first;
	//auto & x =begin(whichList);
	if (find(begin(whichList), end(whichList), kv) != end(whichList))
		return false;
	
	bool breaky = false;
	if (containsValue(kv)){
		for( auto & x : whichList ){
			if(x.first == kv.first &&  x.second != kv.second){
				x = std::move(kv);
				breaky = true;
				currentSize--;
				break;
			}
		}
	}
	if(!breaky)
	whichList.push_back(std::move(kv));

	//  rehash, see Section 5.5
	if (currentSize++ > table.size() )
		rehash();

	return true;
}

template<typename K,typename V>
bool HashTable<K, V>::remove(const K & k){
	//pair <K, V> p;
	auto & whichList = table[myhash(k)];
	
	if(contains(k)){
		for( auto  x = whichList.begin(); x != whichList.end();++x ){		
			if((*x).first == k){
				//std::cout <<  "remove found" <<std::endl;
				whichList.erase( x);
				--currentSize;
				return true;
			}
		}
	}
	
	return false;
}

template<typename K,typename V>
void HashTable<K, V>::makeEmpty(){
	
	for( auto & thisList : table ){
		currentSize--;
		thisList.clear( );
	}
}
template<typename K,typename V>
HashTable<K, V>::~HashTable(){
	clear();
}

template<typename K,typename V>
void HashTable<K, V>::clear(){
	
	makeEmpty();
}


template<typename K,typename V>
void HashTable<K, V>::dump(){
	int count=0;
	for( auto & thisList : table ){
		//if(!thisList.empty()){
			std::cout <<'v'<<'['<<count<<']'<<": ";
			for( auto & x : thisList ){
				std::cout <<x.first <<" "<<x.second <<":";
			}
			std::cout <<std::endl;

		count++;
	}
}
template<typename K,typename V>
bool HashTable<K, V>::load(const char *filename){
	
	std::ifstream myfile (filename);
	 if (!myfile.is_open())
    {
        //std::cout << "Could not open file: " << filename << std::endl;
        return false;;
    }

	K key;
	V value;
	std::pair <K, V> p;
	 while( myfile >>key){
			 myfile >>value;

			insert(std::make_pair(key,value));
			//std::cout << line <<std::endl;
	 }
	return true;
}
template<typename K,typename V>
bool HashTable<K, V>::write_to_file(const char *filename){
	std::ofstream myfile;
	myfile.open (filename);
	if (myfile.fail())
	{
		//std::cout  << "Failed" << std::endl;
		return false;
	}
	
	for( auto & thisList : table ){
		if(!thisList.empty()){
			for( auto & x : thisList ){
				myfile <<x.first <<" "<<x.second <<std::endl;;
			}
		}
	}
	
	return true;
}

template<typename K,typename V>
int HashTable<K, V>::getsize(){
	return currentSize;
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n


template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

