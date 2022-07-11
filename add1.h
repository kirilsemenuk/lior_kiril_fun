#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<sys/mman.h>
#include<pthread.h>
#include<signal.h>
#include"string.h"
#include<errno.h>
#include<time.h>
#define BUFFSIZE 1024

typedef enum { false, true } bool;
struct task
{
    char name[25];
    time_t start_time;
    time_t end_time;
}task;
struct task_linkedlist
{
    struct task x;
    struct task * next;
}task_linkedlist;


#include <unistd.h>
#define SIZE 1024
#define PORT 12344
#define MODESIZE 2

int arg_to_int(char* word);
void check(int a,char * mess);
int get_mode_from_client(int sock);
int server_begin_function();//create loge file ,and data base folder
//int requast_to_add_new_task ;
int send_name_and_discription(int sock,char * name ,char *dis);
int get_name_and_discription(int sock,char * name ,char *dis);
int name2struct2file(char* name);