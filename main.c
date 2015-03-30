#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>

void pwd();
void cd(char *new_dir);

int main(){

  pid_t pid;
  char *line;
  int exit_flag;

  pid=getpid();
  exit_flag=0;
  printf("%d\n", pid);

  printf("To exit my snail shell type exit\n");
  while(exit_flag==0){
    pwd();
    line = readline("snail: ");
  
    if(strstr(line, "ls")!=NULL){
      pid_t child_pid = fork();
      pid_t child_ppid=getppid();
      printf("%d\n", child_pid);
      if(child_pid==0){
	execl("/bin/ls", "ls", (char *)0);
	exit(1);
      }
    }

    if(strstr(line, "cd")!=NULL){
      cd((line+3));
      //pwd();
      printf("%s\n", (line+3));
    }

    //to exit the snail shell type exit
    if(strcmp(line, "exit")==0)
      exit_flag=1;
  }
 
 
  
 
 
  free(line);
  return 0;
}


void pwd(){
 
  char cwd[1024];

  if(getcwd(cwd, sizeof(cwd))!=NULL)
    printf("current working directory: %s\n", cwd);
  else
    printf("ah shit\n");

}


void cd(char *new_dir){
  chdir(new_dir);

}
