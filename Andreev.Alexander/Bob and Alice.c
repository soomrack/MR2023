#include <stdio.h>
#include <math.h>

// ���������� ����������
typedef long long int Money;  // ��� ������

const int MONTH = 240;  // ���������� �������
const double CREDITPERCENT = 0.07;  // ������� �� �������
const double M_KOEF = 0.07 / 12;  // ����������� ������� �������
const double DEPOSIT = 0.09;  // ������� �� ������
const double LOAN = 0.07;  // ������� �� �������

Money CREDIT = 19 * 1000 * 1000 * 100;  // ����� �������
Money CREDITPAYMENT;  // ������ �� �������
Money FLAT = 20 * 1000 * 1000 * 100;  // ��������� ��������

struct Person // �������
{
    Money balance;
    Money bank;
    Money total;
    Money salary;
    Money rent;
};

struct Person Alice = { 0, 1 * 1000 * 100 * 100, 0, 200 * 1000 * 100, 30 * 1000 * 100 };
struct Person Bob = { 0, 0, 0, 200 * 1000 * 100, 0 };

Money creditpay()  // ������ ������� �� �������
{
    int result;
    result = CREDIT * ((M_KOEF * pow(1 + M_KOEF, MONTH)) / (pow(1 + M_KOEF, MONTH) - 1));  // ������ �� �������
    return result;
}

int countBob()
{
    Bob.bank = 0; // �������������� ���������� ���� Bob
    for (int i = 0; i <= MONTH; ++i)
    {
        Bob.bank += Bob.bank * (DEPOSIT / 12);
        Bob.bank -= Bob.bank * (LOAN / 12);
        Bob.bank += Bob.balance;
    }
    return Bob.bank;
}

int countAlice()  // ������ ������� �����
{
    for (int i = 0; i <= MONTH; ++i)
    {
        Alice.bank += Alice.bank * (DEPOSIT / 12);
        Alice.bank -= Alice.bank * (LOAN / 12);
        Alice.bank += Alice.balance;
    }
    return Alice.bank;
}

int countFlat()  // ������ ��������� ��������
{
    for (int i = 0; i <= MONTH; ++i)
    {
        FLAT += FLAT * (0.01 / 12);
    }
    return FLAT;
}

int main()
{
    CREDITPAYMENT = creditpay();

    Alice.balance = Alice.salary - Alice.rent;  // ����������� ������� �����
    Bob.balance = Bob.salary - CREDITPAYMENT;  // ����������� ������� �����

    Alice.total = countAlice() / 100;
    Bob.total = (countBob() + countFlat()) / 100;

    printf("%lld   %lld", Alice.total, Bob.total);
    return 0;
}
