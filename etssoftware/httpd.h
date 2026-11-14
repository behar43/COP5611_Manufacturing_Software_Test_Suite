// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef HTTPD_H
#define HTTPD_H
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <mutex>
#include <atomic>

#define ISspace(x) isspace((int)(x))

#define SERVER_STRING "Server: vxhttpdcpp/0.0.1\n"
#define BT1553_MBUFCOUNT 32

namespace ETS
{   
    class vxhttpd
    {
        public:
            //Constructors
            vxhttpd(ushort port);
            void runMultiThread(void);
            void stop();
        protected:
            /**********************************************************************/
            /* Get a line from a socket, whether the line ends in a newline,
             * carriage return, or a CRLF combination.  Terminates the string read
             * with a null character.  If no newline indicator is found before the
             * end of the buffer, the string is terminated with a null.  If any of
             * the above three line terminators is read, the last character of the
             * string will be a linefeed and the string will be terminated with a
             * null character.
             * Parameters: the socket descriptor
             *             the buffer to save the data in
             *             the size of the buffer
             * Returns: the number of bytes stored (excluding null) */
            /**********************************************************************/
            int get_line(int sock, char *buf, int size);
            /**********************************************************************/
            /* Send a regular file to the client.  Use headers, and report
             * errors to client if they occur.
             * Parameters: a pointer to a file structure produced from the socket
             *              file descriptor
             *             the name of the file to serve */
            /**********************************************************************/
            virtual void serve_file(int client, const char *filename);
            /**********************************************************************/
            /* Send a regular hard coded file to the client.  Use headers, and report
             * errors to client if they occur.
             * Parameters: a pointer to a file structure produced from the socket
             *              file descriptor
             *             the name of the file to serve */
            /**********************************************************************/
            virtual void serve_hardcoded(int client);
            /**********************************************************************/
            /* Return the informational HTTP headers about a file. */
            /* Parameters: the socket to print the headers on
             *             the name of the file */
            /**********************************************************************/
            void headers(int client, std::string contentType, int contentLength);
            /**********************************************************************/
            /* Give a client a 404 not found status message. */
            /**********************************************************************/
            void not_found(int client);
        private:
            //Member functions
            void run(void);
            /**********************************************************************/
            /* A request has caused a call to accept() on the server port to
             * return.  Process the request appropriately.
             * Parameters: the socket connected to the client */
            /**********************************************************************/
            void accept_request(int client);
            /**********************************************************************/
            /* Inform the client that a request it has made has a problem.
             * Parameters: client socket */
            /**********************************************************************/
            void bad_request(int client);
            /**********************************************************************/
            /* Put the entire contents of a file out on a socket.  This function
             * is named after the UNIX "cat" command, because it might have been
             * easier just to do something like pipe, fork, and exec("cat").
             * Parameters: the client socket descriptor
             *             FILE pointer for the file to cat */
            /**********************************************************************/
            void cat(int client, FILE *resource);
            /**********************************************************************/
            /* Print out an error message with perror() (for system errors; based
             * on value of errno, which indicates system call errors) and exit the
             * program indicating an error. */
            /**********************************************************************/
            void error_die(const char *sc);
            /**********************************************************************/
            /* This function starts the process of listening for web connections
             * on a specified port.  If the port is 0, then dynamically allocate a
             * port and modify the original port variable to reflect the actual
             * port.
             * Parameters: pointer to variable containing the port to connect on
             * Returns: the socket */
            /**********************************************************************/
            int startup(u_short *port);
            /**********************************************************************/
            /* Inform the client that the requested web method has not been
             * implemented.
             * Parameter: the client socket */
            /**********************************************************************/
            void unimplemented(int client);
            //private Data members
            int server_sock;
            ushort port;
            std::atomic<bool> m_stop;   
    };
}
#endif

