/*#include <stdio.h>
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
*/

#include "paging_sys.h"
//find oldest page and check ref bit
/*int age_n_ref(int age[], int ref_bit[], int index){
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
}*/

void second(){
	int age[8] = {0};
	int i,j,load,hit,a,b,load_ind,max_age,age_ind,rst_age;

	for(i=0;i<8;i++)
		ref_bit[i]= -1;	
	for(i=0;i<24;i++){
		load = ref_string[i];
		//printf("\n Load: %d",load);
		if((ref_bit[load]==0)||(ref_bit[load]==1))
			ref_bit[load] = 1;
		else if (ref_bit[load]==-1)
			ref_bit[load]++;
		//increasing age of the page
		for(j=0;j<4;j++){
			age_ind = mem[j][i];
			age[age_ind]++;
			}
		//printf("\n Need page %d at time %d",ref_string[i],i);
		hit = check_cache(i);
		//printf("\n Cache stat: %d",hit);
		sleep(1);
		if(hit==1){
			fault[i]=1;
			for(j=0;j<8;j++)
				mem[j][i+1] = mem[j][i];
			}
		else if(hit==2){
			fault[i] = 0;
			//printf("\n Cache miss but space available");
			load_ind = load_init(i);
			for(j=1;j<=load_ind;j++){
			mem[j][i+1] = mem[j-1][i];
			//printf("\n Pushing val %d from %d to %d at time %d",mem[j][i+1],j-1,j,i);
		}
			mem[0][i+1] = ref_string[i];
			
		}
		else if(hit==0){
			fault[i] = 0;
			//printf("\n No space;  Fetching from memory");
			//max_age = ret_max(age,i);
			max_age  = age_n_ref(age,ref_bit,i);
			rst_age = mem[max_age][i];
			age[rst_age]=0;
			for(j=0;j<8;j++)
				mem[j][i+1] = mem[j][i];
			//printf("\n Pushing %d to 2nd mem",mem[max_age][i]);		
			push_2mem(max_age,i);
			ref_bit[mem[max_age][i]]=-1;
			mem[max_age][i+1] = ref_string[i];
		}
		printf("\n************************************************");
		printf("\n Reference String \n   ");
	  	for(a=0;a<i;a++)
			printf(" %d ",ref_string[a]);
	  	printf("\n Memory State \n");
	  	for(a=0;a<8;a++){
			for(b=0;b<(i+1);b++){
				if(mem[a][b]==9)
					printf(" - ");
				else
					printf(" %d ",mem[a][b]);
			}
	  	printf("\n");
  		}
		printf("Page Status\n   ");
  		for(a=0;a<i;a++)
	  		printf(" %d ",fault[a]);
	  	printf("\n************************************************\n\n");	
		/*printf("\n Age Array\n");
		for(j=0;j<8;j++)
			printf("%d  ",age[j]);
		printf("\n Ref Array\n");
		for(j=0;j<8;j++)
			printf("%d  ",ref_bit[j]);*/
	}
	
}


void fifo(){
	int i,j,load,hit,a,b,load_ind,max_age,age_ind,rst_age;
	int age[8] = {0};
	for(i=0;i<24;i++){
		load = ref_string[i];
		for(j=0;j<4;j++){
			age_ind = mem[j][i];
			age[age_ind]++;
			}
		/* printf("\n Memory State \n   ");
	  	for(a=0;a<24;a++)
			printf(" %d ",ref_string[a]);
	  	printf("\n");
	  	for(a=0;a<8;a++){
			for(b=0;b<25;b++)
				printf(" %d ",mem[a][b]);
	  	printf("\n");
  		} */
		/* printf("\n Age Array\n");
		for(j=0;j<8;j++)
			printf("%d  ",age[j]); */
		//printf("\n Need page %d at time %d",ref_string[i],i);
		hit = check_cache(i);
		//printf("\n Cache stat: %d",hit);
		//sleep(1);
		if(hit==1){
			fault[i]=1;
			for(j=0;j<8;j++)
				mem[j][i+1] = mem[j][i];
			}
		else if(hit==2){
			fault[i] = 0;
			//printf("\n Cache miss but space available");
			load_ind = load_init(i);
			for(j=1;j<=load_ind;j++){
			mem[j][i+1] = mem[j-1][i];
			//printf("\n Pushing val %d from %d to %d at time %d",mem[j][i+1],j-1,j,i);
		}
			mem[0][i+1] = ref_string[i];
			
		}
		else if(hit==0){
			fault[i] = 0;
			//printf("\n No space;  Fetching from memory");
			max_age = ret_max(age,i);
			rst_age = mem[max_age][i];
			age[rst_age]=0;
			for(j=0;j<8;j++)
				mem[j][i+1] = mem[j][i];
			//printf("\n Pushing %d to 2nd mem",mem[max_age][i]);		
			push_2mem(max_age,i);
			mem[max_age][i+1] = ref_string[i];
		}
		printf("\n************************************************");
		printf("\n Reference String \n   ");
	  	for(a=0;a<i;a++)
			printf(" %d ",ref_string[a]);
	  	printf("\n Memory State \n");
	  	for(a=0;a<8;a++){
			for(b=0;b<(i+1);b++){
				if(mem[a][b]==9)
					printf(" - ");
				else
					printf(" %d ",mem[a][b]);
			}
	  	printf("\n");
  		}
		printf("Page Status\n   ");
  		for(a=0;a<i;a++)
	  		printf(" %d ",fault[a]);
	  	printf("\n************************************************\n\n");
	}
}
void lru(){

	int load,a,b,i=0,j=0,mem_loc, hit,hit_ind,load_ind,mem_ind;
	for(i=0;i<24;i++){
		load = ref_string[i];
		/*printf("\n Memory State \n   ");
	  	for(a=0;a<24;a++)
			printf(" %d ",ref_string[a]);
	  	printf("\n");
	  	for(a=0;a<8;a++){
			for(b=0;b<25;b++)
				printf(" %d ",mem[a][b]);
	  	printf("\n");
  		}*/
		//printf("\n Need page %d at time %d",ref_string[i],i);
		hit = check_cache(i);
		//printf("\n Cache stat: %d",hit);
		//sleep(1);
		if(hit==0){
			fault[i] = 0;
			//printf("\n No space;  Fetching from memory");
			mem_loc = check_2mem(i);
			//printf("\n Present at location %d",mem_loc);
			if(mem_loc==0){
				for(j=1;j<8;j++)
					mem[j][i+1] = mem[j-1][i];
			}
			else{
				for(j=1;j<=mem_loc;j++)
					mem[j][i+1] = mem[j-1][i];
				for(j=(mem_loc+1);j<8;j++)
					mem[j][i+1] = mem[j][i];
			}
			mem[0][i+1] = ref_string[i];
			
		}
		else if(hit==1){
			fault[i] = 1;
			hit_ind = hit_loc(i);
			//printf("\n Cache hit at %d",hit_ind);
			for(j=1;j<=hit_ind;j++){
				mem[j][i+1] = mem[j-1][i];
				//printf("\n Pushing val %d from %d to %d at time %d",mem[j][i+1],j-1,j,i);
			}
			mem[0][i+1] = ref_string[i];
			for(j=(hit_ind+1);j<8;j++)
				mem[j][i+1] = mem[j][i];
		}
		else if(hit==2){
			fault[i] = 0;
			//printf("\n Cache miss but space available");
			load_ind = load_init(i);
			for(j=1;j<=load_ind;j++){
				mem[j][i+1] = mem[j-1][i];
				//printf("\n Pushing val %d from %d to %d at time %d",mem[j][i+1],j-1,j,i);
			}
			mem[0][i+1] = ref_string[i];	
		}
		printf("\n************************************************");
		printf("\n Reference String \n   ");
	  	for(a=0;a<i;a++)
			printf(" %d ",ref_string[a]);
	  	printf("\n Memory State \n");
	  	for(a=0;a<8;a++){
			for(b=0;b<(i+1);b++){
				if(mem[a][b]==9)
					printf(" - ");
				else
					printf(" %d ",mem[a][b]);
			}
	  	printf("\n");
  		}
		printf("Page Status\n   ");
  		for(a=0;a<i;a++)
	  		printf(" %d ",fault[a]);
	  	printf("\n************************************************\n\n");	
	}
}

int main(void) {
  int choice;
  int i,j;
  for(i=0;i<8;i++)
  	for(j=0;j<25;j++)
		mem[i][j] = 9;
  printf("\n Enter the replacement policy choice:");
  printf("\n \t1.FIFO \n \t2.LRU \n \t3.Second Chance");
  scanf("%d",&choice);
  FILE *fp;
  fp = fopen("ref_string.txt","r");
  if(fp==NULL){
	  perror("Error reading ref string\n");
	  exit(0);
  }
  for(i=0;i<24;i++){
	  fscanf(fp,"%d,",&ref_string[i]);
  }
  switch(choice){
	  case 1: printf("\n \t\tImplementing FIFO\n");
		  	  fifo();
	  break;
	  case 2: printf("\n \t\tImplementing LRU\n");
		  	  lru();
	  break;
	  case 3: printf("\n \t\tImplementing Second Chance\n");
			  second();
	  break;
	  default:printf("\n Invalid entry. Please enter a number in range [1,3]\n");
	  exit(0);
  }
  //displaying mem sys
  /*printf("\n Memory State \n   ");
  for(i=0;i<24;i++)
	  printf(" %d ",ref_string[i]);
  printf("\n");
  for(i=0;i<8;i++){
  	for(j=0;j<25;j++)
		printf(" %d ",mem[i][j]);
  printf("\n");	  
  }
  printf("Status \n   ");	
  for(i=0;i<24;i++)
	  printf(" %d ",fault[i]);
  */
  return 0;
}
