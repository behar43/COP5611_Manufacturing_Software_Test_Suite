// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int atp_single_char_atoi(char s)
{
    int result = 0;

    result = 10*result + s++ - '0';

    return result;
}
/* ParseParametersFromString - Function that takes a string, and parses 
 * the necessary parameters seperated by ":" 
 * @args: 
 *      const char *s, the input string to be parsed
 *      ret_param *par parameters are stored in the structure that is passed in by reference
 * @return: void
 */
void ParseParametersFromString(const char *s, ret_param *par)
{
    char parameters[200];
    char *pch;
    int count = 0;
    bool verified = false;
    //ret_param parameters_numeric;
    
    strcpy(parameters, s);
    printf ("Splitting string \"%s\" into tokens:\n",s);
    pch = strtok (parameters, ":");
    while(pch != NULL)
    {
        printf ("%s\n",pch);
        //pch = strtok(NULL, ":");
        if(count > 0)
        {
            verified = verify(pch);
            if(verified)
            {
                par->data[count-1] = atoi(pch);
                printf("par->data[%d] = %d\n", count-1, par->data[count-1]);
            }
            else
            {
                if(verifyHex(pch))
                {
                    par->data[count-1] = strtol(pch, NULL, 16);
                    printf("par->data[%d] = %x\n", count-1, par->data[count-1]);
                }
                else
                {
                    strcpy(par->ipAddress, pch);
                }
            }
            
        }
        pch = strtok(NULL, ":");
        count++;
    }
}

/* ExtractFile - Function that takes a string, and parses the command represented
 * as a "file" or the command to do a praticular operation.  This function dicards
 * the parameters. 
 * @args: 
 *      const char *s, the input string to be parsed
 *      ret_param *lf the file without parameters is stored in the structure that is passed in by reference
 * @return: void
 */
void ExtractFile(const char *s, ret_param *lf)
{
    const char *p;
    int count = 0;
    
    for (p = s; *p; ++p)
    {
        if(*p != ':')
        {
            printf("if != :\n");
            lf->lFileName[count] = *p;
        }
        else
        {
            printf("else it is : ret_buffer: %s\n", lf->lFileName);
            lf->lFileName[count] = '\0';
            return;
        }
        count++;
    }
    return;
}
/* Custom reverse() function for which the length of the string is
 * known in advance (avoids a call to strlen() and including
 * string.h).
 *
 * @args: a null-terminated string
 * @return: nothing
 * @result: the characters in str are reversed
 */
void reverse(char* str, int length)
{
    int i = 0, j = length-1;
    char tmp;
    while (i < j) 
    {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++; j--;
    }
}

/* Returns the string representation of integer n. Assumes 32-bit
 * int, and 8-bit bytes (i.e. sizeof(char) = 1, sizeof(int) = 4).
 * Assumes char *out is big enough to hold the string
 * representation of n.
 *
 * @args: int n to convert, char* out for the result
 * @result the string representation of n is stored in out
 */
void vxitoa(int n, char* out)
{
    // if negative, need 1 char for the sign
    int sign = n < 0? 1: 0;
    int i = 0;
    if (n == 0) 
    {
        out[i++] = '0';
    } 
    else if (n < 0) 
    {
        out[i++] = '-';
        n = -n;
    }
    while (n > 0) 
    {
        out[i++] = '0' + n % 10;
        n /= 10;
    }
    out[i] = '\0';
    reverse(out + sign, i - sign);
}
/* can bus loop
 * @args: int n to convert, char* out for the result
 * @result the string representation of n is stored in out
 */
void vxcan_loop(int n, char* out, int count)
{
    char tempchar[20] = "46";
    vxitoa(n, out);
    if (count == 25)
    {
        strcpy(out, tempchar);
    }
    else
    {
        vxitoa(n, out);
    }
}
/* returns TRUE on success if it is int, FALSE on failure. */
bool verify(char * string)
{
    int x = 0;
    int len = strlen(string);
    
    while(x < len) 
    {
        if(!isdigit(*(string+x)))
            return true;    
        ++x;
    }
    return true;
}
bool verifyHex(char * string)
{
    int x = 0;
    int len = strlen(string);
    
    while(x < len)
    {
        if(!isxdigit(*(string+x)))
            return true;
        
        ++x;
    }
    return true;
}

char consume_char_ipc_Q(void)
{
    mqd_t mq;
    char ch;

    mq = mq_open(QUEUE_NAME, O_RDONLY | O_NONBLOCK);
    if (mq == (mqd_t)-1)
    {
        return 'z';
    }
    if (mq_receive(mq, &ch, sizeof(char), NULL) == -1)
    {
        ch = 'y';
    }
    else
    {
        printf("IPC char QUEUE Received: %c\n", ch);
    }
    mq_close(mq);
    return ch;
}

