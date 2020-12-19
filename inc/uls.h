#pragma once
#ifndef HEADER_ls
#define HEADER_ls

#include "../libmx/inc/libmx.h"
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

typedef struct t_ls_l {
    struct stat stat;
    char *chmod;
    char *nlink;
    char *name;
    char *grup;
    char *size;
    char *time;
    char *file_name;
}   s_ls_l;

char **mx_ls(char *);

void clean_str_arr(char **);

void mx_ls_l(char **);

#endif
