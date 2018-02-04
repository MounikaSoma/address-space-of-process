#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int g_first,g_second,g_third;
void PrintVariable()
{
	int j,k,l;
	printf("local j:%p\n",&j);
	printf("local k:%p\n",&k);
	printf("local l:%p\n",&l);
	printf("global g_first:%p\n",&g_first);
	printf("global g_second:%p\n",&g_second);
	printf("global g_third:%p\n",&g_third);
}

int main(void)
{
	int a,b,c;
	pid_t PID1,PID2,PID3;
	printf("local a:%p\n",&a);
	printf("local b:%p\n",&b);
	printf("local c:%p\n",&c);
	printf("global g_first:%p\n",&g_first);
	printf("global g_second:%p\n",&g_second);
	printf("global g_third:%p\n",&g_third);
	PID1 = fork();
	FILE * fptr;
	
	if( PID1 == 0)//child process
	{
		 fptr = fopen("PID1.sh","w+");
		fprintf(fptr,"kill -9 %d\n",getpid());
		fclose(fptr);
		printf("child 1\n");
		PrintVariable();
	}
	if(PID1 > 0)//parent process
	{
		PID2 = fork();
		if(PID2 == 0)//child process
		{
			 fptr = fopen("PID2.sh","w+");
			fprintf(fptr,"kill -9 %d\n",getpid());
			fclose(fptr);
			printf("child 2\n");
			PrintVariable();
			while(1){}
		}
		else if(PID2 > 0)//parent process
		{
			PID3 = fork();
			if(PID3 == 0)
			{
				fptr = fopen("PID3.sh","w+");
		fprintf(fptr,"kill -9 %d\n",getpid());
		fclose(fptr);
				printf("child 3 \n");
				PrintVariable();
				while(1){}
			}
			else
			{
			fptr = fopen("parent.sh","w+");
		fprintf(fptr,"kill -9 %d\n",getpid());
		fclose(fptr);
			
			}
		}
		else
		{
			printf("error2\n");
			exit(0);
		}
	while(1)
	{
		
	}
	}
	
	
}

