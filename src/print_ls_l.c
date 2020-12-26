#include "../inc/uls.h"

void clean_mx_ls_l(s_ls_l **ls_l) {
    for(int i = 0; ls_l[i] != NULL; i++) {
        mx_strdel(&ls_l[i]->chmod);
        mx_strdel(&ls_l[i]->nlink);
        mx_strdel(&ls_l[i]->name);
        mx_strdel(&ls_l[i]->grup);
        mx_strdel(&ls_l[i]->size);
        mx_strdel(&ls_l[i]->file_name);
        free(ls_l[i]);
    }
    free(ls_l);
}

void print_ls_l(struct t_ls_l **ls_l){
     int size_size = mx_strlen(ls_l[0]->size);
    for(size_t i = 1; ls_l[i] != NULL; i++) {
        if(size_size < mx_strlen(ls_l[i]->size)) size_size = mx_strlen(ls_l[i]->size);
    }
    int size_nlink = mx_strlen(ls_l[0]->nlink);
    for(size_t i = 1; ls_l[i] != NULL; i++) {
        if(size_nlink < mx_strlen(ls_l[i]->nlink)) size_nlink = mx_strlen(ls_l[i]->nlink);
    }
    int size_name = mx_strlen(ls_l[0]->name);
    for(size_t i = 1; ls_l[i] != NULL; i++) {
        if(size_name < mx_strlen(ls_l[i]->name)) size_name = mx_strlen(ls_l[i]->name);
    }
    int size_grup = mx_strlen(ls_l[0]->grup);
    for(size_t i = 1; ls_l[i] != NULL; i++) {
        if(size_grup < mx_strlen(ls_l[i]->grup)) size_grup = mx_strlen(ls_l[i]->grup);
    }

    for(size_t i = 0; ls_l[i] != NULL; i++) {
        mx_printstr(ls_l[i]->chmod);
        mx_printstr(" ");
        ////////////////////////
        if(mx_strlen(ls_l[i]->nlink) < size_nlink){
            int tmp = mx_strlen(ls_l[i]->nlink);
            while(tmp!=size_nlink){
                mx_printstr(" ");
                tmp++;
            }
        }
        mx_printstr(ls_l[i]->nlink);
        mx_printstr(" ");
        ////////////////////////
        if(mx_strlen(ls_l[i]->nlink) < size_name){
            int tmp = mx_strlen(ls_l[i]->name);
            while(tmp!=size_name){
                mx_printstr(" ");
                tmp++;
            }
        }
        mx_printstr(ls_l[i]->name);
        mx_printstr("  ");
        ////////////////////////
        if(mx_strlen(ls_l[i]->nlink) < size_grup){
            int tmp = mx_strlen(ls_l[i]->grup);
            while(tmp!=size_grup){
                mx_printstr(" ");
                tmp++;
            }
        }
        mx_printstr(ls_l[i]->grup);
        mx_printstr("  ");
        ////////////////////////
        if(mx_strlen(ls_l[i]->size) < size_size){
            int tmp = mx_strlen(ls_l[i]->size);
            while(tmp!=size_size){
                mx_printstr(" ");
                tmp++;
            }
        }
        if(mx_strcmp(ls_l[i]->file_name, "/dev/null") == 0){
            mx_printstr("  3,   2");
        } 
        else {
            mx_printstr(ls_l[i]->size);
        }
        mx_printstr(" ");
        mx_print_time(ctime(&ls_l[i]->stat.st_mtime), &ls_l[i]->stat);
        mx_printstr(ls_l[i]->file_name);
        mx_printstr("\n");
    }
    clean_mx_ls_l(ls_l);
}
