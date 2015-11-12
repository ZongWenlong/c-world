#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/msg.h>  
#include <errno.h>  
#include <pthread.h>
   
struct msg_st  
{  
    long int msg_type;  
    char* msg[1];
};  
void rethread(void)
{
    int running = 1;  
    int msgid = -1;  
    struct msg_st data;  
    long int msgtype = 0; //注意1  
  
    //建立消息队列  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }  
    //从队列中获取消息，直到遇到end消息为止  
    while(running)  
    {  
        if(msgrcv(msgid, (void*)&data, sizeof(char*), msgtype, 0) == -1)  
        {  
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);  
            exit(EXIT_FAILURE);  
        }  
        printf("You wrote: %s\n",data.msg[0]);  
        sleep(1);
        
    }  
    //删除消息队列  
    if(msgctl(msgid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }  
    exit(EXIT_SUCCESS);  
}

void sethread(void)
{
    int running = 1;  
    struct msg_st data;   
    int msgid = -1;  
    char * msg = "wenloz's message";

  
    //建立消息队列  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }  
    
    data.msg_type = 1;    //注意2  
    data.msg[0] = (char*)malloc(sizeof(char) * strlen(msg));
    strcpy(data.msg[0],msg);
    while(1){
        //向队列发送数据  
        if(msgsnd(msgid, (void*)&data, sizeof(char*), 0) == -1)  
        {  
            fprintf(stderr, "msgsnd failed\n");  
            exit(EXIT_FAILURE);  
        }  
        printf("send %s\n", data.msg[0]);  
        sleep(1);
    }
        
 


    sleep(3);   
    exit(EXIT_SUCCESS);  
}


void sethread2(void)
{
    int running = 1;  
    struct msg_st data;   
    int msgid = -1;  
    char * msg = "wenloz's message22222222222";

  
    //建立消息队列  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }  
    
    data.msg_type = 1;    //注意2  
    data.msg[0] = (char*)malloc(sizeof(char) * strlen(msg));
    strcpy(data.msg[0],msg);
    while(1){
        //向队列发送数据  
        if(msgsnd(msgid, (void*)&data, sizeof(char*), 0) == -1)  
        {  
            fprintf(stderr, "msgsnd failed\n");  
            exit(EXIT_FAILURE);  
        }  
        printf("send %s\n", data.msg[0]);  
        sleep(1);
    }
        
 


    sleep(3);   
    exit(EXIT_SUCCESS);  
}
  
int main()  
{  
    pthread_t id;
    pthread_t id2,id3;
    int i,ret,ret2;
    ret=pthread_create(&id,NULL,(void *) rethread,NULL);
    ret2=pthread_create(&id2,NULL,(void *) sethread,NULL);
    ret2=pthread_create(&id3,NULL,(void *) sethread2,NULL);
    if(ret!=0 && ret2 != 0){
        printf ("Create pthread error!\n");
        exit (1);
    }
   
    pthread_join(id,NULL);
    pthread_join(id2,NULL);
    pthread_join(id3,NULL);
    return (0);
}  