#include<iostream>
#include<fstream>
#include<string>
#include<sstream> // brek line for csv
#include<vector> // for multiple user
using namespace std;
class atm{
	// private data cant access outside so we use-
	// getter for to read private data getpin , getbalance
	// setter for change private data setbalance
	int pin;
	int balance;
	public:
		atm(int p=0,int b=0){
			pin=p;
			balance=b;
		}
		void checkbalance();
		void deposit();
		void withdraw();
		// getter setter method (They are used to safely access or change private data members of a class.)
		int getpin();
		int getbalance();
		void setbalance(int b);
		

vector<atm> loadusers() {
    vector<atm> users;
    ifstream infile("users.csv");
    string line;

    while (getline(infile, line)) {
        string pinStr, balanceStr;
        stringstream ss(line);
        getline(ss, pinStr, ',');
        getline(ss, balanceStr, ',');

        if (!pinStr.empty() && !balanceStr.empty()) {
            int pin = stoi(pinStr);
            int balance = stoi(balanceStr);
            users.push_back(atm(pin, balance));
        }
    }

    infile.close();
    return users;
}

		
	
	void saveUsers(vector<atm>& users) {
    ofstream outfile("users.csv");
    if(!outfile.is_open()){
    	cout<<"Error could not open file for writing."<<endl;
    	return;
	}
    for(auto&user:users){
	
        outfile << user.getpin() << "," << user.getbalance() << "\n";
    }
    outfile.close();
}
};
void atm::checkbalance(){
	cout<<"current balance is :"<<balance<<endl;
}
void atm::deposit(){
	int amount;
	cout<<"Enter amount to deposit : ";
	cin>>amount;
	balance+=amount;
	cout<<amount<<" is deposited successfully ."<<endl;
}
void atm::withdraw(){
	int amount;
	cout<<"Enter amount to withdraw : ";
	cin>>amount;
	if(amount>balance){
		cout<<"Insufficient balance "<<endl;
	}
	else{
		balance-=amount;
		cout<<amount<<" is successfully withdraw. "<<endl;
	}
}
int atm::getpin(){
	return pin;
}
int atm::getbalance(){
	return balance;
}
void atm::setbalance(int b){
	balance=b;
}


int main(){
	
    
    atm a;
    vector<atm> users = a.loadusers();  // Load users from file

    int enteredPin;
    cout << "Enter your 4-digit PIN: ";
    cin >> enteredPin;

    bool found = false;

    // Search if the user already exists
    for (auto &user : users) {
        if (user.getpin() == enteredPin) {
            found = true;
            int choice;
            do {
                cout << "\n--- ATM MENU ---\n";
                cout << "1. Check Balance\n";
                cout << "2. Deposit\n";
                cout << "3. Withdraw\n";
                cout << "4. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                case 1:
                    user.checkbalance();
                    break;
                case 2:
                    user.deposit();
                    break;
                case 3:
                    user.withdraw();
                    break;
                case 4:
                    cout << "Thank you for using the ATM!\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
                }
            } while (choice != 4);
            a.saveUsers(users);  // Save updated data
            break;
        }
    }

    // If not found, create new user
    if (!found) {
        cout << "PIN not found. Creating new account...\n";
        int initialBalance;
        cout << "Enter initial balance: ";
        cin >> initialBalance;

        users.push_back(atm(enteredPin, initialBalance));  // Add new user
        a.saveUsers(users);  // Save new user data

        cout << "New account created successfully!\n";
    }

    return 0;
}



	 
