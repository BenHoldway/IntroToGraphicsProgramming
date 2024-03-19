#pragma once

void Task1();
void Task2();
void Task3();
void Task4();
void Task5();

class MathsExperiment
{
	float add(const float& a, const float& b);
	float subtract(const float& a, const float& b);
	float multiply(const float& a, const float& b);
	float divide(const float& a, const float& b);
};

class AccountExperiment
{
	float totalBalance;
	float interestRate;

	void PrintBalance()
	{
		cout << "\nThe total balance is: " << totalBalance;
	}

	void SetBalance(float& newBalance)
	{
		totalBalance = newBalance;
	}

	void AddToBalance(int& valueToAdd)
	{
		totalBalance += valueToAdd;
	}

	void SetInterestRate(float& _interestRate)
	{
		interestRate = _interestRate;
	}

	void ApplyInterestRate()
	{
		totalBalance *= interestRate;
	}
};
