#include <stdio.h>
#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)

struct person
{
	unsigned int credit;
	unsigned int percent;
	float percent_active;
	unsigned int salary;
	int start;
   	unsigned int expenses;
};

double get_active(struct person pers, int years, int* inflation) {
	unsigned int credit = 0;
	if (pers.credit > pers.start) {
		credit = pers.credit - pers.start;
	}

	double active = pers.start;
	
	for (int i = 0; i != years; i++) {
		if (credit != 0) {
			active = active - credit*pers.percent/100.0;
			credit = credit*(1+pers.percent/100.0);
			active = active + credit/(years-i);
    		credit = credit - credit/(years-i);
		}
    	
    	for (int n = 0; n != 12; n++) {
    		active = (active + pers.salary - pers.expenses)*(1 + pers.percent_active/100.0);
    	}

    	active = active * 1 + inflation[i]/100.0;
    	pers.salary = pers.salary * (1 + inflation[i]/100.0);
    }
    return active;
}

int main() {
	struct person bob = {20000000, 7, 0.7, 80000, 2000000, 78000};
	struct person alice = {0, 0, 0.7, 80000, 2000000, 78000};
	
	int inflation[] = {7,6,4,2,6,3,4,1,4,6,2,7,6,4,2,6,3,4,1,4,6,2,7,6,4,2,6,3,4,1,4,6,2};
	int years = 20;

	if (years > (sizeof(inflation)/sizeof(inflation[0]))) {
		printf("Error: out of range");
		return -1;
	}

	double bob_active = get_active(bob, years, inflation);
	double alice_active = get_active(alice, years, inflation);

	printf("Bob active = %f\n",bob_active);
	printf("Alice active = %f\n", alice_active);
    printf("Difference = %f\n", MAX(bob_active, alice_active) - MIN(bob_active, alice_active));

	return 0;
}