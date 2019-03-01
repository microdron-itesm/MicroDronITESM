#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const unsigned int MAX_BUFFER_SIZE = 20;

int main(){
    char imuMessage[] = ",-90.0 90.0 89.0\n";
    float yaw, pitch, roll;

    int result = sscanf(imuMessage + 1, "%f %f %f", &yaw, &pitch, &roll);
    printf("%d\n", result);

    char buffer[10];
    int ret = snprintf(buffer, sizeof buffer, "%f", yaw);
    int i;
    for(i = 0; i < 10; ++i){
        printf("%c", buffer[i]);
    }
    printf("\n");

    //If the correct amount of numbers is found, use them
    if(result == 3){
        printf("Y: %f P: %f R: %f\n", yaw, pitch, roll);
    }
    
    // char bufferPlaceholder[] = "01234567899999999999999999";
    // int bufferSize = sizeof(bufferPlaceholder) / sizeof(char) - 1; 
    // printf("%d\n", bufferSize);


    // char readBuffer [MAX_BUFFER_SIZE];
    // int currentBufferIndex = 0;
    // unsigned char byte;
    
    // while(bufferSize > 0 && currentBufferIndex < MAX_BUFFER_SIZE){
    //     byte = bufferPlaceholder[10 - bufferSize] ;//Read byte;
    //     printf("%d", byte);
    //     readBuffer[currentBufferIndex] = byte;
    //     bufferSize--;
    //     currentBufferIndex++;
    // }
    // printf("%s", readBuffer);


    return 0;
}