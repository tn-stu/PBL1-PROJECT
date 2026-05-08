#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <iomanip>
using namespace std;
int main(){
    int choice;
    librarysystem s;
    do {
        cout<<"=====       =====  ========  =====     ==  ===     ==="<<endl;
	    cout<<"======     ======  ========  ======    ==  ===     ==="<<endl;
	    cout<<"=== ===   === ===  ===       === ===   ==  ===     ==="<<endl;
	    cout<<"===  === ===  ===  ========  ===  ===  ==  ===     ==="<<endl;
	    cout<<"===   =====   ===  ========  ===   === ==  ===     ==="<<endl;
	    cout<<"===    ===    ===  ===       ===    =====  ===     ==="<<endl;
	    cout<<"===     =     ===  ========  ===     ====  ====   ===="<<endl;
	    cout<<"===           ===  ========  ===      ===   ========= "<<endl;
	    cout<<"=================================================="<<endl;
	    cout<<"||1.Dang nhap voi tu cach la admin              ||"<<endl;
	    cout<<"||______________________________________________||"<<endl;
        cout<<"||2.Dang nhap voi tu cach la nguoi dung         ||"<<endl;                          
	    cout<<"=================================================="<<endl;
        cout<<"Lua chon cua ban la: ";
        cin >> choice;
        if (choice ==1){}
    } while (choice != 7);