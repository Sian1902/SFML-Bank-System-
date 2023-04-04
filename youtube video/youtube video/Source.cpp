#include<iostream>
#include<sstream>
#include<vector>
using namespace std;

struct account{
	string username;
	string password;
	string email;
};
struct transactions{
	float transactionAmount;
	string transactionType;
	string recpient;
};
struct user {
	account userAccount;
	vector<transactions> userTransactions;
	int age;
	float balance;
	int transactionCount=0;
	bool frozen = false;
	int accountNumber;
	string phoneNumber;
};
//int anotherUserIndex;
//int thisUserIndex;
// bool signup(vector<user>& users);
//bool findEmail(string email, vector<user> users);
//bool findPhonenumber(string phoneNumber, vector<user> users);
//bool find(int accNUm, vector<user> users);
//bool find(string email, string password, vector<user> users);
//bool login(vector<user> users);
//bool addEmployee(vector<user>& users);
//bool freeze(vector<user>& users);
//bool unFreeze(vector<user>& users);
int main() {
	string s="123";
	cout<<stoi(s)<<endl;
}
//bool signup(vector<user>& users) {
//	user temp;
//	cout << "enter your name" << endl;
//	cin >> temp.userAccount.username;
//	cout << "ente your email" << endl;
//	cin >> temp.userAccount.email;
//	if (findEmail(temp.userAccount.email, users)) {
//		cout << "this email already exist" << endl;
//		return false;
//	}
//	
//	if (temp.userAccount.email.find("@user.bank") == string::npos) {
//		cout << "invalid mail format" << endl;
//		return false;
//	}
//	cout << "enter your password" << endl;
//	cin >> temp.userAccount.password;
//	cout << "enter your age" << endl;
//	cin >> temp.age;
//	if (temp.age < 21) {
//		cout << "invalid age" << endl;
//		return false;
//	}
//	cout << "enter balance " << endl;
//	cin >> temp.balance;
//	if (temp.balance < 300) {
//		cout << "minimum balance is 300" << endl;
//		return false;
//	}
//	cout << "enter your phobne number" << endl;
//	cin >> temp.phoneNumber;
//	if (findPhonenumber(temp.phoneNumber, users)) {
//		cout << "phoneNumber in use" << endl;
//		return false;
//	}
//	temp.accountNumber = (rand() % 101) + 100;
//	while (find(temp.accountNumber, users)){
//		temp.accountNumber = (rand() % 101) + 100;
//	}
//
//	users.push_back(temp);
//}
//bool findEmail(string email, vector<user> users) {
//	for (int i = 0; i < users.size(); i++) {
//		if (email == users[i].userAccount.email) {
//			return true;
//		}
//	}
//	return false;
//}
//bool findPhonenumber(string phoneNumber, vector<user> users) {
//	for (int i = 0; i < users.size(); i++) {
//		if (phoneNumber == users[i].phoneNumber) {
//			return true;
//		}
//	}
//	return false;
//}
//bool find(int accNum, vector<user> users) {
//	for (int i = 0; i < users.size(); i++) {
//		if (accNum == users[i].accountNumber) {
//			return true;
//			anotherUserIndex = i;
//		}
//	}
//	return false;
//}
//bool find(string email, string password, vector<user> users) {
//	for (int i = 0; i < users.size(); i++) {
//		if (email == users[i].userAccount.email && password == users[i].userAccount.password) {
//			return true;
//			thisUserIndex = i;
//		}
//	}
//	return false;
//}
//bool login(vector<user>users) {
//	user temp;
//	cout << "enter your email" << endl;
//	cin >> temp.userAccount.email;
//	cout << "enter your password";
//	cin >> temp.userAccount.password;
//	if (find(temp.userAccount.email, temp.userAccount.password, users)) {
//		if (users[thisUserIndex].frozen) {
//			cout << "this account is frozen" << endl;
//			return false;
//		}
//		cout << "loged in " << endl;
//		return true;
//	}
//	else {
//		cout << "this user doesn't exist" << endl;
//		return false;
//	}
//}
//bool addEmployee(vector<user>& users) {
//	user temp;
//	cout << "enter your name" << endl;
//	cin >> temp.userAccount.username;
//	cout << "ente your email" << endl;
//	cin >> temp.userAccount.email;
//	if (findEmail(temp.userAccount.email, users)) {
//		cout << "this email already exist" << endl;
//		return false;
//	}
//
//	if (temp.userAccount.email.find("@employee.bank") == string::npos) {
//		cout << "invalid mail format" << endl;
//		return false;
//	}
//	cout << "enter your password" << endl;
//	cin >> temp.userAccount.password;
//
//}
//bool freeze(vector<user>& users) {
//	cout << "enter account number" << endl;
//	int accnum;
//	cin >> accnum;
//	if (find(accnum, users)) {
//		users[anotherUserIndex].frozen = true;
//		return true;
//	}
//	else {
//		cout << "this user doesn't exist" << endl;
//		return false;
//	}
//}
//bool unFreeze(vector<user>& users) {
//	cout << "enter account number" << endl;
//	int accnum;
//	cin >> accnum;
//	if (find(accnum, users)) {
//		users[anotherUserIndex].frozen = false;
//		return true;
//	}
//	else {
//		cout << "this user doesn't exist" << endl;
//		return false;
//	}
//}