#include <stdio.h>
#include <string.h>
<<<<<<< HEAD
#include "creditsim.h"

int gmouth = 9;
int gyear = 2023;

event(dentist, -10000);
event(premium, 40000);
event(rent, -25000);
event(eat, -15000);
event(travel, -300000)

void history(struct Person* pers) {
	if (gmouth == 8 || gmouth == 2) dentist(pers);
	if (name_is("Bob") && gmouth == 12) premium(pers);
	(pers->bank_account > 2000000) ? percent_bank_account(pers, 102) : percent_bank_account(pers, 106);
	if (name_is("Bob") && gyear == 2026 && gmouth == 8) set_salary(pers, 100000);
	if (have_property(pers, "Home")) percent_property(pers, "Home", 102);
	if (have_property(pers, "UAZ-2121")) percent_property(pers, "UAZ-2121", 98);
	if (!have_property(pers, "Home")) rent(pers);
	eat(pers);
	if ((name_is("Bob") && gmouth == 3) || (name_is("Alice") && gyear%2 == 0 && gmouth == 3)) travel(pers);
}

int main()
{   
    INIT_PERS(Bob);
    set_salary(Bob, 80000);
    add_bank_account(Bob, 2000000);
    take_credit(Bob, 2000000, 7, 5);
    buy_property(Bob, "Home", 3000000);
    print_person_info(Bob);

    INIT_PERS(Alice);
    set_salary(Alice, 80000);
    add_bank_account(Alice, 2000000);
    print_person_info(Alice);

    pass_time(2, 0);
    buy_property(Alice, "Home", 2000000);
    buy_property(Bob, "UAZ-2121", 200000);
    print_all();

    pass_to_date(2028, 9);
    sold_property(Bob, "UAZ-2121");
    print_all();

=======
#include <stdlib.h>


#define MAX_CREDIT 5
#define MAX_PERSON 2
#define MAX_PROPERTY 20


int MONTH = 9;
int YEAR = 2023;


struct Person* PERSON_LIST[MAX_PERSON];
int COUNT_PERSON = 0;


typedef long long int Money;


// Используется дифференцированный способ начисления процентов по кредиту 
struct Credit
{
    Money amount;
    int credit_percent;
    int credit_month;
    int monthly_payment;
};


struct Property
{
    Money cost;
    char* property_id;
};


struct Person 
{
    char* name;
    Money bank_account;
    Money salary;

    int count_credits;
    struct Credit credit_list[MAX_CREDIT];

    int count_property;
    struct Property property_list[MAX_PROPERTY];
};


void deinit()
{
    for (int num_pers = 0; num_pers < COUNT_PERSON; num_pers++) free(PERSON_LIST[num_pers]);

    COUNT_PERSON = 0;
}


void print_error(const int key, const char* mes)
{
    printf("_____________________________________________________________________\n");
    printf("%s\n", mes);

    if (key) 
    {
        deinit();
        exit(1);
    }
}


struct Person* init_pers(char* name) 
{
    if (COUNT_PERSON >= MAX_PERSON) print_error(1, "Too much person!");

    struct Person* pers = (struct Person*) malloc(sizeof(struct Person));

    if (pers == 0) print_error(1, "Memory error!");

    pers->name = name;
    pers->bank_account = 0;
    pers->salary = 0;
    pers->count_credits = 0;
    pers->count_property = 0;
    COUNT_PERSON += 1; 
    PERSON_LIST[COUNT_PERSON - 1] = pers;
    return pers;
}


void set_salary(struct Person* pers, const int salary) 
{
    pers->salary = salary;
}


void add_bank_account(struct Person* pers, const int add) 
{
    pers->bank_account += add;
}


void percent_bank_account(struct Person* pers, const float percent)
{
    if (pers->bank_account > 0) pers->bank_account = (pers->bank_account * (int)(percent * 100)) / (100*100);
}


void take_credit(struct Person* pers, const Money amount, const float percent, const int credit_years) 
{
    if (pers->count_credits == MAX_CREDIT)
    {
        print_error(0, "Too much credit!");
        return;
    }

    struct Credit credit;
    credit.amount = amount;
    credit.credit_percent = percent * 100;
    credit.credit_month = credit_years * 12;
    credit.monthly_payment = amount / credit.credit_month;

    pers->count_credits += 1;
    pers->credit_list[pers->count_credits - 1] = credit;

    pers->bank_account += amount;
}


void buy_property(struct Person* pers, char* name, const Money cost)
{
    if (pers->count_property == MAX_PROPERTY)
    {
        print_error(0, "Too much property!");
        return;
    }

    if (pers->bank_account < cost)
    {
        print_error(0, "Not enough money to buy property!");
        return;
    }

    struct Property property;
    property.cost = cost;
    property.property_id = name;

    pers->count_property += 1;
    pers->property_list[pers->count_property - 1] = property;

    pers->bank_account -= cost;
}


void add_property(struct Person* pers, char* name, const Money cost)
{
    if (pers->count_property == MAX_PROPERTY) 
    {
        print_error(0, "Too much property!");
        return;
    }

    struct Property property;
    property.cost = cost;
    property.property_id = name;

    pers->count_property += 1;
    pers->property_list[pers->count_property - 1] = property;
}


void sold_property(struct Person* pers, char* name) 
{
    int num_property = 0;

    for (; num_property < pers->count_property; num_property++) 
    {
        if (strcmp(name, pers->property_list[num_property].property_id) == 0)
        {
            pers->bank_account +=  pers->property_list[num_property].cost;
            break;
        }
    }

    if (num_property == pers->count_property) 
    {
        print_error(0, "Property not found!");
        return;
    }

    for (; (num_property + 1) < pers->count_property; num_property++)
        pers->property_list[num_property] = pers->property_list[num_property + 1] ;

    pers->count_property -= 1;
}


void del_property(struct Person* pers, char* name) 
{
    int num_property = 0;

    for (; num_property < pers->count_property; num_property++) 
    {
        if (strcmp(name, pers->property_list[num_property].property_id) == 0) break;
    }

    if (num_property == pers->count_property) 
    {
        print_error(0, "Property not found!");
        return;
    }

    for (; (num_property + 1) < pers->count_property; num_property++)
        pers->property_list[num_property] = pers->property_list[num_property + 1] ;
    
    pers->count_property -= 1;
}


void percent_property(struct Person* pers, char* name, const float percent) 
{
    for (int num_property = 0; num_property < pers->count_property; num_property++) 
    {
        if (strcmp(name, pers->property_list[num_property].property_id) == 0)
        {
            pers->property_list[num_property].cost = (pers->property_list[num_property].cost * (int)(percent * 100)) / (100*100);
            return;
        }
    }

    print_error(0, "Property not found!");
}


int have_property(struct Person* pers, char* name) 
{
    for (int num_property = 0; num_property < pers->count_property; num_property++) 
        if (strcmp(name, pers->property_list[num_property].property_id) == 0) return 1;

    return 0;
}


void print_person_info(struct Person* pers)
{
    printf("_____________________________________________________________________\n");
    printf("Date: %d-%d\n", MONTH, YEAR);
    printf("Person: %s\n", pers->name);
    printf("Bank account: %lld\n", pers->bank_account);
    printf("Salary: %lld\n", pers->salary);

    printf("Credit list:\n");
    for (int num_credit = 0; num_credit < pers->count_credits; num_credit++) 
        printf("   Credit: %lld; Percent: %d; Monthly payment: %d; Years left: %d; Mouth left: %d.\n", 
            pers->credit_list[num_credit].amount, ((float)pers->credit_list[num_credit].credit_percent) / 100, 
            pers->credit_list[num_credit].monthly_payment, pers->credit_list[num_credit].credit_month / 12,
            pers->credit_list[num_credit].credit_month % 12);

    printf("Property list:\n");
    for (int num_property = 0; num_property < pers->count_property; num_property++) 
        printf("   Property: %s; Cost: %lld.\n", pers->property_list[num_property].property_id,
            pers->property_list[num_property].cost);
}


void print_all()
{
    for (int i=0; i<COUNT_PERSON; i++) print_person_info(PERSON_LIST[i]);
}


void dentist(struct Person* pers) {add_bank_account(pers, -10000);}
void premium(struct Person* pers) {add_bank_account(pers, 40000);}
void rent(struct Person* pers) {add_bank_account(pers, -25000);}
void eat(struct Person* pers) {add_bank_account(pers, -15000);}
void travel(struct Person* pers) {add_bank_account(pers, -300000);}
void communal(struct Person* pers) {add_bank_account(pers, -5000);}


void calculate_credit(struct Person* pers)
{
    for (int num_credit = 0; num_credit < pers->count_credits; num_credit++) 
    {
        pers->bank_account -= (pers->credit_list[num_credit].monthly_payment +
            + (pers->credit_list[num_credit].amount * (pers->credit_list[num_credit].credit_percent)) / (12 * 100 * 100));
        pers->credit_list[num_credit].amount -= pers->credit_list[num_credit].monthly_payment;

        pers->credit_list[num_credit].credit_month -= 1;
    }

    for (int num_credit = 0; num_credit < pers->count_credits; num_credit++) 
    {
        if (pers->credit_list[num_credit].credit_month == 0) 
        {   
            int temp_num_credit = num_credit;

            for (; (num_credit + 1) < pers->count_credits; num_credit++) 
            {
                pers->credit_list[num_credit] = pers->credit_list[num_credit + 1];
            }

            pers->count_credits -= 1;

            num_credit = temp_num_credit;
        }
    }
            
}


void pass_to_date(int target_year, int target_month) 
{
    while(YEAR < target_year || (YEAR == target_year && MONTH < target_month)) 
    {
        for (int num_pers = 0; num_pers < COUNT_PERSON; num_pers++) 
        {
            struct Person* pers = PERSON_LIST[num_pers];
            
            eat(pers);
            communal(pers);
            if (MONTH == 8 || MONTH == 2) dentist(pers);

            (pers->bank_account > 2000000) ? percent_bank_account(pers, 102) : percent_bank_account(pers, 106);

            if ((strcmp(pers->name, "Alice") == 0) && YEAR % 2 == 0 && MONTH == 3) travel(pers);
            
            if ((strcmp(pers->name, "Bob") == 0) && MONTH == 12) premium(pers);
            if ((strcmp(pers->name, "Bob") == 0) && MONTH == 3) travel(pers);
            if ((strcmp(pers->name, "Bob") == 0) && YEAR == 2026 && MONTH == 8) set_salary(pers, 400000);

            if (have_property(pers, "Home")) percent_property(pers, "Home", 101.5);
            if (!have_property(pers, "Home")) rent(pers);

            if (have_property(pers, "UAZ-2121")) percent_property(pers, "UAZ-2121", 98);

            calculate_credit(pers);
            
            pers->bank_account += pers->salary;
        }

        MONTH += 1;

        if (MONTH == 13) 
        {
            MONTH = 1;
            YEAR += 1;
        }
    }
}


void pass_time(int target_year, int target_month) 
{
    pass_to_date(YEAR + target_year + (target_month + MONTH) / 12, (target_month + MONTH) % 12);
}


int main()
{   
    struct Person* Bob = init_pers("Bob");
    set_salary(Bob, 350000);
    add_bank_account(Bob, 2000000);
    take_credit(Bob, 20000000, 7.5, 5);
    buy_property(Bob, "Home", 20000000);
    print_person_info(Bob);

    struct Person* Alice = init_pers("Alice");
    set_salary(Alice, 400000);
    add_bank_account(Alice, 2000000);
    print_person_info(Alice);

    pass_time(2, 0);
    buy_property(Bob, "UAZ-2121", 200000);
    print_all();

    pass_to_date(2028, 9);
    sold_property(Bob, "UAZ-2121");
    print_all();

>>>>>>> 9e3c59b97851e1e4c7b154bfd1a9d3a6cc6dd5d0
    deinit();
    return 0;
}
