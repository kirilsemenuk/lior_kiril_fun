#include"add1.h"
pthread_mutex_t mutex ;
volatile sig_atomic_t stop;
bool stop_con =false;

//signal func
void handle_sigtstp(int sig){
    fprintf(stdout,"signal \n" ); 
    stop_con=true;
    //stop=1;
}
//thread function
void * handle_connection(void * p_client_socket){
    int client_socket=*(int*)p_client_socket;
    int MODE=0;
    char buffer[BUFFSIZE];
    MODE=get_mode_from_client(client_socket);
    fprintf(stdout,"\t--->%d\n",MODE);
    switch (MODE)
    {
    case 1:
        /* display a task */
        fprintf(stdout,"/* display a task */");
        
        
        break;
    case 2:
        /* add a task */
         fprintf(stdout,"/* add a task */");
        char name[BUFFSIZE];
        char dis[BUFFSIZE];
        recv(client_socket,name,BUFFSIZE,0);///need to work with szie
        recv(client_socket,dis,BUFFSIZE,0);///need to work with szie

        
        printf(" %s \t %s \n ",name,dis);
        break;    
    case 3:
        /* add file to task */
         fprintf(stdout,"/* add file to task */");
        break;
    case 4:
        /* finsh an task */
         fprintf(stdout,"/* display a task */");
        break;
    case 5:
        /*  get an task */
         fprintf(stdout," /* finsh an task */");
        break;  
    case 6:
        /*   close the server */
         fprintf(stdout,"/ /*   close the server */");
        break;          
    default:
        break;
    }


    fprintf(stdout,"\nconnection end \n");

    close(client_socket);
    return NULL;
    
}

int main(){

    //signals

    signal(SIGUSR2,handle_sigtstp);
    //struct sigaction sa;
    //sa.sa_handler = &handle_sigtstp;
    // sigaction(SIGUSR2,&sa,NULL);
    

    //socket creation
    int server_socket, client_socket;
    struct sockaddr_in serv_addr ;
    check((server_socket=socket(AF_INET,SOCK_STREAM,0)),
    "failed to creatr socket\n");
    serv_addr.sin_family =AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port =htons(PORT);
    check((bind(server_socket,(struct sockaddr*)&serv_addr,sizeof(serv_addr))),
    "failed to bind\n");
    check(listen(server_socket,5),"failed to listen \n");


//base functoin create folder and task file
server_begin_function();
//the loop
    
    while (!stop_con)
    {
        //connecting
        fprintf(stdout,"whaiting to connect \n");
        check(client_socket=accept(server_socket,NULL,NULL)
        ,"failed to accept\n");
        if(stop==1)
            break;
        
        //trading
        void *p_client_socket=(void*)&client_socket;
        pthread_t t;
        pthread_create(&t,NULL,handle_connection,p_client_socket);
        //usleep(4000000);
    }
    //after loop
    printf("good bay ,server go to sleep \n");
    close(server_socket);
    
    return 0;
}