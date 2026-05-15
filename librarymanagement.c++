#include <iostream>
#include <limits>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <iomanip>
#include <algorithm>// dung de su dung remove
using namespace std;
struct Date {
    int d, m, y;
};

class Book {
protected:
	string id;
	string bookname;
	int quantity;
public:
	Book(const string& id, const string& bookname, int quantity) : id(id), bookname(bookname), quantity(quantity) {};
	string getID() const { return id; }
	string getBookname() const { return bookname; }
	int getQuantity() const { return quantity; }
	void setID(const string& id) { this->id = id;}
	void setBookname(const string& bookname) { this->bookname = bookname;}
	void setQuantity(const int quantity) { 
		if(quantity >= 0){
            this->quantity = quantity;
		}
		else{
			cout << "So luong sach khong hop le!" << endl;
		}
	}
};
class BorrowBook:public Book{
	private:
	string username;
	Date borrowdate;
	Date returndate;
	bool status;
	public:
	BorrowBook(const string& id, const string& bookname, int quantity, const string& username, const Date& borrowdate, const Date& returndate = {0,0,0}):
	Book(id, bookname, quantity), username(username), borrowdate(borrowdate), returndate(returndate){};
	string getUsername() const { return username; }
	Date getBorrowDate() const { return borrowdate; }
	Date getReturnDate() const { return returndate; }
	void setUsername(const string& username) { this->username = username; }
	void setBorrowDate(const Date& borrowdate) { this->borrowdate = borrowdate; }
	void setReturnDate(const Date& returndate) { this->returndate = returndate; }
};
class User{
	protected:
		string username, password, fullname,phonenumber,email;
		bool locked;
	public:	
	User(const string& username, const string& password, const string& fullname, const string& phonenumber, const string& email, bool locked = false): 
	username(username), password(password), fullname(fullname), phonenumber(phonenumber), email(email), locked(locked){};
	string getName() const{return username;}
	string getPassword() const{return password;}
	string getFullname() const{return fullname;}
	string getPhonenumber() const{return phonenumber;}
	string getEmail() const{return email;}
	bool isLocked() const{return locked;} //kiểm tra khóa tài khoản
	void setFullname(const string& fullname){ this->fullname = fullname; }
	void setPhonenumber(const string& phonenumber){ this->phonenumber = phonenumber; }
	void setEmail(const string& email){ this->email = email; }
	void setPassword(const string& password){ this->password = password; }
	void LockAcc(){locked = true;}
	void UnlockAcc(){locked = false;}
};
class Admin: public User{
	public:
	Admin(const string& username, const string& password, const string& fullname, const string& phonenumber, const string& email): 
	User(username, password, fullname, phonenumber, email){};
};
class Librarysystem{
	private:
		vector<Admin> Admins;
		vector<User> Users;
		vector<Book> Books;
		vector<BorrowBook> BorrowBooks;
		static string FILENAMEUSER;
		static string FILENAMEADMIN;
		static string FILENAMEBOOKS;
		static string FILENAMEBORROWBOOK;
	public:
	//ham kiem tra ngay thang nam 
	bool isLeap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);}
	int daysInMonth(int m, int y) {
    if (m == 2){
		if (isLeap(y))
		{return 29;}
		else{
		return 28;
		}}
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;}
//ham tính số ngày từ 1/1/0000 đến ngày hiện tại để so sánh ngày trả sách và ngày hiện tại xem có quá hạn hay không
	int toDays(Date date) {
    int days = date.y * 365;
    for (int i = 1; i < date.y; i++) {
        if (isLeap(i)) days++;}
    for (int i = 1; i < date.m; i++) {
        days += daysInMonth(i, date.y);}
    days += date.d;
    return days;}
// them Admin account
	void Adminaccount(const Admin& a){
		Admins.push_back(a);}
	//Check account để sign in
	bool CheckAdmin(const string& nameadmin, const string& password){
		for (const auto& admin : Admins) {
			if (admin.getName() == nameadmin && admin.getPassword() == password) {
				return true;
			}
		}
		return false;
	}
	bool CheckUser(const string& username, const string& password){
		for (const auto& user : Users) {
			if(user.getName() == username){
				if(user.isLocked()){
					cout << "Tai khoan da bi khoa do vi pham!" << endl;
					return false;
				}
				if(user.getPassword() == password){
					return true;
				}			
			    else{
				    cout << "Sai mat khau!" << endl;
				    return false;
				}
			}
		}
		cout << "Khong ton tai tai khoan!" << endl;
		return false;
	}
	//Sign up
	bool Add_New_Admin(const string& nameadmin, const string& password, const string& fullname, const string& phonenumber, const string& email){
		for (const auto& admin : Admins) {
			if (admin.getName() == nameadmin) {
				cout << "Ten dang nhap da ton tai. Vui long chon ten dang nhap khac!" << endl;
				return false;
			}
			if (admin.getEmail() == email) {
				cout << "Gmail da duoc dang ky. Vui long nhap lai thong tin!" << endl;
				return false;
			}
			if(admin.getPhonenumber() == phonenumber) {
				cout << "So dien thoai da duoc dang ky. Vui long nhap lai thong tin!" << endl;
				return false;
			}
		}
		if(nameadmin.empty() || password.empty() || fullname.empty() || phonenumber.empty() || email.empty()) {
			cout << "Vui long dien day du thong tin!" << endl;
			return false;
			}
		Admins.push_back(Admin(nameadmin, password, fullname, phonenumber, email));
		return true;
	}
	//Them User account
	bool Add_New_Account(const string& nameuser, const string& password, const string& fullname, const string& phonenumber, const string& email){
		for (const auto& user : Users) {
			if (user.getName() == nameuser) {
				cout << "Ten dang nhap da ton tai. Vui long chon ten dang nhap khac!" << endl;
				return false;
			}
			if (user.getEmail() == email) {
				cout << "Gmail da duoc dang ky. Vui long nhap lai thong tin!" << endl;
				return false;
			}
			if(user.getPhonenumber() == phonenumber) {
				cout << "So dien thoai da duoc dang ky. Vui long nhap lai thong tin!" << endl;
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
	//Lock tai khoan vi pham
	void Lock_User(const string& username){
		for(auto& user : Users){
			if(user.getName() == username){
				user.LockAcc();
				cout << "Da khoa tai khoan!" << endl;
				return;
			}
		}
		cout << "Khong tim thay tai khoan!" << endl;
	}
	//Unlock User
	void Unlock_User(const string& username){
		for(auto& user : Users){
			if(user.getName() == username){
			    user.UnlockAcc();
			    cout << "Da mo khoa tai khoan!" << endl;
			    return;
			}
		}
		cout << "Khong tim thay tai khoan!" << endl;
	}
	//Add new book
	bool Add_new_book(const string& id, const string& bookname, const int& quantity){
		if(id.empty() || bookname.empty() || quantity <= 0){
			cout << "Thong tin sach khong hop le. Vui long nhap lai!" << endl;
			return false;
		}
		for(const auto& book : Books){
			if(book.getID() == id){
				cout << "Sach da ton tai!" << endl;
				return false;
			}
		}
		Books.push_back(Book(id, bookname, quantity));
		return true;
	}
	//Find book
	Book* Find_book(const string& keyword){ //Ham tra ve dia chi cua sach tim duoc
		for (auto& book : Books) {
			if ((book.getID() == keyword)||(book.getBookname() == keyword)) {
				return &book;
			}
		}
		return nullptr;
	}
	//Delete book (ni chua hoc, chua hieu)
	void Delete_book(const string& keyword){
		auto it = remove_if(Books.begin(), Books.end(), [&keyword](const Book& book) {
			if(book.getID() == keyword||book.getBookname() == keyword) {
				return true;
			}
			return false;
		});
	   if (it != Books.end()) {
			Books.erase(it, Books.end());
			cout << "Da xoa sach : " << keyword << endl;
		} else {
			cout << "Khong tim thay sach: " << keyword << endl;
		}
	}
	//Chinh sua thong tin ca nhan
	void EditProfile(const string& username, const string& password){
		for(auto& user : Users){
			if(user.getName() == username && user.getPassword() == password){
				string fullname, phonenumber, email;
				cout << "Nhap ho va ten moi: "; getline(cin, fullname);
				cout << "Nhap so dien thoai moi: "; getline(cin, phonenumber);
				cout << "Nhap email moi: "; getline(cin, email);
				user.setFullname(fullname);
				user.setPhonenumber(phonenumber);
				user.setEmail(email);
				cout << "Cap nhat thong tin thanh cong!" << endl;
				return;
			}
		}
		cout << "Sai ten dang nhap hoac mat khau!" << endl;
	}
	//Doi password user account
	void ChangePass(const string& username, const string& oldpass, const string& newpass){
		for(auto& user : Users){
			if(user.getName() == username && user.getPassword() == oldpass){
				user.setPassword(newpass);
				cout << "Doi mat khau thanh cong!" << endl;
				return;
			}
		}
		cout << "Sai mat khau!" << endl;
	}
    //Hien thi danh sach sach hien co
	void BookList(){
		if(Books.empty()){
            cout<<"Danh sach rong"<<endl; 
            return;}   
        cout << left;
        cout<<"|"<<setw(15)<<"ID SACH"
            <<"|"<<setw(50)<<"TEN SACH"
            <<"|"<<setw(10)<<"SO LUONG"<<"|"<<endl;
        for(const auto& s: Books){
            cout<<"|"<<setw(15)<<s.getID()
                <<"|"<<setw(50)<<s.getBookname()
                <<"|"<<setw(10)<<s.getQuantity()
				<<"|"<<endl;}}
	//Addnew borrow book
	void AddBorrowBook(const string& id, const string& bookname, int quantity, const string& username, const Date& borrowdate, const Date& returndate){
		BorrowBooks.push_back(BorrowBook(id, bookname, quantity, username, borrowdate, returndate));}
	void loadFile_BorrowBook() {
		ifstream inFile(FILENAMEBORROWBOOK);
		if(!inFile){
		cout << "Khong the mo file borrowBook.txt!" << endl;
		return;
		}
		string line;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string id, bookname, username;
			int quantity;
			Date borrowdate, returndate;
			getline(ss, id,'|');
			getline(ss, bookname,'|');
			ss >> quantity; ss.ignore();
			getline(ss, username,'|');
			ss >> borrowdate.d; ss.ignore();
			ss >> borrowdate.m; ss.ignore();
			ss >> borrowdate.y; ss.ignore();
			ss >> returndate.d; ss.ignore();
			ss >> returndate.m; ss.ignore();
			ss >> returndate.y; ss.ignore();
			BorrowBooks.push_back(BorrowBook(id, bookname, quantity, username, borrowdate, returndate));
		}
		inFile.close();
	}
	void saveFile_BorrowBook() {
		ofstream outFile(FILENAMEBORROWBOOK);
		if(!outFile){
		cout << "Khong the ghi file borrowBook.txt!" << endl;
		return;
		}
		for (const auto& borrow : BorrowBooks) {
			outFile << borrow.getID() << "|" 
			        << borrow.getBookname() << "|" 
					<< borrow.getQuantity() << "|"
					<< borrow.getUsername() << "|"
					<< borrow.getBorrowDate().d << "/"
					<< borrow.getBorrowDate().m << "/"
					<< borrow.getBorrowDate().y<<"|"
					<< borrow.getReturnDate().d << "/"
					<< borrow.getReturnDate().m << "/"
					<< borrow.getReturnDate().y
					<< endl;
		}
		outFile.close();
	}
		
	
    void loadFile_Books() {
		ifstream inFile(FILENAMEBOOKS);
		if(!inFile){
        cout << "Khong the mo file books.txt!" << endl;
        return;
        }
		string line;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string id, bookname;
			int quantity;
			getline(ss, id,'|');
			getline(ss, bookname,'|');
			ss >> quantity;
			Books.push_back(Book(id, bookname, quantity));
		}
		inFile.close();
	}
	void saveFile_Books() {
		ofstream outFile(FILENAMEBOOKS);
		if(!outFile){
        cout << "Khong the ghi file books.txt!" << endl;
        return;
        }
		for (const auto& book : Books) {
			outFile << book.getID() << "|" << book.getBookname() << "|" << book.getQuantity() << endl;}
		outFile.close();
	}
	void loadFile_Admin() {
		ifstream inFile(FILENAMEADMIN);
		if(!inFile){
        cout << "Khong the mo file admin.txt!" << endl;
        return;
        }
		string line;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string nameadmin, password, fullname, phonenumber, email;
			getline(ss, nameadmin,'|');
			getline(ss, password,'|');
			getline(ss, fullname,'|');
			getline(ss, phonenumber,'|');
			getline(ss, email);
			Admins.push_back(Admin(nameadmin, password, fullname, phonenumber, email));
		}
		inFile.close();
	}
	void saveFile_Admin() {
		ofstream outFile(FILENAMEADMIN);
		if(!outFile){
            cout << "Khong the ghi file admin.txt!" << endl;
            return;
        }
		for (const auto& admin : Admins) {
			outFile << admin.getName() << "|" 
			        << admin.getPassword() << "|" 
					<< admin.getFullname() << "|" 
					<< admin.getPhonenumber() << "|" 
					<< admin.getEmail() << endl;
		}
		outFile.close();
	}
	void loadFile_User (){
		ifstream inFile(FILENAMEUSER);
		if(!inFile){
        cout << "Khong the mo file user.txt!" << endl;
        return;
        }
		string line;
		while (getline(inFile, line)) {
			stringstream ss(line);
			string nameuser, password, fullname, phonenumber, email;
			bool locked;
			getline(ss, nameuser,'|');
			getline(ss, password,'|');
			getline(ss, fullname,'|');
			getline(ss, phonenumber,'|');
			getline(ss, email, '|');
			ss >> locked;
			Users.push_back(User(nameuser, password, fullname, phonenumber, email, locked));
		}
		inFile.close();
	}
	void saveFile_User() {
		ofstream outFile(FILENAMEUSER);
		if(!outFile){
            cout << "Khong the ghi file user.txt!" << endl;
            return;
        }
		for (const auto& user : Users) {
			outFile << user.getName() << "|" 
			        << user.getPassword() << "|" 
			        << user.getFullname() << "|" 
			        << user.getPhonenumber() << "|" 
			        << user.getEmail() << "|"
					<< user.isLocked()
					<< endl;
		}
		outFile.close();
	}
	//Hien thi danh sach nguoi dung
	void UserList(){
		if(Users.empty()){
			cout << "Danh sach rong"<<endl;
			return;}
		cout << left; 
		cout << "|" << setw(15) << "TEN NGUOI DUNG"
             << "|" << setw(20) << "HO VA TEN"
             << "|" << setw(15) << "SO DIEN THOAI"
             << "|" << setw(30) << "EMAIL" 
			 << "|" << setw(10) << "STATUS"
			 << "|" << endl;
		for(const auto& user : Users){
        cout << "|" << setw(15) << user.getName()
             << "|" << setw(20) << user.getFullname()
             << "|" << setw(15) << user.getPhonenumber()
             << "|" << setw(30) << user.getEmail() 
			 << "|" << setw(10)
             << (user.isLocked() ? "LOCKED" : "ACTIVE") // toán tử [(condition) ? A : B] -> đúng lấy A sai lấy B
			 << "|" << endl;
	    }
    }
};
string Librarysystem::FILENAMEADMIN = "admin.txt";
string Librarysystem::FILENAMEUSER = "user.txt";
string Librarysystem::FILENAMEBOOKS = "books.txt";
string Librarysystem::FILENAMEBORROWBOOK = "borrowBook.txt";

int main(){
	Librarysystem l;
	l.loadFile_User();
	l.loadFile_Admin();
	l.loadFile_Books();
	l.loadFile_BorrowBook();
    int choice1, choice2, choice3, choice4;
    do {
        cout<<"==========================================="<<endl;
	    cout<<"||1.Dang nhap voi tu cach la Admin       ||"<<endl;
		cout<<"||---------------------------------------||"<<endl;
        cout<<"||2.Dang nhap voi tu cach la User        ||"<<endl;
		cout<<"||---------------------------------------||"<<endl;
        cout<<"||3.Dang ky tai khoan User               ||"<<endl;  
		cout<<"||---------------------------------------||"<<endl;
        cout<<"||4.Thoat                                ||"<<endl;                          
	    cout<<"==========================================="<<endl;
        cout<<"Lua chon cua ban: ";
        cin >> choice1;
		//Admin menu
        if (choice1 ==1){
			string name_admin, password_admin;
			cin.ignore();
			cout<<"Ten dang nhap: ";getline(cin, name_admin);
			cout<<"Mat khau: ";getline(cin, password_admin);
			if(l.CheckAdmin(name_admin, password_admin)) {
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
        	cout<<"||2.Cap nhat thong tin sach                         ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||3.Xoa sach khoi thu vien                          ||"<<endl;
    		cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||4.Hien thi danh sach sach                         ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||5.Duyet yeu cau muon sach                         ||"<<endl; 
			cout<<"||--------------------------------------------------||"<<endl;
			cout<<"||6.Xac nhan tra sach                               ||"<<endl; 
			cout<<"||--------------------------------------------------||"<<endl;
			cout<<"||7.Danh sach sach muon qua han                     ||"<<endl;
			cout<<"||--------------------------------------------------||"<<endl;
			cout<<"||8.Xem danh sach nguoi dung                        ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
        	cout<<"||9.Khoa tai khoan vi pham                          ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
			cout<<"||10.Mo khoa tai khoan User                         ||"<<endl;
			cout<<"||--------------------------------------------------||"<<endl;
			cout<<"||11.Them tai khoan admin                           ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
			cout<<"||12.Thoat                                          ||"<<endl;
	    	cout<<"======================================================"<<endl;
        	cout<<"Lua chon cua ban: ";
        	cin >> choice2;
			    //1.Them sach moi
				if (choice2 == 1){
					string id, bookname;
					int quantity;
					cin.ignore();
					cout << "Nhap ID sach: "; getline(cin, id);
					cout << "Nhap ten sach: "; getline(cin, bookname);
					cout << "Nhap so luong: "; cin >> quantity;
					if(l.Add_new_book(id, bookname, quantity)){
					    cout << "Da them sach moi thanh cong!" << endl;
						l.saveFile_Books();
					}
				}
				//2.Sua thong tin sach 
				else if (choice2==2){
					string keyword;
					cout << "Nhap ID hoac ten sach can cap nhat thong tin: "; 
					cin.ignore();
					getline(cin, keyword);
					Book* book = l.Find_book(keyword);
					if (book!=nullptr) {
						string bookname;
						int quantity;
						cout << "Nhap ten sach moi: "; getline(cin, bookname);
						cout << "Nhap so luong moi: "; cin >> quantity;
						book->setBookname(bookname);
                        book->setQuantity(quantity);
                        cout << "Da cap nhat thong tin sach!" << endl;
						l.saveFile_Books();
						}
					else {
						cout << "Khong tim thay sach voi ID da nhap!" << endl;}
				}
				//3.Xoa sach
				else if (choice2==3){
					string keyword;
					cout << "Nhap ID hoac ten sach can xoa: "; 
					cin.ignore();
					getline(cin, keyword);
					Book* book = l.Find_book(keyword);
					if (book == nullptr) {
						cout << "Khong tim thay sach!" << endl;
					}
					else {
					l.Delete_book(keyword);
					l.saveFile_Books();
				}}
				//4.Hien thi Book list
				else if(choice2 == 4){
					l.BookList();}
				//5.Duyet yeu cau muon sach
				else if(choice2 == 5){

				}
				//6.Xac nhan tra sach
				else if(choice2 == 6){}
				//7.Danh sach sach muon qua han
				else if(choice2 == 7){}
				//8.Xem danh sach tai khoan nguoi dung
				else if(choice2 == 8){
					l.UserList();}
				//9.Khoa tai khoan vi pham
				else if(choice2 == 9){
					string username;
					char confirm;
					cin.ignore();
					cout << "Nhap tai khoan can khoa: ";
					getline(cin, username);
					cout << "Ban co chac chan muon KHOA tai khoan nay? (y/n): ";
					cin >> confirm;
					if(confirm == 'y' || confirm == 'Y'){
					    l.Lock_User(username);
					    l.saveFile_User();
					}
					else if(confirm == 'n' || confirm == 'N'){
                        cout << "Da huy thao tac khoa tai khoan!" << endl;
                    }
				}
				//10.Mo khoa tai khoan User
				else if(choice2 == 10){
					string username;
					char confirm;
					cin.ignore();
					cout << "Nhap tai khoan can mo khoa: ";
					getline(cin, username);
					cout << "Ban co chac chan muon MO KHOA tai khoan nay? (y/n): ";
                    cin >> confirm;
					if(confirm == 'y' || confirm == 'Y'){
					    l.Unlock_User(username);
					    l.saveFile_User();
					}
					else if(confirm == 'n' || confirm == 'N'){
                        cout << "Da huy thao tac mo khoa tai khoan!" << endl;
                    }
				}
				//11.Them tai khoan admin
				else if(choice2 == 11){
					string nameadmin, password, fullname, phonenumber, email;
					cin.ignore();
					bool value = false;
					while (!value) {
					cout<<"Ten dang nhap: ";getline(cin, nameadmin);
					cout<<"Mat khau: ";getline(cin, password);
					cout<<"Ho va ten: "; getline(cin, fullname);
					cout<<"So dien thoai: "; getline(cin, phonenumber);
					cout<<"Email: "; getline(cin, email);
					if (l.Add_New_Admin(nameadmin, password, fullname, phonenumber, email)){
						cout << "Them tai khoan thanh cong!" << endl;
						l.saveFile_Admin();
						value = true;}
				}
			}} while (choice2 != 12);}
			else {
				cout << "Sai tai khoan hoac mat khau!" << endl;};
		}
		//User menu
		else if (choice1==2){
			string nameuser, passworduser;
			cin.ignore();
			cout<<"Ten dang nhap: ";getline(cin, nameuser);
			cout<<"Mat khau: ";getline(cin, passworduser);
			if(l.CheckUser(nameuser, passworduser)) {
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
	    	cout<<"||1.Xem danh sach sach                              ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
        	cout<<"||2.Tim sach theo ID hoac ten                       ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||3.Gui yeu cau muon sach                           ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
        	cout<<"||4.Thong ke sach dang muon va ngay tra             ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
        	cout<<"||5.Doi mat khau                                    ||"<<endl;
	    	cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||6.Chinh sua thong tin ca nhan                     ||"<<endl;
			cout<<"||--------------------------------------------------||"<<endl;
	    	cout<<"||7.Thoat                                           ||"<<endl;
	    	cout<<"======================================================"<<endl;
        	cout<<"Lua chon cua ban la: ";
        	cin >> choice3;
			//1.Hien thi Book list
			if (choice3 == 1){
				l.BookList();
			}
			//2.Tim sach theo ID hoac ten
			else if (choice3 == 2){
				string keyword;
				cin.ignore();
				cout << "Nhap ID hoac ten sach can tim: " << endl;
				getline(cin, keyword);
				Book* book = l.Find_book(keyword);
				if (book != nullptr){
					cout << "ID: " << book->getID() << endl
					     << "Ten sach: " << book->getBookname() << endl
						 << "So luong: " << book->getQuantity() << endl;
				}
				else {
					cout << "Khong tim thay sach!" << endl;
				}
			}
			//3.Gui yeu cau muon sach
			else if (choice3 == 3){
				string id, bookname;
				int quantity;
				char confirm;
				Date borrowdate, returndate;
				cin.ignore();
				cout << "Nhap ID sach can muon: "; getline(cin, id);
				Book* book = l.Find_book(id);
				if(book != nullptr) {
				cout << "Sach ban can muon la " << l.Find_book(id)->getBookname() << " (y/n)?" << endl;
				cin >> confirm;
				    if (confirm == 'y' || confirm == 'Y') {
					    cout << "Nhap so luong sach can muon: "; cin >> quantity;
					    cout << "Nhap ngay muon: " << endl;
						cout <<"Ngay: "; cin >> borrowdate.d;
						cout <<"Thang: "; cin >> borrowdate.m; 
						cout <<"Nam: "; cin >> borrowdate.y;
					    cout << "Nhap ngay tra du kien (Khong qua 30 ngay ke tu ngay muon): " << endl; 
						cout <<"Ngay: "; cin >> returndate.d;
						cout <<"Thang: "; cin >> returndate.m; 
						cout <<"Nam: "; cin >> returndate.y;
						l.AddBorrowBook(id, book->getBookname(), quantity, nameuser, borrowdate, returndate);
				        l.saveFile_BorrowBook();
						cout <<"Gui yeu cau muon sach thanh cong!" << endl;
				}
				    else if (confirm == 'n' || confirm == 'N') {
					    cout << "Huy yeu cau muon sach." << endl;
				}
				}
				else { cout << "Khong tim thay sach!" << endl; }
			}
			//4.Thong ke sach dang muon va ngay tra
			else if (choice3 == 4){}
			//5.Doi mat khau
			else if (choice3 == 5){
				string username, oldpass, newpass;
				cin.ignore();
				cout << "Ten dang nhap: "; getline(cin, username);
				cout << "Mat khau: "; getline(cin, oldpass);
				cout << "Mat khau moi: "; getline(cin, newpass);
				l.ChangePass(username, oldpass, newpass);
				l.saveFile_User();

			}
			//6.Chinh sua thong tin ca nhan
			else if (choice3 == 6){
				string username, password;
				cin.ignore();
				cout << "Ten dang nhap: "; getline(cin, username);
				cout << "Mat khau: "; getline(cin, password);
				l.EditProfile(username, password);
				l.saveFile_User();
			}
		    } while (choice3 != 7);}
		}
		//Dang ky tai khoan User
		else if (choice1==3){
			string nameuser, passworduser, fullname, phonenumber, email;
			cin.ignore();
			bool value = false;
			while (!value) {
			cout<<"Ten dang nhap: ";getline(cin, nameuser);
			cout<<"Mat khau: ";getline(cin, passworduser);
			cout<<"Ho va ten: "; getline(cin, fullname);
			cout<<"So dien thoai: "; getline(cin, phonenumber);
			cout<<"Email: "; getline(cin, email);
			if (l.Add_New_Account(nameuser, passworduser, fullname, phonenumber, email)){
			cout << "Dang ky tai khoan thanh cong!" << endl;
			l.saveFile_User();
		    value = true;}
		    }
	    }
		else if (choice1 == 4) {
            break;
        }
	 	else{
            cout << "Lua chon khong hop le, vui long chon lai." << endl;
        }}
        while (choice1 != 4);
	return 0;
}