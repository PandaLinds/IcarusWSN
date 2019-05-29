#include <ctype.h>      /* For tolower()                 */
#include <netdb.h>      /* For gethostbyname()           */
#include <netinet/in.h> /* For server_sockaddr           */
#include <signal.h>     /* For sigHandler()              */
#include <stdio.h>      /* For printf() and scanf()      */
#include <stdlib.h>     /* For NULL                      */
#include <string.h>     /* For strlen()                  */
#include <strings.h>    /* For bzero()                   */
#include <syslog.h>     /* For syslog()                  */
#include <sys/socket.h> /* For socket()                  */
#include <sys/types.h>  /* For socket()                  */
#include <unistd.h>     /* For gethostname() and sleep() */

#define DEFAULT_PORT 54321

//char* testStr = "Connection to server successful.\n";
char* testStr = "Wazzup!!!\n";

extern int errno;
extern void sigHandler();
extern void brokenPipeHandler();
extern void serveClients();
void viewSysLogs();


static int server_sock, client_sock;
static int fromlen, i, j, numSets;
static char c;
static FILE *fp;
static struct sockaddr_in server_sockaddr, client_sockaddr;
