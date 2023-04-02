#include<iostream>
#include <fstream>
#include <vector>
#include<sstream>
using namespace std;
int thisUserIndex = 0;
int anotherUserIndex;


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

bool findPhone(string phoneNumber, vector<user> users);
bool findEmail(string email, vector<user> users);
bool find(string email, string password, vector<user> users);
bool find(int accounNumber, vector<user> users);

bool addEmployee(vector<user>& users);
bool signUp(vector<user>& users);
bool login(vector<user>& users);

bool freeze(int accountNumber, vector<user>& users);
bool unFreeze(int accountNumber, vector<user>& users);

int main() {
	vector<user> users;
	bool signedUp = false;
	while (!signedUp) {
		signedUp= signUp(users);
	}
	signedUp = 0;
	while (!signedUp) {
		signedUp = login(users);
	}
	signedUp = 0;
	while (!signedUp) {
		signedUp = freeze(users[users.size() - 1].accountNum, users);
	}
	signedUp = 0;
	while (!signedUp) {
		signedUp = login(users);
	}
	signedUp = 0;
	while (!signedUp) {
		signedUp = unFreeze(users[users.size() - 1].accountNum, users);
	}
	signedUp = 0;
	while (!signedUp) {
		signedUp = login(users);
	}

	
}
bool login(vector<user>& users) {
	user temp;
	cout << "enter email"<<endl;
	cin >> temp.userAccount.email;
	cout << "enter password"<<endl;
	cin >> temp.userAccount.password;
	if (!find(temp.userAccount.email, temp.userAccount.password, users)) {
		cout << "email and password doesn't match" << endl;
		return false;
	}
	if (users[thisUserIndex].frozen==true) {
		cout << "this account is frozen" << endl;
		return false;
	}
	else {
		cout << "loged in successfully" << endl;
		cout << thisUserIndex << endl;
	}
}
bool signUp(vector<user>& users) {
	user temp;
	cout << "enter name\n";
	cin >> temp.userAccount.userName;
	cout << "enter email"<<endl;
	cin >> temp.userAccount.email;
	if (findEmail(temp.userAccount.email, users) || temp.userAccount.email.find("@user.bank") == string::npos) {
		cout << "email is already in use enter another one make sure to include @user.bank\n";
		return false;
	}
	cout << "enter password"<<endl;
	cin >> temp.userAccount.password;
	cout << "enter phone number"<<endl;
	cin >> temp.phoneNumber;
	if (findPhone(temp.phoneNumber, users)) {
		cout << "phone number already taken"<<endl;
		return false;
	}
	cout << "enter age"<<endl;
	cin >> temp.age;
	if (temp.age < 21) {
		cout << "invalid age"<<endl;
		return false;
	}
	cout << "enter balance"<<endl;
	cin >> temp.balance;
	if (temp.balance < 300) {
		cout << "balance can't be less than 300 EGP "<<endl;
		return false;
		
	}

	temp.accountNum = (rand() % 101) + 100;
	while (find(temp.accountNum, users)) {
		temp.accountNum = (rand() % 101) + 900;
	}
	users.push_back(temp);
	return true;
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

bool addEmployee(vector<user>& users) {
	user newEmployee;
	cout << "Enter employee name " << endl;
	cin >> newEmployee.userAccount.userName;
	cout << "Enter employee email " << endl;
	cin >> newEmployee.userAccount.email;
	if (findEmail(newEmployee.userAccount.email, users)|| newEmployee.userAccount.email.find("@employee.bank")==string::npos) {
		cout << "Email already in use enter another one make sure that your email contains @employee.bank" << endl;
		return false;
	}
	cout << "Enter employee Password " << endl;
	cin >> newEmployee.userAccount.password;
	users.push_back(newEmployee);
	return true;
}
bool freeze(int accNum, vector<user>& users)
{
	if (!find(accNum, users)) {
		cout << "this user doesn't exist" << endl;
		return false;
	}
	else if (find(accNum, users)) {
		users[anotherUserIndex].frozen = true;
		cout << "frozen" << endl;
	}
	return true;
}
bool unFreeze(int accNum, vector<user>& users)
{
	if (!find(accNum, users)) {
		cout << "this user doesn't exist" << endl;
		return false;
	}
	else if (find(accNum, users)) {
		users[anotherUserIndex].frozen = false;
		cout << "active" << endl;
	}
	return true;

}


