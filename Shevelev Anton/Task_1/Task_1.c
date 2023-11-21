#include <stdio.h>
#include <math.h>


const float percent = 0.07; // инфляция
const float SAL = 200000; // зарплата
const float money = 19000000;

float cap_bob(float traty, float proc_mes, float remont) // ( сколько в месяц тратит Боб, ставка по ипотеке,месячная цена ремонта) 
{
	float sal;
	proc_mes = proc_mes / 12;
	float cap = 0;
	float dolg_proc = money * (proc_mes * (powf(1 + proc_mes, 360)) / (powf(1 + proc_mes, 360) - 1));
	for (int i = 1; i < 360; i++)
	{
		sal = SAL * powf(1 + percent, i  / 12);
		cap += sal;
		if (i >= 60)
		{
			remont = 0;
		}
		cap = (cap - dolg_proc - ((traty + remont) * powf(1 + (percent / 12), i))) * (1 + (0.11 / 12));

	}
	cap = cap + 20000000*(powf(1 + percent, 30));
	printf("\nBob's money: ");
	printf("%f", cap);
	return cap;
};


float cap_alice(float traty, float arenda) // (траты Алисы, аренда (месяц))
{
	float sal;
	float cap = 1000000;
	for (int i = 1; i < 360; i++) // запускаем цикл
	{
		sal = SAL * powf(1 + percent, i / 12); // а ведь у Алисы зп индексируется((
		cap += sal;
		cap = (cap - ((traty + arenda) * powf(1 + (percent / 12), i))) * (1 + (0.11 / 12)); //тут все ясно, 

	}
	printf("\nAlice's money: ");
	printf("%f", cap);
	return cap;
};


int main()
{
	cap_bob(50000, 0.07, 10000);
	cap_alice(50000,30000);	
	return 0;
}
