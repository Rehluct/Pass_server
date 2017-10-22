#include "passserver.h"


PassServer::PassServer(size_t size ):server(size){

}
PassServer::~PassServer(){
	
	
	
}
bool PassServer::addUser(std::pair<std::string,std::string> & kv){

	 
	//std::cout << "\n"<< str2 <<" size "<<std::endl;
	std::pair<std::string,std::string>p;
	std::string l = kv.second;
	p = std::make_pair(kv.first,encrypt(l));
	//std::cout << "ploepwj"<<p.first<<std::endl;
	return server.insert(p);
	
}

bool PassServer::addUser(std::pair<std::string,std::string> && kv){
	
	 
	//std::cout << "\n"<< str2 <<" size "<<std::endl;
	
	return server.insert(make_pair(kv.first,encrypt(kv.second)));
	
}


bool PassServer::removeUser(const std::string & k){
	server.remove(k);
}

bool PassServer::changePassword(const std::pair<std::string,std::string> &p, const std::string & newpassword){
	
	if(p.second == newpassword){
	//std::cout << "1"<<p.first<<std::endl;	
		return false;
	}
	if(!server.contains(p.first)){
	//std::cout << "2"<<p.first<<std::endl;
		return false;
	}

	 
	std::pair<std::string,std::string>j;
	std::string q = p.second;
	j = std::make_pair(p.first,encrypt(q));
	
	if(!server.match(j)){
		//std::cout << "3"<<p.first<<std::endl;
		
		return false;
	}
	
	std::pair<std::string,std::string> l = p;
	l.second = newpassword;
	addUser(l);
	return true;
	
}
std::string PassServer::encrypt(const std::string & str){
	char salt[] = "$1$########";
	char * password = new char [100];
	
	strcpy ( password, crypt(str.c_str(), salt));
	std::string passy = password;
	std::string str2 = passy.substr(12,passy.length());
	return str2;
	
}

bool PassServer::find(const std::string & user){
	if(server.contains(user))
		return true;
		
		return false;
}

void PassServer::dump(){
	server.dump();
}


size_t PassServer::size(){
	return server.getsize();
}



bool PassServer::write_to_file(const char *filename){
	return server.write_to_file(filename);
}


bool PassServer::load(const char *filename){
	return server.load(filename);
}










