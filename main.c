/*
 * main.c
 *
 *  Created on: 26.05.2014
 *      Author: stefan
 *
 *  Sources:
 *      - https://github.com/cymait/virtual-serial-port-example
 *      - http://www.tldp.org/HOWTO/text/Serial-Programming-HOWTO
 */


#include "pseudoterminal.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


uint8_t speed = 1;

char *command(char *input) {
    // All stop
    if (strcmp(input, "S\r") == 0) {
        return "stop";
    }
    // Get current position
    else if (strcmp(input, "C2\r") == 0) {
        return "get_pos";
    }
    // Set speed
    else if (input[0] == 'X') {

        // Size has to be 3
        if (strlen(input) != 3) {
            // error
            return "?";
        }

        // Second character contains speed value
        switch (input[1]) {
        case '1':
            speed = 1;
            break;
        case '2':
            speed = 2;
            break;
        case '3':
            speed = 3;
            break;
        case '4':
            speed = 4;
            break;
        default:
            return "?";
            break;
        }

        return "set_speed";
    }

    return "?";
}

int main(int argc, char** argv) {

    pseudoterminal_t pts = pts_open();

    if (pts.fd < 0) {
    	fprintf(stderr, "Could not open pseudo terminal");
    	return -1;
    }

    fprintf(stdout, "%s\n", pts.name);


    // Read line by line from serial port
    char input[255];
    char *output;
    bool stop = false;
    int res;

    while (stop == false) {
        res = read(pts.fd, input, 255);
        input[res]=0;             /* set end of string, so we can printf */

        output = command(input);

        fprintf(stdout, "input command: %s (%d bytes)\n > return: %s (%d bytes)", input, (int) sizeof(input), output, (int) sizeof(output));

        fprintf(stdout, "\n");
        fflush(stdout);

        // DEBUG: Always send invalid command
        //write(fd, "?", 1);

        // Answer
        write(pts.fd, output, sizeof(output));

        // Stop on 'q'
        if (input[0]=='q') {
            stop = true;
        }
    }


    pts_close(pts);

    return 0;
}
