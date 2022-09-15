#ifndef __GRADIENT_H__
#define __GRADIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    int x;
    int y;
}path_point;

// Odd-numbered size for the view so we have a proper center
#define VIEW_SIZE 11
#define VIEW_RADIUS 5

path_point find_highest_point();
void generate_view(float view[VIEW_SIZE][VIEW_SIZE], int center_y, int center_x);
int declare_peak(int x, int y);

#endif


path_point find_highest_point(){
    printf("Start!\n");
    path_point ret;
    int x_position = 25;
    int y_position = 25;
    float visible[11][11];
    float highest_point_yet = 0;
    int highest_x = 0;
    int highest_y = 0;
    short int newhighestcheck = 1;
    int plateaucheck;
    
    printf("Variables Declared\n");
    while(newhighestcheck == 1){
        plateaucheck = 0;
        generate_view(visible, y_position, x_position);
        newhighestcheck = 0;
        //printf("Loop Start!\n");
        //Traverse x
    for(int i = 0; i < 11; i++){
        //printf("i Loop Start\n");
        //Traverse y
        for(int j = 0; j<11; j++){
            //printf("j Loop Start!\n");
            //printf("%6.2f ", visible[i][j]);
            if(visible[i][j] > highest_point_yet){
                //printf("if Statement Triggered!\n");
                highest_point_yet = visible[i][j];
                highest_x = j-VIEW_RADIUS;
                highest_y = i-VIEW_RADIUS;
                newhighestcheck = 1;
            }
            if(visible[i][j] >= 0 && visible[i][j] == highest_point_yet){
                plateaucheck = plateaucheck + 1;
            }
        }
        //printf("\n");
    }
    //printf("Highest: %0.2f, X: %d, Y: %d\n", highest_point_yet, highest_x, highest_y);
    //printf("plateaucheck: %d\n", plateaucheck);
    
    if(plateaucheck > 5 && highest_y == 0 && highest_x == 0){
        //printf("PLATEAU DETECTED! DEPLOYING EMERGENCY MEASURES!\n");
        newhighestcheck = 1;
        if(visible[11][11] != -1){
            highest_x = 5;
            highest_y = 5;
        }
        else{
            x_position = rand() % 200;
            y_position = rand() % 200;
            highest_point_yet = 0;
            highest_x = 0;
            highest_y = 0;
            newhighestcheck = 1;
        }
    }
    
    x_position = x_position + highest_x;
    y_position = y_position + highest_y;
    highest_x = 0;
    highest_y = 0;
    
    int foundpeak = declare_peak(x_position, y_position);
    printf("%d", foundpeak);
    
    if(newhighestcheck == 0 && foundpeak == 0){
        x_position = rand() % 200;
        y_position = rand() % 200;
        newhighestcheck = 1;
        highest_point_yet = 0;
    }
    //printf("New position is X: %d, Y: %d\n",x_position, y_position);
    //printf("Position changed?: %d\n", newhighestcheck);
    }
    printf("Out of the loop\n");
    printf("Highest: %0.2f, X: %d, Y: %d\n", highest_point_yet, x_position, y_position);
    ret.x = x_position;
    ret.y = y_position;
    return ret;
}