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
	public:
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
	LibrarySystem lib;
	// Tao tai khoan Admin mac dinh de test 
    lib.CreateAdmin("Admin", "000000", "Da Nang", "0123456789", "admin@gmail.com", "admin", "123");
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
			if(lib.AdminLogin(AdminName,Password)){
				cout << "Dang nhap thanh cong!" << endl;
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
	    cout<<"||1.Them sach moi                                   ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
        cout<<"||2.Sua thong tin sach                              ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
	    cout<<"||3.Xoa sach                                        ||"<<endl;
    	cout<<"||--------------------------------------------------||"<<endl;
	    cout<<"||4.Thong ke luong sach hien co                     ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
        cout<<"||5.Xem danh sach tai khoan User                    ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
        cout<<"||6.Xoa tai khoan User vi pham                      ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
	    cout<<"||7.Thong ke sach dang bi muon qua han              ||"<<endl; 
		cout<<"||--------------------------------------------------||"<<endl;
		cout<<"||8.Duyet yeu cau muon sach                         ||"<<endl; 
		cout<<"||--------------------------------------------------||"<<endl;
		cout<<"||9.Xac nhan nguoi dung tra sach                    ||"<<endl;
		cout<<"||--------------------------------------------------||"<<endl;
		cout<<"||10.Thoat                                          ||"<<endl;
	    cout<<"======================================================"<<endl;
        cout<<"Lua chon cua ban la: ";
        cin >> choice_2;
	            }
				while(choice_2 < 1);
			}
			else {
				cout << "Sai tai khoan Admin!" << endl;
			}
		}
	if (choice_1 == 2){
			string Username, Password;
			cin.ignore();
			cout<<"Ten dang nhap: ";
			getline(cin, Username);
			cout<<"Mat khau: ";
			getline(cin, Password);
			if(lib.UserLogin(Username,Password)){
				cout << "Dang nhap thanh cong!" << endl;
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
	    cout<<"||1.Thong ke cac loai sach hien co                  ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
        cout<<"||2.Tim sach theo ten hoac ID                       ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
	    cout<<"||3.Gui yeu cau muon sach                           ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
        cout<<"||4.Danh sach sach dang muon va ngay tra            ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
        cout<<"||5.Doi mat khau                                    ||"<<endl;
	    cout<<"||--------------------------------------------------||"<<endl;
	    cout<<"||6.Chinh sua thong tin ca nhan                     ||"<<endl;
		cout<<"||--------------------------------------------------||"<<endl;
	    cout<<"||7.Thoat                                           ||"<<endl;
	    cout<<"======================================================"<<endl;
        cout<<"Lua chon cua ban la: ";
        cin >> choice_3;
				}
		        while(choice_3 < 1);
			}
			else{
				cout << "Sai tai khoan User!" << endl;
			}
		}
	}
     while (choice_1 <= 2);}