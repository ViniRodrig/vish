#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

void exec_command(char **token_array){
  char *command = NULL;
  int verify;

  if(token_array){
    command = token_array[0];

    verify = execve(command, token_array, NULL);
    
    if(verify == -1)
      perror("Error: ");
  
  }
}

int main()
{
  size_t buffsize = 0;
  size_t characters;
  char *command = NULL;
  char *command_copy = NULL;
  int i;

  char **token_array = NULL;
  char *token = NULL;
  int token_num;
  const char *delimiter = " \n";  



  char *prompt =  "vish... $ ";

  
  while(1){
    printf("%s ", prompt);
    characters = getline(&command,&buffsize,stdin);
    
    // if getline function fail exit
    if((characters == -1 ) || !(strcmp (command, "exit\n")) ){
      printf("Exiting shell\n");
      return (-1);
    }

    command_copy = malloc(sizeof(char) * characters);
    if (command_copy == NULL){
      perror("Unable to alocate the buffer");
      return (-1);
    }
    
    strcpy(command_copy, command);

    token = strtok(command, delimiter);

    while(token != NULL){
        token_num++;
        token = strtok(NULL, delimiter);
    }
    token_num++;

    token_array = malloc(sizeof(char *) * token_num);
    token = strtok(command_copy, delimiter);

    for(i=0; token != NULL; i++){
      token_array[i] = malloc(sizeof(char *) * strlen(token));
      strcpy(token_array[i], token);

      token = strtok(NULL, delimiter);
    }
    token_array[i] = NULL;

    exec_command(token_array);

    free(command_copy);
    free(token_array);

  }


  return 0;
}
