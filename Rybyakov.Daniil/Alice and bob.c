#include <stdio.h>
#include <math.h>


//����������
typedef long long int Money;  //�������

int MONTH = 240;  // ������
double CREDITPERCENT = 0.07;  // ������� �� �������
double m_koef = 0.07 / 12;  // ����� ������� �������
double DEPOSIT = 0.09;  //�������� � �����

Money CREDIT = 19 * 1000 * 1000 * 100;  // ����� �������
Money CREDITPAYMENT;  //������ �� �������
Money FLAT = 20 * 1000 * 1000 * 100;  //��������� ��������


struct Person
{
	Money balance;
	Money bank;
	Money total;
	Money salary;
	Money rent;
};

struct Person Alice = { 0,  1 * 1000 * 1000 * 100,  0,  200 * 1000 * 100,  30 * 1000 * 100 };
struct Person Bob = { 0,  0,  0,  200 * 1000 * 100,  0 };


Money creditpay()  //������ ������� �� �������
{
	int result;
	result = CREDIT * ((m_koef * pow(1 + m_koef, MONTH)) / (pow(1 + m_koef, MONTH) - 1));  //������ �� �������
	return result;
}


int countAlice()  //������ ������� �����
{
	for (int i = 0; i <= MONTH; ++i);
	{
		Alice.bank += Alice.bank * (DEPOSIT / 12);
		Alice.bank -= Alice.bank * (0.07 / 12);
		Alice.bank += Alice.balance;
	}
	return Alice.bank;
}


int countBob()  //������ ������� ����
{
	for (int i = 0; i <= MONTH; ++i);
	{
		Bob.bank += Bob.bank * (DEPOSIT / 12);
		Bob.bank -= Bob.bank * (0.07 / 12);
		Bob.bank += Bob.balance;
	}
	return Bob.bank;
}


int countFlat()  //������ ��������� ��������
{
	for (int i = 0; i <= MONTH; ++i);
	{
		FLAT += FLAT * (0.01 / 12);
	}
	return FLAT;
}


main()
{
	CREDITPAYMENT = creditpay();

	Alice.balance = Alice.salary - Alice.rent;  // ����������� ������� �����
	Bob.balance = Bob.salary - CREDITPAYMENT;  //����������� ������� �����

	Alice.total = countAlice() / 100;
	Bob.total = (countBob() + countFlat()) / 100;

	printf("%d   %d", Alice.total, Bob.total);
}
