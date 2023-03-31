#include<iostream>
#include <fstream>
#include <vector>
#include<sstream>
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
bool findPhone(string phoneNumber, vector<user> users);
bool findEmail(string email, vector<user> users);
bool find(string email, string password, vector<user> users);
bool find(int accounNumber, vector<user> users);
void signup(vector<user>& users);
void login(vector<user>& users);

void Withdraw(vector<user>& users);
void Transfer(vector<user>& user1);
void ViewTransactions(vector<user> users);

//global variables
int thisUserIndex;
int anotherUserIndex;

int main() {
	vector<user> users;
	read(users);
	cout << "press 1 to sign up or 0 to sign in\n";
	int choice;
	int choice1;

	cin >> choice;
	if (choice == 1) {
		signup(users);

	}
	else if (choice == 0) {
		login(users);
		do {
			cout << "Press 0 for withdrawal or 1 to transfer\n";
			cin >> choice1;
			if (choice1 == 0) {
				Withdraw(users);
			}
			else if (choice1 == 1) {
				Transfer(users);

				ViewTransactions(users);
			}
			else
				cout << "Please enter a valid choice\n";
			
		} while (choice1 != 1 || choice1 != 0);
		

	}
	else
		cout << "invalid choice";

}
void login(vector<user>& users) {
	user temp;
	cout << "enter email\n";
	cin >> temp.userAccount.email;
	cout << "enter password\n";
	cin >> temp.userAccount.password;
	while (!find(temp.userAccount.email,temp.userAccount.password,users)) {
		cout << "email and password doesn't match\n";
		cout << "enter email\n";
		cin >> temp.userAccount.email;
		cout << "enter password\n";
		cin >> temp.userAccount.password;
	}

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
	while (temp.balance<300) {
		cout << "balance can't be less than 300 EGP pls enter another amount\n";
		cin >> temp.balance;
	}

	temp.accountNum = (rand() % 101) + 100;
	while (find(temp.accountNum, users)) {
		temp.accountNum = (rand() % 101) + 900;
	}
	write(temp);
	login(users);
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
			thisUserIndex = i;
			return true;
		}
	}
	return false;
}

bool find(int accountNumber, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (accountNumber == users[i].accountNum) {
			anotherUserIndex = i;
			return true;
		}
	}
	return false;
}

void Withdraw(vector<user>& users) {
	float amount;
	transaction temp;
	cout << "Please enter the amount needed to withdraw\n";
	cin >> amount;
	if (users[thisUserIndex].balance - amount < 0) {
		cout << "Not enough balance\n";
	}
	else {
		users[thisUserIndex].balance -= amount;
		temp.recepient = "No recepient";
		temp.transactionAmount = amount;
		temp.transactionType = "Withdrawal";
		users[thisUserIndex].transactionCount++;
		users[thisUserIndex].userTransaction.push_back(temp);
		cout << "you have withdrawn " << amount << " with remaining balance " << users[thisUserIndex].balance << " in your account\n ";

	}

};
void Transfer(vector<user>& users) {
	float amount;
	int accNum;
	string accNumString;
	transaction temp;
	cout << "Please Enter the amount you need to transfer\n";
	cin >> amount;
	if (users[thisUserIndex].balance - amount < 0) {
		cout << "Not enough balance\n";
	}
	else {
		cout << "Please Enter the account number that you want to transfer this amount to\n";
		cin >> accNum;
		if (find(accNum, users)) {
			users[thisUserIndex].balance -= amount;
			users[anotherUserIndex].balance += amount;
			accNumString = to_string(accNum);
			temp.recepient = accNumString;
			temp.transactionAmount = amount;
			temp.transactionType = "Transfer";
			users[thisUserIndex].userTransaction.push_back(temp);
			users[thisUserIndex].transactionCount++;
			cout << "You have transferred amount of " << amount << " to the account " << accNum << endl;
		}
		else {
			cout << "This acount does not exist\n";
		}
	}
};
void ViewTransactions(vector<user> users){
	for (int i = users[thisUserIndex].userTransaction.size();i==0;i--) {
		cout << "Transaction of type " << users[thisUserIndex].userTransaction[i].transactionType << " with amount of " << users[thisUserIndex].userTransaction[i].transactionAmount << " to " << users[thisUserIndex].userTransaction[i].recepient << endl;
	}

}






