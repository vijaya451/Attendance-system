 /// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include<time.h>

int main()
{
        FILE *fp= NULL;
        fp = fopen("data.txt","r");
        if(fp == NULL)
        {
                perror("fopen data.txt");
                return 1;
        }

        char read1[20];

        while(1)
        {
                int serial_port = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
                if(serial_port < 0)
                {
                        perror("open /dev/TTYUSB0\n");
                        sleep(1);
                        continue;
                }

                // Create new termios struct, we call it 'tty' for convention
                struct termios tty;

                if(tcgetattr(serial_port, &tty) != 0) {
                        perror("tcgettattr\n");
                        close(serial_port);
                        return 1;
                }

                tty.c_cflag &= ~PARENB;
                tty.c_cflag &= ~CSTOPB;
                tty.c_cflag &= ~CSIZE;
                tty.c_cflag |= CS8;
                tty.c_cflag &= ~CRTSCTS;
                tty.c_cflag |= CREAD | CLOCAL;

                tty.c_lflag &= ~ICANON;
                tty.c_lflag &= ~ECHO;
                tty.c_lflag &= ~ECHOE;
                tty.c_lflag &= ~ECHONL;
                tty.c_lflag &= ~ISIG;

                tty.c_iflag &= ~(IXON | IXOFF | IXANY);
                tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

                tty.c_oflag &= ~OPOST;
                tty.c_oflag &= ~ONLCR;

                tty.c_cc[VTIME] = 10;
                tty.c_cc[VMIN] = 100;

                cfsetispeed(&tty, B9600);
                cfsetospeed(&tty, B9600);

                if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
                        perror("tcsetattr\n");
                        close(serial_port);
                        return 1;
                }

                char read_buf[256];
                memset(read_buf, '\0', sizeof(read_buf));

                int num_bytes = read(serial_port, read_buf, sizeof(read_buf)-1);

                if (num_bytes <= 0) {
                        printf("Error reading: %s", strerror(errno));
                        close(serial_port);
                        return 1;
                }

                if(num_bytes == 0)
                {
                        close(serial_port);
                        usleep(100000);
                        continue;
                }

                read_buf[num_bytes] = '\0';

                int len = strlen(read_buf);
                if(len >= 12)
                {
                        memcpy(read1, &read_buf[len-12], 12);
                        read1[12] = '\0';
                }
                else
                {
                        close(serial_port);
                        continue;
                }

                FILE *fd = fopen("p1","a+");
                if(!fd)
                {
                        perror("fopen p1 error\n");
                        close(serial_port);
                        return 1;
                }

                rewind(fd);

                char s1[128], s2[128];
                int found = 0;

                rewind(fp);
                if(fp == NULL)
                {
                        perror("fp NULL");
                        continue;
                }

                while(fgets(s1,50,fp) != NULL)
                {
                        if(strstr(s1, read1))
                        {
                                found = 1;
                                int c = 0;

                                rewind(fd);
                                while(fgets(s2,50,fd) != NULL)
                                {
                                        if(strstr(s2, read1))
                                        {
                                                c++;
                                        }
                                }

                                time_t t;
                                time(&t);

                                if(c % 2 == 0)
                                        fprintf(fd, "%s in-time %s", s1, ctime(&t));
                                else
                                        fprintf(fd, "%s out-time %s", s1, ctime(&t));

                                fflush(fd);
                                printf("card scanned successfully: %s\n", read1);
                                break;
                        }
                }

                if(found == 0)
                {
                        printf("tag %s not found in data.txt\n", read1);
                }

                fclose(fd);
                close(serial_port);
                usleep(200000);
        }

        fclose(fp);
        return 0;
}
