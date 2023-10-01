#include <stdio.h>
#include <math.h>


//����������
typedef long long int Money;  // �������

int YEARS = 0;
int MONTH = 240;  // ������
<<<<<<< HEAD
double CREDITPERCENT = 0.07;  // ������� �� �������
double m_koef = 0.07 / 12;  // ����� ������� �������
=======
int FLAT_TAX = 0.05;
double M_KOEF = 0.07 / 12;  // ����� ������� �������
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0

Money MORTAGE = 19 * 1000 * 1000 * 100;  // ����� �������
Money MORTAGE_PAYMENT;  // ������ �� �������
Money FLAT = 20 * 1000 * 1000 * 100;  // ��������� ��������
Money DEPOSIT_BONUS = 5 * 1000 * 1000 * 100;  // ������� ���������� ������ � �����

<<<<<<< HEAD

struct Person
{
	Money balance;  //���-�� ����� ����� �������� �� �����
	Money bank;  //���� � �����
	Money total;  //�������� ���������
	Money salary;  
	Money rent;  //��������� ������
	double deposit;  //������� ����� � �����
=======
struct Person{
    Money balance;  // ���-�� ����� ����� �������� �� �����
    Money bank;  // ���� � �����
    Money capital;  // �������� ���������
    Money salary;  
    Money rent;  // ��������� ������
    Money spending;
    double deposit;  // ������� ����� � �����
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
};

struct Person Alice;
struct Person Bob;

void initialization_Alice()
{
<<<<<<< HEAD
	Alice.balance = 0;
	Alice.bank = 1 * 1000 * 1000 * 100;
	Alice.total = 0;
	Alice.salary = 200 * 1000 * 100;
	Alice.rent = 30 * 1000 * 100;
	Alice.deposit = 0.09;
=======
    Alice.bank = 1 * 1000 * 1000 * 100;
    Alice.capital = 0;
    Alice.salary = 200 * 1000 * 100;
    Alice.rent = 30 * 1000 * 100;
    Alice.deposit = 0.09;
    Alice.spending = 15 * 1000 * 100;
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
}


void initialization_Bob()
{
<<<<<<< HEAD
	Bob.balance = 0;
	Bob.bank = 0;
	Bob.total = 0;
	Bob.salary = 200 * 1000 * 100;
	Bob.rent = 0;
	Bob.deposit = 0.09;
}


void creditpay()  //������ ������� �� �������
{
	CREDITPAYMENT = CREDIT * ((m_koef * pow(1 + m_koef, MONTH)) / (pow(1 + m_koef, MONTH) - 1));  //������ �� �������
}


void Alice_free_mooney()
{
	Alice.balance = Alice.salary - Alice.rent;  // ����������� ������� �����
}


void Bob_free_mooney()
{
	Bob.balance = Bob.salary - CREDITPAYMENT;  //����������� ������� �����
}


void count_Alice(int now_year, int now_month)  //������ ������� �����
{
	int year = 0;
	int i;
	Money deposit_bonus = 5 * 1000 * 1000 * 100;  //������� ���������� ������ � �����
	for (i = 0; i <= MONTH; ++i)
	{
		if (i % 12 == 0)  //���������� ����
		{
			year += 1;
		}

		if ((year == now_year) && (i % 12 == now_month))  //����� ������ ��������
		{
			Alice.balance = 0;
		}

		if (Alice.bank / deposit_bonus == 1)  //���������� ������
		{
			deposit_bonus += 5 * 1000 * 1000 * 100;
			Alice.deposit += 0.01;
		}

		if ((year % 10 == 0) && (i % 12 == 0))  //����� �� �������
		{
			Alice.bank -= 500 * 1000 * 100;
		}

		Alice.bank += Alice.bank * (Alice.deposit / 12);
		Alice.bank -= Alice.bank * (0.07 / 12);
		Alice.bank += Alice.balance;
	}
}


void count_Bob(int now_year, int now_month)  //������ ������� ����
{
	int year = 0;
	int i;
	Money deposit_bonus = 5 * 1000 * 1000 * 100;  //������� ���������� ������ � �����
	for (i = 0; i <= MONTH; ++i)
	{
		if (i % 12 == 0)  //���������� ����
		{
			year += 1;
		}

		if (Bob.bank / deposit_bonus == 1)  //���������� ������ � �����
		{
			deposit_bonus += 5 * 1000 * 1000 * 100;
			Bob.deposit += 0.01;
		}

		Bob.bank += Bob.bank * (Bob.deposit / 12);
		Bob.bank -= Bob.bank * (0.07 / 12);
		Bob.bank += Bob.balance;
	}
}


void count_Flat()  //������ ��������� ��������
{
	for (int i = 0; i <= MONTH; ++i)
	{
		FLAT += FLAT * (0.01 / 12);
	}
}


void final_Alice()  //��������� ������ ����� � ������
{
	Alice.total = Alice.bank / 100;
}


void final_Bob()  //��������� ������ ���� � ������
{
	Bob.total = (Bob.bank + FLAT) / 100;
}


void result()  //����� ����������
{
	printf("%lld   %lld", Alice.total, Bob.total);
=======
    Bob.bank = 0;
    Bob.capital = 0;
    Bob.salary = 200 * 1000 * 100;
    Bob.rent = 0;
    Bob.deposit = 0.09;
    Bob.spending = 15 * 1000 * 100;
}


void MORTAGE_pay()  // ������ ������� �� �������
{
    MORTAGE_PAYMENT = MORTAGE * ((M_KOEF * pow(1 + M_KOEF, MONTH)) / (pow(1 + M_KOEF, MONTH) - 1));  // ������ �� �������
}


void years_count(int input)  // ������� ���
{
    if (input % 12 == 0) {
        YEARS += 1;
    }
}


void Alice_loses_salary(int condition_year, int condition_month, int now_month)
{
    if ((YEARS == condition_year) && (now_month % 12 == condition_month)) {  // ����� ������ ��������
        Alice.salary = 0;
    }
    else {
        Alice.salary = 200 * 1000 * 100;
    }
}


void deposit_bonus() 
{
    
    if (Alice.bank / DEPOSIT_BONUS == 1) {  // ���������� ������
        DEPOSIT_BONUS += 5 * 1000 * 1000 * 100;
        Alice.deposit += 0.01;
    }
    if (Bob.bank / DEPOSIT_BONUS == 1) {  // ���������� ������ � �����
        DEPOSIT_BONUS += 5 * 1000 * 1000 * 100;
        Bob.deposit += 0.01;
    }
}


void dentist(month)
{
    if ((YEARS % 10 == 0) && (month % 12 == 0)) {  // ����� �� �������
        Alice.bank -= 500 * 1000 * 100;
    }
}


void flat_tax(month)
{
    if ((YEARS % 1 == 0) && (month % 12 == 0)) { 
        Bob.bank -= FLAT*FLAT_TAX;
    }
}


Alice_spend_money(month)
{
    if ((YEARS % 1 == 0) && (month % 12 == 0)) {
        Alice.spending += Alice.spending * 0.03;
    }
}


Bob_spend_money(month)
{
    if ((YEARS % 1 == 0) && (month % 12 == 0)) {
        Bob.spending += Bob.spending * 0.03;
    }
}


void count_Alice(int condition_year, int condition_month)  // ������ ������� �����
{
    int month;
    YEARS = 0;
    DEPOSIT_BONUS = 5 * 1000 * 1000 * 100;

    for (month = 0; month<= MONTH; ++month){

        years_count(month);
        Alice_loses_salary(condition_year, condition_month, month);
        deposit_bonus();
        dentist(month);
        Alice_spend_money(month);

        Alice.bank += Alice.salary;
        Alice.bank -= Alice.spending - Alice.rent;
        Alice.bank += Alice.bank * (Alice.deposit / 12);
        Alice.bank -= Alice.bank * (0.07 / 12);
        Alice.bank += Alice.balance;
    }
}


void count_Bob(int condition_year, int condition_month)  // ������ ������� ����
{
    YEARS = 0;
    DEPOSIT_BONUS = 5 * 1000 * 1000 * 100;
    int month;
   
    for (month = 0;month<= MONTH; ++month){
        years_count(month);
        deposit_bonus();
        flat_tax(month);
        Bob_spend_money(month);

        Bob.bank += Bob.salary;
        Bob.bank -= Bob.spending - MORTAGE_PAYMENT;
        Bob.bank += Bob.bank * (Bob.deposit / 12);
        Bob.bank -= Bob.bank * (0.07 / 12);
        FLAT += FLAT * (0.01 / 12);
    }

}


void final_Alice()  // ��������� ������ ����� � ������
{
    Alice.capital = Alice.bank / 100;
}


void final_Bob()  // ��������� ������ ���� � ������
{
    Bob.capital = (Bob.bank + FLAT) / 100;
}


void result()  // ����� ����������
{
    printf("%lld   %lld", Alice.capital, Bob.capital);
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
}


main()
{
<<<<<<< HEAD
	creditpay();
	initialization_Alice();
	initialization_Bob();
	Alice_free_mooney();
	Bob_free_mooney();
	count_Flat();
	count_Alice(15, 8);
	count_Bob(1, 3);
	final_Alice();
	final_Bob();
	result();
=======
    MORTAGE_pay();
    initialization_Alice();
    initialization_Bob();
    count_Alice(1, 8);
    count_Bob(1, 3);
    final_Alice();
    final_Bob();
    result();
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
}