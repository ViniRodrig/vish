#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  size_t bufsize = 64;
  size_t characters;
  char *command;
  

  command = (char *)malloc(bufsize * sizeof(char));
  char *prompt =  "vish... $ ";
  
  if(command == NULL){
    perror("Unable to allocate buffer");
    exit(1);
  }
  
  while(1){
    printf("%s ", prompt);
    characters = getline(&command,&bufsize,stdin);
    
    // if getline function fail exit
    if((characters == -1 ) || !(strcmp (command, "exit\n")) ){
      printf("Exiting shell\n");
      return(-1);
    }
    
    printf("%s", command)
;
  }

  free(command);
  return 0;
}
