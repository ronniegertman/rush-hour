#include <stdio.h>
#include <stdbool.h>

#define MAX_LOT_LENGTH 9
#define MAX_CAR_AMOUNT 10

#define EMPTY_SLOT ' '
#define EMPTY_SLOT_INPUT 'x'
#define RED_CAR_CHAR '*'

#define MAX_TURN_COUNT 10

    // static int counter = 0;

// gets as input from the user the entire parking lot configuration and retuns it's length
// an empty slot in the parking lot will be represented as 'x', but when the lot s printed it should be as ' ' (space)
// @param lot - the 2D array to fill as the parking lot.
// returns int that is the lenght of the lot

int inputAndParseParkingLot(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH]);
int car_amount(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int size);




int inputAndParseParkingLot(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH]){
    printf("Are you ready for rush hour?\n");
    int length = -1;
    printf("Please enter the parking lot length: ");
    scanf("%d", &length); // assume this is always correct
    printf("Please enter the parking lot:\n");
    for(int i =0; i < length; ++i){
        for(int j = 0; j < length; ++j){
            scanf(" %c", &(lot[i][j]));
            if(lot[i][j] == EMPTY_SLOT_INPUT){
                lot[i][j] = EMPTY_SLOT;
            }
        }
    }
    return length;
}

//calculates the amount of cars in the parking lot - index 0 is ladybug.
int car_amount(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int size){
    int amount = 0;
    int count [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(lot[i][j] == '*'){
                count[0] = 1;
            } else if(lot[i][j] != EMPTY_SLOT){
                count[lot[i][j] - '0'] = 1;
            }
        }
    }
    for(int i=0; i<10; i++){
        if(count[i] == 1){
            amount ++;
        }
    }
    return amount;
}


char car_shape(char car, char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int length);

//checks if a car exists in the parking lot
// params: car to check, amount of cars in the parking lot
bool is_exist(char car, int amount){
    if(car == '*'){
        return true;
    } if(car - '0' >= 1 && car - '0' < amount){
        return true;
    } return false;
    
}


bool is_square(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int l, int i, int j){
    if(i != (l -1) && j != (l -1)){
        if((lot[i][j] == lot[i+1][j]) && (lot[i][j+1] == lot[i][j])){
            return true;
        }
    } return false;
}

bool is_column(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int l, int i, int j){
    if(i != l - 1){
        if(lot[i][j] == lot[i+1][j]){
            return true;
        }
    } return false;
}

bool is_row(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int l, int i, int j){
    if(j != l -1){
        if(lot[i][j] == lot[i][j+1]){
            return true;
        }
    } return false;
}

//l: length of the real parking lot
int size_column(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int i, int j, int l){
    int size = 0;
    char car  = lot[i][j];
    for(int y = i; y<l; y++){
        if(lot[y][j] == car){
            size ++;
        } if(lot[y][j] != car){
            break;
        }
    }
    return size;
}


//l: length of the real parking lot 
int size_row(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int i, int j, int l){
    int size = 0; 
    char car = lot[i][j];
    for(int y = j; y<l; y++){
        if(lot[i][y] == car){
            size ++; 
        } if(lot[i][y] != car){
            break;
        }
    }
    return size; 
}

bool move_down(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int l, int i, int j, 
int size){
    char car = lot[i][j];
    if(i+size < l){
        if(lot[i+size][j] == EMPTY_SLOT){
        lot[i+size][j] = lot[i][j];
        lot[i][j] = EMPTY_SLOT;
        return true;
    } }
    return false;
    } 


bool move_up(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int l, int i, int j,
int size){
    char car = lot[i][j];
    if(i-1 >= 0){
        if(lot[i-1][j] == EMPTY_SLOT){
            lot[i-1][j] = lot[i][j];
            lot[i+size -1][j] = EMPTY_SLOT;
            return true;
    } }
    return false;
}

//should be done on a copy of the lot matrix and then, if returns true will be 
//copied to the real matrix.

bool move_right(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int l, int i, int j,
int size){
    char car = lot[i][j];
    if(j+size<l){
        if(lot[i][j+size] == EMPTY_SLOT){
            lot[i][j+size] = lot[i][j];
            lot[i][j] = EMPTY_SLOT;
            return true;
        }
    }
    return false;
}


bool move_left(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int l, int i, int j,
int size){
    char car = lot[i][j];
        if(j-1>=0){
            if(lot[i][j-1] == EMPTY_SLOT){
                lot[i][j-1] = lot[i][j];
                lot[i][j+size-1] = EMPTY_SLOT;
                return true;
            }
        }
        
    return false;
}


void copy(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], 
char mat[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int l){
    for(int i=0; i<l; i++){
        for(int j=0; j<l; j++){
            mat[i][j] = lot[i][j];
        }
    }
}


bool move_car(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int l,
char dir, int i, int j, char car){
    //we have to check if car exists first 
    char shape = car_shape(car, lot, l);
    if(shape == 'c' && (dir == 'r' || dir == 'l')){
        return false;
    }
    if(shape == 'r' &&(dir == 'u' || dir == 'd')){
        return false;
    }
    
    if(dir == 'r'){
        return move_right(lot, l, i, j, size_row(lot, i, j, l));
    } if(dir == 'l'){
        return move_left(lot, l, i, j, size_row(lot, i, j, l));
    } if(dir == 'u'){
        return move_up(lot, l, i, j, size_column(lot, i, j, l));
    } if(dir == 'd'){
        return move_down(lot, l, i, j, size_column(lot, i, j, l));
    } return false;

}


//returns the shape of the car
char car_shape(char car, char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int length){
    int i =0, j=0;
    for(i; i<length; i++){
        for(j; j<length; j++){
            if(lot[i][j] == car){
                break;
            }
        }
    if(is_square(lot, length, i, j)){
        return 's';
    } if(is_column(lot, length, i, j)){
        return 'c';
    } 
    return 'r';
}
}


// prints the parking lot
// empty slot will be printed as ' ' (define EMPTY_SLOT)
void printParkingLot(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int length){
    for(int k = 0; k < length; ++k){
            printf("~~~");
        }
    printf("\n");
    for(int i = 0; i < length; ++i){
        for(int j = 0; j < length; ++j){
            printf("|%c|", lot[i][j]);
        }
        printf("\n");
        for(int k = 0; k < length; ++k){
            printf("~~~");
        }
        printf("\n");
    }
}

void printEnterCar(){
    printf("Enter the car you want to move:\n");
}

void printInvalidCar(){
    printf("Invalid car id! enter again:\n");
}

void printEnterDirection(){
    printf("Please enter the direction to move the car:\n");
}

void printInvalidDirection(){
    printf("Invalid direction!\n");
}

void printInvalidMove(){
    printf("Invalid move!\n");
}

void printGameWon(){
    printf("GAME OVER! YOU WIN :D\n");
}

void printGameLost(){
    printf("GAME OVER! YOU LOST :(\n");
}


bool valid_input(char dir){
    return dir == 'r' || dir == 'l' || dir == 'u' || dir == 'd';
}

int index_i(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int size, char car){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++)
        if(lot[i][j] == car){
            return i;
        }
    } return -1;
}

int index_j(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int size, char car){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++)
        if(lot[i][j] == car){
            return j;
        }
    } return -1;
}


bool is_win(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int size){
    if(lot[(size/2)][size - 1] == '*'){
        return true;
    } return false;
}


bool handle_game(char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH], int size){
    
    int moves = 0;
    bool again = false;
    char copied[MAX_LOT_LENGTH][MAX_LOT_LENGTH] = {0};
    
    bool tempCheck1 = true; // ------------------------
    bool tempCheck2 = false;
    
    while(moves < 10){
        char car, dir; 
        if(!again){
            printEnterCar();
        }
        
        if(scanf(" %c", &car) != 1 || !is_exist(car, car_amount(lot, size))){
            printInvalidCar(); 
            again = true; 
            continue; 
        }else{
            again = false;
        }
        
        // ----------------------------------
        // if (tempCheck1) {
        //     if (car != '2') {
        //         return false;
        //     } else {
        //         tempCheck1 = false;
        //         tempCheck2 = true;
        //     }
        // } else if (tempCheck2) {
        //     if (car != '4') {
        //         return false;
        //     } else {
        //         tempCheck2 = false;
        //     }
        // }
        
  
        printEnterDirection();
        if(scanf(" %c", &dir) != 1 || !valid_input(dir)){
            printInvalidDirection(); printParkingLot(lot, size); continue;
        }
        
        
        copy(lot, copied, size);
        int i = index_i(lot, size, car), j = index_j(lot, size, car);
        
        if(move_car(copied, size, dir, i, j, car))
        {
            copy(copied, lot, size);
            printParkingLot(lot, size);
            moves ++;
        } 
        else
        {
            printInvalidMove();
            printParkingLot(lot, size);
        }
        
        if(moves <= 10 && is_win(lot, size))
        {
            return true;
        }
    
    } 
    
        if (moves>10)
        {
            return false;
        }
    
    return false;
}

// int main(){
//     return 0;
// }

int main()
{
    char lot[MAX_LOT_LENGTH][MAX_LOT_LENGTH];
    int size = inputAndParseParkingLot(lot);
    
    // if(size != 7){
    //     return 0;
    // }
    
    printParkingLot(lot, size);
    if(handle_game(lot, size)){
        printGameWon();
        return 0;
    }
    printGameLost();
    return 0;
    // good luck! try and break this into small parts.
    // maybe start with counting how many cars...?
}
