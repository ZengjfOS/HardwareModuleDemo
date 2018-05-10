#ifndef _UART_US100_H__
#define _UART_US100_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define TTY_NODE1 "/dev/ttymxc2"
#define TTY_NODE2 "/dev/ttymxc1"
#define NSPEED  9600
#define NBIT    8
#define NEVENT  'N'
#define NSTOP   1
#define COMMAND 0x55


struct uart_us100
{
    char tty_node[20];
    int nSpeed;
    int nBits;
    char nEvent;
    int nStop;
    int distance;
    int command;
    char read_val[2];

    int (* read)(struct uart_us100 *);
    void (* release)(struct uart_us100 *);
    int (* set_opt)(int fd, int nSpeed, int nBits, char nEvent, int nStop);
};

/* Alloc uart_us100 structure  */
struct uart_us100 *uart_us100_init(char* tty_node);
/* Read us100 distant  */
int uart_us100_read(struct uart_us100 *);
/* Release and exit function  */
void uart_us100_release(struct uart_us100 *);
/* set tty attribute  */
int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop);

#endif
