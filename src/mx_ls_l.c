#include "../inc/uls.h"

static char mx_check_per(struct stat *Stat) {
    if ((Stat->st_mode & S_IFMT) == S_IFDIR)
        return 'd';
    if ((Stat->st_mode & S_IFMT) == S_IFLNK)
        return 'l';
    if ((Stat->st_mode & S_IFMT) == S_IFBLK)
        return 'b';
    if ((Stat->st_mode & S_IFMT) == S_IFCHR)
        return 'c';
    if ((Stat->st_mode & S_IFMT) == S_IFIFO)
        return 'p';
    if ((Stat->st_mode & S_IFMT) == S_IFSOCK)
        return 's';
    if ((Stat->st_mode & S_IFMT) == S_IFWHT)
        return 'w';
    return '-';
}

void mx_print_per(struct stat *Stat) {
    char chmod[11];

    chmod[0] = mx_check_per(Stat);
    chmod[1] = (S_IRUSR & Stat->st_mode) ? 'r' : '-';
    chmod[2] = (S_IWUSR & Stat->st_mode) ? 'w' : '-';
    chmod[3] = (S_IXUSR & Stat->st_mode) ? 'x' : '-';
    chmod[4] = (S_IRGRP & Stat->st_mode) ? 'r' : '-';
    chmod[5] = (S_IWGRP & Stat->st_mode) ? 'w' : '-';
    chmod[6] = (S_IXGRP & Stat->st_mode) ? 'x' : '-';
    chmod[7] = (S_IROTH & Stat->st_mode) ? 'r' : '-';
    chmod[8] = (S_IWOTH & Stat->st_mode) ? 'w' : '-';
    chmod[9] = (S_IXOTH & Stat->st_mode) ? 'x' : '-';
    chmod[10] = '\0';

    mx_printstr(chmod);


}

void print_name(struct stat *Stat) {
    struct passwd *pw = getpwuid(Stat->st_uid);
    if (pw) {
        mx_printstr(pw->pw_name);
    }
}

void print_grup(struct stat *Stat) {
    struct group *grp = getgrgid(Stat->st_gid);
    if (grp) {
        mx_printstr(grp->gr_name);
    }
}

void mx_ls_l(char **files) {
    struct stat Stat;

    /*for(int i = 0; files[i] != NULL; i++) {
        if(i != 0) {
            int word_len = mx_strlen(files[i - 1]);
            for(int j = 0; j < (15 - word_len) + 1; j++) {
                mx_printstr(" ");
            }
        }
        mx_printstr(files[i]);
    }*/

    
    int check = lstat(files[0], &Stat);

    if(check == -1) {
        mx_printerr("problem with reading stats\n");
        exit(0);
    }

    mx_print_per(&Stat);
    mx_printstr("  ");
    mx_printint(Stat.st_nlink);
    mx_printstr(" ");
    print_name(&Stat);
    mx_printstr("  ");
    print_grup(&Stat);
    mx_printstr("  ");
    mx_printstr(mx_itoa(Stat.st_size));
    mx_printstr("  ");
    mx_printstr(mx_itoa(Stat.st_ctime));
    
}
