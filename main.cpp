#include <iostream>
#include "cell.h"
#include "additional funtions.h"


int main() {

    cell field[SIZE_OF_FIELD][SIZE_OF_FIELD];

    set_field( field );
    

    for (;END_OF_GAME == 0;){
        menu(field);
        print_field( field );
    }

    epiloge(score, win_amount);

    return 0;
}
