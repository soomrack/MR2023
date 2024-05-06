#include <stdio.h>
#include <math.h>
int main()
{
	float credit = 20000000; //вся сумма кредита
	float years = 20; //кол-во лет
	float salary = 200000; //ЗП сотрудников
	float food = 15000; //Сколько Боб платит за еду
	float inflation_flat = credit * pow(1.07, 20); //считаем стоимость кв-ры после инфляции
	printf("Flat after inflation = %f \n", inflation_flat);

	float total_months = years * 12; //сколько всего месяцев платят кредит
	float bet_mortgage = 0.07; //пр-я ставка за ипотеку
	float r = bet_mortgage / 12; //пр-я ставка за ипотеку за 1 месяц
	float n = total_months; //для простоты обозначил одной буквой, хотя лучше меньше переменных

	float payment_bob = credit * ((r * pow(1 + r, n)) / (pow(1 + r, n) - 1));//Сколько платит в месяц Боб
	printf("Bob pays per month = %f \n", payment_bob);
	
	


	float payment_bob_bank = 12 * (salary - payment_bob - food); //сколько Боб отложил за год в банк 
	float payment_bob_bank1 = 0; //вспомогательная переменная
	int i = 0;
	while (i<20) //сколько Боб получил от Банка за 20 лет
	{
		payment_bob_bank1 += payment_bob_bank;
		payment_bob_bank1 *= 1.09;
		i++;
	}
	printf("Bob received from the bank for 1 year = %f \n", payment_bob_bank);
	printf("Bob received from the bank for 20 years = %f \n", payment_bob_bank1);
	float bob_capital = payment_bob_bank1; //капитал боба - это столько, сколько он получил от банка
	printf("Bob's capital = %f \n", bob_capital);

	
	
	//float flat_cost = 30000; //Сколько Алиса платит за месяц в квартиру
	float payment_alice = payment_bob; //Алиса вкладывает в банк 

	float payment_alice_bank = 12 * payment_alice; //сколько Алиса отложила за год в банк 
	float payment_alice_bank1 = 0; //вспомогательная переменная
	int j = 0;
	while (j<20) //сколько Алиса получила от Банка за 20 лет
	{
		payment_alice_bank1 += payment_alice_bank;
		payment_alice_bank1 *= 1.09;
		j++;
	}
	printf("Alice received from the bank for 20 years = %f \n", payment_alice_bank);
	printf("Alice received from the bank for 20 years = %f \n", payment_alice_bank1);
	float alice_capital = payment_alice_bank1 - inflation_flat; //капитал Алисы - это столько, сколько она накопила с вычетом стоимости квартиры
	printf("Alice's capital = %f \n", alice_capital);

	if (alice_capital > bob_capital)
	{
		printf("Alice will have more capital! \n");
	}
	else
	{
		printf("Bob will have more capital! \n");
	}
}