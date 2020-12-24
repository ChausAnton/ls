#include "../inc/uls.h"

void clean_str_arr(char **arr) {
    for(int i = 0; arr[i] != NULL; i++) {
        mx_strdel(&arr[i]);
    }
    free(arr);
    arr = NULL;
}

void mx_sort_by_dir(char **paths){
    for (int i = 0; paths[i] != NULL; i++) {
		for (int j = 0; paths[j+1] != NULL; j++) {
            struct stat temp;
            struct stat temp1;
            stat(paths[j], &temp);
            stat(paths[j+1], &temp1);
            if(S_ISDIR(temp.st_mode) && !S_ISDIR(temp1.st_mode)) {  
                void *tmp = paths[j];
				paths[j] = paths[j+1];
				paths[j+1] = tmp;
            }   
		}
	}   
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
        if((argv[1][0] == '-' && argv[1][1] == 'l')) {
            paths[0] = mx_strdup("./");
        }
        else {
            paths[0] = mx_strdup(argv[1]);
        }
    }
    if(argc > 2) {
        int j = 0;
        int i = 0;
        if (argc > 1 && (argv[1][0] == '-' && argv[1][1] == 'l')) {
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
    mx_sort_by_dir(paths);

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
        }
        else if (argc > 1 && (argv[1][0] != '-' || argv[1][1] != 'l')) {
            mx_printstr(paths[g]);
            mx_printstr("\n");
           
            struct stat tmp_check;
            stat(paths[g+1], &tmp_check);
            if(!S_ISDIR(temp.st_mode) && S_ISDIR(tmp_check.st_mode)) {
                mx_printstr("\n");
            }  
            continue;
        } 
        if(mx_strcmp(paths[g], "./") != 0 && (paths[g + 1] != NULL || g >= 1) && S_ISDIR(temp.st_mode)) {
            mx_printstr(paths[g]);
            mx_printstr(":\n");
        }
        if(argc > 1 && (argv[1][0] == '-' && argv[1][1] == 'l')) {
            bool total = false;
            if(S_ISDIR(temp.st_mode)) {
                paths[g] = mx_strjoin(paths[g], "/");
                for(int i = 0; arr[i] != NULL; i++) {
                    arr[i] = mx_strjoin(paths[g], arr[i]);
                }
                total = true;
            }
            else{
                int size = 0;
                for (int i = 0; paths[i] != NULL; i++) {
                    struct stat temp;
                    stat(paths[i], &temp);
                    if(!S_ISDIR(temp.st_mode)) {
                        size++;
                    }
                    else {
                        break;
                    }
                    
                }
                arr = (char **) malloc((size + 1) *  sizeof(char *));
                for (int i = 0; i < size; i++) {
                    arr[i] = mx_strdup(paths[g]);
                    g++;
                }
                g--;
                arr[size] = NULL;
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

