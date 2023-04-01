#include<iostream>
#include <fstream>
#include <vector>
#include<sstream>
using namespace std;
int thisUserIndex = 0;
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
void loan(vector<user>&users,float trans);

void Withdraw(vector<user>& users);
void Transfer(vector<user>& user1);
void ViewTransactions(vector<user>& users);
void exit(vector<user> users);
//global variables
int anotherUserIndex;

void freeze(int id, vector<user>& users);
void unfreeze(int id, vector<user>& users);
void view(int id, vector<user> users);
int main() {
	vector<user> users;
	cout << "hi" << endl;
	read(users);

	cout << users.size()<<endl;
	///*signup(users);
	//signup(users);
	//addEmployee(users);

	//freeze(12, users);
	//freeze(8827, users);*/
	//login(users);
	////ViewTransactions(users);
	////Withdraw(users);
	////Transfer(users);
	////ViewTransactions(users);
	////loan(users, 10000);
	//Transfer(users);
	//ViewTransactions(users);
	exit(users);
	
	
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
	if (find(temp.userAccount.email, temp.userAccount.password, users)) {
		if (temp.userAccount.email.find("@admin.bank") != string::npos) {
			cout << "admin ACC" << endl;
		}
		else if (temp.userAccount.email.find("@employee.bank") != string::npos) {
			cout << "employee ACC" << endl;
		}
		else {
			cout << "user ACC" << endl;
		}
	}
	if (temp.frozen) {
		cout << "you can't login " << endl;
	}
	cout << users[thisUserIndex].balance << endl;
	
	cout << thisUserIndex << endl;
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
	

void loan(vector<user> &users,float trans) {
	transaction transa;



	if (trans * 0.25 >= users[thisUserIndex].balance) {
		cout << "Rejected due to low balance " << endl;
	}


	else if (trans > 100000) {
		months =( (trans + users[thisUserIndex].balance) / trans)*6;
		cout << "loan is accepted and have to be returned by " << months << " months";

		transa.transactionType = "loan";
		transa.transactionAmount = trans;
	}


	else {
	months = (trans + users[thisUserIndex].balance) / trans;
	cout << "loan is accepted and have to be returned by " << months<<" months";
    
	transa.transactionType = "loan";
	transa.transactionAmount = trans;

	}
	users[thisUserIndex].userTransaction.push_back(transa);
	
	

}

void signup(vector<user>& users) {
	user temp;
	cout << "enter name\n";
	cin >> temp.userAccount.userName;
	cout << "enter email\n";
	cin >> temp.userAccount.email;
	while (findEmail(temp.userAccount.email, users)|| temp.userAccount.email.find("@user.bank")==string::npos) {
		cout << "email is already in use enter another one make sure to include @user.bank\n";
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
	transaction transactiontemp;
	
	ifstream in("userData.txt");
	if (!in) {
		cout << "file not found";
		return;
	}

	for (int i = 0; !in.eof(); i++) {
		in >> temp.accountNum >> temp.userAccount.userName >> temp.userAccount.email >> temp.phoneNumber >>
			temp.balance >> temp.transactionCount >> temp.age >> temp.userAccount.password >> temp.frozen;
		for (int j = 0; j < temp.transactionCount; j++) {
			temp.userTransaction.push_back(transactiontemp);
			in >> temp.userTransaction[j].recepient >> temp.userTransaction[j].transactionType >> temp.userTransaction[j].transactionAmount;
			
		}
		users.push_back(temp);
	}
	in.close();
	cout << users.size() << endl;
}

void write(vector<user> users) {
	cout << users.size()<<endl;
	fstream out("userData.txt", ios::out);
	if (!out) {
		cout << "file not found";
		return;
	}
	for (int i = 0; i < users.size(); i++) {
		out << users[i].accountNum << " " << users[i].userAccount.userName << " " << users[i].userAccount.email << " " << users[i].phoneNumber << " " <<
			users[i].balance << " " << users[i].transactionCount << " " << users[i].age << " " << users[i].userAccount.password << " " << users[i].frozen<<endl;
		for (int j = 0; j < users[i].transactionCount; j++) {
			out  << users[i].userTransaction[j].recepient << " " << users[i].userTransaction[j].transactionType << " " << users[i].userTransaction[j].transactionAmount<<endl;
		}
	
	}
	out.close();
}
bool findPhone(string phoneNumber, vector<user> users)
{
	for (int i = 0; i < users.size(); i++) {
		if (phoneNumber == users[i].phoneNumber) {
			thisUserIndex = i;
			return true;
		}
	}
	return false;
}

bool findEmail(string email, vector<user> users) {
	for (int i = 0; i < users.size(); i++) {
		if (email == users[i].userAccount.email) {
			thisUserIndex = i;
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
		users[thisUserIndex].transactionCount++;
		cout << temp.transactionAmount << endl;
		users[thisUserIndex].userTransaction.push_back(temp);
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = "noRecepient";
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "withdrawl";

		cout << "you have withdrawn " << amount << " with remaining balance " << users[thisUserIndex].balance << " "<<"in your account\n ";
		cout << thisUserIndex << endl;
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
			users[thisUserIndex].transactionCount++;
			users[anotherUserIndex].transactionCount++;
			accNumString = to_string(accNum);
			users[thisUserIndex].userTransaction.push_back(temp);
			users[anotherUserIndex].userTransaction.push_back(temp);
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = accNumString;
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "transfer";


			users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].transactionAmount = amount;
			users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].recepient = to_string(users[thisUserIndex].accountNum);
			users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].transactionType = "transfer";
			cout << "You have transferred amount of " << amount << " to the account " << accNum << endl;
		}
		else {
			cout << "This acount does not exist\n";
		}
	}
};
void ViewTransactions(vector<user>& users){
	int index = users[thisUserIndex].transactionCount-1;
	for (int i = index; i >= 0;i--) {
		cout << "Transaction of type " << users[thisUserIndex].userTransaction[i].transactionType << 
			" with amount of " << users[thisUserIndex].userTransaction[i].transactionAmount <<
			" to " << users[thisUserIndex].userTransaction[i].recepient << endl;
		if (i == index - 4)
			break;
	}

}



void addEmployee(vector<user>& users) {
	user newEmployee;
	cout << "Enter employee name " << endl;
	cin >> newEmployee.userAccount.userName;
	cout << "Enter employee email " << endl;
	cin >> newEmployee.userAccount.email;
	while (findEmail(newEmployee.userAccount.email, users)|| newEmployee.userAccount.email.find("@employee.bank")==string::npos) {
		cout << "Email already in use enter another one make sure that your email contains @employee.bank" << endl;
		cin >> newEmployee.userAccount.email;
	}
	cout << "Enter employee Password " << endl;
	cin >> newEmployee.userAccount.password;

	users.push_back(newEmployee);
}

void freeze(int accNum, vector<user>& users)
{
	if (!find(accNum, users)) {
		cout << "this user doesn't exist" << endl;
	}
	else if (find(accNum, users)) {
		users[thisUserIndex].frozen = true;
		cout << "frozen" << endl;
	}

}
void unfreeze(int accNum, vector<user>& users)
{
	if (!find(accNum, users)) {
		cout << "this user doesn't exist" << endl;
	}
	else if (find(accNum, users)) {
		users[thisUserIndex].frozen = false;
		cout << "active" << endl;
	}

}
void exit(vector<user> users) {
	write(users);
}

