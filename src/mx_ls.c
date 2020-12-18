#include "../inc/uls.h"

void mx_sort_ls(char **files) {
	for (int i = 0;files[i] != NULL; i++) {
		for (int j = 0;files[j] != NULL; j++) {
			if (mx_strcmp(files[i], files[j]) < 0) {
				void *tmp = files[i];
				files[i] = files[j];
				files[j] = tmp;
				
			}
		}
	}
}

char **mx_ls(char *path) {
    size_t size = 0;

    struct dirent *entry;
    DIR *dir = opendir(path);
    if (!dir) {
        mx_printerr("error with open file\n");
        exit(0);
    }
    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_name[0] != '.') {
            size++;
        }
    }

    if(closedir(dir) == -1) {
        mx_printerr("error while close file\n");
    }

    char **files = (char **) malloc((size + 1) * sizeof(char *));
    for(size_t i = 0; i < size + 1; i++) {
        files[i] = NULL;
    }

    dir = opendir(path);
    if (!dir) {
        mx_printerr("error with open file\n");
        exit(0);
    }
    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_name[0] != '.') {
            files[i] = mx_strdup(entry->d_name);
            i++;
        }
    }

    if(closedir(dir) == -1) {
        mx_printerr("error while close file\n");
    }

    mx_sort_ls(files);

    return files;
}
