#include <stdio.h>
#include <math.h>
int main()
{
	float credit = 20000000; //��� ����� �������
	float years = 20; //���-�� ���
	float salary = 200000; //�� �����������
	float food = 15000; //������� ��� ������ �� ���
	float inflation_flat = credit * pow(1.07, 20); //������� ��������� ��-�� ����� ��������
	printf("Flat after inflation = %f \n", inflation_flat);

	float total_months = years * 12; //������� ����� ������� ������ ������
	float bet_mortgage = 0.07; //��-� ������ �� �������
	float r = bet_mortgage / 12; //��-� ������ �� ������� �� 1 �����
	float n = total_months; //��� �������� ��������� ����� ������, ���� ����� ������ ����������

	float payment_bob = credit * ((r * pow(1 + r, n)) / (pow(1 + r, n) - 1));//������� ������ � ����� ���
	printf("Bob pays per month = %f \n", payment_bob);
	
	


	float payment_bob_bank = 12 * (salary - payment_bob - food); //������� ��� ������� �� ��� � ���� 
	float payment_bob_bank1 = 0; //��������������� ����������
	int i = 0;
	while (i<20) //������� ��� ������� �� ����� �� 20 ���
	{
		payment_bob_bank1 += payment_bob_bank;
		payment_bob_bank1 *= 1.09;
		i++;
	}
	printf("Bob received from the bank for 1 year = %f \n", payment_bob_bank);
	printf("Bob received from the bank for 20 years = %f \n", payment_bob_bank1);
	float bob_capital = payment_bob_bank1; //������� ���� - ��� �������, ������� �� ������� �� �����
	printf("Bob's capital = %f \n", bob_capital);

	
	
	//float flat_cost = 30000; //������� ����� ������ �� ����� � ��������
	float payment_alice = payment_bob; //����� ���������� � ���� 

	float payment_alice_bank = 12 * payment_alice; //������� ����� �������� �� ��� � ���� 
	float payment_alice_bank1 = 0; //��������������� ����������
	int j = 0;
	while (j<20) //������� ����� �������� �� ����� �� 20 ���
	{
		payment_alice_bank1 += payment_alice_bank;
		payment_alice_bank1 *= 1.09;
		j++;
	}
	printf("Alice received from the bank for 20 years = %f \n", payment_alice_bank);
	printf("Alice received from the bank for 20 years = %f \n", payment_alice_bank1);
	float alice_capital = payment_alice_bank1 - inflation_flat; //������� ����� - ��� �������, ������� ��� �������� � ������� ��������� ��������
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