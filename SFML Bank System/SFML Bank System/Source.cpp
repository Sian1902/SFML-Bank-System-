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
int main() {
	vector<user> users;


	read(users);
	write(users[0]);
	for (int i = 0; i < 1; i++) {
		cout << users[i].accountNum << " " << users[i].userAccount.userName << " " << users[i].userAccount.email << " " << users[i].phoneNumber << " " <<
			users[i].balance << " " << users[i].transactionCount << " " << users[i].age << " " << users[i].userAccount.password << endl;
	}
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
	fstream out("userData.txt",ios::app);
	if (!out) {
		cout << "file not found";
		return;
	}
		out << users.accountNum << " " << users.userAccount.userName << " " << users.userAccount.email << " " << users.phoneNumber << " " <<
			users.balance << " " << users.transactionCount << " " << users.age << " " << users.userAccount.password << endl;
	out.close();
}