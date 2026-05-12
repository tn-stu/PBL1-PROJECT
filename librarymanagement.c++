#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <iomanip>
#include <algorithm>// dung de su dung remove
using namespace std;
class Book {
private:
	string id;
	string bookname;
	string quantity;
public:
	Book(string id, string bookname, string quantity) : id(id), bookname(bookname), quantity(quantity) {};
	string getID() const { return id; }
	string getBookname() const { return bookname; }
	string getQuantity() const { return quantity; }
	void setID(const string id) { this->id = id;}
	void setBookname(const string bookname) { this->bookname = bookname;}
	void setQuantity(const string quantity) { this->quantity = quantity;}
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
};
class Admin: public User{
	public:
	Admin(string Nameacount, string password,string fullname, string phonenumber, string email): 
	User(Nameacount, password, fullname, phonenumber, email){};
};
class Librarysystem{
	private:
		vector<Admin> Admins;
		vector<User> Users;
		vector<Book> Books;
		static string FILENAMEUSER;
		static string FILENAMEADMIN;
		static string FILENAMEBOOKS;
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
	bool CheckUser(const string& nameuser, const string& password){
		for (const auto& user : Users) {
			if (user.getName() == nameuser && user.getPassword() == password) {
				return true;
			}
		}
		return false;
	}
	bool Add_New_Account(const string& nameuser, const string& password, const string& fullname, const string& phonenumber, const string& email){
		for (const auto& user : Users) {
			if (user.getName() == nameuser) {
				cout << "Vui long chon ten dang nhap khac!" << endl;
				return false;
			}
			if (user.getEmail() == email || user.getPhonenumber() == phonenumber) {
				cout << "Tai khoan da ton tai. Vui long nhap lai thong tin!" << endl;
				return false;
			}
		}
		if(nameuser.empty() || password.empty() || fullname.empty() || phonenumber.empty() || email.empty()) {
			cout << "Vui long dien day du thong tin!" << endl;
			return false;
			}
		Users.push_back(User(nameuser, password, fullname, phonenumber, email));
		return true;
	}
	//them sach moi
	void Add_new_book(const string& id, const string& bookname, const string& quantity){
		Books.push_back(Book(id, bookname, quantity));
	}
	//tim sach theo ID
	Book* Find_book_by_id(const string& id){
		for (auto& book : Books) {
			if (book.getID() == id) {
				return &book;
			}
		}
		return nullptr;
	}
	//xoa sach (ni chua hoc, chua hieu)
	void Delete_book(const string& id){
		auto it = remove_if(Books.begin(), Books.end(), [&id](const Book& book) {
			return book.getID() == id;
		});
	    if (it != Books.end()) {
			Books.erase(it, Books.end());
			cout << "Da xoa sach co ID: " << id << endl;
		} else {
			cout << "Khong tim thay sach co ID: " << id << endl;
		}
	}
	void Danh_sach_sach_hien_co(){
		if(Books.empty()){
            cout<<"Danh sach rong"<<endl; 
            return;}   
        cout << left;
        cout<<"|"<<setw(15)<<"ID SACH"
            <<"|"<<setw(10)<<"TEN SACH"
            <<"|"<<setw(20)<<"SO LUONG"<<"|"<<endl;
        for(auto s: Books){
            cout<<"|"<<setw(15)<<s.getID()
                <<"|"<<setw(10)<<s.getBookname()
                <<"|"<<setw(20)<<s.getQuantity()<<"|"<<endl;}}
	

	void loadFile_Books() {
		ifstream inFile(FILENAMEBOOKS);
		string line;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string id, bookname, quantity;
			getline(ss, id,',');
			getline(ss, bookname,',');
			getline(ss, quantity);
			Books.push_back(Book(id, bookname, quantity));
		}
		inFile.close();
	}
	void saveFile_Books() {
		ofstream outFile(FILENAMEBOOKS);
		for (const auto& book : Books) {
			outFile << book.getID() << "," << book.getBookname() << "," << book.getQuantity() << endl;}
		outFile.close();
	}
	void loadFile_Admin() {
		ifstream inFile(FILENAMEADMIN);
		string line;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string nameadmin, password, fullname, phonenumber, email;
			getline(ss, nameadmin,',');
			getline(ss, password,',');
			getline(ss, fullname,',');
			getline(ss, phonenumber,',');
			getline(ss, email);
			Admins.push_back(Admin(nameadmin, password, fullname, phonenumber, email));
		}
		inFile.close();
	}
	void loadFile_User (){
		ifstream inFile(FILENAMEUSER);
		string line;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string nameuser, password, fullname, phonenumber, email;
			getline(ss, nameuser,',');
			getline(ss, password,',');
			getline(ss, fullname,',');
			getline(ss, phonenumber,',');
			getline(ss, email);
			Users.push_back(User(nameuser, password, fullname, phonenumber, email));
		}
		inFile.close();
	}
	void saveFile_User() {
		ofstream outFile(FILENAMEUSER);
		for (const auto& user : Users) {
			outFile << user.getName() << "," << user.getPassword() << "," << user.getFullname() << "," << user.getPhonenumber() << "," << user.getEmail() << endl;
		}
		outFile.close();
	}
};
string Librarysystem::FILENAMEADMIN = "admin.txt";
string Librarysystem::FILENAMEUSER = "user.txt";
string Librarysystem::FILENAMEBOOKS = "books.txt";
int main(){
	Librarysystem l;
	l.loadFile_User();
	l.loadFile_Admin();
	l.loadFile_Books();
    int choice1,choice2,choice3,choice4;
    
    do {
        cout<<"==========================================="<<endl;
	    cout<<"||1.Dang nhap voi tu cach la admin       ||"<<endl;
		cout<<"||---------------------------------------||"<<endl;
        cout<<"||2.Dang nhap voi tu cach la nguoi dung  ||"<<endl;
		cout<<"||---------------------------------------||"<<endl;
        cout<<"||3.Dang ky tai khoan                    ||"<<endl;  
		cout<<"||---------------------------------------||"<<endl;
        cout<<"||4.Thoat                                ||"<<endl;                          
	    cout<<"==========================================="<<endl;
        cout<<"Lua chon cua ban la: ";
        cin >> choice1;
		//Dang nhap tk admin
        if (choice1 ==1){
			string name_admin, password_admin;
			cin.ignore();
			cout<<"Ten dang nhap admin: ";getline(cin, name_admin);
			cout<<"Mat khau admin: ";getline(cin, password_admin);
			if(l.CheckAdmin(name_admin, password_admin)) {
				cout << "Dang nhap admin thanh cong!" << endl;
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
				if (choice2 == 1){
					string id, tensach;
					string soluong;
					cin.ignore();
					cout << "Nhap ID sach:"; getline(cin, id);
					cout << "Nhap ten sach:"; getline(cin, tensach);
					cout << "Nhap so luong:"; getline(cin, soluong);
					l.Add_new_book(id, tensach, soluong);
					cout << "Da them sach moi thanh cong!" << endl;
					l.saveFile_Books();
				}
				else if (choice2==2){
					string id;
					cout << "Nhap ID sach can sua:"; 
					cin.ignore(); 
					getline(cin, id);
					Book* book = l.Find_book_by_id(id);
					if (book!=nullptr) {
						string bookname;
						string quantity;
						cout << "Nhap ten sach moi:"; getline(cin, bookname);
						cout << "Nhap so luong moi:"; getline(cin, quantity);
						book->setBookname(bookname);
						book->setQuantity(quantity);
						cout << "Da cap nhat thong tin sach!" << endl;
						l.saveFile_Books();}
						else {
						cout << "Khong tim thay sach voi ID da nhap!" << endl;}
				}
				else if (choice2==3){
					string id;
					cout << "Nhap ID sach can xoa:"; 
					cin.ignore(); 
					getline(cin, id);
					Book* book = l.Find_book_by_id(id);
					if (book == nullptr) {
						cout << "Khong tim thay sach voi ID da nhap!" << endl;
					}
					else {
					l.Delete_book(id);
					l.saveFile_Books();
				}}
				else if(choice2 == 4){
					l.Danh_sach_sach_hien_co();
				}
				else if(choice2 == 5){}
				else if(choice2 == 6){}
				else if(choice2 == 7){}
				else if(choice2 == 8){}
				else if(choice2 == 9){}
			} while (choice2 != 10);}
			else {
				cout << "Sai tai khoan hoac mat khau admin!" << endl;};
		}
		else if (choice1==2){
			string nameuser, passworduser;
			cin.ignore();
			cout<<"Ten dang nhap nguoi dung: ";getline(cin, nameuser);
			cout<<"Mat khau nguoi dung: ";getline(cin, passworduser);
			if(l.CheckUser(nameuser, passworduser)) {
				cout << "Dang nhap nguoi dung thanh cong!" << endl;
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
        	cout<<"||2.Tim sach theo ID hoac ten                       ||"<<endl;
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
				cout << "Sai tai khoan hoac mat khau nguoi dung!" << endl;}
		}
		else if (choice1==3){
			string nameuser, passworduser, fullname, phonenumber, email;
			cin.ignore();
			bool value = false;
			while (!value) {
			cout<<"Ten dang nhap nguoi dung: ";getline(cin, nameuser);
			cout<<endl;
			cout<<"Mat khau nguoi dung: ";getline(cin, passworduser);
			cout<<endl;
			cout<<"Ho va ten: "; getline(cin, fullname);
			cout<<endl;
			cout<<"So dien thoai: "; getline(cin, phonenumber);
			cout<<endl;
			cout<<"Email: "; getline(cin, email);
			if (l.Add_New_Account(nameuser, passworduser, fullname, phonenumber, email)){
			cout << "Dang ky tai khoan thanh cong!" << endl;
			l.saveFile_User();
		    value = true;}
		}
	}
			
	 	else {
            cout << "Lua chon khong hop le, vui long chon lai." << endl;
        }}
     while (choice1 != 4);}