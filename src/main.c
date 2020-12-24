#include "../inc/uls.h"

void clean_str_arr(char **arr) {
    for(int i = 0; arr[i] != NULL; i++) {
        mx_strdel(&arr[i]);
    }
    free(arr);
    arr = NULL;
}

int main(int argc, char *argv[]) {

    char **paths = (char **) malloc((argc + 1) * sizeof(char *));
    for (int i = 0; i < argc + 1; i++){
        paths[i] = NULL;
    }

    if(argc == 1) {
        paths[0] = mx_strdup("./");
    }
    if(argc == 2) {
        if(mx_strcmp(argv[1], "-l") == 0) {
            paths[0] = mx_strdup("./");
        }
        else {
            paths[0] = mx_strdup(argv[1]);
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
            paths[j] = mx_strdup(argv[i]);
            j++;
        }
    }

    mx_sort_ls(paths);

    for(int g = 0; paths[g] != NULL; g++) {
        char **arr = mx_ls(paths[g]);
        
        if(mx_strcmp(paths[g], "./") != 0 && (paths[g + 1] != NULL || g >= 1)) {
            mx_printstr(paths[g]);
            mx_printstr(":\n");
        }

        if(argc > 1 && mx_strcmp(argv[1], "-l") == 0) {
            paths[g] = mx_strjoin(paths[g], "/");
            for(int i = 0; arr[i] != NULL; i++) {
                arr[i] = mx_strjoin(paths[g], arr[i]);
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

        if(paths[g + 1] != NULL) mx_printstr("\n");
    }
    clean_str_arr(paths);
}

