// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifndef LWS_H
#define LWS_H
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <mutex>
#include <atomic>
#include "httpd.h"
#include "etss.h"

namespace LWS
{
    class lightwebserver : public ETS::vxhttpd
    {
        public:
            lightwebserver(ushort port);
            /**********************************************************************/
            /* Send a regular hard coded file to the client.  Use headers, and report
             * errors to client if they occur.
             * Parameters: a pointer to a file structure produced from the socket
             *              file descriptor
             *             the name of the file to serve */
            /**********************************************************************/
            void serve_hardcoded(int client);
            /**********************************************************************/
            /* Send a regular file to the client.  Use headers, and report
            * errors to client if they occur.
            * Parameters: a pointer to a file structure produced from the socket
            *              file descriptor
            *             the name of the file to serve */
            /**********************************************************************/
            void serve_file(int client, const char *filename);
            //Data members
            ETSS::etss etsobj;
    };
}
#endif

