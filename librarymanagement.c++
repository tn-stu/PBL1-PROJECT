#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <iomanip>
using namespace std;
class User{
	protected:
		string Name, password;
	public:	
	User(string Name, string password): Name(Name), password(password){};
	string getName() const{ return Name; }
	string getPassword() const{ return password; }
};
class Admin: public User{
	public:
	Admin(string Name, string password): User(Name, password){};
};
class Lybrarysystem{
	private:
		vector<Admin> Admins;
		vector<User> Users;
	void Adminaccount(const Admin& a){
		Admins.push_back(a);
	}
};
int main(){
    int choice;
    
    do {
       
	    cout<<"=================================================="<<endl;
	    cout<<"||1.Dang nhap voi tu cach la admin              ||"<<endl;
		cout<<"||----------------------------------------------||"<<endl;
        cout<<"||2.Dang nhap voi tu cach la nguoi dung         ||"<<endl;                          
	    cout<<"=================================================="<<endl;
        cout<<"Lua chon cua ban la: ";
        cin >> choice;
        if (choice ==1){
			string nameadmin, password;
			cin.ignore();
			cout<<"Ten dang nhap admin: ";getline(cin, nameadmin);
			cout<<endl;
			cout<<"Mat khau admin: ";getline(cin, password);
			
		}}
     while (choice != 7);}