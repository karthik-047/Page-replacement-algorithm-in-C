#include "paging_sys.h"


//function to implement second chance algorithm
void second_chance(){
	int age[8] = {0}; //variable to store the age of the pages
	int i,j,load,hit,a,b,load_ind,max_age,age_ind,rst_age;
	for(i=0;i<8;i++)
		ref_bit[i]= -1;	
	for(i=0;i<24;i++){
		load = ref_string[i];
		//setting ref bit to 1 if alredy presesnt in cache
		if((ref_bit[load]==0)||(ref_bit[load]==1))
			ref_bit[load] = 1;
		//setting ref bit to 0 when stored in cache initially
		else if (ref_bit[load]==-1)
			ref_bit[load]++;
		//increasing the age of pages in the cache
		for(j=0;j<4;j++){
			age_ind = mem[j][i];
			age[age_ind]++;
			}
		hit = check_cache(i);
		if(hit==1){
			//page hit - do nothing
			fault[i]=1;
			for(j=0;j<8;j++)
				mem[j][i+1] = mem[j][i];
			}	
		else if(hit==2){
			//page fault - space available in cache
			fault[i] = 0;
			load_ind = load_init(i);
			for(j=1;j<=load_ind;j++){
			mem[j][i+1] = mem[j-1][i];
		}
			mem[0][i+1] = ref_string[i];
			
		}
		else if(hit==0){
			//page fault - fetching page from memory and replace oldest page with ref bit 0
			fault[i] = 0;
			max_age  = age_n_ref(age,ref_bit,i);
			rst_age = mem[max_age][i];
			age[rst_age]=0;
			for(j=0;j<8;j++)
				mem[j][i+1] = mem[j][i];		
			push_2mem(max_age,i);
			ref_bit[mem[max_age][i]]=-1;
			mem[max_age][i+1] = ref_string[i];
		}
		//printing the reference string upto the called instance
		printf("\n************************************************");
		printf("\n Reference String \n   ");
	  	for(a=0;a<=i;a++)
			printf(" %d ",ref_string[a]);
	  	//printing the memory buffer 
		printf("\n Memory State \n");
	  	for(a=0;a<8;a++){
			for(b=0;b<=(i+1);b++){
				if(mem[a][b]==9)
					printf(" - ");
				else
					printf(" %d ",mem[a][b]);
			}
			if(a==3)
				printf("\n");
	  		printf("\n");
  		}
		//printing the page fault status
		printf("Page Hit Status\n   ");
  		for(a=0;a<=i;a++)
	  		printf(" %d ",fault[a]);
	  	printf("\n************************************************\n\n");
	}
	
}


void fifo(){
	int i,j,load,hit,a,b,load_ind,max_age,age_ind,rst_age;
	int age[8] = {0};   //initializing array for storing age of pages
	for(i=0;i<24;i++){
		load = ref_string[i];
		//incrementing age of pages in cache
		for(j=0;j<4;j++){
			age_ind = mem[j][i];
			age[age_ind]++;
			}
		hit = check_cache(i);
		if(hit==1){
			//page hit - do nothing
			fault[i]=1;
			for(j=0;j<8;j++)
				mem[j][i+1] = mem[j][i];
			}
		else if(hit==2){
			//page fault - space available in cache
			fault[i] = 0;
			load_ind = load_init(i);
			for(j=1;j<=load_ind;j++){
			mem[j][i+1] = mem[j-1][i];
		}
			mem[0][i+1] = ref_string[i];
			
		}
		else if(hit==0){
			//page fault - fetching page from memory and replace oldest page
			fault[i] = 0;
			max_age = ret_max(age,i);
			rst_age = mem[max_age][i];
			age[rst_age]=0;
			for(j=0;j<8;j++)
				mem[j][i+1] = mem[j][i];	
			push_2mem(max_age,i);
			mem[max_age][i+1] = ref_string[i];
		}
		//printing the reference string upto the called instance
		printf("\n************************************************");
		printf("\n Reference String \n   ");
	  	for(a=0;a<=i;a++)
			printf(" %d ",ref_string[a]);
	  	//printing the memory buffer 
		printf("\n Memory State \n");
	  	for(a=0;a<8;a++){
			for(b=0;b<=(i+1);b++){
				if(mem[a][b]==9)
					printf(" - ");
				else
					printf(" %d ",mem[a][b]);
			}
			if(a==3)
				printf("\n");
	  		printf("\n");
  		}
		//printing the page fault status
		printf("Page Hit Status\n   ");
  		for(a=0;a<=i;a++)
	  		printf(" %d ",fault[a]);
	  	printf("\n************************************************\n\n");
	}
}
void lru(){

	int load,a,b,i=0,j=0,mem_loc, hit,hit_ind,load_ind,mem_ind;
	for(i=0;i<24;i++){
		load = ref_string[i];
		hit = check_cache(i);
		if(hit==0){
			//page fault - space available in cache
			fault[i] = 0;
			mem_loc = check_2mem(i);
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
			//page hit - update the page to the top and push the rest down by 1 index
			fault[i] = 1;
			hit_ind = hit_loc(i);
			for(j=1;j<=hit_ind;j++){
				mem[j][i+1] = mem[j-1][i];
			}
			mem[0][i+1] = ref_string[i];
			for(j=(hit_ind+1);j<8;j++)
				mem[j][i+1] = mem[j][i];
		}
		else if(hit==2){
			//page fault - fetching from memory and the rest pushed down by 1 index
			fault[i] = 0;
			load_ind = load_init(i);
			for(j=1;j<=load_ind;j++){
				mem[j][i+1] = mem[j-1][i];
			}
			mem[0][i+1] = ref_string[i];	
		}
		//printing the reference string upto the called instance
		printf("\n************************************************");
		printf("\n Reference String \n   ");
	  	for(a=0;a<=i;a++)
			printf(" %d ",ref_string[a]);
	  	//printing the memory buffer 
		printf("\n Memory State \n");
	  	for(a=0;a<8;a++){
			for(b=0;b<=(i+1);b++){
				if(mem[a][b]==9)
					printf(" - ");
				else
					printf(" %d ",mem[a][b]);
			}
			if(a==3)
				printf("\n");	
	  		printf("\n");
  		}
		//printing the page fault status
		printf("Page Hit Status\n   ");
  		for(a=0;a<=i;a++)
	  		printf(" %d ",fault[a]);
	  	printf("\n************************************************\n\n");
	}
}

int main(void) {
  int choice;
  int i,j;
  //reading the page calls from txt file
  FILE *fp;
  fp = fopen("ref_string.txt","r");
  if(fp==NULL){
	  perror("Error reading ref string\n");
	  exit(0);
  }
  for(i=0;i<24;i++){
	  fscanf(fp,"%d,",&ref_string[i]);
  }
  while(1){
  //assigning initial value to memory buffer
	  for(i=0;i<8;i++)
	  	for(j=0;j<25;j++)
			mem[i][j] = 9;
	  //Getting user choice for the policy to be implemented
	  printf("\n Enter the replacement policy choice:");
	  printf("\n \t1.FIFO \n \t2.LRU \n \t3.Second Chance\n \t4.Exit\n \t");
	  scanf("%d",&choice);
	  switch(choice){
		  case 1: printf("\n \t\tImplementing FIFO\n");
			  	  fifo();
		  break;
		  case 2: printf("\n \t\tImplementing LRU\n");
			  	  lru();
		  break;
		  case 3: printf("\n \t\tImplementing Second Chance\n");
				  second_chance();
		  break;
		  case 4: printf("\n \t\tExiting...\n");
		  		  exit(0);
		  break;
		  default: printf("\n Invalid entry. Please enter a number in range [1,4]\n");
	  }
  }
  return 0;
}
