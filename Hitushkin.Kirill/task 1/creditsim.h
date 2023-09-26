#define INIT_PERS(Name) struct Person* Name = init_pers(#Name); count_person += 1; person_list[count_person-1] = Name;
#define name_is(n) (strcmp(pers->name, n) == 0)
#define event(name, cost) void name(struct Person* pers) {add_bank_account(pers, cost);}

#define max_credit 5
#define max_person 10
#define max_property 20

int gmouth;
int gyear;

struct Person* person_list[max_person];
int count_person;

typedef long long int Money;

struct Person {
	char *name;
    Money bank_account;
    Money salary;
    int count_credits;
    Money credit[max_credit];
    int credit_percent[max_credit];
    int credit_mouth[max_credit];
    Money property[max_property];
    char *property_name[max_property];
    int count_property;
};

struct Person* init_pers(char* name);

void deinit();

void set_salary(struct Person* pers, int salary);

void add_bank_account(struct Person* pers, int add);

void percent_bank_account(struct Person* pers, int percent);

void take_credit(struct Person* pers, Money credit, int percent, int credit_years);

void buy_property(struct Person* pers, char* name, Money property);
void add_property(struct Person* pers, char* name, Money property);
void sold_property(struct Person* pers, char* name);
void del_property(struct Person* pers, char* name);
void percent_property(struct Person* pers, char* name, int percent);
int have_property(struct Person* pers, char* name);

void print_person_info(struct Person* pers);

void print_all();

void history(struct Person* pers);

void pass_to_date(int year, int mouth);

void pass_time(int year, int mouth);