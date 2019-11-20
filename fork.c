#include<stdlib.h>
#include<time.h>
#include<error.h>
#include<errno.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
/*
在Linux系统中编写程序，要求如下：
1.主进程（父进程）在同一目录下创建三个文本文件A、B、C，其中A文件为空，B、C两个文件的大小均为10字节，内容任意指定；
2.主进程创建两个子进程P1和P2,要求进程P1首先将文件B中的第一个字符写入文件A作为A的第一个字符，然后进程P2将文件C中的第一个字符写入A作为A的第二个字符，接着P1将B中的第二个字符写入A作为A的第三个字符，P2将C中的第二个字符写入A作为A的第四个字符，这样逐字节依次类推，将B、C文件中的内容全部写入文件A。
3.当步骤2的内容完成后，子进程P1终止退出，子进程P2使用exec函数族的函数执行shell命令“vi”打开文件A。
*/
int get_msecond()
{
	struct timeval tv;
	while(1)
	{
		gettimeofday(&tv, NULL);
		printf("millisecond:%ld\n", tv.tv_usec/1000);
		sleep(1);
	}		//sleep(0.5);
}
int get_second()
{
	time_t timer;
	struct tm *tblock;
	time(&timer);
	tblock = gmtime(&timer);
	return (int)(tblock->tm_sec);
}
int init()
{
	FILE *fd1, *fd2, *fd3;

	fd1 = fopen("a.cfg", "w");
	if(fd1 == NULL)
	{
		printf(" init open file error!\n");
		exit(1);
	}
	fclose(fd1);

	fd1 = fopen("c.cfg", "w");
	if(fd1 == NULL)
	{
		printf(" init open file error!\n");
		exit(1);
	}
	fputs("helloworld", fd1);
	fclose(fd1);

	fd2 = fopen("b.cfg", "w");
	if(fd2 == NULL)
	{
		printf("init open file error!\n");
		exit(1);
	}
	fputs("0123456789", fd2);
	fclose(fd2);

}
int read_from_pipe(int fd)
{
        char message[100] = {0};
        if(read(fd, message, 100) > 0)
	{
        //	printf("read from pipe:%s\n", message);
		return 1;
	}
	else
		return 0;
}

int write_to_pipe(int fd)
{
    char *message = "Linux is a nice system!\n";
	if(write(fd, message, strlen(message)+1) == -1)
	{
		printf("write error!\n");
		exit(1);
	}
	return 1;
}
int Fgets(const char *file, char *str)
{
	FILE *fd1;
	fd1 = fopen(file, "r+");
	if(fd1 == NULL)
	{
		printf("open file error!\n");
		exit(1);
	}
	fgets(str, 11, fd1);
	fclose(fd1);
}
int Write(int i, char *p)
{
	FILE *fd1;
	fd1 = fopen("a.cfg", "a");
	if(fd1 == NULL)
	{
		printf("open file error!\n");
		exit(1);
	}
	fputc(p[i], fd1);
	fclose(fd1);
}
int main()
{
	pid_t pid, pid1, pid2;
 	int stat = 0, i = 0, fd[2], fd1[2];
	char p[11] = {0};
	char *ar[] = {"vi", "a.cfg", NULL};
	init();
	if(pipe(fd) || pipe(fd1))
	{
		perror("Create pipe failed!\n");
		exit(1);
	}
	pid1 = fork();
	if(pid1 == 0)//第一个子进程
	{
		Fgets("b.cfg", p);
		p[10] = '\0';
		close(fd[0]);//关闭fd的读端，用fd来写
		close(fd1[1]);//关闭fd1的写端，用fd1来读
		do
		{
			Write(i, p);
			++i;
			//close(fd[0]);//关闭fd的读端，用fd来写
			//close(fd1[1]);//关闭fd1的写端，用fd1来读
			printf("P1 running\n");
			write_to_pipe(fd[1]);//
		}while(i<10 && read_from_pipe(fd1[0]));
		close(fd[1]);
		close(fd1[0]);
		exit(0);
	}
	else
	{
		pid2 = fork();
		if(pid2 == 0)
		{
			Fgets("c.cfg", p);
			p[10] = '\0';
			//sleep(1);
			close(fd[1]);//关闭fd的写端，用fd来读
			close(fd1[0]);//关闭fd1的读端，用fd1来写
			while(i<10 && read_from_pipe(fd[0]))
			{
				Write(i, p);
				++i;
				//close(fd1[0]);//关闭fd1的读端，用fd1来写
				write_to_pipe(fd1[1]);
				printf("P2 running\n");
				//close(fd[1]);
			}
			close(fd[0]);
			close(fd1[1]);
		}
		else
		{
			printf("parent process PID is %ld, P1 process PID is %d, P2 process PID is %d\n", getpid(), pid1, pid2);
			waitpid(pid2, NULL, NULL);
		}
	}
	if(pid2 == 0)
	{
		errno = 0;
		printf("process %d will use vi open file %s\n", getpid(), "a.cfg");
		if(execl("/usr/bin/vi", "vi", "/home/wbw/fork/a.cfg",NULL)<0)
			printf("error num is %d, reason is %s\n", errno, strerror(errno));
	}
	exit(0);
}
