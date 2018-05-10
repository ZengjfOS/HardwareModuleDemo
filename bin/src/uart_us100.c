#include "../include/uart_us100.h"

struct uart_us100 *uart_us100_init(char* tty_node)
{
    struct uart_us100 *us100;

    us100 = (struct uart_us100 *)malloc(sizeof(struct uart_us100));
    if (!us100)
        return NULL;

    memset(us100, 0, sizeof(struct uart_us100));

    strcpy(us100->tty_node, tty_node);
    us100->nSpeed = NSPEED;
    us100->nBits = NBIT;
    us100->nEvent = NEVENT;
    us100->nStop = NSTOP;
    us100->command = COMMAND;

    us100->read = uart_us100_read;
    us100->release = uart_us100_release;
    us100->set_opt = set_opt;

    return us100;
}

int uart_us100_read(struct uart_us100 *us100)
{
    int retval, tty_fd, distant;

    // printf("%s.\n", us100->tty_node);

    tty_fd = open(us100->tty_node, O_RDWR | O_NOCTTY | O_NDELAY);
    if (tty_fd < 0)
    {
        perror("open tty error ");
        return -1;
    }

    retval = set_opt(tty_fd, us100->nSpeed, us100->nBits, us100->nEvent, us100->nStop);
    if (retval < 0)
    {
        perror("set error");
        return -1;
    }

    // printf("command: %d.\n", us100->command);
    retval = write(tty_fd, &(us100->command), 1);
    if (retval < 0)
    {
        perror("write error");
        return -1;
    }

    usleep(100000);

    retval = read(tty_fd, us100->read_val, 1);
    if (retval < 0)
    {
        perror("read errno");
        return -1;
    }

    distant = us100->read_val[0];
    // printf("distant: %d.\n", us100->read_val[0]);

    close(tty_fd);

    return distant;
}

void uart_us100_release(struct uart_us100 *us100)
{
    free(us100);
}

int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio, oldtio;
    if(tcgetattr(fd, &oldtio) != 0)
    {
        perror("SetupSerial 1");
        return -1;
    }
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD;   //CLOCAL:忽略modem控制线  CREAD：打开接受者
    newtio.c_cflag &= ~CSIZE;           //字符长度掩码。取值为：CS5，CS6，CS7或CS8

    switch( nBits )
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }

    switch( nEvent )
    {
    case 'O':
        newtio.c_cflag |= PARENB;           //允许输出产生奇偶信息以及输入到奇偶校验
        newtio.c_cflag |= PARODD;           //输入和输出是奇及校验
        newtio.c_iflag |= (INPCK | ISTRIP); // INPACK:启用输入奇偶检测；ISTRIP：去掉第八位
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }

    switch( nSpeed )
    {
    case 2400:
        cfsetispeed(&newtio, B2400);
        cfsetospeed(&newtio, B2400);
        break;
    case 4800:
        cfsetispeed(&newtio, B4800);
        cfsetospeed(&newtio, B4800);
        break;
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    case 460800:
        cfsetispeed(&newtio, B460800);
        cfsetospeed(&newtio, B460800);
        break;
    default:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    }

    if( nStop == 1 )
        newtio.c_cflag &=  ~CSTOPB;     //CSTOPB:设置两个停止位，而不是一个
    else if ( nStop == 2 )
        newtio.c_cflag |=  CSTOPB;

    newtio.c_cc[VTIME]  = 0;            //VTIME:非cannoical模式读时的延时，以十分之一秒位单位
    newtio.c_cc[VMIN] = 0;              //VMIN:非canonical模式读到最小字符数
    tcflush(fd,TCIFLUSH);               // 改变在所有写入 fd 引用的对象的输出都被传输后生效，所有已接受但未读入的输入都在改变发生前丢弃。
    if((tcsetattr(fd,TCSANOW,&newtio))!=0) //TCSANOW:改变立即发生
    {
        perror("com set error");
        return -1;
    }
    return 0;
}


