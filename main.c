#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void sig_handler(int signum)
{
	int i = 5;
	int j = 0;
	switch (signum)
	{
	// Child stopped or terminated
	case SIGCHLD:
		printf("I am in Child stopped or terminated\n");
		fflush(stdout);
		raise(SIGUSR1); // this will raise the next one
		break;

	// User-defined signal 1
	case SIGUSR1:
		printf("I am in User-defined signal 1\n");
		fflush(stdout);
		j = i / j; // this will rais the next one
		break;

	// Floating-point exception
	case SIGFPE:
		printf("I am in Floating-point exception\n");
		fflush(stdout);
		alarm(1); // this will rais the next one
		sleep(1);
		break;

	// Timer signal from alarm(2)
	case SIGALRM:
		printf("I am in Timer signal from alarm(2)\n");
		fflush(stdout);
		asm("ud2"); // this will raise the next one
		break;

	// Illegal Instruction
	case SIGILL:
		printf("i am in Illegal Instruction\n");
		fflush(stdout);
		int *p = NULL; // this will raise the next one
		*p = 45;
		break;

	// Invalid memory reference
	case SIGSEGV:
		printf("i am in Invalid memory reference\n");
		fflush(stdout);
		kill(getpid(), SIGUSR2); // this will raise the next one
		break;

	//  User-defined signal 2
	case SIGUSR2:
		printf("I am in User-defined signal 2\n");
		exit(1);
		break;
	}
}

int main()
{
	// signal represents the catch of the signal and where to send it
	int status;
	signal(SIGCHLD, sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGALRM, sig_handler);
	signal(SIGFPE, sig_handler);
	signal(SIGILL, sig_handler);
	signal(SIGUSR2, sig_handler);
	signal(SIGSEGV, sig_handler);

	if (!(fork()))
	{
		exit(1);
	}
	wait(&status);
}