#include "passserver.h"
using namespace std;
//using namespace cop4530;
void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

int main(){
	
	
	char choice;
	int sizey = 101;;
	cout<<"Enter preferred hash table capacity: ";
	cin >>sizey;
	cout<<endl;
	PassServer table(sizey);
	do{
		
		Menu();
		cin>>choice;
		
		if(choice == 'l' ){
			string a =" ";
			cout<<"Enter password file name to load from: "<<endl;
			cin>>a;
			table.load(a.c_str());
			
			
		}
		if(choice == 'w' ){
			string a =" ";
			cout<<"Enter password file name to write to: "<<endl;
			cin>>a;
			cout<<endl;
			table.write_to_file(a.c_str());
			
		}
		if(choice == 'f' ){
			string a =" ";
			cout<< "Enter username    :"<<endl;;
			cin>>a;
			if(table.find(a))
				cout<< "User '"<<a<< "' found."<<endl;
			else
				cout<< "User '"<<a<< "' not found."<<endl;
		}
		if(choice == 's' ){
			cout<<"Size of hashtable: "<<table.size()<<endl;
		}		
			
			
		if(choice == 'a' ){
			string a =" ";
			string b =" ";
			cout<< "Enter username: ";
			cin>>a;
			cout<< "Enter password: ";
			cin>>b;
			cout<<endl;
			table.addUser(std::make_pair(a,b));
			cout<< "User "<<a<<" added."<<endl;
		}
		if(choice == 'c' ){
			string a = " ";
			string b = " ";
			string c = " ";
			cout<< "Enter username: ";
			cin>>a;
			cout<< "Enter password: ";
			cin>>b;
			cout<<endl;
			cout<< "Enter new password: ";
			cin>>c;
			cout<<endl;
			if(!table.changePassword(std::make_pair(a,b),c))
				cout<< "*****Error: Could not change user password "<<endl;
			else
				cout<< "Password changed for user "<< a<<endl;
		}
		if(choice == 'd' ){
			table.dump();
		}
		if(choice == 'r' ){
			string a =" ";
			cout<< "Enter username: ";
			cin>>a;

			if(!table.removeUser(a.c_str()))
				cout<<"*****Error: User not found.  Could not delete user"<<endl;
			else
				cout<<"User "<<a<<" deleted."<<endl;
		}
		
		
		
		
	}while( choice != 'x');
		
		
		
		
		
		
		

	
	
	

	
	
	
	/*

	
	std::string c="steven";
	std::string v="password";
	
	std::string a="john";
	std::string g="lopo";
	
	PassServer b(3);
	
	pair<string,string>p;
	p = std::make_pair(c,v);
	//b.removeUser("steven");
	
	b.addUser(std::make_pair(c,v));
	b.addUser(std::make_pair(a,g));
	b.addUser(std::make_pair("willy","8921"));
	b.addUser(std::make_pair("chris ","8921"));
	b.addUser(std::make_pair("phlip","8921"));
	b.write_to_file("lol.txt");
	b.dump();
	b.load("lol.txt");
	//b.changePassword(std::make_pair("willy","hi"),"5621");
*/
	/*HashTable <char,int > b(3);
	
	pair <char, int> m;
	pair <char, int> u;
	pair <char, int> t;
	int salt = 159;
	char key = 'b';
	
	std::cout << " 1"<<std::endl;
	p = make_pair('l',salt);
	b.insert(make_pair('l',salt));
	
	std::cout << " 2 "<<std::endl;
	m = make_pair('c',13);
	b.insert( make_pair('c',13));
	
	std::cout << " 3"<<std::endl;
	t = make_pair('k',50);
	b.insert(make_pair('k',50));
	
	
	
	std::cout << " 4"<<std::endl;
	u = make_pair('g',20);
	b.insert(make_pair('g',20));
	//b.contains('c');
	//b.dump();
	//b.remove('g');
	std::cout << " topppp "<<std::endl;
	b.write_to_file("lol.txt");
	b.clear();
	std::cout << " bot "<<std::endl;
	b.dump();
	
	b.load("lol.txt");
	std::cout << " mid "<<std::endl;
	b.dump();
	
	/*
	
	b.insert(make_pair('f',230));
	*/
	/*
	//std::cout << "rehash "<<std::endl;
	p = make_pair(key,14);
	b.insert(p);
	
	//std::cout << "rehash 1"<<std::endl;
	
	
	
	//std::cout << "rehash 2"<<std::endl;
	p = make_pair(key,21);
	//b.insert(p);
	*/
	
}