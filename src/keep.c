#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum Command{
    INIT
};
int commandNumber(char* commandNmae);
void keep_init();

int main(int argc, char** args)
{
    if(argc == 0){
        perror("help message");
        return -1;
    }
    
    switch(commandNumber(args[0])){
        case INIT:
            keep_init();
            break;
        default:
            perror("help message");
            return -1;
    }

}
int commandNumber(char* commandName){
    if(strcmp(commandName,"init")){
        return INIT;
    }else return 0;
}

void keep_init(){
    char* keep_dir = ".keep";

    //Make .keep diractory
    if(access(keep_dir,F_OK) != -1){
        printf(".keep already exist");
        exit(-1);
    }
    else{
        if(mkdir(keep_dir) != 0){
            printf("failed to make .keep in this dir");
            exit(-1);
        }            
    }

    //Make tracking-files in .keep dir
    FILE* track_file = fopen("./.keep/tracking-files","w");
    FILE* version = fopen("./.keep/latest-version","w"); 
    if(track_file == NULL){
        printf("Failed to make tracking-files");
        exit(-1);
    }
    if(version == NULL){
        printf("Failed to make latest-version");
        exit(-1);
    }

    fprintf(version,"0");

    fclose(track_file);
    fclose(version);
}