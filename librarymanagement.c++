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
	User(string Name, string ID, string Address, string Phonenumber, string Email, string Username, string Password): 
	Name(Name), ID(ID), Address(Address), Phonenumber(Phonenumber), Email(Email), Username(Username), Password(Password){
		Fine = 0;
		Status = true;
	};
	string getName() const { return Name; }
	string getID() const { return ID; }
	string getAddress() const { return Address; }
	string getPhonenumber() const { return Phonenumber; }
	string getEmail() const { return Email; }
	string getUsername() const { return Username; }
    string getPassword() const { return Password; }
	void setAddress(const string Address) {
        this-> Address = Address; 
        }
	void setPhonenumber(const string Phonenumber) {
        this-> Phonenumber = Phonenumber; 
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
		friend class Admin; //Chi cho Admin truy cap vao private
};

class Admin: public User{
	private:
	Admin(string Name, string ID, string Address,string Phonenumber, string Email, string Username, string Password)
    : User(Name, ID, Address, Phonenumber, Email, Username, Password) {};
	friend class LibrarySystem; //Chi cho Librarysystem truy cap vao private
};
class LibrarySystem{
	private:
		vector<Admin> Admins;
		vector<User> Users;
		vector<Book> Books;
	//Ham tao Admin chi co LibrarySystem moi tao duoc -> encapsulation
	void CreateAdmin(string Name, string ID, string Address, string Phonenumber, string Email, string Username, string Password){
        Admins.push_back(Admin(Name, ID, Address, Phonenumber, Email, Username, Password));
    }
	//Kiem tra User co ton tai hay chua
	bool UserCheck(const string& Username){
		for(const auto& user : Users){ //range-based for loop
			if(user.getUsername() == Username){
				return true;
			}
		}
		return false;
	}
	//Dang ky cho User
	bool UserSignUp(string Name, string ID, string Address, string Phonenumber, string Email, string Username, string Password){
		if(UserCheck(Username)){
			return false;
		}
		Users.push_back(User(Name, ID, Address, Phonenumber, Email, Username, Password));
        return true;
	}
	//Dang nhap
	bool AdminLogin(const string& AdminName, const string& Password){
		for(const auto& admin : Admins){ //range-based for loop
			if(admin.getUsername() == AdminName && admin.getPassword() == Password){
				return true;
			}
		}
		return false;
	}
	bool UserLogin(const string& Username, const string& Password){
		for(const auto& user : Users){ //range-based for loop
			if(user.getUsername() == Username && user.getPassword() == Password){
				return true;
			}
		}
		return false;
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
     while (choice_1 <= 2);}