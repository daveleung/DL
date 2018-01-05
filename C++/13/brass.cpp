#include <iostream>
#include "brass.h"
using namespace std;

typedef std::ios_base::fmtflags format;
typedef std::streamsize precis;
format setFormat();
void restore(format f, precis p);

Brass::Brass(const string & s, long an, double bal)
{
	fullName = s;
	acctNum = an;
	balance = bal;
}

void Brass::Deposit(double amt)
{
	if (amt < 0)
		cout << "Negative depost not allowed;"
			<< "deposit is cancelled.\n";
	else
		balance += amt;
}

void Brass::Withdraw(double amt)
{
	format initialState = setFormat();
	precis prec = cout.precision(2);

	if (amt < 0)
		cout << "Withdrawal amount must be positive; "
			<< "Withdrawal canceled.\n";
	else if (amt <= balance)
		balance -= amt;
	else 
		cout << "Withdrawal amount of $" << amt
			<< " exceeds your balance.\n"
			<< "Withdrawal canceled.\n";
	restore(initialState, prec);
}
double Brass::Balance() const
{
	return balance;
}

void Brass::ViewAcct() const
{
	format initialState= setFormat();
	precis prec = cout.precision(2);
	cout << "Client: " << fullName << endl;
	cout << "Account Number: " << acctNum << endl;
	cout << "Balance: $" << balance << endl;
	restore(initialState, prec);
}

//BrassPlus Methods
BrassPlus::BrassPlus(const string & s, long an, double bal,
				double ml, double r) : Brass(s, an, bal)
{
	maxLoan = ml;
	oweBank = 0.0;
	rate = r;
}

BrassPlus::BrassPlus(const Brass & ba, double ml, double r) : Brass(ba)
{
	maxLoan = ml;
	oweBank = 0.0;
	rate = r;
}

//redefine how ViewAcct() works
void BrassPlus::ViewAcct() const
{
	format initialState = setFormat();
	precis prec = cout.precision(2);

	Brass::ViewAcct();
	cout << "Maximum loan: $" << maxLoan << endl;
	cout << "Owed to bank:$" << oweBank << endl;
	cout.precision(3);
	cout << "Loan Rate: " << 100 * rate << "%\n";
	restore(initialState, prec);
}

//redefine how
void BrassPlus::Withdraw(double amt)
{
	format initialState = setFormat();
	precis prec = cout.precision(2);

	double bal = Balance();
	if (amt <= bal)
		Brass::Withdraw(amt);
	else if (amt <= bal + maxLoan - oweBank)
	{
		double advance = amt = bal;
		oweBank += advance * (1.0 + rate);
		cout << "Bank advance:$" << advance << endl;
		cout << "Finance charge:$" << advance * rate << endl;
		Deposit(advance);
		Brass:Withdraw(amt);
	}
	else
		cout << "Credit limit exceeded. Transaction cancelled.\n";
	restore(initialState, prec);
}

format setFormat()
{
	return cout.setf(std::ios_base::fixed,
				std::ios_base::floatfield);

}

void restore(format f, precis p)
{
	cout.setf(f, std::ios_base::floatfield);
	cout.precision(p);
}

// int main()
// {
// 	return 0;
// }