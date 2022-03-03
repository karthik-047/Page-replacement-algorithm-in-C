#include "paging_sys.h"

//find oldest page and check ref bit
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
		max=0;    //again check for the oldest page
		//printf("\n Ref bit of oldest page %d is 1 with age %d",ind,max);
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
	//printf("\n Oldest page present at ind %d",ind);
	return ind;
}

//move the replaced page from cache to main memory
void push_2mem(int mem_ind,int index){
	int i,pushed=0;
	int ind = 7;
	for(i=4;i<8;i++){
		if(mem[i][index]==ref_string[index]){
			ind = i;
			//printf("\n placing %d in mem2 slot at %d",mem[mem_ind][index],i);
			break;
		}	
	}
	for(i=5;i<=ind;i++)
		mem[i][index+1] = mem[i-1][index];
	mem[4][index+1] = mem[mem_ind][index];
}

int ret_max(int age[],int index){
	int max=0,ind,i;
	for(i=0;i<8;i++){
		if(age[i]>max){
			max = age[i];
			ind = i;
		}
	}
	//printf("\n Oldest page is %d with age %d",ind,max);
	for(i=0;i<4;i++){
		if(ind==mem[i][index]){
			ind = i;
		}
	}
	//printf("\n Oldest page present at ind %d",ind);
	return ind;
	
}
int check_2mem(int index){
		int i,loc=0;
		for(i=4;i<8;i++){			
			if(mem[i][index]==ref_string[index]){
				//printf("\n Present in 2nd_mem");
				loc = i;
				break;
			}
		}
	return loc;
	
	}
int hit_loc(int index){
	int i,loc;
	for(i=0;i<4;i++){
		if(mem[i][index]==ref_string[index]){
			loc = i;
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
	//printf("\n Space availabe at loc: %d",loc);
	return loc;	
}

int fetch_mem(int index){
	int i,j,loc=0;
	for(i=4;i<8;i++){
		if(mem[i][index]==ref_string[index]){
			loc = i;
			break;
		}			
	}
	//printf("\n Found in 2mem at index: %d",loc);
	if(loc<8)
		return loc;
	else
		return 0;
}
int check_cache(int index){
	int i,j,stat;
	for(i=0;i<4;i++){
		if(mem[i][index]==ref_string[index]){
			stat = 1; //present in cache
			break;
		}
		else if(mem[i][index]==9){
			stat = 2; //miss but space available
			break;
		}	
		else
			stat = 0;  //need to fetch from mem
	}
	//printf("\n Cache status returned");
	return stat;
}
