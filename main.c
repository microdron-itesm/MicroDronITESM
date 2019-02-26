#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    char imuMessage[] = "90 80 89";
    float yaw, pitch, roll;

    int result = sscanf(imuMessage, "%f %f %f", &yaw, &pitch, &roll);
    printf("%i", result);

    //If the correct amount of numbers is found, use them
    if(result == 3){
        printf("Y: %f P: %f R: %f", yaw, pitch, roll);
    }
  
    return 0;
}