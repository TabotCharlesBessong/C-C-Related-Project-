
#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;

class Customers {
  public:
    string name,gender,address;
    int age , mobileNo , customerID;
    char all[999];

    void getDetails(){


    // saving file
      ofstream out("oldCustomers.txt",ios::app);
      {
        cout<<"Enter your CustomerID"<<endl;
        cin>>customerID;
        cout<<"Enter your Name"<<endl;
        cin>>name;
        cout<<"Are you Male or Female"<<endl;
        cin>>gender;
        cout<<"Enter your Telephone Number"<<endl;
        cin>>mobileNo;
        cout<<"Enter your Address"<<endl;
        cin>>address;
        // cout<<"Enter your CustomerID"<<endl;
        // cin>>customerID;
      }  
      out << "\nCustomerId: "<<customerID<<"\nName: "<<name<<"\nTelephone: "<<mobileNo<<"\nGender: "<<gender<<"\nAddress: "<<address<<"\nAge:"<<age<<endl;
      out.close();
      cout<<"\n"<<"Saved\n: Note:We save your detail record for future purpose\n"<<endl;
    }

    void showDetails(){
      ifstream in("oldCustomers.txt");
      { 
        if(!in){
          cout<<"File ERROR"<<endl;
        }
        while(!(in.eof())){
          in.getline(all,999);
          cout<<all<<endl;
        }
        in.close();
      }
    }
};

class Cabs {
  public:
    int cabChoice;
    int km;
    float cost;
    float lastCabCost;

    void cabDetails(){
      cout << "We collaborate with the fastest and suresst cab services for your convinience"<<endl;
      cout<<"-------------ABC Cabs -------\n"<<endl;
      cout<<"1. Rent s standard Cab - 25000XAF for 2km"<<endl;
      cout<<"2. Rent a Luxury Cab for 100000XAF for 2km"<<endl;

      cout<<"\n To Calate the cost for your journey\nEnter the type of Cab you wish to Rent: "<<endl;
      cin>> cabChoice;
      cout<<"\nPlease Enter your distance , its annother important parameter we need for calculation"<<endl;
      cin>>km;

      int hireCab;
      if(cabChoice == 1){
        cost = km * 12500;
        cout<<"\nYour Cost is: "<<cost<<" XAF"<<endl;
        cout<<"Press 1 to Rent a Cab: or"<<endl;
        cout<<"Press 2 to select another Cab: "<<endl;
        cin>>hireCab;
        system("CLS");
        if(hireCab == 1){
          lastCabCost = cost;
          cout<<"\nYou have successfully Hired a Standard cab"<<endl;
          cout<<"Go to menu and take the receipt"<<endl;
        }else if(hireCab == 2){
          cabDetails();
        }else{
          cout<<"Invalid Input Redirecting to previous menu: PLease wait"<<endl;
          Sleep(99);
          system("CLS");
          cabDetails();
        }
      }else if(cabChoice == 2){
        cost = km * 50000;
        cout<<"\nYour Cost is: "<<cost<<" XAF"<<endl;
        cout<<"Press 1 to Rent a Cab: or"<<endl;
        cout<<"Press 2 to select another Cab: "<<endl;
        cin>>hireCab;
        system("CLS");
        if(hireCab == 1){
          lastCabCost = cost;
          cout<<"\nYou have successfully Hired a Luxury cab"<<endl;
          cout<<"Go to menu"<<endl;
        }else if(hireCab == 2){
          cabDetails();
        }else{
          cout<<"Invalid Input Redirecting to previous menu: PLease wait"<<endl;
          Sleep(99);
          system("CLS");
          cabDetails();
          // menu();
        }
      }else{
        cout<<"\nPlease enter the right choice Press 1 to redirect to main menu: "<<endl;
        cin>>hireCab;
        system("CLS");
        if(hireCab == 1){
          cabDetails();
        }else{
          cabDetails();
        }
      }
    }
};

class Booking{
  public:
    int choiceHotels, packChoice;
    float hotelCost;

    void hotels(){
      string hotelNo[] = {"Avulion","Obvulion","Pakatcha"};
      for(int i = 0 ; i < 3 ; i++){
        cout<<(i+1)<<hotelNo[i];
      }
      cout<<"\nThe system currently collaborated with the above hotels: "<<endl;
      cout<<"Press any key to book or \n Enter number of the hotel you want to book: "<<endl;
      cin>>choiceHotels;
      system("CLS");

      if(choiceHotels == 1){
        
      }
    }
};

class Charges {

};

int main(){
  cout<<"Hello world"<<endl;
}