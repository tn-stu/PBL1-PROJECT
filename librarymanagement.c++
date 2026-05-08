#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <iomanip>
using namespace std;
class Book {
private:
	string id;
	string title;
public:
	Book(string id, string title) : id(id), title(title) {}
};
class User{
	protected:
		string Nameacount, password, fullname,phonenumber,email;
	public:	
	User(string Nameacount, string password, string fullname, string phonenumber, string email): 
	Nameacount(Nameacount), password(password), fullname(fullname), phonenumber(phonenumber), email(email){};
	string getName() const{ return Nameacount;}
	string getPassword() const{return password;}
	string getFullname() const{return fullname;}
	string getPhonenumber() const{return phonenumber;}
	string getEmail() const{return email;}
	static string FILENAMEUSER;
};
class Admin: public User{
	public:
	Admin(string Nameacount, string password,string fullname, string phonenumber, string email): 
	User(Nameacount, password, fullname, phonenumber, email){};
	static string FILENAMEADMIN;
};
class Librarysystem{
	private:
		vector<Admin> Admins;
		vector<User> Users;
	public:
	void Adminaccount(const Admin& a){
		Admins.push_back(a);}
	//kiem tra tai khoan admin da ton tai chua
	bool CheckAdmin(const string& nameadmin, const string& password){
		for (const auto& admin : Admins) {
			if (admin.getName() == nameadmin && admin.getPassword() == password) {
				return true;
			}
		}
		return false;
	}
};
string Admin::FILENAMEADMIN = "admin.txt";
string User::FILENAMEUSER = "user.txt";

int main(){
	Librarysystem l;
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
			if (l.CheckAdmin(nameadmin, password)) {
				cout << "Dang nhap admin thanh cong!" << endl;
				cout<<"=====       =====  ========  =====     ==  ===     ==="<<endl;
	    cout<<"======     ======  ========  ======    ==  ===     ==="<<endl;
	    cout<<"=== ===   === ===  ===       === ===   ==  ===     ==="<<endl;
	    cout<<"===  === ===  ===  ========  ===  ===  ==  ===     ==="<<endl;
	    cout<<"===   =====   ===  ========  ===   === ==  ===     ==="<<endl;
	    cout<<"===    ===    ===  ===       ===    =====  ===     ==="<<endl;
	    cout<<"===     =     ===  ========  ===     ====  ====   ===="<<endl;
	    cout<<"===           ===  ========  ===      ===   ========= "<<endl;
	    cout<<"======================================================"<<endl;
	    cout<<"||1.Dang ky thong tin sinh vien                     ||"<<endl;
	    cout<<"||__________________________________________________||"<<endl;
        cout<<"||2.Chinh sua thong tin sinh vien                   ||"<<endl;
	    cout<<"||__________________________________________________||"<<endl;
	    cout<<"||3.Xem danh sach sinh vien                         ||"<<endl;
    	cout<<"||__________________________________________________||"<<endl;
	    cout<<"||4.Xem danh sach cac nhom hien tai                 ||"<<endl;
	    cout<<"||__________________________________________________||"<<endl;
        cout<<"||5.Tuy chinh thuat toan                            ||"<<endl;
	    cout<<"||__________________________________________________||"<<endl;
        cout<<"||6. Chay lai he thong                              ||"<<endl;
	    cout<<"||__________________________________________________||"<<endl;
	    cout<<"||7.Thoat he thong                                  ||"<<endl;
	    cout<<"======================================================"<<endl;
        cout<<"Lua chon cua ban la: ";
        cin >> choice;
		if (choice == 1){}
			} else {
				cout << "Sai tai khoan hoac mat khau admin!" << endl;
			};
		}
		else if (choice==2){
			string nameuser, password;
			cin.ignore();
			cout<<"Ten dang nhap nguoi dung: ";getline(cin, nameuser);
			cout<<endl;
			cout<<"Mat khau nguoi dung: ";getline(cin, password);

		}
			
		}
     while (choice != 7);}