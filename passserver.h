
#include "hashtable.h"
#include <string>
#include <crypt.h>
#include <cstring>

using namespace cop4530;
class PassServer{
	
	public:
		PassServer(size_t size = 101);
		~PassServer();
		bool load(const char *filename);
		bool addUser(std::pair<std::string,std::string> & kv);
		bool addUser(std::pair<std::string,std::string> && kv);
		bool removeUser(const std::string & k);
		bool changePassword(const std::pair<std::string,std::string> &p, const std::string & newpassword);
		bool find(const std::string & user);
		void dump();
		size_t size();
		bool write_to_file(const char *filename);
	
	
		
	private:
	cop4530::HashTable<std::string,std::string> server;
	std::string encrypt(const std::string & str);
};























