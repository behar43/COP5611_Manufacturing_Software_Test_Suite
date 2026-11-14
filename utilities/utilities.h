// Author: Ben Prishtina
// Purpose: Semester Project
// Class: COP 5611 Operating Systems Design Principles
#ifdef __cplusplus
extern "C"{
#endif
#ifndef UTILITIES_H
#define UTILITIES_H
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

#define QUEUE_NAME "/my_queue"
typedef struct
{
    int data[20];
    char lFileName[200];
    char ipAddress[1256];
}ret_param;

int atp_single_char_atoi(char s);
void ExtractFile(const char *s, ret_param *lf);
void ParseParametersFromString(const char *s, ret_param *par);
void reverse(char* str, int length);
void vxitoa(int n, char* out);
void vxcan_loop(int n, char* out, int count);
bool verify(char * string);
bool verifyHex(char * string);
char consume_char_ipc_Q(void);
#endif
#ifdef __cplusplus
}
#endif
