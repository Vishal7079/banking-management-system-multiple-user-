// advance banking management system
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

class Account{
	public:
		string name;
		int account_number ;
		int pin;
		double balance;
		vector<string>history;
	
		Account(){}
			
			Account(string n , int acc , int p , double bal){
				name = n;
				account_number = acc;
				pin = p;
				balance = bal;
			}
			
			void deposit(double amount){
				balance += amount;
				history.push_back("deposited : " + to_string(amount));
				cout<<"deposit successful!\n";
			}
			void withdraw(double amount){
				if(amount<=balance){
					balance -=amount;
					history.push_back("withdrawn:" + to_string(amount));
					cout<<"withdrawl successfully!\n";					
				}
				else {
					cout<<"insufficient balance!\n";
				}
			}
			void display(){
				cout<<"\n---Account Details---\n";
				cout<<"Name:"<<name<<endl;
				cout<<"Account Number: "<<account_number<<endl;
				cout<<"balance:"<<balance<<endl;
			}
			
			void showhistory(){
				cout<<"\n---Transaction History---\n";
				if(history.empty()){
					cout<<"No transactions yet. \n";
					return ;
				}
				for(string h:history){
					cout<<h<<endl;
				}
			}
	
};

vector<Account>accounts;
// save all accounts file
void savedata(){
	ofstream file("bankdata.txt");
	for(auto &&acc : accounts){
		file<<acc.name<<"|"
		<<acc.account_number<<"|"
		<<acc.pin<<"|"
		<<acc.balance<<"|";
		
		for(string h:acc.history)
		file<<h<< ",";
		
		file<<"\n";
	}
	file.close();
}

// load all accounts from file
void loaddata(){
	ifstream file("bankdata.txt");
	string line;
	
	while(getline (file,line)){
		Account acc;
		string temp = "";
		int part = 0;
		
		for (char c: line){
			if(c=='|'){
				if(part == 0) acc.name=temp;
				else if(part == 1)acc.account_number = stoi(temp);
				else if(part == 2)acc.pin = stoi(temp);
				else if(part == 3)acc.balance=stod(temp);
				temp ="";
				part++;
				
			}
			else if(c==','){
				acc.history.push_back(temp);
				temp = "";
			}else temp +=c;
		}
		accounts.push_back(acc);
	}file.close();
}

void createaccount(){
	string name;
	int accNo, pin;
	
	cout<<"enter name : ";
	cin.ignore();
	getline(cin,name);
	cout<<"enter account number : ";
	cin>>accNo;
	cout<<"set 4 digit PIN : ";
	cin>>pin;
	
	accounts.push_back(Account(name,accNo,pin,0.0));
	savedata();
	
	cout<<"account created successfully!\n";
}	
Account*login(){
	int accNo , pin;
	cout<<"enter account number : ";
	cin>>accNo;
	cout<<"enter PIN:";
	cin>>pin;
	
	for(auto &acc:accounts){
		if(acc.account_number == accNo&&acc.pin==pin){
			return &acc;
		}
		
	}
	cout<<"invalid account number /PIN!\n";
	return nullptr;
}

void deleteaccount(Account*user){
	for(int i = 0 ; i<accounts.size();i++){
		if(accounts[i].account_number == user->account_number){
			accounts.erase(accounts.begin()+i);
			savedata();
			cout<<"account deleted successfully!\n";
			return;
		}
	}
}

int main(){
	
	loaddata();
	int choice;
	
	while(true){
		cout<<"\n====Banking Management System====\n";
		cout<<"1. Create account\n";
		cout<<"2. login to account\n";
		cout<<"3. exit\n";
		cout<<"choice:";
		cin>>choice;
		
		if(choice==1)createaccount();
		
		else if(choice==2){
			Account*user = login();
			if(user == nullptr)continue;
			
			int option;
			do{
				cout<<"\n---Welcome, "<<user->name<<"---\n";
				cout<<"1.Deposit\n";
				cout<<"2.Withdraw\n";
				cout<<"3.View Details\n";
				cout<<"4. Transaction history\n";
				cout<<"5. Delete account\n";
				cout<<"6.logout\n";
				cout<<"enter choice:";
				cin>>option;
				
				if(option ==1){
					double amt;
					cout<<"amount:";
					cin>>amt;
					user->deposit(amt);
					savedata();
				}
				else if(option ==2){
					double amt;
					cout<<"amount:";
					cin>>amt;
					user->withdraw(amt);
					savedata();
				}
					else if(option==3)user->display();
					else if(option==4)user->showhistory();
					else if(option==5){
						deleteaccount(user);
						break;
					}
					
			}while(option!=6);
		}
		else if(choice==3){
			cout<<"Thanking you for using the system!\n";
			break;
		}
		else cout<<"Invalid Choice!\n";
	}
	
	return 0;
}
