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
    if(argc >= 1 && argv[0][0] != '\0')
        path = mx_strdup("./");
    else
        path = mx_strdup(argv[1]);
        
    char **arr = mx_ls(path);

    if(mx_strcmp(argv[argc - 1], "-l") == 0) {
        mx_ls_l(arr);
        exit(0);
    }

    for(int i = 0; arr[i] != NULL; i++) {
        if(i != 0) {
            int word_len = mx_strlen(arr[i - 1]);
            for(int j = 0; j < (15 - word_len) + 1; j++) {
                mx_printstr(" ");
            }
        }
        mx_printstr(arr[i]);
    }

    clean_str_arr(arr);
}

