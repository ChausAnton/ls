#include "../inc/uls.h"

int main(int argc, char *argv[]) {

    char *path;
    if(argc == 1 && argv[0][0] != '\0')
        path = mx_strdup("./");
    else
        path = mx_strdup(argv[1]);
        
    struct dirent *entry;

    DIR *dir = opendir("./");
    if (!dir) {
        mx_printerr("error with open file\n");
    }

    while ((entry = readdir(dir)) != NULL) {
        if(entry->d_name[0] != '.') {
            mx_printstr(entry->d_name);
            mx_printstr("             ");
        }
    }
    
}
