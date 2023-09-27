#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "creditsim.h"

int count_person = 0;

struct Person* init_pers(char* name) {
	if (count_person >= max_person) {
		printf("_____________________________________________________________________\n");
        printf("Too much person!\n");
        exit(1);
	}
	struct Person* pers = (struct Person*) malloc(sizeof(struct Person));
	if (pers == 0) {
		printf("_____________________________________________________________________\n");
        printf("Memory error!\n");
        exit(1);
	}
    pers->name = name;
    pers->bank_account = 0;
    pers->salary = 0;
    pers->count_credits = 0;
    pers->count_property = 0;
    count_person += 1; 
    person_list[count_person-1] = pers;
    return pers;
}

void deinit(){
	for (int i=0; i<count_person; i++) free(person_list[i]);
 	count_person = 0;
}

void set_salary(struct Person* pers, int salary) {
    pers->salary = salary;
}

void add_bank_account(struct Person* pers, int add) {
    pers->bank_account += add;
}

void percent_bank_account(struct Person* pers, int percent){
	if (pers->bank_account > 0) pers->bank_account = (pers->bank_account*percent)/100;
}

void take_credit(struct Person* pers, Money credit, int percent, int credit_years) {
    if (pers->count_credits == max_credit) {
    	printf("_____________________________________________________________________\n");
        printf("Too much credit!\n");
    } else {
        pers->count_credits += 1;
        pers->credit[pers->count_credits-1] = credit;
        pers->credit_percent[pers->count_credits-1] = percent;
        pers->credit_mouth[pers->count_credits-1] = credit_years*12;
        pers->bank_account += credit;
    }
}

void buy_property(struct Person* pers, char* name, Money property) {
    if (pers->count_property == max_property) {
    	printf("_____________________________________________________________________\n");
        printf("Too much property!\n");
    } else if (pers->bank_account < property) {
    	printf("_____________________________________________________________________\n");
        printf("Not enough money to buy %s!\n", name);
    } else {
        pers->count_property += 1;
        pers->property[pers->count_property-1] = property;
        pers->property_name[pers->count_property-1] = name;
        pers->bank_account -= property;
    }
}

void add_property(struct Person* pers, char* name, Money property) {
    if (pers->count_property == max_property) {
    	printf("_____________________________________________________________________\n");
        printf("Too much property!\n");
    } else {
        pers->count_property += 1;
        pers->property[pers->count_property-1] = property;
        pers->property_name[pers->count_property-1] = name;
    }
}

void sold_property(struct Person* pers, char* name) {
	for (int i=0; i<pers->count_property; i++) {
		if (strcmp(name, pers->property_name[i]) == 0){
			pers->bank_account +=  pers->property[i];
			i++;
			for (; i<pers->count_property; i++) {
				pers->property[i-1] = pers->property[i] ;
		        pers->property_name[i-1] = pers->property_name[i];
			}
			pers->count_property -= 1;
			break;
		}
		if (i == pers->count_property-1) {
			printf("_____________________________________________________________________\n");
			printf("Property %s not found!\n", name);
		}
	}
}

void del_property(struct Person* pers, char* name) {
	for (int i=0; i<pers->count_property; i++) {
		if (strcmp(name, pers->property_name[i]) == 0){
			i++;
			for (; i<pers->count_property; i++) {
				pers->property[i-1] = pers->property[i] ;
		        pers->property_name[i-1] = pers->property_name[i];
			}
			pers->count_property -= 1;
			break;
		}
		if (i == pers->count_property-1) {
			printf("_____________________________________________________________________\n");
			printf("Property %s not found!\n", name);
		}
	}
}

void percent_property(struct Person* pers, char* name, int percent) {
	for (int i=0; i<pers->count_property; i++) {
		if (strcmp(name, pers->property_name[i]) == 0){
			pers->property[i] = (pers->property[i]*percent)/100;
			break;
		} 
		if (i == pers->count_property-1) {
			printf("_____________________________________________________________________\n");
			printf("Property %s not found!\n", name);
		}
	}
}

int have_property(struct Person* pers, char* name) {
	for (int i=0; i<pers->count_property; i++) 
		if (strcmp(name, pers->property_name[i]) == 0) return 1;
	return 0;
}

void print_person_info(struct Person* pers){
    printf("_____________________________________________________________________\n");
    printf("Date: %d-%d\n", gmouth, gyear);
    printf("Person: %s\n", pers->name);
    printf("Bank account: %lld\n", pers->bank_account);
	printf("Salary: %lld\n", pers->salary);
    printf("Credit list:\n");
    for (int i=0; i<pers->count_credits; i++) 
        printf("   Credit: %lld;  Percent: %d;  Years left: %d; Mouth left: %d.\n", 
        	pers->credit[i], pers->credit_percent[i], pers->credit_mouth[i]/12, pers->credit_mouth[i]%12);
    printf("Property list:\n");
    for (int i=0; i<pers->count_property; i++) 
        printf("   Property: %s;  Cost: %lld.\n", 
        	pers->property_name[i], pers->property[i]);
}

void print_all(){
	for (int i=0; i<count_person; i++) print_person_info(person_list[i]);
}

void pass_to_date(int year, int mouth) {
	while(gyear < year || (gyear == year && gmouth < mouth)) {
		for (int i=0; i<count_person; i++) {
			struct Person* pers = person_list[i];
			history(pers);
			
			for (int n=0; n<pers->count_credits; n++) {
				pers->bank_account -= pers->credit[n]/(pers->credit_mouth[n]);
	    		pers->credit[n] -= pers->credit[n]/(pers->credit_mouth[n]);

	    		if (gmouth == 12) pers->credit[n] = (pers->credit[n]*(100+pers->credit_percent[n]))/100;

	    		pers->credit_mouth[n] -= 1;
	    		if (pers->credit_mouth[n] == 0) {
	    			for (int nn=n+1; nn<pers->count_credits; n++) {
				        pers->credit[nn-1] = pers->credit[nn];
				        pers->credit_percent[nn-1] =  pers->credit_percent[nn];
				        pers->credit_mouth[nn-1] = pers->credit_mouth[nn];
	    			}
	    			pers->count_credits -= 1;
	    			n -= 1;
	    		}
			}

    		pers->bank_account += pers->salary;
    	}
		gmouth += 1;
		if (gmouth == 13) {
			gmouth = 1;
			gyear += 1;
		}
	}
}

void pass_time(int year, int mouth) {
	pass_to_date(gyear+year+(mouth + gmouth)/12, (mouth + gmouth)%12);
}
