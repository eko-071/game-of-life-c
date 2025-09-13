#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>

void sleep_screen(){
    Sleep(200);
}

#else

#include <unistd.h>

void sleep_screen(){
    usleep(200000);
}

#endif

void clear_screen(){
    printf("\033[H\033[J");
}

typedef struct{
    int* row;
} grid;

grid* create_grid(int rows, int cols, int random){
    grid* array = (grid*) malloc(sizeof(grid)*rows);

    for(int i=0; i<rows; i++){
        array[i].row = (int*) malloc(sizeof(int) * cols);

        for(int j=0; j<cols; j++){
            if(rand()%random == 0) array[i].row[j] = 1;
            else array[i].row[j] = 0;
        }
    }

    return array;
}

grid* create_empty_grid(int rows, int cols){
    grid* array = (grid*) malloc(sizeof(grid)*rows);

    for(int i=0; i<rows; i++){
        array[i].row = (int*) malloc(sizeof(int) * cols);
    }

    return array;
}

void print_grid(grid* grid, int rows, int cols){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            //Prints a blue hash if cell is alive, and a gray dot if the cell is dead
            if(grid[i].row[j]==1) printf("\033[34m# \033[0m");
            else printf("\033[90m. \033[0m");
        }
        printf("\n");
    }
}

int get_alive_neighbours(grid* grid, int row, int col, int rows, int cols){
    int sum=0;
    for(int i=-1; i<2; i++){
        for(int j=-1; j<2; j++){
            if(i==0 && j==0) continue;
            //The modulus makes the graph wrap around
            //The extra addition of rows and cols is to avoid negative values
            sum += grid[(row + rows + i)%rows].row[(col + cols + j)%cols];
        }
    }
    return sum;
}

void create_next_generation(grid* present, grid* future, int rows, int cols){
    //Rules of Game of Life
    //Case 1: Cell is alive in present generation
    //Dies from underpopulation if it has less than 2 neighbours, and overpopulation if it has more than 3
    //Case 2: Cell is dead in present generation
    //Becomes alive if it has exactly 3 neighbours

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            int neighbours = get_alive_neighbours(present, i, j, rows, cols);

            if(present[i].row[j] == 1){
                if(neighbours < 2 || neighbours > 3) future[i].row[j] = 0;
                else future[i].row[j] = 1;
            }
            else{
                if(neighbours == 3) future[i].row[j] = 1;
                else future[i].row[j] = 0;
            }
        }
    }
}

int grid_change(grid* present, grid* future, int rows, int cols){
    //If grid doesn't change from present to future, it will always remain the same
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(present[i].row[j] != future[i].row[j]) return 1;
        }
    }
    return 0;
}

void start_game(int rows, int cols, int generations, int random){
    grid* present = create_grid(rows, cols, random);
    grid* future = create_empty_grid(rows, cols);

    for(int i=1; i<=generations; i++){
        clear_screen();
        print_grid(present, rows, cols);
        printf("Generation %d\n", i);
        create_next_generation(present, future, rows, cols);
        sleep_screen();
        if(grid_change(present, future, rows, cols) == 0) break;
        grid* temp = present;
        present = future;
        future = temp;
    }

    for(int i=0; i<rows; i++){
        free(present[i].row);
        free(future[i].row);
    }
    free(present);
    free(future);
}

int main(){
    srand(time(NULL));
    clear_screen();
    
    int rows, cols, generations, random;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    printf("Enter number of generations: ");
    scanf("%d", &generations);
    printf("Enter random density (i.e., 1 in x cells should be alive): " );
    scanf("%d", &random);

    if(random < 1) random = 1;
    
    start_game(rows, cols, generations, random);
    return 0;
}