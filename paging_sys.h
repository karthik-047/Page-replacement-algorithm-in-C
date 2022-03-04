#ifndef PAGING_SYS_H
#define PAGING_SYS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int ref_string[24];   //variable to store the reference string
int mem[8][25];		  //variable to store the pages in the cache and main memory
int fault[24];		  //variable to store the page hit/fault - 1/0
int ref_bit[8];       //variable to store reference bit of the pages

void fifo();          
void second_chance();
void lru();
int check_cache(int);
int load_init(int);
int hit_loc(int);
int check_2mem(int);
int ret_max(int age[],int);
void push_2mem(int, int);
int age_n_ref(int age[],int ref_bit[],int);

#endif
