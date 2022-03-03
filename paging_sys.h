#ifndef PAGING_SYS_H
#define PAGING_SYS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int ref_string[24];
int mem[8][25];
int fault[24];
int ref_bit[8];

void fifo(); 
void second();
void lru();
int check_cache(int);
int fetch_mem(int);
int load_init(int);
int hit_loc(int);
int check_2mem(int);
int ret_max(int age[],int);
void push_2mem(int, int);
int age_n_ref(int age[],int ref_bit[],int);

#endif
