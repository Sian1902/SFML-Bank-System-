#include<iostream>
#include <fstream>
#include <vector>
using namespace std;

struct account
{
	string userName;
	string email;
	string password;
};
struct transaction {
	string transactionType;
	float transactionAmount;
	string recepient;
};
struct user {
	account userAccount;
	vector<transaction> userTransaction;
	int age=20;
	float balance=0;
	string phoneNumber=" ";
	int accountNum=0;
	bool frozen = false;
	int transactionCount = 0;

};
void read(vector<user> &users);
void write(user users);
bool findPhone(string phoneNumber, vector<user> users);
bool findEmail(string email, vector<user> users);
bool find(string email, string password, vector<user> users);
bool find(int accounNumber, vector<user> users);
void addEmployee(vector<user> &users);




int main() {
	vector<user>users;
	read(users);
	addEmployee(users);

}


void read(vector<user> &users) {
	user temp;
	ifstream in("userData.txt");
	if (!in) {
		cout << "file not found";
		return;
	}
	for (int i = 0; !in.eof();i++) {
		in >> temp.accountNum >> temp.userAccount.userName >> temp.userAccount.email >> temp.phoneNumber >>
			temp.balance >> temp.transactionCount >> temp.age >> temp.userAccount.password;
		users.push_back(temp);
	}
	in.close();
}

void write(user users) {
	fstream out("userData.txt", ios::app);
	if (!out) {
		cout << "file not found";
		return;
	}
	out << users.accountNum << " " << users.userAccount.userName << " " << users.userAccount.email << " " << users.phoneNumber << " " <<
		users.balance << " " << users.transactionCount << " " << users.age << " " << users.userAccount.password << endl;
	out.close();
}
bool findPhone(string phoneNumber, vector<user> users)
{
	for (int i = 0; i < users.size(); i++) {
		if (phoneNumber == users[i].phoneNumber) {
			return true;
		}
	}
	return false;
}

bool findEmail(string email, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (email == users[i].userAccount.email) {
			return true;
		}
	}
	return false; 
}
bool find(string email, string password, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (email == users[i].userAccount.email && password == users[i].userAccount.password) {
			return true;
		}
	}
	return false;
}

bool find(int accountNumber, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (accountNumber == users[i].accountNum) {
			return true;
		}
	}
	return false;
}
void addEmployee(vector<user> &users){
	user newEmployee;
	cout << "Enter employee name " << endl;
	cin >> newEmployee.userAccount.userName;
	cout << "Enter employee email " << endl;
	cin >> newEmployee.userAccount.email;
	while (findEmail(newEmployee.userAccount.email, users)) {
		cout << "Email already in use enter another one" << endl;
		cin >> newEmployee.userAccount.email;
	}
	cout << "Enter employee Password " << endl;
	cin >> newEmployee.userAccount.password;

	users.push_back(newEmployee);
	write(users[users.size() - 1]);
}


