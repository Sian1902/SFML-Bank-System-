#include<iostream>
#include <fstream>
#include <vector>
#include<sstream>
using namespace std;
int thisUserIndex = 0;
int months;
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




//second video
bool validBalance(user users, float amount);
void loan(vector<user>& users, float amount);
void Withdraw(vector<user>& users);
void transfer(vector<user>& users);
void viewTransactions(vector<user> users);



//third video
void write(vector<user> users);
void read(vector<user>& users);


int main() {
	vector<user> users;
	read(users);
	login(users);
	Withdraw(users);
	write(users);

	
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
 

//second video
bool validBalance(user users, float amount) {



	if (users.balance - amount <= 0) {
		return false;

	}
	 if (amount < 50) {
		return false;

	}

		return true;


}
void loan(vector<user>& users, float amount) {
	transaction loanTransaction;

	if (amount * 0.25 >= users[thisUserIndex].balance) {
		cout << "Rejected due to low balance " << endl;
	}


	else {
		if (amount > 100000) {
			months = ((amount + users[thisUserIndex].balance) / amount) * 6;
		}
		else {
			months = (amount + users[thisUserIndex].balance) / amount;
		}
		cout << "loan is accepted and have to be returned by " << months << " months" << endl;

		loanTransaction.transactionType = "loan";
		loanTransaction.transactionAmount = amount;
		users[thisUserIndex].balance += amount;
		users[thisUserIndex].transactionCount++;
		users[thisUserIndex].userTransaction.push_back(loanTransaction);

	}
}
void Withdraw(vector<user>& users) {
	float amount;
	transaction withdrawTransaction;
	cout << "Please enter the amount needed to withdraw"<<endl;
	cin >> amount;
	if (!validBalance(users[thisUserIndex],amount)) {
		cout << "Not enough balance"<<endl;
	}
	else {
		users[thisUserIndex].balance -= amount;
		users[thisUserIndex].transactionCount++;
		cout << withdrawTransaction.transactionAmount << endl;
		users[thisUserIndex].userTransaction.push_back(withdrawTransaction);
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = "noRecepient";
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "withdrawl";

		cout << "you have withdrawn " << amount << " with remaining balance " << users[thisUserIndex].balance << " " << "in your account "<<endl;
		cout << thisUserIndex << endl;
	}

};
void transfer(vector<user>& users) {
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
			// saving transaction for the sender
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = accNumString;
			users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "transfer";

			// saving transaction for the reciever 
			users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].transactionAmount = amount;
			users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].recepient = to_string(users[thisUserIndex].accountNum);
			users[anotherUserIndex].userTransaction[users[anotherUserIndex].transactionCount - 1].transactionType = "transfer";
			cout << "You have transferred amount of " << amount << " to the account " << accNum << endl;
		}
		else {
			cout << "This acount does not exist"<<endl;
		}
	}
};
void viewTransactions(vector<user> users) {
	int index = users[thisUserIndex].transactionCount - 1;
	for (int i = index; i >= 0; i--) {
		cout << "Transaction of type " << users[thisUserIndex].userTransaction[i].transactionType <<
			" with amount of " << users[thisUserIndex].userTransaction[i].transactionAmount <<
			" to " << users[thisUserIndex].userTransaction[i].recepient << endl;
		if (i == index - 4)
			break;
	}
}

//third video
void write(vector<user> users) {

	fstream out("userData.txt", ios::out);
	if (!out) {
		cout << "file not found";
		return;
	}
	for (int i = 0; i < users.size() - 1; i++) {
		out << users[i].accountNum << " " << users[i].userAccount.userName << " " << users[i].userAccount.email << " " << users[i].phoneNumber << " " <<
			users[i].balance << " " << users[i].transactionCount << " " << users[i].age << " " << users[i].userAccount.password << " " << users[i].frozen << endl;
		for (int j = 0; j < users[i].transactionCount; j++) {
			out << users[i].userTransaction[j].recepient << " " << users[i].userTransaction[j].transactionType << " " << users[i].userTransaction[j].transactionAmount << endl;
		}

	}
	out.close();
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
}
