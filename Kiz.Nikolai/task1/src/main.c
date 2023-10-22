#include <math.h>
#include "bankModel.h"




int main(int argc, char * argv[])
{
    Person alice = init_alice();
    Person bob = init_bob();
    process_model(&alice, &bob);
    handle_result(&alice, &bob);
}