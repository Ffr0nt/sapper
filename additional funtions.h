//
// Created by Фёдор Захаров on 28.09.2021.
//
#ifndef UNTITLED1_ADDITIONAL_FUNTIONS_H
#define UNTITLED1_ADDITIONAL_FUNTIONS_H
#endif //UNTITLED1_ADDITIONAL_FUNTIONS_H

//get int number from user and check if it really is
int enter_number()
{
    int number;
    while (true)
    {
        if ( std::cin >> number) // если ввод успешный...
        {
            if (number < 0)
            {
                std::cout << "ERROR: number less then 0!" <<  std::endl <<  std::endl;
            }
            else
            {
                std::cout <<  std::endl;
                return number;
            }
        }
        else // а если ввод плохой...
        {
            std::cout << "ERROR: It's not a number!" <<  std::endl <<  std::endl;
            std::cin.clear(); // Очищает признак ошибки в cin
            std::cin.ignore(std::numeric_limits< std::streamsize>::max(), '\n'); // Очистить буфер ввода
        }
    }
}

//print pictures of all sells in a field shape
void print_field (const cell (&field)[SIZE_OF_FIELD][SIZE_OF_FIELD]){
    std::cout << "  ";
    for (int i =0 ;i < SIZE_OF_FIELD; i++) {
        std::cout << i;
    }
    std::cout <<std::endl;


    for (int i =0 ;i < SIZE_OF_FIELD; i++){
        std::cout   << i << "|";
        for (int k = 0;k < SIZE_OF_FIELD; k++){
            if (field[i][k].is_open == 1){
                std::cout   <<  field[i][k].picture;
                continue;}

            {
                if (field[i][k].flag == 1){
                    std::cout   <<  'F';
                    continue;
                }
                std::cout   <<  "#";}
        }
        std::cout<< std::endl;
    }
}

//developer tool
void print_field_mines (const cell (&field)[SIZE_OF_FIELD][SIZE_OF_FIELD]){
    std::cout << "  ";
    for (int i =0 ;i < SIZE_OF_FIELD; i++) {
        std::cout << i;
    }
    std::cout <<std::endl;


    for (int i =0 ;i < SIZE_OF_FIELD; i++){
        std::cout   << i << "|";
        for (int k = 0;k < SIZE_OF_FIELD; k++){

            if (field[i][k].is_mina_here == 1){
                std::cout   << '*';
                continue;}

            if (field[i][k].number_of_mines_near == 0){
                std::cout   << '0';
                continue;}

            std::cout   << '#';

        }
        std::cout<< std::endl;
    }
}

//check if cell with such corditates exist
bool check_if_cell_exist (int high, int wide){
    if ((high >= 0) && (high < SIZE_OF_FIELD) && (wide < SIZE_OF_FIELD) && (wide >= 0)){
        return 1;
    }
    else{return 0;}
}
//////////////////////////////////////////////////////////////////////////

// sets all the field of cells
//sets mines and count num of mines near
void set_field( cell (&field)[SIZE_OF_FIELD][SIZE_OF_FIELD] ) {
    char symbols[] = {'0','1','2','3','4','5','6','7','8','9'};

    srand(time(0));
    int a[SIZE_OF_FIELD * 3/2][2];

    for (int i = 0; i < int(SIZE_OF_FIELD * 3/2); i++) {
        a[i][0] =  rand() % SIZE_OF_FIELD;
        a[i][1] =  rand() % SIZE_OF_FIELD;
    }

    for (int i = 0; i < int(SIZE_OF_FIELD * 3/2); i++) {

        for (int k = 0; k < int(SIZE_OF_FIELD * 3/2); k++) {

            if (k == i){k ++;}

            if ((a[i][0] == a[k][0]) && (a[i][1] == a[k][1])){
                a[i][0] = rand() % SIZE_OF_FIELD;
                a[i][1] = rand() % SIZE_OF_FIELD;
                k = 0;
            }
        }
    }
    //mark cells with mines
    for(int i = 0;i < int(SIZE_OF_FIELD * 3/2); i++){
        field [ a[i][0] ][ a[i][1] ].is_mina_here = 1;
        field [ a[i][0] ][ a[i][1] ].picture = '*';
    }

    //for each cell count mines near and cordinates
    for(int k = 0;k < SIZE_OF_FIELD; k++){
        for(int i = 0;i < SIZE_OF_FIELD; i++){

            field [ k ][ i ].position_h  = k;
            field [ k ][ i ].position_w = i;
            field [ k ][ i ].get_number_of_mines_near(field);
            field [ k ][ i ].picture = symbols[field [ k ][ i ].number_of_mines_near];
    }
    }

}

//user's interface. Provide choice of command (open cell, raise/take of flag)
void menu(cell (&field)[SIZE_OF_FIELD][SIZE_OF_FIELD]){
    int H = 0,W = 0;

    if (score == win_amount){
        END_OF_GAME = 1;
        return;
    }

    std::cout << "If U want to open cell enter 1."<< std::endl;
    std::cout << "If U want to raise a flag enter 2."<< std::endl;
    std::cout << "If U want to take a flag of enter 3."<< std::endl;

    int comand_number = enter_number();


    switch(comand_number) {
        case 1:

            std::cout << "Enter H and W cordinates in format: H W"<< std::endl;
            std::cin >> H >> W;

            if   (!check_if_cell_exist(H,W)){
                std::cout << "This cell do not exist"<< std::endl;
                return;}

            field[H][W].open_cell(field);
            break;
        case 2:

            std::cout << "Enter H and W cordinates of flag in format: H W"<< std::endl;
            std::cin >> H >> W;

            if   (!check_if_cell_exist(H,W)){
                std::cout << "This cell do not exist"<< std::endl;
                return;}

            field[H][W].raise_flag();
            break;

        case 3:

            std::cout << "Enter H and W cordinates of flag u want to take of in format: H W"<< std::endl;
            std::cin >> H >> W;

            if   (!check_if_cell_exist(H,W)){
                std::cout << "This cell do not exist"<< std::endl;
                return;}
            field[H][W].take_flag_of();
            break;

        default:
            std::cout << "Wrong number!!!"<< std::endl;
    }


}

//final message
void epiloge(int score, int  winn_amount){


if (score == winn_amount){
    std::cout << "U win!!!"<< std::endl;
}
else{
    std::cout << "U loose..."<< std::endl;
}
}