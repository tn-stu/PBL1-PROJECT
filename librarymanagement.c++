#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <iomanip>
using namespace std;

class Book{
	private:
	    string BookName;
	    string Author;
	    int Quantity;
	public:
	    Book(string BookName, string Author, int Quantity): BookName(BookName), Author(Author), Quantity(Quantity){}
		string getBookName() const{ return BookName; }
		string getAuthor() const { return Author; }
		int getQuantity() const { return Quantity; }
		void setQuantity(const int Quantity){
			this->Quantity = Quantity;
	}
};
class User{
	protected:
		string Name;
		string ID;
		string Address;
		string Phonenumber;
		string Email;

		string Username;
		string Password;

		vector<string> BorrowedBook;
		double Fine;
		bool Status;
	public:	
	User(string Name, string ID, string Address, string Email, string Username, string Password): Name(Name), ID(ID), Address(Address), Email(Email), Username(Username), Password(Password){
		Fine = 0;
		Status = true;
	};
	string getName() const { return Name; }
	string getID() const { return ID; }
	string getAddress() const { return Address; }
	string getEmail() const { return Email; }
	string getUsername() const { return Username; }
    string getPassword() const { return Password; }
	void setAddress(const string Address) {
        this-> Address = Address; 
        }
	void setEmail(const string Email) {
        this-> Email = Email; 
        }
	void setUsername(const string Username) {
        this-> Username = Username; 
        }
	void setPassword(const string Password) {
        this-> Password = Password; 
        }
		friend class Admin;
};

class Admin: public User{
	public:
	Admin(string Name, string ID, string Address, string Email, string Username, string Password)
    : User(Name, ID, Address, Email, Username, Password) {};
};
class Librarysystem{
	private:
		vector<Admin> Admins;
		vector<User> Users;
	void Adminaccount(const Admin& a){
		Admins.push_back(a);
	}
};
int main(){
    int choice_1, choice_2, choice_3, choice_4;
    do {
		cout<<"=====       =====  ========  =====     ==  ===     ==="<<endl;
	    cout<<"======     ======  ========  ======    ==  ===     ==="<<endl;
	    cout<<"=== ===   === ===  ===       === ===   ==  ===     ==="<<endl;
	    cout<<"===  === ===  ===  ========  ===  ===  ==  ===     ==="<<endl;
	    cout<<"===   =====   ===  ========  ===   === ==  ===     ==="<<endl;
	    cout<<"===    ===    ===  ===       ===    =====  ===     ==="<<endl;
	    cout<<"===     =     ===  ========  ===     ====  ====   ===="<<endl;
	    cout<<"===           ===  ========  ===      ===   ========= "<<endl;
	    cout<<"------------------------------------------------------"<<endl;
	    cout<<"======================================================"<<endl;
	    cout<<"||1.Dang nhap voi tu cach Admin                     ||"<<endl;
		cout<<"||--------------------------------------------------||"<<endl;
        cout<<"||2.Dang nhap voi tu cach User                      ||"<<endl;  
		cout<<"||--------------------------------------------------||"<<endl;
		cout<<"||3.Dang ky tai khoan                               ||"<<endl; 
		cout<<"||--------------------------------------------------||"<<endl;   
		cout<<"||4.Thoat                                           ||"<<endl;              
	    cout<<"======================================================"<<endl;
        cout<<"Lua chon cua ban: ";
        cin >> choice_1;
        if (choice_1 == 1){
			string AdminName, Password;
			cin.ignore();
			cout<<"Ten dang nhap: ";
			getline(cin, AdminName);
			cout<<"Mat khau: ";
			getline(cin, Password);
		}
	if (choice_1 == 2){
			string Username, Password;
			cin.ignore();
			cout<<"Ten dang nhap: ";getline(cin, Username);
			cout<<"Mat khau: ";getline(cin, Password);
		}
	}
     while (choice_1 != 7);}