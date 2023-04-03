#include<iostream>
#include <fstream>
#include <vector>
#include<sstream>
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;
int thisUserIndex = 0;
int months;
int anotherUserIndex;

RenderWindow window(sf::VideoMode(1920, 1080), "HaithamBank", Style::Fullscreen);
Font rockebFont, britanicFont, berlinSansFont;
Texture headerTexture, closeTexture, mininmizeTexture, optionsTexture, backgroundTexture, bigButtonTexture, smallButtonTexture, darkBackgroundTexture, darkBackgroundSmallTexture, enterValuesBackgroundTexture;


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

struct bigDarkBox {
	Sprite background;
	Sprite valueField1;
	Sprite valueField2;
	Text amountTxt;
	Text Totxt;
};
struct button {
	Sprite buttonSprite;
	Text text;
};
struct Header {
	Sprite background, closeBtn, minimizeBtn, optionsBtn;
	Text goodMorning, user, haithamBank;

};

void setbigDarkBoxTransferBalance(bigDarkBox&, button&);
void setHeader(Header&);
void setButton(button&);
void drawBigBox(bigDarkBox, button);
void drawHeader(Header);

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


int main() {
	//
	//////textures and loading them
	backgroundTexture.loadFromFile("Assets/background.png");
	smallButtonTexture.loadFromFile("Assets/samll button.png");
	darkBackgroundSmallTexture.loadFromFile("Assets/small dark background.png");
	////sprites 
	Sprite background, header, closeBtn, minimizeBtn, optionsBtn, bigButton, smallButton[6], darkBackground, mediumDarkBackground, enterValuesBackground[2];
	background.setTexture(backgroundTexture);
	for (int i = 0;i < 6;i++) {
		smallButton[i].setTexture(smallButtonTexture);
	}
	mediumDarkBackground.setTexture(darkBackgroundSmallTexture);
	////fonts and loading them
	rockebFont.loadFromFile("Fonts/rockeb.ttf");
	britanicFont.loadFromFile("Fonts/BRITANIC.ttf");
	berlinSansFont.loadFromFile("Fonts/Berlin Sans FB Regular.ttf");
	////texts
	Text haithamBankText, balanceText, userBalance, transferBalance1, transferBalance2, withdraw, withdraw1, lastTransactions, askForLoan, askForLoan1, amount, toText, goodMorning, userName;
	////background modification
	background.setScale(1.5, 1.5);
	background.setPosition(-50, 0);
	//small dark background
	mediumDarkBackground.setPosition(60, 250);
	mediumDarkBackground.setScale(1.16, 1.07);
	////inside small box
	// balance text
	balanceText.setFont(rockebFont);
	balanceText.setString("Balance");
	balanceText.setCharacterSize(80);
	balanceText.setFillColor(Color::White);
	balanceText.setPosition(150, 260);
	//user's balance text
	userBalance.setFont(rockebFont);
	userBalance.setString("0,0 EGP");
	userBalance.setCharacterSize(60);
	userBalance.setFillColor(Color::White);
	userBalance.setPosition(170, 350);



	////Buttons beside big box
	for (int i = 2;i < 6;i++) {
		smallButton[i].setPosition(80, 500 + ((i - 2) * 115));
		smallButton[i].setScale(1.2, 1.2);
	}
	//transfer balance text
	transferBalance1.setFont(rockebFont);
	transferBalance1.setString("Transfer Balance");
	transferBalance1.setFillColor(Color::White);
	transferBalance1.setPosition(130, 525);
	//withdraw text
	withdraw.setFont(rockebFont);
	withdraw.setString("Withdraw");
	withdraw.setFillColor(Color::White);
	withdraw.setPosition(185, 643);
	//last transcations text
	lastTransactions.setFont(rockebFont);
	lastTransactions.setString("Last Transactions");
	lastTransactions.setFillColor(Color::White);
	lastTransactions.setPosition(125, 760);
	//ask for loan text
	askForLoan.setFont(rockebFont);
	askForLoan.setString("Ask for a Loan");
	askForLoan.setFillColor(Color::White);
	askForLoan.setPosition(150, 875);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		bigDarkBox bigdarkBox;
		button btn;
		Header header;
		setbigDarkBoxTransferBalance(bigdarkBox,btn);
		setHeader(header);
		window.clear();
		window.draw(background);
		////small box
		window.draw(mediumDarkBackground);
		//texts inside small box
		window.draw(balanceText);
		window.draw(userBalance);

		//buttons beside big box
		for (int i = 2;i < 6;i++) {
			window.draw(smallButton[i]);
		}
		window.draw(transferBalance1);
		window.draw(withdraw);
		window.draw(lastTransactions);
		window.draw(askForLoan);
		drawBigBox(bigdarkBox,btn);
		drawHeader(header);
		window.display();
	}

	return 0;

}
bool login(vector<user>& users) {
	user temp;
	cout << "enter email" << endl;
	cin >> temp.userAccount.email;
	cout << "enter password" << endl;
	cin >> temp.userAccount.password;
	if (!find(temp.userAccount.email, temp.userAccount.password, users)) {
		cout << "email and password doesn't match" << endl;
		return false;
	}
	if (users[thisUserIndex].frozen == true) {
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
	cout << "enter email" << endl;
	cin >> temp.userAccount.email;
	if (findEmail(temp.userAccount.email, users) || temp.userAccount.email.find("@user.bank") == string::npos) {
		cout << "email is already in use enter another one make sure to include @user.bank\n";
		return false;
	}
	cout << "enter password" << endl;
	cin >> temp.userAccount.password;
	cout << "enter phone number" << endl;
	cin >> temp.phoneNumber;
	if (findPhone(temp.phoneNumber, users)) {
		cout << "phone number already taken" << endl;
		return false;
	}
	cout << "enter age" << endl;
	cin >> temp.age;
	if (temp.age < 21) {
		cout << "invalid age" << endl;
		return false;
	}
	cout << "enter balance" << endl;
	cin >> temp.balance;
	if (temp.balance < 300) {
		cout << "balance can't be less than 300 EGP " << endl;
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
	if (findEmail(newEmployee.userAccount.email, users) || newEmployee.userAccount.email.find("@employee.bank") == string::npos) {
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
	cout << "Please enter the amount needed to withdraw" << endl;
	cin >> amount;
	if (!validBalance(users[thisUserIndex], amount)) {
		cout << "Not enough balance" << endl;
	}
	else {
		users[thisUserIndex].balance -= amount;
		users[thisUserIndex].transactionCount++;
		cout << withdrawTransaction.transactionAmount << endl;
		users[thisUserIndex].userTransaction.push_back(withdrawTransaction);
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionAmount = amount;
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].recepient = "noRecepient";
		users[thisUserIndex].userTransaction[users[thisUserIndex].transactionCount - 1].transactionType = "withdrawl";

		cout << "you have withdrawn " << amount << " with remaining balance " << users[thisUserIndex].balance << " " << "in your account " << endl;
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
			cout << "This acount does not exist" << endl;
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
//sfml Functions
void setbigDarkBoxTransferBalance(bigDarkBox& bigDarkbox, button& btn) {
	String textArr[2] = { "Amount","To" };
	darkBackgroundTexture.loadFromFile("Assets/medium dark background.png");
	enterValuesBackgroundTexture.loadFromFile("Assets/enter values background.png");
	bigDarkbox.background.setTexture(darkBackgroundTexture);
	bigDarkbox.background.setPosition(710, 500);
	bigDarkbox.background.setScale(1.11, 1.105);
	bigDarkbox.valueField1.setTexture(enterValuesBackgroundTexture);
	bigDarkbox.valueField1.setPosition(1000, 650);
	bigDarkbox.valueField2.setTexture(enterValuesBackgroundTexture);
	bigDarkbox.valueField2.setPosition(1000, 750);
	bigDarkbox.amountTxt.setFont(rockebFont);
	bigDarkbox.amountTxt.setString(textArr[0]);
	bigDarkbox.amountTxt.setFillColor(Color::White);
	bigDarkbox.amountTxt.setPosition(820, 670);
	bigDarkbox.Totxt.setFont(rockebFont);
	bigDarkbox.Totxt.setString(textArr[1]);
	bigDarkbox.Totxt.setFillColor(Color::White);
	bigDarkbox.Totxt.setPosition(870, 770);
	setButton(btn);
}
void drawBigBox(bigDarkBox bigDarkbox, button btn) {
	window.draw(bigDarkbox.background);
	window.draw(btn.buttonSprite);
	window.draw(btn.text);
	window.draw(bigDarkbox.valueField1);
	window.draw(bigDarkbox.valueField2);
	window.draw(bigDarkbox.amountTxt);
	window.draw(bigDarkbox.Totxt);
}
void setButton(button& btn) {
	String textArr[4] = {"Transfer Balance","Withdraw","Last Transactions","Ask for a Loan"};
	bigButtonTexture.loadFromFile("Assets/big button.png");
	rockebFont.loadFromFile("Fonts/rockeb.ttf");
	btn.buttonSprite.setTexture(bigButtonTexture);
	btn.buttonSprite.setPosition(1000, 530);
	btn.buttonSprite.setScale(1.1, 1.1);
	btn.text.setFont(rockebFont);
	btn.text.setFillColor(Color::White);
	btn.text.setPosition(1100, 555);
	btn.text.setString(textArr[0]);
}
void setHeader(Header& header) {
	String textArr[3] = { "Good Morning, ", "Loser","Haitham Bank" };
	headerTexture.loadFromFile("Assets/header.png");
	closeTexture.loadFromFile("Assets/close.png");
	mininmizeTexture.loadFromFile("Assets/minimize.png");
	optionsTexture.loadFromFile("Assets/options.png");
	header.background.setTexture(headerTexture);
	header.background.setPosition(0, -60);
	header.background.setScale(1.107, 1.5);
	header.closeBtn.setTexture(closeTexture);
	header.minimizeBtn.setTexture(mininmizeTexture);
	header.optionsBtn.setTexture(optionsTexture);
	header.closeBtn.setPosition(1850, 30);
	header.minimizeBtn.setPosition(1780, 45);
	header.optionsBtn.setPosition(1200, 75);
	header.goodMorning.setFont(berlinSansFont);
	header.goodMorning.setString(textArr[0]);
	header.goodMorning.setCharacterSize(60);
	header.goodMorning.setFillColor(Color::White);
	header.goodMorning.setPosition(50, 30);
	header.user.setFont(berlinSansFont);
	header.user.setString(textArr[1]);
	header.user.setCharacterSize(70);
	header.user.setFillColor(Color::White);
	header.user.setPosition(100, 80);
	header.haithamBank.setString(textArr[2]);
	header.haithamBank.setFont(berlinSansFont);
	header.haithamBank.setCharacterSize(70);
	header.haithamBank.setFillColor(Color::White);
	header.haithamBank.setPosition(750, 45);
}
void drawHeader(Header header) {
	window.draw(header.background);
	window.draw(header.closeBtn);
	window.draw(header.minimizeBtn);
	window.draw(header.optionsBtn);
	window.draw(header.haithamBank);
	window.draw(header.goodMorning);
	window.draw(header.user);
}
