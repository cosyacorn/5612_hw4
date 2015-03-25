#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<readline/readline.h>
#include<readline/history.h>

void pwd();
void cd(char *new_dir);

int main(){

  
 
  pwd();
  cd("/usr/bin");
  pwd();
 
  char *line;
  line = readline("enter a command: ");
  
 
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
