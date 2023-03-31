#include<iostream>
#include <fstream>
#include <vector>
using namespace std;
int index = 0;
int months = 0;

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
	int age;
	float balance;
	string phoneNumber;
	int accountNum;
	bool frozen = false;
	int transactionCount = 0;

};
void read(vector<user>& users);
void write(user users);
bool findPhone(string phoneNumber, vector<user> users);
bool findEmail(string email, vector<user> users);
bool find(string email, string password, vector<user> users);
bool find(int accounNumber, vector<user> users);
void signup(vector<user>& users);
void login(vector<user>& users);
bool vaildBalance(user users, float trans);
float loan(vector<user>&users,float trans);

int main() {
	vector<user> users;
	
	read(users);
	login(users);
	

}
void login(vector<user>& users) {
	user temp;
	cout << "enter email\n";
	cin >> temp.userAccount.email;
	cout << "enter password\n";
	cin >> temp.userAccount.password;
	while (!find(temp.userAccount.email, temp.userAccount.password, users)) {
		cout << "email and password doesn't match\n";
		cout << "enter email\n";
		cin >> temp.userAccount.email;
		cout << "enter password\n";
		cin >> temp.userAccount.password;
	}
	cout << users[index].balance << endl;
	

}


bool vaildBalance(user users,float trans ) {



	if (users.balance - trans <= 0) {
		return false;

	}
	else if (trans < 50) {
		return false;

	}
	else
		return true;


}
	

float loan(vector<user> &users,float trans) {
	transaction transa;



	if (trans * 0.25 >= users[index].balance) {
		cout << "Rejected due to low balance " << endl;
	}


	else if (trans > 100000) {
		months =( (trans + users[index].balance) / trans)*6;
		cout << "loan is accepted and have to be returned by " << months << " months";

		transa.transactionType = "loan";
		transa.transactionAmount = trans;
	}


	else {
	months = (trans + users[index].balance) / trans;
	cout << "loan is accepted and have to be returned by " << months<<" months";
    
	transa.transactionType = "loan";
	transa.transactionAmount = trans;

	}
	users[index].userTransaction.push_back(transa);
	
	

}

void signup(vector<user>& users) {
	user temp;
	cout << "enter name\n";
	cin >> temp.userAccount.userName;
	cout << "enter email\n";
	cin >> temp.userAccount.email;
	while (findEmail(temp.userAccount.email, users)) {
		cout << "email is already in use enter another one\n";
		cin >> temp.userAccount.email;
	}
	cout << "enter password\n";
	cin >> temp.userAccount.password;
	cout << "enter phone number\n";
	cin >> temp.phoneNumber;
	cout << "enter age\n";
	cin >> temp.age;
	while (temp.age < 21) {
		cout << "under age 7aker must be older than 21 to continue pls enter another age\n";
		cin >> temp.age;
	}
	cout << "enter balance\n";
	cin >> temp.balance;
	while (temp.balance < 300) {
		cout << "balance can't be less than 300 EGP pls enter another amount\n";
		cin >> temp.balance;
	}

	temp.accountNum = (rand() % 101) + 100;
	while (find(temp.accountNum, users)) {
		temp.accountNum = (rand() % 101) + 900;
	}
	write(temp);
}

void read(vector<user>& users) {
	user temp;
	ifstream in("userData.txt");
	if (!in) {
		cout << "file not found";
		return;
	}
	for (int i = 0; !in.eof(); i++) {
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
		if (email == users[i].userAccount.email)
		{
			
			return true;
		}
	}
	return false;
}
bool find(string email, string password, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (email == users[i].userAccount.email && password == users[i].userAccount.password) {
			index = i;
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
