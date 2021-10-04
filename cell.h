//
// Created by Фёдор Захаров on 28.09.2021.
//

#ifndef UNTITLED1_CELL_H
#define UNTITLED1_CELL_H
#endif //UNTITLED1_CELL_H

const int SIZE_OF_FIELD = 3;

extern bool check_if_cell_exist(int high, int wide);

bool END_OF_GAME = 0;
int score =0;
const int max_amount_of_raised_flags = int(SIZE_OF_FIELD * 3/2);
const int win_amount = int(SIZE_OF_FIELD * 3/2);
int amount_of_raised_flags = 0;

char symbols[] = {'0','1','2','3','4','5','6','7','8','9'};


class cell{

public:
    char picture = '#';
    bool is_mina_here = 0, flag = 0, is_open = 0;
    int number_of_mines_near, position_h, position_w;

private:

public:
    //print picture of cell
    void depict_cell(){std::cout << picture;}


    //check if cell was opened, if so does it has mine and change picture, open nearest empty cells
    //in a fact do all condition changes of a cell
    void open_cell ( cell (&field)[SIZE_OF_FIELD][SIZE_OF_FIELD]){

        if   ( !check_if_cell_exist(position_h,position_w) ){return;}

        if (is_open == 1){

            return;
        }

        if (is_mina_here == 1){
            END_OF_GAME = 1;
            is_open = 1;
            picture = '*';
            return ;
        }

        if ( number_of_mines_near == 0 )
        {
            for (int i = -1; i < 2; i++) {
                for (int k = -1; k < 2; k++)
                    if (!((i == 0) && (k == 0))) {
                        if (check_if_cell_exist(position_h + i, position_w + k)) {
                             field[position_h + i ][position_w + k].open_cell( field );
                                picture = symbols[0];
                                is_open= 1;

                        }
                    }
            }

            return;
        }

        else
            is_open = 1;
        return;
    }

    //get amount of mines in 1 cell range
    int get_number_of_mines_near(const cell (&field)[SIZE_OF_FIELD][SIZE_OF_FIELD] )
    {
        number_of_mines_near = 0;
        for (int i = -1; i < 2; i++) {
            for (int k = -1; k < 2; k++) {
                if (!((i == 0) && (k == 0))) {
                    if (check_if_cell_exist(position_h + i, position_w + k)) {
                        if (field[position_h + i][position_w + k].is_mina_here) {

                            //std::cout << position_h + i << "," << position_w + k <<" | ";

                            number_of_mines_near++; }

                    }
                }
            }
        }
        //std::cout  << "||||||"<< number_of_mines_near << "|||||"<< position_h << "," << position_w  << std::endl;

//
        return number_of_mines_near;
    };

    //put a flag on a cell
    void raise_flag (){

        if   (!check_if_cell_exist(position_h,position_w)){return;}

        if (amount_of_raised_flags >= max_amount_of_raised_flags){
            std::cout << "U already raised " << amount_of_raised_flags << ". Take one off.";
            return;
        }

        if (flag == 1){
            std::cout << "Flag here have already been raised"<< std::endl;
            return;
        }

        std::cout << is_mina_here << std::endl;
        if (is_mina_here == 1){
            score ++;
        }

        amount_of_raised_flags ++;
        flag = 1;
    }

    //take flag off
    void take_flag_of(){
        if   (!check_if_cell_exist(position_h,position_w)){return;}

        if (flag == 0){
            std::cout << "There is no flag!"<< std::endl;
            return;
        }

        if (is_mina_here == 1){
            score --;
        }
        flag = 0;
        amount_of_raised_flags--;
    }

};
