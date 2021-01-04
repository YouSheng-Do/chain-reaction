#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions
 * 1. ~ 4. are listed in next block)
 *
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 *
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

#define MAX 100000
#define MIN -100000

int evaluator(Board board,Player player){
    int value = 0;
    bool vulnerable;
    int my_orbs = 0,enemy_orbs = 0;
    for(int i = 0;i <= ROW;i++){
        for(int j = 0;j <= COL;j++){
            if(board.get_cell_color(i,j)==player.get_color()){
                my_orbs += board.get_orbs_num(i,j);
                vulnerable = true;
                if(i-1>=0){//top
                    if(board.get_cell_color(i-1,j)!=player.get_color()&&board.get_orbs_num(i-1,j)==board.get_capacity(i,j)-1){
                        value -= 8-board.get_capacity(i,j);
                        vulnerable = false;
                    }
                }
                if(j-1>=0){//left
                    if(board.get_cell_color(i,j-1)!=player.get_color()&&board.get_orbs_num(i,j-1)==board.get_capacity(i,j)-1){
                        value -= 8-board.get_capacity(i,j);
                        vulnerable = false;
                    }
                }
                if(i+1>=0){//bottom
                    if(board.get_cell_color(i+1,j)!=player.get_color()&&board.get_orbs_num(i+1,j)==board.get_capacity(i,j)-1){
                        value -= 8-board.get_capacity(i,j);
                        vulnerable = false;
                    }
                }
                if(j+1>=0){//top
                    if(board.get_cell_color(i,j+1)!=player.get_color()&&board.get_orbs_num(i,j+1)==board.get_capacity(i,j)-1){
                        value -= 8-board.get_capacity(i,j);
                        vulnerable = false;
                    }
                }
                if(vulnerable){
                    if(board.get_capacity(i,j)==5)
                        value+=3;
                    else if(board.get_capacity(i,j)==3)
                        value+=5;
                    if(board.get_orbs_num(i,j)==board.get_capacity(i,j)-1)
                        value+=3;
                }
            }
            else{
                enemy_orbs += board.get_orbs_num(i,j);
            }
        }
    }
    value += my_orbs;
    if(enemy_orbs==0&&my_orbs>1){
        return 10000;
    }
    else if(my_orbs==0&&enemy_orbs>1){
        return -10000;
    }
    //chain value
    return value;
}

int alphabeta(Board board,Player player,int depth,int alpha,int beta,bool maximizingPlayer){
    int temp;
    int value;
    if(depth==0)
        return evaluator(board,player);
    if(maximizingPlayer){
        value = MIN;
        for(int i = 0;i < ROW;i++){
            for(int j = 0;j<COL;j++){
                if(board.get_cell_color(i,j)==player.get_color()||board.get_cell_color(i,j)=='w'){
                    Board new_board = board;
                    new_board.place_orb(i,j,&player);
                    temp = alphabeta(new_board,player,depth-1,alpha,beta,false);
                    if(value<temp)
                        value=temp;
                    if(alpha<value)
                        alpha = value;
                    if(alpha>beta)
                        break;
                }
            }
        }
        return value;
    }
    else{
        value = MAX;
        for(int i = 0;i < ROW;i++){
            for(int j = 0;j<COL;j++){
                if(board.get_cell_color(i,j)!=player.get_color()||board.get_cell_color(i,j)=='w'){
                    Board new_board = board;
                    new_board.place_orb(i,j,&player);
                    temp = alphabeta(new_board,player,depth-1,alpha,beta,true);
                    if(value>temp)
                        value=temp;
                    if(beta>value)
                        beta = value;
                    if(alpha>beta)
                        break;
                }
            }
        }
        return value;
    }
}

void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
    int alpha = MIN;
    int beta = MAX;
    int max_val = MIN;
    for(int i = 0;i < ROW;i++){
        for(int j = 0;j<COL;j++){
            if(board.get_cell_color(i,j)==player.get_color()||board.get_cell_color(i,j)=='w'){
                Board new_board = board;
                new_board.place_orb(i,j,&player);
                int temp = alphabeta(new_board,player,4,alpha,beta,false);
                if(temp>max_val){
                    max_val = temp;
                    alpha = temp;
                    index[0] = i;
                    index[1] = j;
                }
            }
        }
    }
}
