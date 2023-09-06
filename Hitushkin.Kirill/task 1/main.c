#include <stdio.h>
#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)

int main() {
	int years = 20;
	// Bob
	int credit = 20000000;
	int percent = 7;
	int percent_active = 6;
	int salary = 90000;
	int start = 1000000;
   	int expenses = 30000;

   	credit = credit - start;

    int bob_active = 0;

    for (int i = 0; i != years; i++) {
    	bob_active = bob_active - (int)(credit*percent/100);
    	credit = credit - (credit + credit*percent/100)/((years-i));
    	for (int n = 0; n != 12; n++) {
    		bob_active = (bob_active + salary - expenses)*(1+percent_active/100);
    	}
    }
    printf("Bob active = %d\n",bob_active);

    // alice
	salary = 90000;
	start = 1000000;
   	expenses = 30000;
   	percent_active = 6;

    int alice_active = start;

    for (int i = 0; i != years; i++) {
    	for (int n = 0; n != 12; n++) {
    		alice_active = (alice_active + salary - expenses)*(1+percent_active/100);
    	}
    }
    printf("Alice active = %d\n", alice_active);
    printf("Difference = %d\n", MAX(bob_active, alice_active) - MIN(bob_active, alice_active));
}