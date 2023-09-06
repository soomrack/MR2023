#include <stdio.h>

int main() {
	for (;;) {
		int credit = 0;
		int percent = 0;
		int salary = 0;
		int years = 0;
		int start = 0;

	    printf("Credit: ");
	    scanf("%d", &credit);
	    //printf("Percent: ");
	    //scanf("%d", &percent);  
	    printf("Salary: ");
	    scanf("%d", &salary);
	    printf("years: ");
	    scanf("%d", &years);
	    printf("Start: ");
	    scanf("%d", &start);

	   	int expenses = 0;
	   	int new_expenses = 0;
	    do {
	    	printf("Other expenses (0 to end):");
	    	scanf("%d", &new_expenses);
	    	expenses += new_expenses;
	    } while(new_expenses != 0);

	    credit = credit - start;

	    int sum = 0;
	    int minus = credit / (12*years);

	    for (int i = 0; i != years; i++) {
	    	sum += (salary - expenses - minus);
	    }

	    printf("Remainder = %d\n",sum);
	}
}