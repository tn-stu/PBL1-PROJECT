#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <iomanip>
using namespace std;
class Book{
private:
	string id;
	string bookname;
	int quantity;
public:
	Book(string id, string bookname, int quantity) : id(id), bookname(bookname), quantity(quantity) {};
	
};
class User{
	protected:
		string username, password, fullname, phonenumber, email;
	public:	
	User(string username, string password, string fullname, string phonenumber, string email): 
	username(username), password(password), fullname(fullname), phonenumber(phonenumber), email(email){};
	string getName() const{ return username;}
	string getPassword() const{return password;}
	string getFullname() const{return fullname;}
	string getPhonenumber() const{return phonenumber;}
	string getEmail() const{return email;}
};
class Admin: public User{
	public:
	Admin(string username, string password,string fullname, string phonenumber, string email): 
	User(username, password, fullname, phonenumber, email){};
};
class Librarysystem{
	private:
		vector<Admin> Admins;
		vector<User> Users;
		vector<Book> Books;
		static string FILENAMEUSER;
		static string FILENAMEADMIN;
		static string FILENAMEBOOK;
	public:
	void addAdmin(const Admin& ad){
		Admins.push_back(ad);}
	//check account để login
	bool CheckAdmin(const string& nameadmin, const string& password){
		for (const auto& admin : Admins){ //Range-based for loop
			if (admin.getName() == nameadmin && admin.getPassword() == password) {
				return true;
			}
		}
		return false;
	}
	bool CheckUser(const string& nameuser, const string& password){
		for (const auto& user : Users){ //Range-based for loop
			if (user.getName() == nameuser && user.getPassword() == password) {
				return true;
			}
		}
		return false;
	}
	bool Add_New_Account(const string& nameuser, const string& password, const string& fullname, const string& phonenumber, const string& email){
		//check account để sign up
		for (const auto& user : Users){
			if (user.getName() == nameuser){
				cout << "Ten dang nhap da ton tai. Vui long chon ten dang nhap khac!" << endl;
				return false;
			}
			if (user.getEmail() == email || user.getPhonenumber() == phonenumber){
				cout << "Tai khoan da ton tai. Vui long nhap lai thong tin!" << endl;
				return false;
			}
		}
		if(nameuser.empty() || password.empty() || fullname.empty() || phonenumber.empty() || email.empty()){
			cout << "Vui long dien day du thong tin!" << endl;
			return false;
			}
		Users.push_back(User(nameuser, password, fullname, phonenumber, email));
		return true;
	}
	void loadFile_Admin() {
		ifstream inFile(FILENAMEADMIN);
		if (!inFile){
			cout << "Loi mo file admin!" << endl;
			return;
		}
		string line;
		while (getline(inFile, line)){ // đọc từng dòng trong file rồi lưu vào line
			stringstream ss(line); // biến chuỗi line thành luồng nhập để có thể tách dữ liệu
			string nameadmin, password, fullname, phonenumber, email;
			// đọc dữ liệu từ ss và tách bằng dấu '|'
			getline(ss, nameadmin, '|');
			getline(ss, password, '|');
			getline(ss, fullname, '|');
			getline(ss, phonenumber, '|');
			getline(ss, email, '|');
			// tạo object Admin rồi thêm vào vector Admins
			Admins.push_back(Admin(nameadmin, password, fullname, phonenumber, email));
		}
		inFile.close();
	}
	void loadFile_User(){
		ifstream inFile(FILENAMEUSER);
		if(!inFile){
			cout << "Loi mo file nguoi dung!" << endl;
			return;
		}
		string line;
		while(getline(inFile, line)){
			stringstream ss(line);
			string nameuser, password, fullname, phonenumber, email;
			getline(ss, nameuser, '|');
			getline(ss, password, '|');
			getline(ss, fullname, '|');
			getline(ss, phonenumber, '|');
			getline(ss, email, '|');
			Users.push_back(User(nameuser, password, fullname, phonenumber, email));
		}
		inFile.close();
	}
	void loadFile_Book(){
		ifstream inFile(FILENAMEBOOK);
		if(!inFile){
			cout << "Loi mo file sach!" << endl;
			return;
		}
		string line;
		while(getline(inFile,line)){
			stringstream ss(line);
			string id, bookname;
			int quantity;
			getline(ss, id, '|');
			getline(ss, bookname, '|');
			ss >> quantity;
			Books.push_back(Book(id, bookname, quantity));
		}
		inFile.close();
	}
	void saveFile_User() {
		ofstream outFile(FILENAMEUSER);
		if (!outFile) {
			cout << "Loi mo file nguoi dung!" << endl;
			return;
		}
		for (const auto& user : Users) {
			outFile << user.getName() << "," << user.getPassword() << "," << user.getFullname() << "," << user.getPhonenumber() << "," << user.getEmail() << endl;
		}
		outFile.close();
	}
};

string Librarysystem::FILENAMEADMIN = "admin.txt";
string Librarysystem::FILENAMEUSER = "user.txt";
string Librarysystem::FILENAMEBOOK = "book.txt";

int main(){
	Librarysystem lib;
	lib.loadFile_User();
	lib.loadFile_Admin();
    int choice1,choice2,choice3,choice4;
    
    do {
        cout<<"==========================================="<<endl;
	    cout<<"||1.Dang nhap voi tu cach Admin          ||"<<endl;
		cout<<"||---------------------------------------||"<<endl;
        cout<<"||2.Dang nhap voi tu cach User           ||"<<endl;
		cout<<"||---------------------------------------||"<<endl;
        cout<<"||3.Dang ky                              ||"<<endl;  
		cout<<"||---------------------------------------||"<<endl;
        cout<<"||4.Thoat                                ||"<<endl;                          
	    cout<<"==========================================="<<endl;
        cout<<"Lua chon cua ban la: ";
        cin >> choice1;
		//Dang nhap tk admin
        if (choice1 == 1){
			string name_admin, password_admin;
			cin.ignore();
			cout<<"Ten dang nhap: ";getline(cin, name_admin);
			cout<<"Mat khau: ";getline(cin, password_admin);
			if(lib.CheckAdmin(name_admin, password_admin)) {
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
        	cout<<"||5.Xem danh sach tat ca tai khoan nguoi dung       ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
        	cout<<"||6.Xoa tai khoan vi pham                           ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||7.Xem danh sach sach dang bi muon qua han         ||"<<endl; 
			cout<<"||--------------------------------------------------||"<<endl;
			cout<<"||8.Duyet yeu cau muon sach                         ||"<<endl; 
			cout<<"||--------------------------------------------------||"<<endl;
			cout<<"||9.Xac nhan nguoi dung tra sach                    ||"<<endl;
			cout<<"||--------------------------------------------------||"<<endl;
			cout<<"||10.Thoat                                          ||"<<endl;
	    	cout<<"======================================================"<<endl;
        	cout<<"Lua chon cua ban la: ";
        	cin >> choice2;
				if (choice2 == 1){}
			} 
			while (choice2 != 10);}
			else {
				cout << "Sai tai khoan hoac mat khau!" << endl;};
		}
		else if (choice1 == 2){
			string nameuser, passworduser;
			cin.ignore();
			cout<<"Ten dang nhap: ";getline(cin, nameuser);
			cout<<endl;
			cout<<"Mat khau: ";getline(cin, passworduser);
			if(lib.CheckUser(nameuser, passworduser)) {
				cout << "Dang nhap nguoi thanh cong!" << endl;
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
	    	cout<<"||1.Xem danh sach tat ca loai sach hien co          ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
        	cout<<"||2.Tim sach theo ten hoac ID                       ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||3.Gui yeu cau muon sach                           ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
        	cout<<"||4.Xem danh sach sach dang muon va ngay phai tra   ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
        	cout<<"||5.Doi mat khau                                    ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||6.Chinh sua thong tin ca nhan                     ||"<<endl;
			cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||7.Thoat                                           ||"<<endl;
	    	cout<<"======================================================"<<endl;
        	cout<<"Lua chon cua ban la: ";
        	cin >> choice3;
			if (choice3 == 1){}
			} while (choice3 != 7);}
			else {
				cout << "Sai tai khoan hoac mat khau!" << endl;}
		}
		else if (choice1==3){
			string nameuser, passworduser, fullname, phonenumber, email;
			cin.ignore();
			bool value = false;
			while (!value) {
			cout<<"Ten dang nhap: ";getline(cin, nameuser);
			cout<<endl;
			cout<<"Mat khau: ";getline(cin, passworduser);
			cout<<endl;
			cout<<"Ho va ten: "; getline(cin, fullname);
			cout<<endl;
			cout<<"So dien thoai: "; getline(cin, phonenumber);
			cout<<endl;
			cout<<"Email: "; getline(cin, email);
			if (lib.Add_New_Account(nameuser, passworduser, fullname, phonenumber, email)){
			cout << "Dang ky tai khoan thanh cong!" << endl;
			lib.saveFile_User();
		    value = true;}
		}
	}
			
	 	else {
            cout << "Lua chon khong hop le, vui long chon lai." << endl;
        }}
     while (choice1 != 4);}