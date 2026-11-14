// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>      // std::out_of_range
#include "lightwebserver.h"
#include "url.h"
#include "utilities.h"
#include "defines.h"
#include "Queue.h"
#include "ATP_LOG_REC.h"

extern BLIST::Queue<ATP_LOG_REC> theQs[ATP_TEST_MAX];

LWS::lightwebserver::lightwebserver(ushort port_param)
    :vxhttpd(port_param)
{

}
void LWS::lightwebserver::serve_hardcoded(int client)
{
    char buf[21024];
    std::string atpHelpStr = "\nATP commands defined:<br>\n"
        "   http://192.168.1.105:8080/cextractfile?name=something:12:34:35:56:65:70:88:99:21:23:36<br>\n"
        "   http://192.168.1.105:8080/cparseparam?name=something:12:34:35:56:65:70:88:99:21:23:36<br>\n"
        "   http://192.168.1.105:8080/sbcGpioStateSet?bankNo=1&pinNo=1&state=1<br>\n"
        "   http://192.168.1.105:8080/atp?tidMask=7&stopOnErrMask=0<br>\n"
        "   http://192.168.1.105:8080/atpTest?tid=1&stopOnErr=0<br>\n"
        "   http://192.168.1.105:8080/atpTestStop?tid=1<br>\n"
        "   http://192.168.1.105:8080/atpLogGet?tid=1<br>\n"
        "   http://192.168.1.105:8080/atpStop<br>\n";
    std::string content_type = "Content-Type: text/html; charset=UTF-8\n";
    memset(buf, 0, sizeof(buf));

    strcpy(buf, "<!DOCTYPE html PUBLIC \"-//IETF//DTD HTML 2.0//EN\">\n");
    strcat(buf, "<HTML>\r\n");
    strcat(buf, "<HEAD>\r\n");
    strcat(buf, "<TITLE>\r\n");
    strcat(buf, "vxhttpd IWSPES \r\n");
    strcat(buf, "</TITLE>\r\n");
    strcat(buf, "</HEAD>\r\n");
    strcat(buf, "<BODY>\r\n");
    strcat(buf, "<H1>vxhttpd ETS for COP5611 semester project</H1>\r\n");
    strcat(buf, "<P>Default Hard Coded Page: please specify what you want to run ie. This Web Server is meant for "); 
    strcat(buf, "Computer to Computer communication such as Test Station to UUT, <br>where the communications happens to be HTTP<br>");
    strcat(buf, "replies are returned in JSON for easy standard parsing</P>\r\n");
    strcat(buf, "<P>ETS HTTPD commands:<br>\r\n");
    strcat(buf, atpHelpStr.c_str());
    strcat(buf, "</P>\r\n");
    strcat(buf, "</BODY>\r\n");
    strcat(buf, "</HTML>\r\n");

    headers(client, content_type, strlen(buf));
    send(client, buf, strlen(buf), 0);
}
void LWS::lightwebserver::serve_file(int client, const char *filename)
{   
    int numchars = 1;
    char buf[2024];
    std::vector<std::string> strings;
    std::vector<std::string> stringsArr;
    std::vector<std::string> stringsArr2;
    std::string content_type = "Content-Type: application/json; charset=ISO-8859-1\n";

    memset(buf, 0, sizeof(buf));

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
        std::string command(filename);
        ETS::url u(command);
        std::cout << "Protocol: " << u.protocol() << std::endl;
        std::cout << "Host: "  << u.host() << std::endl; 
        std::cout << "Path: "  << u.path() << std::endl; 
        std::cout << "Query: " << u.query() << std::endl;
        std::cout << "QueryArr: " << u.queryArr() << std::endl;
        std::cout << "QueryArr2: " << u.queryArr2() << std::endl;
        if("hello" == u.path())
        {   
            std::string buffer("{\"vxhttpdcpp\":\"");

            strings = u.extractparams(u.query());
            try
            {   
                buffer += strings.at(1);
            }
            catch (const std::out_of_range& oor)
            {
                std::cerr << "Out of Range error: " << oor.what() << std::endl;
                buffer = buffer + "HELLO";
            }
            buffer = buffer + "\"}";            

            headers(client, content_type, strlen(buffer.c_str()));
            send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
        else if("cextractfile" == u.path())
        {   
            ret_param retvalstruct;
            std::string buffer("{\"cextractfile\":\"");
            strings = u.extractparams(u.query());
            try
            {
                ExtractFile(strings[1].c_str(), &retvalstruct);
                buffer = buffer + retvalstruct.lFileName;
            }
            catch (const std::out_of_range& oor)
            {
                std::cerr << "Out of Range error: " << oor.what() << std::endl;
                buffer = buffer + "OUT_OF_RANGE_ERROR";
            }
            buffer = buffer + "\"}";

            headers(client, content_type, strlen(buffer.c_str()));
            send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
        else if("cparseparam" == u.path())
        {
            ret_param retvalstruct;
            std::string tmp;
            std::string buffer("{\"cparseparam\": [");
            strings = u.extractparams(u.query());
            try
            {
                ParseParametersFromString(strings[1].c_str(), &retvalstruct);
                for(int i = 0; i < 20; i++)
                {
                    tmp = std::to_string(retvalstruct.data[i]);
                    buffer = buffer + tmp;
                    if(i < (20 - 1))
                        buffer = buffer + ",";
                }
                buffer = buffer + "]";
                buffer = buffer + "}";
            }
            catch (const std::out_of_range& oor)
            {
                std::cerr << "Out of Range error: " << oor.what() << std::endl;
                buffer = buffer + "]}";
            }
            headers(client, content_type, strlen(buffer.c_str()));
            send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
        else if("sbcGpioStateSet" == u.path())
        {
            std::string buffer("{\"sbcGpioStateSet\":\"");
            strings = u.extractparams(u.query());
            stringsArr = u.extractparams(u.queryArr());
            stringsArr2 = u.extractparams(u.queryArr2());

            int bankNo, pinNo;
            bool state;
            bool retval = false;
            //bool sbcGpioStateSet(int bankNo, int pinNo, bool state)
            try
            {
                bankNo = atoi(strings.at(1).c_str());
                pinNo = atoi(stringsArr.at(1).c_str());
                state = u.to_bool(stringsArr2.at(1));
                retval = sbcGpioStateSet(bankNo, pinNo, state);

                if(retval == true)
                {
                    buffer = buffer + "PASS";
                }
                else
                {
                    buffer = buffer + "FAIL";
                }
            }   
            catch (const std::out_of_range& oor)
            {
                std::cerr << "Out of Range error: " << oor.what() << std::endl;
                buffer = buffer + "OUT OF RANGE";
            }
            buffer = buffer + "\"}";

            headers(client, content_type, strlen(buffer.c_str()));
            send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
        else if("atp" == u.path())
        {
            unsigned int tid_mask = 0;
            unsigned int stop_on_error_mask = 0;

            std::string buffer("{\"atp\":\"");
            strings = u.extractparams(u.query());
            stringsArr = u.extractparams(u.queryArr());
            try
            {
                tid_mask = atoi(strings.at(1).c_str());
                stop_on_error_mask = atoi(stringsArr.at(1).c_str());
                etsobj.atp(tid_mask, stop_on_error_mask);
            }
            catch (const std::out_of_range& oor)
            {
                std::cerr << "Out of Range error: " << oor.what() << std::endl;
                buffer = buffer + "OUT OF RANGE";
            }
            buffer = buffer + "DONE";
            buffer = buffer + "\"}";

            headers(client, content_type, strlen(buffer.c_str()));
            send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
        else if("atpTest" == u.path())
        {
            unsigned int tid = 0;
            bool stop_on_error = false;
            int retval = 0;

            std::string buffer("{\"atpTest\":\"");
            strings = u.extractparams(u.query());
            stringsArr = u.extractparams(u.queryArr());
            try
            {
                tid = atoi(strings.at(1).c_str());
                stop_on_error = u.to_bool(stringsArr.at(1));
                retval = etsobj.atpTest(tid, stop_on_error);
            }
            catch (const std::out_of_range& oor)
            {
                std::cerr << "Out of Range error: " << oor.what() << std::endl;
                buffer = buffer + "OUT OF RANGE";
            }
            buffer = buffer + std::to_string(retval);
            buffer = buffer + "\"}";

            headers(client, content_type, strlen(buffer.c_str()));
            send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
        else if("atpTestStop" == u.path())
        {
            unsigned int tid = 0;
            bool retval = 0;

            std::string buffer("{\"atpTestStop\":\"");
            strings = u.extractparams(u.query());
            try
            {
                tid = atoi(strings.at(1).c_str());
                retval = etsobj.atpTestStop(tid);
            }
            catch (const std::out_of_range& oor)
            {
                std::cerr << "Out of Range error: " << oor.what() << std::endl;
                buffer = buffer + "OUT OF RANGE";
            }
            buffer = buffer + std::to_string(retval);
            buffer = buffer + "\"}";

            headers(client, content_type, strlen(buffer.c_str()));
            send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
        else if("atpStop" == u.path())
        {
            std::string buffer("{\"atpStop\":\"");
            etsobj.atpStop();

            buffer = buffer + "DONE";
            buffer = buffer + "\"}";

            headers(client, content_type, strlen(buffer.c_str()));
            send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
        else if("atpLogGet" == u.path())
        {
            unsigned int tid = 0;
            ATP_LOG_REC testresult;

            std::string buffer("{\"atpLogArray");
            strings = u.extractparams(u.query());
            try
            {
                tid = atoi(strings.at(1).c_str());
            }
            catch (const std::out_of_range& oor)
            {
                std::cerr << "Out of Range error: " << oor.what() << std::endl;
                buffer = buffer + "OUT OF RANGE";
            }
            theQs[tid-1].dequeue(testresult);
            buffer = buffer + "\": [";
            //message id element
            buffer = buffer + "{\"";
            buffer = buffer + "MessageID\":\"";
            buffer = buffer + std::to_string(testresult.mid);
            buffer = buffer + "\"}";
            buffer = buffer + ",";
            //test id element
            buffer = buffer + "{\"";
            buffer = buffer + "TestID\":\"";
            buffer = buffer + std::to_string(testresult.tid);
            buffer = buffer + "\"}";
            buffer = buffer + ",";
            //error code element
            buffer = buffer + "{\"";
            buffer = buffer + "ErrorCode\":\"";
            buffer = buffer + std::to_string(testresult.err);
            buffer = buffer + "\"}";
            buffer = buffer + ",";
            //dev code element
            buffer = buffer + "{\"";
            buffer = buffer + "DeviceID\":\"";
            buffer = buffer + std::to_string(testresult.dev);
            buffer = buffer + "\"}";
            buffer = buffer + ",";
            //count code element
            buffer = buffer + "{\"";
            buffer = buffer + "Counter\":\"";
            buffer = buffer + std::to_string(testresult.cnt);
            buffer = buffer + "\"}";
            buffer = buffer + ",";
            //DATA element
            buffer = buffer + "{\"";
            buffer = buffer + "Data\":\"";
            buffer = buffer + std::to_string(testresult.dat);
            buffer = buffer + "\"}";
            //close array
            buffer = buffer + "]";
            buffer = buffer + "}";

            headers(client, content_type, strlen(buffer.c_str()));
            send(client, buffer.c_str(), strlen(buffer.c_str()), 0);
        }
        else
        {
            not_found(client);
            std::cout << "served NOT FOUND" << std::endl;
        }
    }
}

