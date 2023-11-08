#include <stdio.h>
#include <math.h>


typedef long long int cents; //kopeika

const int YEARS_COUNT = 20;
const int YEAR = 2023;
const int MONTH = 9;
const double INFLATION = 0.07;
const cents START_SUM = 1*1000000*100;
const cents MONTH_SALARY =200*1000*100;
const cents ALIСE_START_RENT = 30000*100;
const double BANK_PERCENT = 0.09;
const cents FLAT_COST = 20*1000*1000*100; // first year

struct Person{
    cents bank_acc;
    cents salary;
    cents rent;
};

struct Person Aliсe; 
struct Person Bob; 

cents flat_cost = 20*1000*1000*100;


void aliсe_init()
{
    Aliсe.bank_acc=START_SUM;
    Aliсe.salary=MONTH_SALARY;
    Aliсe.rent=ALIСE_START_RENT;
}


void bob_init()
{
    Bob.bank_acc = 0;
    Bob.salary = MONTH_SALARY;
    
}


cents bob_month_pay(){
    double month_per = BANK_PERCENT / 12;
    cents bob_month_payment =(FLAT_COST-START_SUM) * (month_per + (month_per / (pow(1 + month_per, YEARS_COUNT * 12) - 1)));
    return bob_month_payment;
}


void aliсe_add_salary(const int month){
    int salary_change;
    salary_change = 0; // здесь можно поменять переключатель или придумать ввод
    
    if(salary_change){
        Aliсe.salary = 300 * 1000 * 1000 * 100; 
    }

    Aliсe.bank_acc += Aliсe.salary; // добавляем зп на счёт
    
    if(month % 12 == 0 ){
        Aliсe.salary *= (1 + 0.07);
    }
}


void bob_add_salary(const int month){
    int salary_change;
    salary_change = 0; 

    if(salary_change){
        Bob.salary = 300 * 1000 * 1000 * 100; 
    }
    Bob.bank_acc += Bob.salary; 
    
    if(month % 12 == 0){
        Bob.salary *= (1 + 0.07);
    }
}


void aliсe_rent(){
    int rent_sw;
    rent_sw=0;
    if(rent_sw){
        Aliсe.rent += 10 * 1000 * 100;
    }
    Aliсe.bank_acc -= Aliсe.rent;
}


void bob_payment(cents payment){
    Bob.bank_acc -= payment; 

}


void aliсe_spend_for_life(const int year,const int month){
    static cents life_exp = 30 * 1000 * 100;
    Aliсe.bank_acc -= life_exp;
    life_exp *= (INFLATION / 12 + 1);
}


void bob_spend_for_life(const int year,const int month){
    static cents life_exp = 25*1000*100;
    Bob.bank_acc -= life_exp;
    life_exp *= (INFLATION / 12 + 1);

    if((month % 11) == 0){
        cents taxes = 60 * 1000 * 100;
        Bob.bank_acc -= taxes;
        taxes *= (1 + INFLATION);
    }
}


void aliсe_extra_spend(const int year,const int month){
    int voyage_to_eu = 0;
    if(voyage_to_eu){
        cents voyage_cost = 500 * 1000 * 1000 * 100;
        Aliсe.bank_acc -= voyage_cost;
    }
    // something else extra
}


void bob_extra_spend(const int year,const int month){
    int voyage_to_eu = 0;
    if(voyage_to_eu){
        cents voyage_cost = 500 * 1000 * 1000 * 100;
        Bob.bank_acc -= voyage_cost;
    }
    // something else extra
}


void aliсe_bank_percent(const int year, const int month)
{
    if (Aliсe.bank_acc > 5 * 1000 * 1000 * 100) {
        Aliсe.bank_acc *= (1 + (BANK_PERCENT + 0.01) / 12);
    }else {
    Aliсe.bank_acc *= (1 + BANK_PERCENT / 12);
    }
    // something else extra, exmpl: percent changes
}


void bob_bank_percent(const int year, const int month){
    Bob.bank_acc *= (1 + BANK_PERCENT / 12);
    // something else extra, exmpl: percent changes
}


void aliсe_inflation(const int year, const int month){
    Aliсe.rent *= (1 + INFLATION / 12);
}


void bob_inflation(const int year, const int month){
    flat_cost *= (1 + INFLATION / 12);
}


void result(){
    double bob_sum = flat_cost + Bob.bank_acc;
    double aliсe_sum = Aliсe.bank_acc;
    bob_sum /= 100;
    aliсe_sum /= 100;
    printf("bob_capital = %f \n",(bob_sum));
    printf("alice_capital = %f \n",aliсe_sum);
}


void simulation(const cents bob_month_payment){
    int year = YEAR;
    int years_count = YEARS_COUNT;
    int month = MONTH;

    while(month != MONTH + 12 * years_count){
    
        aliсe_add_salary(month);
        aliсe_rent();
        aliсe_spend_for_life(year,month); // FOOD + kOMMUNALKA + CAR
        aliсe_extra_spend(year,month);  // VOYAGE, medical spents
        aliсe_bank_percent(year,month);
        aliсe_inflation(year,month);

        bob_add_salary(month);
        bob_payment(bob_month_payment);
        bob_spend_for_life(year,month); // FOOD + kOMMUNALKA + CAR
        bob_extra_spend(year,month);  // VOYAGE, medical spents
        bob_bank_percent(year,month);
        bob_inflation(year,month);

       ++month;
       if(month % 12 == 0) {
            ++year;
       }
    }
 

}


int main() {

    aliсe_init();
    bob_init();
    cents bob_month_payment = bob_month_pay();
    simulation(bob_month_payment);
    result();

}
