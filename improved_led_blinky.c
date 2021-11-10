/**
 ******************************************************************************
 * @file			improved_led_blinky.c
 * @brief			This program is an improved version of the led_blinky
 *                  program that we implemented. This program gracefully exits
 *                  after unexporting the GPIO pin.
 * 										
 * @author			Dheeraj Reddy
 * @version			v1.0
 ******************************************************************************
 */ 


/*******************************************************************************
 * Header inclusions
 ******************************************************************************/
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define LED_PIN     "6"       /* GPIO 6 on Linksys E1200 v2 controls the LED */ 

/**
 * Cleanup function that unexports the GPIO pin after we
 * terminate the program. If we don not do this,
 * the program quits with a "Resource busy" error.
 * @param	None
 * @return	None
 * */

static void Cleanup(void){
	printf("\nSIGINT Trapped! Cleaning up and exiting...\n");

    /* Open the gpio unexport file*/
    u_int32_t fd = open("/sys/class/gpio/unexport", O_WRONLY);

    /* Error check*/
    if (fd < 0){
        perror("Unable to open /sys/class/gpio/unexport");
        exit(EXIT_FAILURE);
    }

    if (write(fd, LED_PIN, 2*sizeof(char)) != 2) {
        perror("Error writing to /sys/class/gpio/unexport");
        exit(EXIT_FAILURE);
    }

    close(fd);
	exit(EXIT_SUCCESS);
}

/**
 * Program entry point
 * @param	None
 * @return	0 on success and -1 on failure
 * */

int main(int argc, char const *argv[]){

	/* Trap SIGINT signal: delivered on pressing Ctrl + c */
    struct sigaction act;
	memset(&act, 0, sizeof(act));
	act.sa_sigaction = (void*) Cleanup;
	if((sigaction(SIGINT, &act, NULL)) < 0)
		perror("sigaction() on SIGINT failed");

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
        /* Sleep for 250 milliseconds*/       
        usleep(250000);

        printf("Turning LED OFF\n");
        if (write(fd, "1", 1) != 1){
            perror("Error writing to /sys/class/gpio/gpio6/value");
            exit(EXIT_FAILURE);
        }
        /* Sleep for 250 milliseconds*/  
        usleep(250000);
    }

}
