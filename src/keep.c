#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum Command{
    INIT,
    TRACT
};

const char* keep_dir = "./.keep";
const char* trackFilePath = "./.keep/tracking-files";
const char* versionFilePath = "./.keep/latest-version";

int commandNumber(char* commandNmae);
void keep_init();
void keep_track(char* fileName);

int main(int argc, char** args)
{
    if(argc == 0){
        printf("help message");
        return -1;
    }
    
    switch(commandNumber(args[1])){
        case INIT:
            keep_init();
            break;
        case TRACT:
            keep_track(args[2]);
            break;
        default:
            printf("help message: invaild command");
            return -1;
    }
}

int commandNumber(char* commandName){
    if(strcmp(commandName,"init") == 0){
        return INIT;
    }else if(strcmp(commandName,"track") == 0){
        return TRACT;
    }else
     return -1;
}

void keep_init(){
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

    //Make tracking-files and latest-version in .keep dir
    FILE* track_file = fopen(trackFilePath,"w");
    FILE* version_file = fopen(versionFilePath,"w"); 
    if(track_file == NULL){
        printf("Failed to make tracking-files");
        exit(-1);
    }
    if(version_file == NULL){
        printf("Failed to make latest-version");
        exit(-1);
    }

    fprintf(version_file,"0");

    fclose(track_file);
    fclose(version_file);
}

void keep_track(char* fileName){

    FILE* track_file = fopen(trackFilePath,"a");

    if(track_file == NULL){
        printf("Failed to open tracking-files");
        exit(-1);
    }

    fprintf(track_file,fileName);
    fprintf(track_file,"\n");

    fclose(track_file);
}