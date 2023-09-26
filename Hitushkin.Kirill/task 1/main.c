#include <stdio.h>
#include <string.h>
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
	if ((name_is("Bob") && gmouth == 3) || name_is("Alice") && gyear%2 == 0 && gmouth == 3) travel(pers);
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

    deinit();
    return 0;
}
