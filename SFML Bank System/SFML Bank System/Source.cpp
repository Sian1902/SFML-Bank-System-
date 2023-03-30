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
	int age;
	float balance;
	string phoneNumber;
	int accountNum;
	bool frozen = false;
	int transactionCount = 0;

};
void read(vector<user> &users);
void write(user users);
bool find(string phoneNumber, vector<user> users);
bool find(string email, vector<user> users);
bool find(string email, string password, vector<user> users);
bool find(int accounNumber, vector<user> users);

int main() {
	
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
bool find(string phoneNumber, vector<user> users)
{
	for (int i = 0; i < users.size(); i++) {
		if (phoneNumber == users[i].phoneNumber) {
			return true;
		}
	}
	return false;
}

bool find(string email, vector<user> users) {
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



