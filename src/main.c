#include "../inc/uls.h"

void clean_str_arr(char **arr) {
    for(int i = 0; arr[i] != NULL; i++) {
        mx_strdel(&arr[i]);
    }
    free(arr);
    arr = NULL;
}

int main(int argc, char *argv[]) {

    char *path = NULL;
    if(argc == 1){
        path = mx_strdup("./");
    } else if (argc == 2 && argv[1][0] == '-'){
        path = mx_strdup("./");
    } else if (argc == 2 && argv[1][0] != '-'){
        path = mx_strdup(argv[1]);
    } else if (argc == 3 && argv[1][0] == '-' && argv[2][0] != '-'){
        path = mx_strdup(argv[2]);
    } else if (argc >= 3 && argv[1][0] == '-' && argv[2][0] != '-'){
        printf("%d argc with flag\n\n", argc-1);
        exit(0);
    }
        
    char **arr = mx_ls(path);

    if(argc > 1 && mx_strcmp(argv[1], "-l") == 0) {
        path = mx_strjoin(path, "/");
        for(int i = 0; arr[i] != NULL; i++) {
            arr[i] = mx_strjoin(path, arr[i]);
        }
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

