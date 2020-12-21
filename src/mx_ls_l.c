#include "../inc/uls.h"

char mx_check_per(struct stat *Stat) {
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

char mx_listxattr(char *file) {
    acl_t temp;

    if (listxattr(file, NULL, 0, XATTR_NOFOLLOW) > 0) {
        return '@';
    }
    if ((temp = acl_get_file(file, ACL_TYPE_EXTENDED))) {
        acl_free(temp);
        return ('+');
    }
    return (' ');
}

char *mx_str_per(struct stat *Stat, char *file) {
    char chmod[12];
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
    chmod[10] = mx_listxattr(file);
    chmod[11] = '\0';
    char *tmp = mx_strdup(chmod);
    return tmp;
}

char *str_name(struct stat *Stat) {
    struct passwd *pw = getpwuid(Stat->st_uid);
    if (pw) {
        return mx_strdup(pw->pw_name);
    }
    return NULL;
}

char *print_grup(struct stat *Stat) {
    struct group *grp = getgrgid(Stat->st_gid);
    if (grp) {
        return mx_strdup(grp->gr_name);
    }
    return NULL;
}

void mx_print_time(char *t, struct stat *Stat) {
    int i = 0;
        if (1565913600 >= Stat->st_mtime) {
            for(i = 4; i < 10; i++)
                mx_printchar(t[i]);
            mx_printstr("  ");
            for (i = 20; i < 24; i++)
                mx_printchar(t[i]); 
        }
        else
            for(i = 4; i < 16; i++)
                mx_printchar(t[i]);
    mx_printstr(" ");
}

void mx_ls_l(char **files) {
    size_t size = 1;
    unsigned int total = 0;
    for(int i = 0; files[i] != NULL; i++) {
        struct stat Stat;
    
        int check = lstat(files[i], &Stat);

        if(check == -1) {
            mx_printerr("problem with reading stats\n");
            exit(0);
        }
        size++;
        total += Stat.st_blocks;
    }

    s_ls_l **ls_l = (s_ls_l **) malloc(size * sizeof(s_ls_l *));
    for(size_t i = 0; i < size; i++) {
        ls_l[i] = (s_ls_l *) malloc(sizeof(s_ls_l));
    }
    ls_l[size - 1] = NULL;

    mx_printstr("total ");
    mx_printint(total);
    mx_printstr("\n");

    for(int i = 0; files[i] != NULL; i++) {
        struct stat Stat;
    
        int check = lstat(files[i], &Stat);

        if(check == -1) {
            mx_printerr("problem with reading stats\n");
            exit(0);
        }
        ls_l[i]->stat = Stat;
        ls_l[i]->chmod = mx_strdup(mx_str_per(&Stat, files[i]));
        ls_l[i]->nlink = mx_itoa(Stat.st_nlink);
        ls_l[i]->name = str_name(&Stat);
        ls_l[i]->grup = print_grup(&Stat);
        ls_l[i]->size = mx_itoa(Stat.st_size);
        ls_l[i]->file_name = mx_strdup(files[i]);
    }
    print_ls_l(ls_l);
}
