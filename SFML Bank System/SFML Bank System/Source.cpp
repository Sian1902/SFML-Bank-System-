#include<iostream>
#include <fstream>
#include <vector>
#include<sstream>
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
	string transactionType = "";
	float transactionAmount = 0;
	string recepient = "";
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
void write(vector<user> users);
bool findPhone(string phoneNumber, vector<user> users);
bool findEmail(string email, vector<user> users);
bool find(string email, string password, vector<user> users);
bool find(int accounNumber, vector<user> users);

void addEmployee(vector<user>& users);
void signup(vector<user>& users);
void login(vector<user>& users);
bool vaildBalance(user users, float trans);
float loan(vector<user>&users,float trans);

void Withdraw(vector<user>& users);
void Transfer(vector<user>& user1);
void ViewTransactions(vector<user> users);

//global variables
int thisUserIndex;
int anotherUserIndex;

void freeze(int id, vector<user>& users);
void unfreeze(int id, vector<user>& users);
void view(int id, vector<user> users);
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
	vector<user> users;
	read(users);
	signup(users);
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
	users.push_back(temp);
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
			temp.balance >> temp.transactionCount >> temp.age >> temp.userAccount.password >> temp.frozen;
		for (int j = 0; j < temp.userTransaction.size(); j++) {
			in >> temp.userTransaction[j].recepient >> temp.userTransaction[j].transactionType >> temp.userTransaction[j].transactionAmount;
		}
		users.push_back(temp);
	}
	in.close();
}

void write(vector<user>& users) {
	fstream out("userData.txt", ios::out);
	if (!out) {
		cout << "file not found";
		return;
	}
	for (int i = 0; i < users.size(); i++) {
		out << users[i].accountNum << " " << users[i].userAccount.userName << " " << users[i].userAccount.email << " " << users[i].phoneNumber << " " <<
			users[i].balance << " " << users[i].transactionCount << " " << users[i].age << " " << users[i].userAccount.password << " " << users[i].frozen;
		for (int j = 0; j < users[i].userTransaction.size(); j++) {
			out << " " << users[i].userTransaction[j].recepient << " " << users[i].userTransaction[j].transactionType << " " << users[i].userTransaction[j].transactionAmount;
		}
		out << endl;
	}
	out.close();
}
bool findPhone(string phoneNumber, vector<user> users)
{
	for (int i = 0; i < users.size(); i++) {
		if (phoneNumber == users[i].phoneNumber) {
			index = i;
			return true;
		}
	}
	return false;
}

bool findEmail(string email, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (email == users[i].userAccount.email) {
			index = i;
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



void addEmployee(vector<user>& users) {
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
}

void freeze(int id, user u) // Passing account ID
{
	u.frozen = true;

}

void freeze(int accNum, vector<user>& users)
{
	if (!find(accNum, users)) {
		cout << "this user doesn't exist" << endl;
	}
	else 	if (find(accNum, users)) {
		users[index].frozen = true;
		cout << "frozen" << endl;
	}

}
void unfreeze(int accNum, vector<user>& users)
{
	if (!find(accNum, users)) {
		cout << "this user doesn't exist" << endl;
	}
	else if (find(accNum, users)) {
		users[index].frozen = false;
		cout << "active" << endl;
	}

}
void view(int accNum, vector<user> users) {
	if (!find(accNum, users)) {
		cout << "this user doesn't exist" << endl;
	}
	else if (find(accNum, users)) {
		cout << users[index].balance << " " << users[index].userAccount.userName;
	}
}

