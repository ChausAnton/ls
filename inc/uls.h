#pragma once
#ifndef HEADER_ls
#define HEADER_ls

#include "../libmx/inc/libmx.h"
#include <dirent.h>

char **mx_ls(char *);

void clean_str_arr(char **);

#endif
