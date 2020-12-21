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
    } else if (argc == 3 && argv[1][0] != '-' && argv[2][0] == '-'){
        path = mx_strdup(argv[1]);
    } else if (argc >= 3 && argv[1][0] != '-' && argv[2][0] != '-' && argv[argc-1][0] != '-'){
        printf("\n%d argc without flags\n\n", argc-1);
        exit(0);
    } else if (argc >= 4 && argv[1][0] != '-' && argv[2][0] != '-' && argv[argc-1][0] == '-'){
        printf("\n%d argc with flags\n\n", argc-2);
        exit(0);
    }
        
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

