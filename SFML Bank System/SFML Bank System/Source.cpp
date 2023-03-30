#include<iostream>
using namespace std;

struct account
{
	string userName;
	string email;
	string password;
};
struct transaction {
	int transactionCount;
	string transactionType;
	float transactionAmount;
	string recepient;
};
struct user {
	account userAccount;
	transaction userTransaction;
	int age;
	float balance;
	string phoneNumber;
	int accountNum;
	bool frozen=false;

};
int main() {
	
}