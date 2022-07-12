#include"add1.h"
bool stop_con =false;
int main(int argc ,char *argv[]){

    int MOOD;
   // fprintf(stdout,"hi");
   
    char buff[BUFFSIZE];
    char mode_buff[MODESIZE];
    int sock, Read_Size;
    struct sockaddr_in serv_addr={0} ;
   
   //conction
    check((sock=socket(AF_INET,SOCK_STREAM,0)),"Faild to create an socket\n");
    serv_addr.sin_family =AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port =htons(PORT);
    check(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)),
    "failed to connect\n");
   
   
//-------------------------------------------------------------------------------------------------------------------------------------
if(argc !=1)
     MOOD=arg_to_int(argv[1]);
else   
    MOOD=666;    
switch (MOOD)
{
case 1:
    /* display a task */
    fprintf(stdout,"/* display a task */");
    send(sock,"01",MODESIZE,0);
    break;

case 2:
    /* add a task */
    //fprintf(stdout,"/* add a task */");
    send(sock,"02",MODESIZE,0);
    send_name_and_discription(sock,argv[2],argv[3]);
    break;

case 3:
    /* add file to task */
    fprintf(stdout,"/* add file to task */");
    send(sock,"03",MODESIZE,0);
    break;

case 4:
    /* finsh an task */
    fprintf(stdout,"/* finsh an task */");
    send(sock,"04",MODESIZE,0);
    //sent task name
    break;

case 5:

    /* get an task */
    fprintf(stdout,"/* get a task */");
    send(sock,"05",MODESIZE,0);
    break;
 case 6:
    /* close the server */
    fprintf(stdout,"/* close server */");
    send(sock,"06",MODESIZE,0);
    break;   

default:
    /*display alll*/
    fprintf(stdout,"/* display all task's */");
    send(sock,"00",MODESIZE,0);
    break;
}










   /*if(argc==1){//arg c=1
        sprintf(buff,"Display all");
        send(sock,buff,sizeof(buff),0);
        while(!stop_con){
            Read_Size=recv(sock,buff,sizeof(buff),0);
            if(Read_Size == 0){

                stop_con=true;
                fprintf(stdout,"end message 1 \n");
               // break;
            }
            
            fprintf(stdout,"%s",buff);
        }
        fprintf(stdout,"WE finsh here\n");
   }
   */




 

    
    close(sock);

    

}