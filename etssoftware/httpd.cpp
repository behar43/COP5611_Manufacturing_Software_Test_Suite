// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include "httpd.h"


ETS::vxhttpd::vxhttpd(ushort port_param)
:m_stop()
{
    port = port_param;
    server_sock = -1;   
}
void ETS::vxhttpd::runMultiThread(void)
{
    std::thread t1(&ETS::vxhttpd::run, this);
    t1.detach();
}
void ETS::vxhttpd::run(void)
{
    int client_sock = -1;
    
    struct sockaddr_in client_name;
    struct timeval timeout;
    fd_set readfds;

    socklen_t client_name_len = sizeof(client_name);
    int val = 1;
    timeout.tv_sec = 5; // 5 seconds timeout
    timeout.tv_usec = 0;

    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));
    setsockopt(server_sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(int));
    setsockopt(client_sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int));

    server_sock = startup(&port);
    while (!m_stop)
    {
        FD_ZERO(&readfds);
        FD_SET(server_sock, &readfds);

        int num_ready = select(server_sock + 1, &readfds, NULL, NULL, &timeout);
        if(num_ready > 0)
        {
            client_sock = accept(server_sock,
                    (struct sockaddr *)&client_name,
                    &client_name_len);
            if (client_sock == -1)
                error_die("accept");
    
            //accept_request(client_sock);
            std::thread accpt(&ETS::vxhttpd::accept_request, this, client_sock);
            accpt.detach();
        }
    }
    std::cout << "close client socket" << std::endl;
    std::cout << "close server socket" << std::endl;
    close(client_sock);
    close(server_sock);
}
void ETS::vxhttpd::accept_request(int client)
{
    char buf[1024];
    int numchars;
    char method[255];
    char url[255];
    char path[512];
    size_t i, j;
    
    numchars = get_line(client, buf, sizeof(buf));
    //std::cout << "CPP buffer: " << buf << std::endl;
    i = 0; j = 0;
    while (!ISspace(buf[j]) && (i < sizeof(method) - 1))
    {
        method[i] = buf[j];
        i++; j++;
    }
    method[i] = '\0';
    
    if (strcasecmp(method, "GET") && strcasecmp(method, "POST"))
    {
        printf("ERROR: unimplemented\n");
        while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
            numchars = get_line(client, buf, sizeof(buf));
        printf("Discard Headers\n");
        printf("Method %s\n", method);
        unimplemented(client);
        printf("Executed unimplemented\n");

        close(client);
        printf("closed client\n");
        return;
    }
    
    i = 0;
    while (ISspace(buf[j]) && (j < sizeof(buf)))
        j++;
    while (!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf)))
    {
        url[i] = buf[j];
        i++; j++;
    }
    url[i] = '\0';
    
    sprintf(path, "%s", url);
    if (path[strlen(path) - 1] == '/')
        strcat(path, "index.html");
    printf("%s\n", path);
    
    std::cout << "Served: serve_hardcoded client" << std::endl;
    serve_file(client, path);
    
    close(client);
    std::cout << "ACCEPT_REQUEST: END OF TASK" << std::endl;
}
void ETS::vxhttpd::bad_request(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "Content-type: text/html\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "<P>Your browser sent a bad request, ");
    send(client, buf, sizeof(buf), 0);
    sprintf(buf, "such as a POST without a Content-Length.\r\n");
    send(client, buf, sizeof(buf), 0);
}
void ETS::vxhttpd::cat(int client, FILE *resource)
{
    char buf[1024];

    fgets(buf, sizeof(buf), resource);
    while (!feof(resource))
    {
        send(client, buf, strlen(buf), 0);
        fgets(buf, sizeof(buf), resource);
    }
}
void ETS::vxhttpd::error_die(const char *sc)
{
    perror(sc);
    exit(1);
}
int ETS::vxhttpd::get_line(int sock, char *buf, int size)
{
    int i = 0;
    char c = '\0';
    int n;

    while ((i < size - 1) && (c != '\n'))
    {
        n = recv(sock, &c, 1, 0);
        /* DEBUG printf("%02X\n", c); */
        if (n > 0)
        {
            if (c == '\r')
            {
                n = recv(sock, &c, 1, MSG_PEEK);
                /* DEBUG printf("%02X\n", c); */
                if ((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
            buf[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buf[i] = '\0';

    return(i);
}
void ETS::vxhttpd::headers(int client, std::string contentType, int contentLength)
{
    std::string reply;  
    std::string tmp;
    std::string contentLengthstr;

    tmp = std::to_string(contentLength); //itoa equivalent
        
    contentLengthstr = "Content-Length: ";
    contentLengthstr = contentLengthstr + tmp + "\n";
    
    reply = "HTTP/1.1 200 OK\n";
    reply = reply + "Date: Wed, 09 Oct 2013 14:33:04 ET\n";
    reply = reply + SERVER_STRING;
    reply = reply + "Last-Modified: Wed, 09 Oct 2013 14:33:04 ET\n";
    reply = reply + "ETag: \"56d-9989200-1132c580\"\n";
    reply = reply + contentType;
    reply = reply + contentLengthstr;
    reply = reply + "Accept-Ranges: bytes\n";
    reply = reply + "Connection: close\n";
    reply = reply + "Access-Control-Allow-Origin: *\n"; // Allow requests from different domain port
    reply = reply + "\n";

    send(client, reply.c_str(), strlen(reply.c_str()), 0);
}
void ETS::vxhttpd::not_found(int client)
{
    char buf[1024];

    sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, SERVER_STRING);
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "Content-Type: text/html\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "your request because the resource specified\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "is unavailable or nonexistent.\r\n");
    send(client, buf, strlen(buf), 0);
    sprintf(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}
void ETS::vxhttpd::serve_file(int client, const char *filename)
{
    int numchars = 1;
    char buf[2024];
    std::string content_type = "Content-Type: application/json; charset=ISO-8859-1\n";

    buf[0] = 'A'; buf[1] = '\0';
    while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
        numchars = get_line(client, buf, sizeof(buf));
    
    if(strcmp("/index.html", filename) == 0)
    {
        serve_hardcoded(client);
        std::cout << "served index.html" << std::endl;
    }
    else
    {
        if(strcmp("/hello", filename) == 0)
        {
            strcat(buf, "{\"vxhttpdcpp\":\"HELLO\"}");
            headers(client, content_type, strlen(buf));
            send(client, buf, strlen(buf), 0);
        }
        else
        {
            not_found(client);
            std::cout << "served NOT FOUND" << std::endl;
        }
    }
}
void ETS::vxhttpd::serve_hardcoded(int client)
{
    char buf[21024];
    std::string content_type = "Content-Type: text/html; charset=UTF-8\n";
    
    strcpy(buf, "<!DOCTYPE html PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n");
    strcat(buf, "<HTML>\r\n");
    strcat(buf, "<HEAD>\r\n");
    strcat(buf, "<TITLE>\r\n");
    strcat(buf, "vxhttpd IWSPES \r\n");
    strcat(buf, "</TITLE>\r\n");
    strcat(buf, "</HEAD>\r\n");
    strcat(buf, "<BODY>\r\n");
    strcat(buf, "<H1>vxhttpd IWSPES <br>(Integrated Web Server Prototype for Embedded Systems) <br>Running real time Operating Systems</H1>\r\n");
    strcat(buf, "<P>Default Hard Coded Page: please specify what you want to run ie. \"/sbcGpioGetAll\".<br> This Web Server is meant for "); 
    strcat(buf, "Computer to Computer communication such as Test Station to UUT, <br>where the communications happens to be HTTP<br>");
    strcat(buf, "replies are returned in JSON for easy standard parsing</P>\r\n");
    strcat(buf, "</BODY>\r\n");
    strcat(buf, "</HTML>\r\n");
    headers(client, content_type, strlen(buf));
    send(client, buf, strlen(buf), 0);
}
int ETS::vxhttpd::startup(u_short *port)
{
    int httpd = 0;
    struct sockaddr_in name;

    httpd = socket(PF_INET, SOCK_STREAM, 0);
    if (httpd == -1)
        error_die("socket");
    memset(&name, 0, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(*port);
    name.sin_addr.s_addr = htonl(INADDR_ANY); //ipv4 address
    if (bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0) //bind to the port because I am the server
        error_die("bind");
    if (*port == 0)  /* if dynamically allocating a port, this should never execute */
    {
        socklen_t namelen = sizeof(name);
        if (getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
            error_die("getsockname");
        *port = ntohs(name.sin_port);
    }
    if (listen(httpd, 115) < 0)
        error_die("listen");
    return(httpd);
}
void ETS::vxhttpd::unimplemented(int client)
{
    char buf[1024];

    
    strcpy(buf, "HTTP/1.0 501 Method Not Implemented\r\n"); 
    strcat(buf, SERVER_STRING); 
    strcat(buf, "Content-Type: text/html\r\n"); 
    strcat(buf, "\r\n");    
    strcat(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");   
    strcat(buf, "</TITLE></HEAD>\r\n"); 
    strcat(buf, "<BODY><P>HTTP request method not supported.\r\n"); 
    strcat(buf, "</BODY></HTML>\r\n");
    send(client, buf, strlen(buf), 0);
}
void ETS::vxhttpd::stop()
{
    m_stop = true;
}

