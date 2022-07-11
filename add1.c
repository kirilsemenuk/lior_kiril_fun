#include"add1.h"


void check(int a,char * mess){
    if(a==-1){
    fprintf(stdout,"%s\n",mess);
    exit(0);
    }

}
int get_mode_from_client(int sock){
    char M_buff[MODESIZE]={0};
    int mode=0;
    recv(sock,M_buff,MODESIZE,0);
    mode=atoi(M_buff);
    return mode;
}
int arg_to_int(char* word){

    if(strcmp(word,"-d")==0){
        return 1;
    }
    else if (strcmp(word,"-n")==0)
    {
       return 2;
    }
    else if (strcmp(word,"-u")==0)
    {
       return 3;
    }else if (strcmp(word,"-x")==0)
    {
       return 4;
    }
    else if (strcmp(word,"-g")==0)
    {
       return 5;
    }
    else
         return -1;
}
int server_begin_function(){
    if(mkdir("DataBase",0777)==-1)
    perror("Error");
    FILE* f1=fopen("DataBase/task.bin","r");
    int x=0;
    if(f1==NULL){
        f1=fopen("DataBase/task.bin","w");
    }
    fclose(f1);
    return 0;

}
int send_name_and_discription(int sock,char * name ,char *dis){
    char buff[BUFFSIZE];
    strcpy(buff,name);
    send(sock,buff,BUFFSIZE,0);
    fprintf(stdout,"h1\n");
    strcpy(buff,dis);
    send(sock,buff,BUFFSIZE,0);
    fprintf(stdout,"h2\n");
    return 0;
}


int get_name_and_discription(int sock,char* name ,char * dis){
    char buff[BUFFSIZE];
    recv(sock,buff,BUFFSIZE,0);////need to work with the size
    strcpy(name,buff);
    recv(sock,buff,BUFFSIZE,0);
    strcpy(dis,buff);


    return 0;
}