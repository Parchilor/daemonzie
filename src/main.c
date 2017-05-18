#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define err_quit(fmt, ...)	do{ \
					fprintf (stdout, ""fmt"\n", ##__VA_ARGS__); \
					exit (1); \
				}while(0)

#define err_print(fmt, ...)	do{ \
					fprintf (stdout, ""fmt"\n", ##__VA_ARGS__); \
				}while(0)

#define LOG_PATH	"/tmp/test.log"//	"/home/goockr/codes/daemonize/test.log"
#define DOC_PERMISSION	"a"

void
init_daemon(const char *cmd)
{
	int			i, fd[3];
	pid_t			pid;
	struct rlimit		rl;
	struct sigaction	sa;
	/*
	 * Clear file creation mask.
	 */
	umask(0);

	/*
	 * Get maximum number of file descriptors.
	 */
	if (getrlimit (RLIMIT_NOFILE, &rl) < 0) {
		err_quit ("%s: Can't get file limit", cmd);
	}

	/*
	 * Become asession leader to lose controlling TTY.
	 */
	if ((pid = fork ()) < 0) {
		err_quit ();
	} else if (pid !=0) {
		exit(0);
	}
	setsid ();

	/*
	 * Ensure futrure opens won't allocate controlling TTYs.
	 */
	sa.sa_handler = SIG_IGN;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction (SIGHUP, &sa, NULL) < 0) {
		err_quit ("%s: Can't ignore SIGHUP", cmd);
	}
	if ((pid = fork ()) < 0) {
		err_quit ("%s: Can't fork", cmd);
	} else if (pid != 0) {
		exit(0);
	}

	/*
	 * Change the current working directory to the root so
	 * we won't prevent file systems from being unmounted.
	 */
	if (chdir ("/") < 0) {
		err_quit ("%s: Can't change directory to'/'", cmd);
	}

	/*
	 * Close all open file descriptors.
	 */
	if (rl.rlim_max == RLIM_INFINITY) {
		rl.rlim_max = 1024;
	}
	for (i = 0; i < rl.rlim_max; i++) {
		close (i);
	}

	/*
	 * Attach file descriptors 0, 1, and 2 to /dev/null.
	 */
	fd[0] = open ("/dev/null", O_RDWR);
	fd[1] = dup (0);
	fd[2] = dup (0);

	/*
	 * Initialize the log file.
	 */
	openlog (cmd, LOG_CONS, LOG_DAEMON);
	if (fd[0] != 0 || fd[1] != 1|| fd[2] != 2) {
		syslog (LOG_ERR, "Unexpected file descriptors %d %d %d",
				fd[0],
				fd[1],
				fd[2]
			   );
		exit(1);
	}
}

int
main (int argc, char *argv[])
{
	FILE *fd;
	time_t rawtime;
	struct tm * timeinfo;

	init_daemon("daemonize");

	//守护进程每隔10s打日志
	while(1){
		if((fd = fopen(LOG_PATH, DOC_PERMISSION)) == NULL){
			printf("Opened LOG file fail!\n");
			perror("fopen");
			exit(1);
		}
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		printf("\007The current date/time is: %s", asctime(timeinfo));
		fprintf(fd,"\007The Current Date/time is: %s", asctime(timeinfo));
		fclose(fd) ;
		sleep(10) ;
	}
	return 0;
}
