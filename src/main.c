#include "../inc/uls.h"

int main(int argc, char *argv[]) {

    char *path;
    if(argc == 1 && argv[0][0] != '\0')
        path = mx_strdup("./");
    else
        path = mx_strdup(argv[1]);
        
    char **arr = mx_ls(path);

    for(int i = 0; arr[i] != NULL; i++) {
        mx_printstr(arr[i]);
        mx_printstr("\t\t");
    }
    
    
    
}
