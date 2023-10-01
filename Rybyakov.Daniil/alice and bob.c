#include <stdio.h>
#include <math.h>


//переменные
typedef long long int Money;  // копейки

int YEARS = 0;
int MONTH = 240;  // месяцы
<<<<<<< HEAD
double CREDITPERCENT = 0.07;  // процент по кредиту
double m_koef = 0.07 / 12;  // коэфф расчета платежа
=======
int FLAT_TAX = 0.05;
double M_KOEF = 0.07 / 12;  // коэфф расчета платежа
>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0

Money MORTAGE = 19 * 1000 * 1000 * 100;  // сумма кредита
Money MORTAGE_PAYMENT;  // платеж по кредиту
Money FLAT = 20 * 1000 * 1000 * 100;  // стоимость квартиры
Money DEPOSIT_BONUS = 5 * 1000 * 1000 * 100;  // условие увеличения ставки в банке

<<<<<<< HEAD

struct Person
{
	Money balance;  //кол-во денег после расходов на жизнь
	Money bank;  //счте в банке
	Money total;  //конечный результат
	Money salary;  
	Money rent;  //стоимость аренды
	double deposit;  //процент счета в банке
=======
struct Person{
    Money balance;  // кол-во денег после расходов на жизнь
    Money bank;  // счте в банке
    Money capital;  // конечный результат
    Money salary;  
    Money rent;  // стоимость аренды
    Money spending;
    double deposit;  // процент счета в банке
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


void creditpay()  //расчет платежа по кредиту
{
	CREDITPAYMENT = CREDIT * ((m_koef * pow(1 + m_koef, MONTH)) / (pow(1 + m_koef, MONTH) - 1));  //платеж по кредиту
}


void Alice_free_mooney()
{
	Alice.balance = Alice.salary - Alice.rent;  // ежемесячный остаток денег
}


void Bob_free_mooney()
{
	Bob.balance = Bob.salary - CREDITPAYMENT;  //ежемесячный остаток денег
}


void count_Alice(int now_year, int now_month)  //расчет баланса алисы
{
	int year = 0;
	int i;
	Money deposit_bonus = 5 * 1000 * 1000 * 100;  //условие увеличения ставки в банке
	for (i = 0; i <= MONTH; ++i)
	{
		if (i % 12 == 0)  //вычисление года
		{
			year += 1;
		}

		if ((year == now_year) && (i % 12 == now_month))  //Алиса теряет зарплату
		{
			Alice.balance = 0;
		}

		if (Alice.bank / deposit_bonus == 1)  //увеличение ставки
		{
			deposit_bonus += 5 * 1000 * 1000 * 100;
			Alice.deposit += 0.01;
		}

		if ((year % 10 == 0) && (i % 12 == 0))  //траты на зубного
		{
			Alice.bank -= 500 * 1000 * 100;
		}

		Alice.bank += Alice.bank * (Alice.deposit / 12);
		Alice.bank -= Alice.bank * (0.07 / 12);
		Alice.bank += Alice.balance;
	}
}


void count_Bob(int now_year, int now_month)  //расчет баланса боба
{
	int year = 0;
	int i;
	Money deposit_bonus = 5 * 1000 * 1000 * 100;  //условие увеличения ставки в банке
	for (i = 0; i <= MONTH; ++i)
	{
		if (i % 12 == 0)  //вычисление года
		{
			year += 1;
		}

		if (Bob.bank / deposit_bonus == 1)  //увеличения ставки в банке
		{
			deposit_bonus += 5 * 1000 * 1000 * 100;
			Bob.deposit += 0.01;
		}

		Bob.bank += Bob.bank * (Bob.deposit / 12);
		Bob.bank -= Bob.bank * (0.07 / 12);
		Bob.bank += Bob.balance;
	}
}


void count_Flat()  //расчет стоимости квартиры
{
	for (int i = 0; i <= MONTH; ++i)
	{
		FLAT += FLAT * (0.01 / 12);
	}
}


void final_Alice()  //финальный баланс алисы в рублях
{
	Alice.total = Alice.bank / 100;
}


void final_Bob()  //финальный баланс боба в рублях
{
	Bob.total = (Bob.bank + FLAT) / 100;
}


void result()  //вывод результата
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


void MORTAGE_pay()  // расчет платежа по кредиту
{
    MORTAGE_PAYMENT = MORTAGE * ((M_KOEF * pow(1 + M_KOEF, MONTH)) / (pow(1 + M_KOEF, MONTH) - 1));  // платеж по кредиту
}


void years_count(int input)  // счетчик лет
{
    if (input % 12 == 0) {
        YEARS += 1;
    }
}


void Alice_loses_salary(int condition_year, int condition_month, int now_month)
{
    if ((YEARS == condition_year) && (now_month % 12 == condition_month)) {  // Алиса теряет зарплату
        Alice.salary = 0;
    }
    else {
        Alice.salary = 200 * 1000 * 100;
    }
}


void deposit_bonus() 
{
    
    if (Alice.bank / DEPOSIT_BONUS == 1) {  // увеличение ставки
        DEPOSIT_BONUS += 5 * 1000 * 1000 * 100;
        Alice.deposit += 0.01;
    }
    if (Bob.bank / DEPOSIT_BONUS == 1) {  // увеличения ставки в банке
        DEPOSIT_BONUS += 5 * 1000 * 1000 * 100;
        Bob.deposit += 0.01;
    }
}


void dentist(month)
{
    if ((YEARS % 10 == 0) && (month % 12 == 0)) {  // траты на зубного
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


void count_Alice(int condition_year, int condition_month)  // расчет баланса алисы
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


void count_Bob(int condition_year, int condition_month)  // расчет баланса боба
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


void final_Alice()  // финальный баланс алисы в рублях
{
    Alice.capital = Alice.bank / 100;
}


void final_Bob()  // финальный баланс боба в рублях
{
    Bob.capital = (Bob.bank + FLAT) / 100;
}


void result()  // вывод результата
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