#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<string.h>
#include<sys/wait.h>

void cd(char *cwd);
void parse(char *line);
void parse(char *line);

int num_args;
char *my_args[16];



int main(int argc, char **argv, char **envp){

  pid_t pid;
  char *line, cwd[1024];
  int exit_flag;

  pid=getpid();//parent id
  exit_flag=0;//set an exit flag

  //Open the shell with a pretty picture
  printf("\n\n\tWelcome to my snail shell!!\n\n");
  printf("\t@             _________\n");
  printf("\t \\____       /         \\ \n");
  printf("\t /    \\     /   ____    \\ \n");  
  printf("\t \\_    \\   /   /    \\    \\ \n");
  printf("\t   \\    \\ (    \\__/  )    ) \n");
  printf("\t    \\    \\_\\ \\______/    / \n");
  printf("\t     \\      \\           /__ \n");
  printf("\t      \\______\\_________/____'-_ \n");
  printf("\n");


  printf("To exit my snail shell type exit\n\n");

  while(exit_flag==0){
    //get and print the current working directory
    if(getcwd(cwd, sizeof(cwd))!=NULL)
      printf("[%s] ", cwd);
    else
      printf("ah shit\n");

    num_args=0;
    line = readline("snail: ");//prompt
    
    parse(line);
   
    //check for cd command
    if(my_args[0]!=NULL && strcmp(my_args[0],"cd")==0){
      cd(cwd);
    }
    else if(num_args>0){

      pid_t child_pid=fork();
      
      if(child_pid==0){//ensure you're working on forked process
	if(strcmp(my_args[num_args-1],"&")==0){//determine whether process is bg proces 
	  my_args[num_args-1]=NULL;
	  num_args=num_args-1;
	  //execute the command if it's not exit
	  if(execvp(my_args[0], my_args)<0 && strcmp(my_args[0], "exit")!=0){
	    printf("%s: not found\n", my_args[0]);//error message
	    exit(1);
	  }
	}
	//for foreground process
	else{
	  //ensure that we're not being asked to exit the snail shell
	  if(strcmp(my_args[0], "exit")!=0){
	    //ececute the command
	    execvp(my_args[0], my_args);
	    //error message
	    if(execvp(my_args[0], my_args)<0)
	      printf("%s: not found\n", my_args[0]);
	    exit(1);
	  }
	}
      }
      //only wait on foreground processes
      if(strcmp(my_args[num_args-1],"&")!=0)//check for & again
	wait(NULL);
    }
      
    //to exit the snail shell type exit
    if(my_args[0]!=NULL && strcmp(my_args[0], "exit")==0)
      exit_flag=1;
  }
 
  free(line);
  return 0;
}


void parse(char *line){

  int i;
  char *temp;

  num_args=0;
  temp=NULL;

  for(i=0;i<16;i++)
    my_args[i]=NULL;

  temp=strtok(line, " ");

  i=0;
  while(temp!=NULL){
    my_args[i]=temp;
    num_args++;
    i++;
    temp=strtok(NULL, " ");
  }
}



void cd(char cwd[1024]){
  
  static char prev_dir[1024];//need to hold this for multiple calls

  //procedure if '-' is give with cd
  if(my_args[1]!=NULL && strcmp("-", my_args[1]) == 0){
    chdir(prev_dir);
  }
  //if no arguments supplied
  else if(my_args[1]==NULL){
    chdir(getenv("HOME"));
    printf("%s\n", getenv("HOME"));
  }
  else chdir(my_args[1]);

  strncpy(prev_dir,cwd,1024);//store the previous directory
}


