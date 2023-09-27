#include <stdio.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

typedef long long int cents; //kopeika

const int YEARS_COUNT = 20;
const int YEAR = 2023;
const int MONTH = 9;
const double INFLATION = 0.07;
const cents START_SUM = 1*1000000*100;
const cents MONTH_SALARY =200*1000*100;
const cents ALISE_START_RENT = 30000*100;
const double BANK_PERCENT =0.09;
const cents FLAT_COST = 20*1000*1000*100; // first year

struct Capital{
    cents bank_acc;
    cents salary;
    cents rent;
};

struct Capital Alise; 
struct Capital Bob; 

void alise_init(){
    Alise.bank_acc=START_SUM;
    Alise.salary=MONTH_SALARY;
    Alise.rent=ALISE_START_RENT;
}

cents bob_init(){
    Bob.bank_acc=0;
    Bob.salary=MONTH_SALARY;
    double month_per = BANK_PERCENT/12;
    cents bob_month_payment =(FLAT_COST-START_SUM)*(month_per+(month_per/(pow(1+month_per,YEARS_COUNT*12)-1)));
    return bob_month_payment;
}

void alise_add_salary(){
    int salary_change;
    salary_change = 0; // здесь можно поменять переключатель или придумать ввод
    //scanf("%d \n",salary_change);
    if(salary_change){
        scanf("%li \n", Alise.salary); 
    }
    Alise.bank_acc += Alise.salary; // добавляем зп на счёт
}

void bob_add_salary(){
    int salary_change;
    salary_change = 0; 
    scanf("%d \n",salary_change);
    if(salary_change){
        scanf("%li \n", Bob.salary); 
    }
    Bob.bank_acc += Bob.salary; 
}

void alise_rent(){
    int rent_sw;
    rent_sw=0;
    if(rent_sw){
        scanf("%li \n", Alise.rent);
    }
    Alise.bank_acc -= Alise.rent;
}

void bob_payment(cents payment){
    Bob.bank_acc -= payment; 

}

void alise_spend_for_life(year,month){
    static cents life_exp = 30*1000*100;
    Alise.bank_acc -= life_exp;
    life_exp *= (INFLATION+1);
}

void bob_spend_for_life(year,month){
    static cents life_exp = 30*1000*100;
    Bob.bank_acc -= life_exp;
    life_exp *= (INFLATION/12 + 1);
}

void alise_extra_spend(int year,int month){
    int voyage_to_eu =0;
    if(voyage_to_eu){
        cents voyage_cost = 500*1000*1000*100;
        scanf("%li \n", voyage_cost);
        Alise.bank_acc -= voyage_cost;
    }
    // something else extra
}

void bob_extra_spend(int year,int month){
    int voyage_to_eu =0;
    if(voyage_to_eu){
        cents voyage_cost;
        scanf("%li \n", voyage_cost);
        Bob.bank_acc -= voyage_cost;
    }
    // something else extra
}

void alise_bank_percent(int year,int month)
{
    if(Alise.bank_acc>5*1000*1000*100){
        Alise.bank_acc *= (1+BANK_PERCENT+0.01);
    }else {
    Alise.bank_acc *= (1+BANK_PERCENT);
    }
    // something else extra, exmpl: percent changes
}

void bob_bank_percent(int year,int month){
    Bob.bank_acc *= (1+BANK_PERCENT);
    // something else extra, exmpl: percent changes
}

void alise_inflation(int year, int month){
    Alise.salary *= (1 + INFLATION);
    Alise.rent *= (1 + INFLATION);
}

void bob_inflation(int year, int month){
    Bob.salary *= (1 + INFLATION);
}

void result(){
    printf("bob_capital = %li \n",FLAT_COST*(pow(1+(INFLATION),YEARS_COUNT))+Bob.bank_acc);
    printf("alise_capital = %li \n",Alise.bank_acc);
}


void simulation(){
    int year = YEAR;
    int years_count = YEARS_COUNT;
    int month = MONTH;

    alise_init();
    cents bob_month_payment = bob_init();

    while(year != year+years_count && month != MONTH-1){
        alise_add_salary();
        bob_add_salary();
        alise_rent();
        bob_payment(bob_month_payment);
        alise_spend_for_life(year,month); 
        bob_spend_for_life(year,month); 
        alise_extra_spend(year,month);
        bob_extra_spend(year,month);
        alise_bank_percent(year,month);
        bob_bank_percent(year,month);
        alise_inflation(year,month);
        bob_inflation(year,month);
        result();
        // написать про инфляцию боба и алисы
        /*
        
        
        
        WRITE CODE
    
        
        
        */
       ++month;
       if(month == 13) {
            ++year;
            month=1;
       }
    }

}




int main() {
    
    simulation();

/*
    Alise.salary=r_salary;
    Bob.salary=r_salary;
    
    cents *ukaz_bob_salary;
    cents *ukaz_alise_salary;

    cents alise_rent=alise_rent_start;
    cents alise_bank_capital=start_sum;
    double bob_bank_capital=0;
    double alise_realty_capital=0;
    double bob_realty_capital=0;
    double life_exp;
    //Можем ввести из потока или не вводить из потока
    //scanf("%lf", &alise_life_exp);
    life_exp=20000;
    double month_inf = month_inflation();
    double month_per = bank_percent/12;
    double bob_month_payment =(flat_cost-start_sum)*(month_per+(month_per/(pow(1+month_per,years*12)-1)));
    //printf("bob_month_payment = %lf \n",bob_month_payment);
    for(int i=0;i<years*12;++i){
        bob_bank_capital += (salary-bob_month_payment-life_exp);
        bob_bank_capital *= (month_per+1);
        salary *= month_inf;
        alise_rent *= month_inf;
        life_exp *= month_inf;
        alise_bank_capital += (salary-life_exp-alise_rent);
        alise_bank_capital *= (month_per+1);
    }
    bob_realty_capital =flat_cost*(pow(1+(inflation/100),years));
    printf("bob_capital = %lf \n",bob_realty_capital+bob_bank_capital);
    printf("alise_capital = %lf \n",alise_realty_capital+alise_bank_capital);
    return 0;
    */
}
