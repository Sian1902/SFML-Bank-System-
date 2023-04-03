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
// GUI global variables 

Font rockebFont, britanicFont, berlinSansFont;
Texture headerTexture, closeTexture, mininmizeTexture, optionsTexture, backgroundTexture, bigButtonTexture, smallButtonTexture, darkBackgroundTexture, darkBackgroundSmallTexture, enterValuesBackgroundTexture;


RenderWindow window(sf::VideoMode(1920, 1080), "HaithamBank", Style::Default);

//system entities struct
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

// GUI entities struct 

struct button {
	
	Text btnText;
	Sprite btnSprite;
};
struct balancePanel {
	Sprite panel;
	Text balnceText;
	Text amountText;
};

// system functions  

bool findPhone(string phoneNumber, vector<user> users);
bool findEmail(string email, vector<user> users);
bool find(string email, string password, vector<user> users);
bool find(int accounNumber, vector<user> users);

bool addEmployee(vector<user>& users);
bool signUp(vector<user>& users);
bool login(vector<user> users);
bool freeze(int accountNumber, vector<user>& users);
bool unFreeze(int accountNumber, vector<user>& users);

//second video
bool validBalance(user users, float amount);
void loan(vector<user>& users, float amount);
void Withdraw(vector<user>& users);
void transfer(vector<user>& users);
void viewTransactions(vector<user> users);

//GUI functions

void btnIntializer(button btn[], int arrSize);
void sideButtonDrawer(button btn[] ,int arrSize);
void texturesAndFonts();
void balancePanelIntializer(balancePanel& panel);
void balancePanelDrawer(balancePanel& panel);
int main() {
	// loading fonts and textures
	texturesAndFonts();

	////sprites 
	Sprite background, header, closeBtn, minimizeBtn, optionsBtn, bigButton , darkBackground,  enterValuesBackground[2];
	background.setTexture(backgroundTexture);
	header.setTexture(headerTexture);
	closeBtn.setTexture(closeTexture);
	minimizeBtn.setTexture(mininmizeTexture);
	optionsBtn.setTexture(optionsTexture);
	bigButton.setTexture(bigButtonTexture);
	darkBackground.setTexture(darkBackgroundTexture);
	for (int i = 0;i < 2;i++) {
		enterValuesBackground[i].setTexture(enterValuesBackgroundTexture);
	}


	////texts
	Text haithamBankText, transferBalance1, transferBalance2, withdraw, withdraw1, lastTransactions, askForLoan, askForLoan1, amount, toText, goodMorning, userName;
	////background modification
	background.setScale(1.5, 1.5);
	background.setPosition(-50, 0);
	////header modification
	header.setPosition(0, 0);
	header.setScale(1.11, 1.11);
	//buttons modification
	closeBtn.setPosition(1850, 30);
	minimizeBtn.setPosition(1780, 45);
	optionsBtn.setPosition(1200, 75);
	//good morning text
	goodMorning.setFont(berlinSansFont);
	goodMorning.setString("Good Morning,");
	goodMorning.setCharacterSize(60);
	goodMorning.setFillColor(Color::White);
	goodMorning.setPosition(50, 30);
	//username text
	userName.setFont(berlinSansFont);
	userName.setString("User");
	userName.setCharacterSize(70);
	userName.setFillColor(Color::White);
	userName.setPosition(100, 80);

	//haitham bank text
	haithamBankText.setString("Haitham Bank");
	haithamBankText.setFont(berlinSansFont);
	haithamBankText.setCharacterSize(70);
	haithamBankText.setFillColor(Color::White);
	haithamBankText.setPosition(750, 45);

	//big dark background
	darkBackground.setPosition(710, 500);
	darkBackground.setScale(1.11, 1.105);
	////inside big dark box when tranferBalance
	bigButton.setPosition(1000, 530);
	bigButton.setScale(1.1, 1.1);
	for (int i = 0;i < 2;i++) {
		enterValuesBackground[i].setPosition(1000, 650 + (i * 100));
	}
	//transfer balance text
	transferBalance2.setFont(rockebFont);
	transferBalance2.setString("Transfer  Balance");
	transferBalance2.setFillColor(Color::White);
	transferBalance2.setPosition(1100, 555);
	//withdraw text
	withdraw1.setFont(rockebFont);
	withdraw1.setString("Withdraw");
	withdraw1.setFillColor(Color::White);
	withdraw1.setPosition(1130, 548);
	withdraw1.setCharacterSize(40);
	//ask for loan text
	askForLoan1.setFont(rockebFont);
	askForLoan1.setString("Ask for a Loan");
	askForLoan1.setFillColor(Color::White);
	askForLoan1.setPosition(1120, 555);

	//amount text
	amount.setFont(rockebFont);
	amount.setString("Amount");
	amount.setFillColor(Color::White);
	amount.setPosition(820, 670);
	//to text
	toText.setFont(rockebFont);
	toText.setString("To");
	toText.setFillColor(Color::White);
	toText.setPosition(870, 770);



	button sideButtons[4];
	balancePanel panel;
	balancePanelIntializer(panel);
	btnIntializer(sideButtons, 4);
	while (window.isOpen())
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::M)) {
			//window.setSize(0,1080);
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(Color::Transparent);
		window.draw(background);
		//header
		window.draw(header);
		window.draw(closeBtn);
		window.draw(minimizeBtn);
		window.draw(optionsBtn);
		window.draw(haithamBankText);
		window.draw(goodMorning);
		window.draw(userName);
		balancePanelDrawer(panel);
		//large dark box
		window.draw(darkBackground);
		//inside big dark box when transferBalance
		window.draw(bigButton);
		for (int i = 0;i < 2;i++) {
			window.draw(enterValuesBackground[i]);
		}
		window.draw(transferBalance2);
		window.draw(amount);
		window.draw(toText);
		//inside big box when withdraw or ask for loan
		/* window.draw(bigButton);
		for (int i = 0;i < 1;i++) {
			window.draw(enterValuesBackground[i]);
		}
		if withdraw
			window.draw(withdraw1);
		if ask for loan
			window.draw(askForLoan1);
		window.draw(amount);*/

		//buttons beside big box
		sideButtonDrawer(sideButtons, 4);

		window.draw(transferBalance1);
		window.draw(withdraw);
		window.draw(lastTransactions);
		window.draw(askForLoan);
		window.display();
	}

	return 0;
	
}

// functions implementation 


// system functions 

bool login(vector<user> users) {
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

///GUI functiuons

void btnIntializer(button btn[], int arrSize) {


	rockebFont.loadFromFile("Fonts/rockeb.ttf");
	smallButtonTexture.loadFromFile("Assets/samll button.png");
	string btnstring[4] = { "Transfer Balance","Withdraw","Last Transactions","Ask for a Loan" };

	for (int i = 0; i < arrSize; i++) {
		btn[i].btnSprite.setTexture(smallButtonTexture);
		btn[i].btnText.setFont(rockebFont);
		btn[i].btnText.setFillColor(Color::White);
		btn[i].btnSprite.setPosition(80, 500 + ((i ) * 115));
		btn[i].btnSprite.setScale(1.2, 1.2);
		btn[i].btnText.setString(btnstring[i]);
	}
	btn[0].btnText.setPosition(130, 525);
	btn[1].btnText.setPosition(185, 643);
	btn[2].btnText.setPosition(125, 760);
	btn[3].btnText.setPosition(150, 875);
}
void texturesAndFonts() {
	headerTexture.loadFromFile("Assets/header.png");
	closeTexture.loadFromFile("Assets/close.png");
	mininmizeTexture.loadFromFile("Assets/minimize.png");
	optionsTexture.loadFromFile("Assets/options.png");
	backgroundTexture.loadFromFile("Assets/background.png");
	bigButtonTexture.loadFromFile("Assets/big button.png");
	smallButtonTexture.loadFromFile("Assets/samll button.png");
	darkBackgroundTexture.loadFromFile("Assets/medium dark background.png");
	darkBackgroundSmallTexture.loadFromFile("Assets/small dark background.png");
	enterValuesBackgroundTexture.loadFromFile("Assets/enter values background.png");
	rockebFont.loadFromFile("Fonts/rockeb.ttf");
	britanicFont.loadFromFile("Fonts/BRITANIC.ttf");
	berlinSansFont.loadFromFile("Fonts/Berlin Sans FB Regular.ttf");
}
void balancePanelIntializer(balancePanel& panel) {
	panel.panel.setTexture(darkBackgroundSmallTexture);
	panel.panel.setPosition(60, 250);
	panel.panel.setScale(1.16, 1.07);
	panel.balnceText.setFont(rockebFont);
	panel.balnceText.setString("Balance");
	panel.balnceText.setCharacterSize(80);
	panel.balnceText.setFillColor(Color::White);
	panel.balnceText.setPosition(150, 260);
	panel.amountText.setFont(rockebFont);
	panel.amountText.setString("0,0 EGP");
	panel.amountText.setCharacterSize(60);
	panel.amountText.setFillColor(Color::White);
	panel.amountText.setPosition(170, 350);

}
void sideButtonDrawer(button btn[], int arrSize) {
	for (int i = 0; i < arrSize; i++) {
		window.draw(btn[i].btnSprite);
		window.draw(btn[i].btnText);
	}
}
void balancePanelDrawer(balancePanel& panel) {
	window.draw(panel.panel);
	window.draw(panel.balnceText);
	window.draw(panel.amountText);

}

