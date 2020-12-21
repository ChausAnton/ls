#include "../inc/uls.h"

void clean_str_arr(char **arr) {
    for(int i = 0; arr[i] != NULL; i++) {
        mx_strdel(&arr[i]);
    }
    free(arr);
    arr = NULL;
}

int main(int argc, char *argv[]) {



    char **path = (char **) malloc((argc + 1) * sizeof(char *));
    for (int i = 0; i < argc + 1; i++){
        path[i] = NULL;
    }

    if(argc == 1) {
        path[0] = mx_strdup("./");
    }
    if(argc == 2) {
        if(mx_strcmp(argv[1], "-l") == 0) {
            path[0] = mx_strdup("./");
        }
        else {
            path[0] = mx_strdup(argv[1]);
        }
    }
    if(argc > 2) {
        int j = 0;
        int i = 0;
        if (mx_strcmp(argv[1], "-l") == 0) {
            i = 2;
        }
        else{
            i = 1;
        }

        for(; i < argc; i++) {
            path[j] = mx_strdup(argv[i]);
            j++;
        }
        
    }

    for(int g = 0; path[g] != NULL; g++) {
        char **arr = mx_ls(path[g]);

        if(argc > 1 && mx_strcmp(argv[1], "-l") == 0) {
            if(mx_strcmp(argv[1], "./") != 0)
                path[g] = mx_strjoin(path[g], "/");
            for(int i = 0; arr[i] != NULL; i++) {
                arr[i] = mx_strjoin(path[g], arr[i]);
            }
            mx_ls_l(arr);
        }
        else {
            for(int i = 0; arr[i] != NULL; i++) {
                mx_printstr(arr[i]);
                mx_printstr("\n");
            }
        }
        clean_str_arr(arr);
    }
    clean_str_arr(path);
}

