#include "paging_sys.h"

//find oldest page and check ref bit for second chance
int age_n_ref(int age[], int ref_bit[], int index){
	int max=0,ind,i;
	int age_ref[8];
	for(i=0;i<8;i++)
		age_ref[i]=age[i];
	while(1){
	for(i=0;i<8;i++){
		if(age_ref[i]>max){
			max = age_ref[i];
			ind = i;  //find oldest page
		}
	}
	if(ref_bit[ind]==1){   //check if ref bit is 1 and set it to 0
		ref_bit[ind]=0;
		age_ref[ind]=0;
		max=0;    //again check for the oldest page till it encounters 0
	}
	else
		break;
	}
	//find the location of the oldest page in cache
	for(i=0;i<4;i++){
		if(ind==mem[i][index]){
			ind = i;
		}
	}
	return ind;  //return the index of the oldest page in cache with ref bit 0
}

//move the replaced page from cache to main memory
void push_2mem(int mem_ind,int index){
	int i,pushed=0;
	int ind = 7;
	
	for(i=4;i<8;i++){
		if(mem[i][index]==ref_string[index]){ //checking location of currently called page
			ind = i;
			break;
		}	
	}
	for(i=5;i<=ind;i++)  //pushing the pages in memory down by 1 index and keeping currently removed page on top
		mem[i][index+1] = mem[i-1][index];
	mem[4][index+1] = mem[mem_ind][index];
}

//find the oldest page for FIFO algorithm
int ret_max(int age[],int index){
	int max=0,ind,i;
	for(i=0;i<8;i++){
		if(age[i]>max){
			max = age[i];  
			ind = i;     //store the page which has the max age
		}
	}
	for(i=0;i<4;i++){
		if(ind==mem[i][index]){
			ind = i;    //find the index of the oldest page and return
		}
	}
	return ind;
	
}

//check whether the called page is in main memory
int check_2mem(int index){
		int i,loc=0;
		for(i=4;i<8;i++){			
			if(mem[i][index]==ref_string[index]){
				loc = i;   //store the index of the called page and return
				break;
			}
		}
	return loc;
	
}

//find the location of the called page in cache for LRU algorithm
int hit_loc(int index){
	int i,loc;
	for(i=0;i<4;i++){
		if(mem[i][index]==ref_string[index]){
			loc = i;   //store the index of the called page and return
			break;
		}
	}
	return loc;
}

//check for space in cache and return index
int load_init(int index)
{
	int i,loc=0;
	for(i=0;i<4;i++){
		if(mem[i][index]==9){
			loc = i;
			break;
		}
	}
	return loc;	
}

//check for hit/miss
int check_cache(int index){
	int i,j,stat;
	for(i=0;i<4;i++){
		if(mem[i][index]==ref_string[index]){
			stat = 1; //present in cache
			break;
		}
		else if(mem[i][index]==9){
			stat = 2; //cache miss but space available
			break;
		}	
		else
			stat = 0;  //need to fetch from mem
	}
	return stat;
}
