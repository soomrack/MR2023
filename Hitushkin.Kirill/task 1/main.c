#include <stdio.h>
#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)

int main() {
	int years = 20;
	int inflation = 7;
	// Bob
	int credit = 20000000;
	int percent = 7;
	int percent_active = 6;
	int salary = 80000;
	int start = 1000000;
   	int expenses = 60000;

   	credit = credit - start;

    long bob_active = start;

    for (int i = 0; i != years; i++) {
    	bob_active = bob_active - (long)(credit*percent/100.0);
    	credit = credit*(1+percent/100.0);
    	credit = credit - credit/((years-i));
    	for (int n = 0; n != 12; n++) {
    		bob_active = (bob_active + salary - expenses)*(long)(1+percent_active/100.0);
    	}
    	bob_active = bob_active * (long)(1 + inflation/100.0);
    	salary = salary * (1 + inflation/100.0);
    }
    printf("Bob active = %ld\n",bob_active);

    // alice
	salary = 60000;
	start = 100000;
   	expenses = 50000;
   	percent_active = 6;

    long alice_active = start;

    for (int i = 0; i != years; i++) {
    	for (int n = 0; n != 12; n++) {
    		alice_active = (alice_active + salary - expenses)*(long)(1+percent_active/100.0);
    	}
    	alice_active = alice_active*(long)(1 + inflation/100.0);
    	salary = salary * (1 + inflation/100.0);
    }
    printf("Alice active = %ld\n", alice_active);
    printf("Difference = %ld\n", MAX(bob_active, alice_active) - MIN(bob_active, alice_active));
}