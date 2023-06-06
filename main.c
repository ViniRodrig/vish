#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    size_t bufsize = 64;
    size_t characters;
    char *command;

    buffer = (char *)malloc(bufsize * sizeof(char));
  
    if(buffer == null){
        perror("Unable to allocate buffer");
        exit(1)
    }

    char *prompt =  "vish... $";
    printf("%s ", prompt);
    
    characters = getline(&buffer,&bufsize,stdin);
    

    return 0;
}
