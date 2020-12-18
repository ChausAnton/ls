#include "../inc/uls.h"

void clean_str_arr(char **arr) {
    for(int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
}

int main(int argc, char *argv[]) {

    char *path;
    if(argc == 1 && argv[0][0] != '\0')
        path = mx_strdup("./");
    else
        path = mx_strdup(argv[1]);
        
    char **arr = mx_ls(path);

    clean_str_arr(arr);
}

