#include "../inc/uls.h"

void clean_str_arr(char **arr) {
    for(int i = 0; arr[i] != NULL; i++) {
        mx_strdel(&arr[i]);
    }
    free(arr);
    arr = NULL;
}

int main(int argc, char *argv[]) {

    char *path;
    if(argc >= 1 && argv[0][0] != '\0')
        path = mx_strdup("./");
    else
        path = mx_strdup(argv[1]);
        
    char **arr = mx_ls(path);

    if(mx_strcmp(argv[argc - 1], "-l") == 0) {
        mx_ls_l(arr);
    }
    else {
    int size = 0;
    for(int i = 0; arr[i] != NULL; i++) {
        if(size < mx_strlen(arr[i])) {
            size = mx_strlen(arr[i]);
        }
    }

    while (size % 4 != 0) {
        size++;
    }
    size = size / 4;
    
    for(int i = 0; arr[i] != NULL; i++) {
        mx_printstr(arr[i]);
        mx_printstr("\n");
    }
    }
    clean_str_arr(arr);
}

