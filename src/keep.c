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

    // tracking-file check
    if(access(trackFilePath,F_OK) == -1){
        printf("tracking-file doesn\'exist");
        exit(-1);
    }

    //fileName check
    char onlyFileName[128] = ".\\";
    char* temp = strrchr(fileName,'\\') + 1;
    if(temp == NULL) temp = fileName;
    strcat(onlyFileName,temp);

    printf(onlyFileName);
    printf("\n");

    if(access(onlyFileName,F_OK) == -1){
        printf("invalid file name");
        exit(-1);
    }

    //check a file name duplicated
    FILE* track_file_r = fopen(trackFilePath,"r+");
    char str_cmp[128];
    while(!feof(track_file_r)){
        fgets(str_cmp,128,track_file_r);
        //if (strstr(str_cmp,onlyFileName) != NULL) 
    }

    fclose(track_file_r);

    //modify tracking-file
    FILE* track_file = fopen(trackFilePath,"a");
    if(track_file == NULL){
        printf("Failed to open tracking-files");
        exit(-1);
    }

    fprintf(track_file,onlyFileName);
    fprintf(track_file," ");

    fprintf(track_file,"0");
    fprintf(track_file,"\n");

    fclose(track_file);
}