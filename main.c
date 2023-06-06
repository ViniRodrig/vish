#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  size_t bufsize = 64;
  size_t characters;
  char *command;
  
  command = (char *)malloc(bufsize * sizeof(char));
  
  if(command == NULL){
    perror("Unable to allocate buffer");
    exit(1);
  }

  char *prompt =  "vish... $";
  printf("%s ", prompt);
    
  characters = getline(&command,&bufsize,stdin);
    
  return 0;
}
