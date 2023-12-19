#include <stdio.h>  //Подключаем стандартную библиотеку команд С
#include <math.h> // Подключаем библиотеку математики

int main() //Точка входа в программу на языке С, int - указывает, что функция main возвращает целочисленное значение (при успешном завершении main вернет 0)
{
    // Объявляем начальные условия
    int start = 1000000; //Начальный капитал
    float kvar = 20000000; //Стоимость квартиры вначале
    float vklad = 11; // % по вкладу
    float ipoteka = 7; // % по ипотеке
    int year = 30; // лет в исследовании
    int months = 12; // месяцев в исследовании
    float zp = 200000; // зарплата сотрудника
    float rent = 30000; // рента за съем квартиры
    float rashod = 30000; // сумма месячных расходов
    float inf = 7; // % инфляции
    /////////////////////


    // В этом блоке считаем сумму аннуитетного платежа Боба
    int S = kvar - start; // Сумма кредита
    float r = (ipoteka / 100) / 12; // Месячная ставка
    int n = year * 12; // Кол-во месяцев во всем сроке кредита
    float result = pow((1 + r), (float)n); // Возводим (1+r) в степень n, попутно переводя n из int в float
    float plata = S * ((r * result) / (result - 1)); // Сумма ежемесячного платежа по ипотеке по формуле
    /////////////////////

    
    // В этом блоке идет расчет капитала Элис
    float zp_Alice = zp;
    float rashod_Alice = rashod;
    float ost_Alice;
    float schet_Alice = start; // Элис положила стартовый капитал на вклад

    for (int i = 1; i <= year; i++) { // Счетчик лет        
        for (int j = 1; j <= months; j++) { // Счетчик месяцев в каждом годе
            ost_Alice = zp_Alice - (rent + rashod_Alice); // Элис оплатила расходы
            schet_Alice = schet_Alice + ost_Alice; // Счет Элис пополнился остатком зарплаты
            schet_Alice = schet_Alice * (1 + (vklad / 100) / 12); // Начисляем в конце месяца проценты по вкладу
        }
        zp_Alice = zp_Alice * (1 + (inf / 100)); // ЗП увеличилась на инфляцию
        rashod_Alice = rashod_Alice * (1 + (inf / 100)); // расходы увеличились на инфляцию
        rent = rent * (1 + (inf / 100)); // рента увеличилась на инфляцию
    }
    /////////////////////
        

    // В этом блоке идет расчет капитала Боба
    float zp_Bob = zp;
    float rashod_Bob = rashod;
    float ost_Bob;
    float schet_Bob = 0; // Стартовый капитал на первоначальный взнос по ипотеке

    for (int i = 1; i <= year; i++) { // Счетчик лет
        for (int j = 1; j <= months; j++) { // Счетчик месяцев в каждом годе
            ost_Bob = zp_Bob - (plata + rashod_Bob); // Боб оплатил расходы и заплатил платеж по ипотеке
            schet_Bob = (schet_Bob + ost_Bob); // Счет Боба пополнился остатком зарплаты
            schet_Bob = schet_Bob * (1 + (vklad / 100) / 12); // Начисляем в конце месяца проценты по вкладу
        }
        zp_Bob = zp_Bob * (1 + (inf / 100)); // ЗП увеличилась на инфляцию
        rashod_Bob = rashod_Bob * (1 + (inf / 100)); // расходы увеличились на инфляцию
        kvar = kvar * (1 + (inf / 100)); // Инфляция на недвижимость
    }
    schet_Bob = schet_Bob + kvar;
    /////////////////////


    // В этом блоке выводим результаты
    printf("Alice:                                 %.0f rub.\n", schet_Alice);
    printf("Bob:                                   %.0f rub. \n", schet_Bob);
    printf("Stoimost kvartiri na konec perioda:    %.0f rub. \n", kvar);
    printf("Velichina platega po ipoteke:          %.0f rub. \n", plata);
    /////////////////////
  
    getchar();getchar(); // Ждем символ, чтобы консоль не закрывалась автоматически
    return 0; // Если дошло до этого момента, то возвращаем 0
    
}