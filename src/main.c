#include "../inc/uls.h"

void clean_str_arr(char **arr) {
    for(int i = 0; arr[i] != NULL; i++) {
        mx_strdel(&arr[i]);
    }
    free(arr);
    arr = NULL;
}

int main(int argc, char *argv[]) {
    
    char *legal_flags = mx_strdup("l");
    if(argc > 1 && argv[1][0] == '-') {
        for(int i =1; argv[1][i]; i++){
            if(mx_get_char_index(legal_flags ,argv[1][i]) == -1){
                mx_printerr("uls: illegal option -- ");
                write(2, &argv[1][i], 1);
                mx_printerr("\nusage: uls [-l] [file ...]\n");
                exit(0);
            }
        }
    }
    
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
        if (argc > 1 && mx_strcmp(argv[1], "-l") == 0) {
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
        struct stat temp;
        if(stat(paths[g], &temp) == -1) {
            mx_printerr("uls: ");
            mx_printerr(paths[g]);
            mx_printerr(": No such file or directory\n");
            continue;
        }
        if(S_ISDIR(temp.st_mode)) {  
            continue;
        } else if (argc > 1 && mx_strcmp(argv[1], "-l") != 0) {
            mx_printstr(paths[g]);
            mx_printstr("\n");
            continue;
        }
    }
    for(int g = 0; paths[g] != NULL; g++) {
        struct stat temp;
        if(stat(paths[g], &temp) == -1) {
            mx_printerr("uls: ");
            mx_printerr(paths[g]);
            mx_printerr(": No such file or directory\n");
            continue;
        }
        char **arr = NULL;
        if(S_ISDIR(temp.st_mode)) {
            arr = mx_ls(paths[g]);   
            //continue;
        } else if (argc > 1 && mx_strcmp(argv[1], "-l") != 0) {
            //mx_printstr(paths[g]);
            //mx_printstr("\n");
            continue;
        }
                
        if(mx_strcmp(paths[g], "./") != 0 && (paths[g + 1] != NULL || g >= 1) && S_ISDIR(temp.st_mode)) {
            mx_printstr(paths[g]);
            mx_printstr(":\n");
        }
        if(argc > 1 && mx_strcmp(argv[1], "-l") == 0) {
            bool total = false;
            if(S_ISDIR(temp.st_mode)) {
                paths[g] = mx_strjoin(paths[g], "/");
                for(int i = 0; arr[i] != NULL; i++) {
                    arr[i] = mx_strjoin(paths[g], arr[i]);
                }
                total = true;
            }
            else{
                arr = (char **) malloc(2 *  sizeof(char *));
                arr[1] = NULL;
                arr[0] = mx_strdup(paths[g]);
            }
            
            mx_ls_l(arr, total);
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

