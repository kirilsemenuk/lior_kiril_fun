#include"04_add.h"





int send_name(int sock,char * name){
    char buff[BUFFSIZE];
    strcpy(buff,name);
    send(sock,buff,BUFFSIZE,0);
    fprintf(stdout,"h1\n");
    return 0;
}
int end_tasck(char * name,int client_socket)
{
    struct task_linkedlist *alltsk=file2ll();
    struct task_linkedlist *head=alltsk;
    int i=0;
    char  buff[254];
    while(alltsk!=NULL)
    {
        if(strcmp(name,alltsk->x.name)==0)
        {
            if(alltsk->x.end_time!=0)
            {
                printf("task all-ready ended\n");
                send(client_socket,"task all-ready ended",20,0);
                return 0;
            }
            alltsk->x.end_time=time(NULL);
            sprintf( buff,"task: %s\n\t number of sec:%ld\n",alltsk->x.name,alltsk->x.end_time-alltsk->x.start_time);
            send(client_socket,buff,254,0);
            break;
        }
        i++;
        alltsk=alltsk->next;
    }
    ll2file(head);
    return 0;
}

int printAll(int client_socket)
{
    struct task_linkedlist *alltsk=file2ll();
    struct tm *ptm,*ptm1;
    char  buff[254],buff1[254];
    int i=1;
    while(alltsk->x.start_time!=0)
    {   
        if (alltsk->x.end_time==0)
        {
            ptm = localtime(&alltsk->x.start_time);
            sprintf( buff, "%2d. %20s start at:%2d/%2d/%d %2d:%2d\n",i,alltsk->x.name,ptm->tm_mday,ptm->tm_mon+1,ptm->tm_year+1900,ptm->tm_hour,ptm->tm_min);
            
        }
        else if(alltsk->x.end_time!=0)
        {
            ptm = localtime(&alltsk->x.start_time);
            ptm1 = localtime(&alltsk->x.end_time);
            sprintf( buff, "%2d. %20s start at:%2d/%2d/%d %2d:%2d\n\t\t\t   end at:%2d/%2d/%d %2d:%2d\n",i,alltsk->x.name,ptm->tm_mday,ptm->tm_mon+1,ptm->tm_year+1900,ptm->tm_hour,ptm->tm_min,ptm1->tm_mday,ptm1->tm_mon+1,ptm1->tm_year+1900,ptm1->tm_hour,ptm1->tm_min);
        }
        send(client_socket,buff,1024,0);
        alltsk=alltsk->next;
        i++;
    }
    send(client_socket,"*__*",5,0);
    return 0;
}
int ll2file(struct task_linkedlist *head){

    FILE*f1;
    remove ("DataBase/task.bin");
    f1=fopen("DataBase/task.bin","wb");
    struct task_linkedlist* temp=head,*temp2;
    while (head!=NULL)
    {
        fwrite(&head->x,1,sizeof(struct task),f1);
        temp=head;
        head=head->next;
        if(temp!=NULL)
        {
            free(temp);
        }
    }
    fclose(f1);
    return 0;
}
int CprintAll(int client_socket)
{
    char printTask[BUFFSIZE];
    for(;;)
    {
        recv(client_socket,printTask,BUFFSIZE,0);
        if(strcmp(printTask,"*__*")==0){
            return 0;
        }
        printf("%s\n",printTask);
    }
}
int print1task(int client_socket,char * name)
{
    struct task_linkedlist *alltsk=file2ll();
    struct tm *ptm,*ptm1;
    char  buff[254],buff1[254];
    int i=1;
    while(alltsk->x.start_time!=0)
    {   
        //printf("%s==%s\n",name,alltsk->x.name);
        if(strcmp(name,alltsk->x.name)==0)
        {
            if (alltsk->x.end_time==0)
            {
                ptm = localtime(&alltsk->x.start_time);
                sprintf( buff, "%2d. %20s start at:%2d/%2d/%d %2d:%2d\n",i,alltsk->x.name,ptm->tm_mday,ptm->tm_mon+1,ptm->tm_year+1900,ptm->tm_hour,ptm->tm_min);
                
            }
            else if(alltsk->x.end_time!=0)
            {
                ptm = localtime(&alltsk->x.start_time);
                ptm1 = localtime(&alltsk->x.end_time);
                sprintf( buff, "%2d. %20s start at:%2d/%2d/%d %2d:%2d\n\t\t\t   end at:%2d/%2d/%d %2d:%2d\n",i,alltsk->x.name,ptm->tm_mday,ptm->tm_mon+1,ptm->tm_year+1900,ptm->tm_hour,ptm->tm_min,ptm1->tm_mday,ptm1->tm_mon+1,ptm1->tm_year+1900,ptm1->tm_hour,ptm1->tm_min);
            }
            send(client_socket,buff,1024,0);
            return 0;
        }
        alltsk=alltsk->next;
        i++;
    }
    return 0;
}
struct task_linkedlist* dell_task(int num,struct task_linkedlist* head)
{
    struct task_linkedlist *one=head;
    struct task_linkedlist *two=head->next;
    int i=1;
    while (two!=NULL)
    {
        if(i==num && num==1)
        {
            one=one->next;
            free(head);
            return one;
        }
        if(i==num && num!=1)
        {
            one->next=two->next;
            free(two);
            return head;
        }
        if(i>num)
        {
            printf("number task dont found\n");
            return NULL;//or head
        }
        if(i!=1)
        {
        one=one->next;
        two=two->next;
        }
        i++ ;  
    }
    return NULL;
}
int cleanFolder(int client_socket)
{
    struct task_linkedlist *alltsk=file2ll();
    struct task_linkedlist *head;
    char def1[50],def2[50];
    int i=1,j=0;
    head=alltsk;
    while(true)
    {
        if(alltsk->x.end_time!=0)
        {
            dell_task(i,head);
            sprintf(def1,"DataBase/%s",alltsk->x.name);
            sprintf(def2,"DataBase/finished/%s",alltsk->x.name);
            printf("%s->%s\n\n",def1,def2);
            rename(def1,def2);
            j++;
        }
        alltsk=alltsk->next;
        i++;
    }
    if(j!=0)
    {
        send(client_socket,"remove files sucsessfuly!",1024,0);
    }
    else
    {
        send(client_socket,"dont faund finished files!",1024,0);
    }
}