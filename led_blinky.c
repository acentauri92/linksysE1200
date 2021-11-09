#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define LED_PIN     "6"       /* GPIO 6 on Linksys E1200 v2 controls the LED */ 

int main(int argc, char const *argv[])
{
    /* Open the gpio export file*/
    u_int32_t fd = open("/sys/class/gpio/export", O_WRONLY);

    /* Error check*/
    if (fd < 0){
        perror("Unable to open /sys/class/gpio/export");
        exit(EXIT_FAILURE);
    }

    if (write(fd, LED_PIN, 2*sizeof(char)) != 2) {
        perror("Error writing to /sys/class/gpio/export");
        exit(EXIT_FAILURE);
    }

    close(fd);

    /* Make pin 6 as an output pin*/
    fd = open("/sys/class/gpio/gpio6/direction", O_WRONLY);
    if (fd < 0) {
        perror("Unable to open /sys/class/gpio/gpio6/direction");
        exit(EXIT_FAILURE);
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio6/direction");
        exit(EXIT_FAILURE);
    }

    close(fd);

    /* Open file for writing the value*/
    fd = open("/sys/class/gpio/gpio6/value", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio6/value");
        exit(EXIT_FAILURE);
    }

    /* Toggle LED */
    while(1){

        printf("Turning LED ON\n");
        if (write(fd, "0", 1) != 1){
            perror("Error writing to /sys/class/gpio/gpio6/value");
            exit(EXIT_FAILURE);
        }
        /* Sleep for 1 second*/       
        usleep(250000);

        printf("Turning LED OFF\n");
        if (write(fd, "1", 1) != 1){
            perror("Error writing to /sys/class/gpio/gpio6/value");
            exit(EXIT_FAILURE);
        }
        usleep(250000);
    }

    return EXIT_SUCCESS;
}
