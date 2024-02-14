#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_CREDIT 5
#define MAX_PERSON 2
#define MAX_PROPERTY 20


int MONTH = 9;
int YEAR = 2023;


typedef long long int Money;


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
    char *property_id;
};


struct Person 
{
    char *Name;
    Money bank_account;
    Money salary;

    int count_credits;
    struct Credit credit_list[MAX_CREDIT];

    int count_property;
    struct Property property_list[MAX_PROPERTY];
} Bob = {"Bob"}, Alice = {"Alice"};


static char *ErrorNames[] = {
    "out_of_range"
};


enum Errors {
    out_of_range
};


void print_error(enum Errors err)
{
    printf("%s\n", ErrorNames[err-1]);
    exit(err);
}


struct Person *PERSON_LIST[MAX_PERSON];
int COUNT_PERSON = 0;


void init_pers(struct Person *pers) 
{
    if (COUNT_PERSON >= MAX_PERSON) print_error(out_of_range);

    pers->bank_account = 0;
    pers->salary = 0;
    pers->count_credits = 0;
    pers->count_property = 0;

    PERSON_LIST[COUNT_PERSON] = pers;
    COUNT_PERSON += 1; 
}


void del_persons()
{
    for (int num_pers = 0; num_pers < COUNT_PERSON; num_pers++) (PERSON_LIST[num_pers] = NULL);

    COUNT_PERSON = 0;
}


void set_salary(struct Person *pers, const int salary) 
{
    pers->salary = salary;
}


void add_bank_account(struct Person *pers, const int add) 
{
    pers->bank_account += add;
}


void percent_bank_account(struct Person *pers, const float percent)
{
    if (pers->bank_account > 0) pers->bank_account = (pers->bank_account * (int)(percent * 100)) / (100*100);
}


void take_credit(struct Person *pers, const Money amount, const float percent, const int credit_years) 
{
    if (pers->count_credits == MAX_CREDIT)
    {
        print_error(out_of_range);
        return;
    }

    struct Credit credit;
    credit.amount = amount;
    credit.credit_percent = percent * 100;
    credit.credit_month = credit_years * 12;
    credit.monthly_payment = amount / credit.credit_month;

    pers->credit_list[pers->count_credits] = credit;
    pers->count_credits += 1;

    pers->bank_account += amount;
}


void buy_property(struct Person *pers, char *name, const Money cost)
{
    if (pers->count_property == MAX_PROPERTY)
    {
        print_error(out_of_range);
        return;
    }

    if (pers->bank_account < cost)
    {
        printf("Not enough money to buy property!\n");
        return;
    }

    struct Property property;
    property.cost = cost;
    property.property_id = name;

    pers->property_list[pers->count_property] = property;
    pers->count_property += 1;

    pers->bank_account -= cost;
}


void add_property(struct Person *pers, char *name, const Money cost)
{
    if (pers->count_property == MAX_PROPERTY) 
    {
        print_error(out_of_range);
        return;
    }

    struct Property property;
    property.cost = cost;
    property.property_id = name;

    pers->property_list[pers->count_property] = property;
    pers->count_property += 1;
}


void sold_property(struct Person *pers, char *name) 
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
        printf("Property not found!\n");
        return;
    }

    for (; (num_property + 1) < pers->count_property; num_property++)
        pers->property_list[num_property] = pers->property_list[num_property + 1] ;

    pers->count_property -= 1;
}


void del_property(struct Person *pers, char *name) 
{
    int num_property = 0;

    for (; num_property < pers->count_property; num_property++) 
    {
        if (strcmp(name, pers->property_list[num_property].property_id) == 0) break;
    }

    if (num_property == pers->count_property) 
    {
        printf("Property not found!\n");
        return;
    }

    for (; (num_property + 1) < pers->count_property; num_property++)
        pers->property_list[num_property] = pers->property_list[num_property + 1] ;
    
    pers->count_property -= 1;
}


void percent_property(struct Person *pers, char *name, const float percent) 
{
    for (int num_property = 0; num_property < pers->count_property; num_property++) 
    {
        if (strcmp(name, pers->property_list[num_property].property_id) == 0)
        {
            pers->property_list[num_property].cost = (pers->property_list[num_property].cost * (int)(percent * 100)) / (100*100);
            return;
        }
    }

    printf("Property not found!\n");
}


int have_property(struct Person *pers, char *name) 
{
    for (int num_property = 0; num_property < pers->count_property; num_property++) 
        if (strcmp(name, pers->property_list[num_property].property_id) == 0) return 1;

    return 0;
}


void print_person_info(struct Person *pers)
{
    printf("_____________________________________________________________________\n");
    printf("Date: %d-%d\n", MONTH, YEAR);
    printf("Name: %s\n", pers->Name);
    printf("Bank account: %lld\n", pers->bank_account);
    printf("Salary: %lld\n", pers->salary);

    printf("Credit list:\n");
    for (int num_credit = 0; num_credit < pers->count_credits; num_credit++) 
        printf("   Credit: %lld; Percent: %5.2f; Monthly payment: %d; Years left: %d; Mouth left: %d.\n", 
            pers->credit_list[num_credit].amount, ((float)pers->credit_list[num_credit].credit_percent) / 100.0, 
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


// Используется дифференцированный способ начисления процентов по кредиту 
void calculate_credit(struct Person *pers)
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

            for (; (temp_num_credit + 1) < pers->count_credits; temp_num_credit++) 
            {
                pers->credit_list[temp_num_credit] = pers->credit_list[temp_num_credit + 1];
            }

            pers->count_credits -= 1;
        }
    }
            
}


void dentist(struct Person *pers) {add_bank_account(pers, -10000);}
void rent(struct Person *pers) {add_bank_account(pers, -25000);}
void eat(struct Person *pers) {add_bank_account(pers, -15000);}
void communal(struct Person *pers) {add_bank_account(pers, -5000);}


void travel_bob() 
{
    if (YEAR == 2026 && MONTH == 8) add_bank_account(&Bob, -300000);
    if (YEAR == 2027 && MONTH == 8) add_bank_account(&Bob, -400000);
}


void bob_active_calc()
{
    eat(&Bob);
    communal(&Bob);
    if (MONTH == 7 || MONTH == 1) dentist(&Bob);

    percent_bank_account(&Bob, 102);

    calculate_credit(&Bob);

    percent_property(&Bob, "Home", 101.5);
    if (have_property(&Bob, "UAZ-2121")) percent_property(&Bob, "UAZ-2121", 98);

    travel_bob();

    if (MONTH == 12 && YEAR == 2026) set_salary(&Bob, 400000);

    Bob.bank_account += Bob.salary;
}


void alice_active_calc()
{
    eat(&Alice);
    rent(&Alice);
    communal(&Alice);

    if (MONTH == 7 || MONTH == 1) dentist(&Alice);

    percent_bank_account(&Alice, 102);

    // travel
    if (YEAR % 2 == 0 && MONTH == 3) add_bank_account(&Alice, -500000);

    Alice.bank_account += Alice.salary;
}


void pass_to_date(int target_year, int target_month) 
{
    while(YEAR < target_year || (YEAR == target_year && MONTH < target_month)) 
    {
        bob_active_calc();

        alice_active_calc();

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
    init_pers(&Bob);
    init_pers(&Alice);

    set_salary(&Bob, 400000);
    add_bank_account(&Bob, 2000000);
    take_credit(&Bob, 20000000, 7.5, 5);
    buy_property(&Bob, "Home", 20000000);
    print_person_info(&Bob);

    set_salary(&Alice, 400000);
    add_bank_account(&Alice, 2000000);
    print_person_info(&Alice);

    pass_time(2, 0);
    buy_property(&Bob, "UAZ-2121", 200000);
    print_all();

    pass_to_date(2028, 9);
    //sold_property(&Bob, "UAZ-2121");
    print_all();

    return 0;
}
