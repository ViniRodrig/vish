#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <signal.h>


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

void parser_fork(char **token_array, int token_count){
  
  int pid;
  char *ampersand = "&";
  if (strcmp(token_array[token_count-2], ampersand) == 0){
    token_array[token_count-2] = '\0';
    pid = fork();
    if (pid == 0){
      exec_command(token_array);
    } else {
      signal(SIGCHLD, SIG_IGN);
    }
  } 
  else
  {
    pid = fork();
    if (pid == 0 ){
      exec_command(token_array);
    } else {
      wait(NULL);
    }
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
  int token_count;
  const char *delimiter = " \n";  



  char *prompt =  "vish... $ ";

  
  while(1){
    token_count = 0;
    
    // get a line from the user
    printf("%s ", prompt);
    characters = getline(&command,&buffsize,stdin);
    
    // if getline function fail exit
    if((characters == -1 ) || !(strcmp (command, "exit\n")) ){
      printf("Exiting shell\n");
      return (-1);
    }

    // alocate the copy buffer to be used to strktok
    command_copy = malloc(sizeof(char) * characters);
    if (command_copy == NULL){
      perror("Unable to alocate the buffer");
      return (-1);
    }
    
    // copy the typed string to command_copy
    strcpy(command_copy, command);

    // goes through the typed string couting every token
    token = strtok(command, delimiter);

    while(token != NULL){
        token_count++;
        token = strtok(NULL, delimiter);
    }
    token_count++;

    // alocates the token array with the size of a pointer to every single token
    token_array = malloc(sizeof(char *) * token_count);
    token = strtok(command_copy, delimiter);

    // alocates every single token and put in the token array
    for(i=0; token != NULL; i++){
      token_array[i] = malloc(sizeof(char *) * strlen(token));
      strcpy(token_array[i], token);

      token = strtok(NULL, delimiter);
    }
    token_array[i] = NULL;

    parser_fork(token_array, token_count);

    free(command_copy);
    free(token_array);

  }


  return 0;
}
