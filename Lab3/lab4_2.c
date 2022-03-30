#include<stdio.h>

void fifo(int list [], int block [], int list_size, int block_size){
	int i,j,k,z,temp;
	int count = 0;
	for(i=0;i<list_size;i++){
		for(j=0;j<block_size;j++){
			if(list[i]==block[j]){
				break;
			}
		}
		if(j==block_size){
			temp=list[i];
			for(k=0;k<block_size-1;k++){
				block[k]=block[k+1];		
			}
			block[k]=temp;
			count++;
		}
		printf("\tNO.%d\t",i+1);
		for(z=block_size-1;z>=0;z--){	
			printf("%d\t",block[z]);
		}
		printf("\n");
	}
	printf("Page-faults:%d",count);
}

int search(int list[],int size_list, int i, int k){
	int cache = 0;
	while(i<size_list){
		if(list[i]==k){
			cache = i;
			break;
		}
		else if(cache==0&&i==size_list-1){cache = size_list;}
		i++;
	}
	return cache;
}

void OPT(int list[], int block[],int size_list,int size_block){
	int storage[size_block][2];
	for(int a=0;a<size_block;a++){
			storage[a][0]=block[a];
			storage[a][1]=0;
		}
	
	int i,j,k,z;
	int index_max = 0;
	int count=0;
	for(i=0;i<size_list;i++){
		for(j=0;j<size_block;j++){
			if(list[i]==storage[j][0]){
				break;
			}
		}
		if(j==size_block){
			count++; 
			k = i+1;
			for(int b=0;b<size_block;b++){
				storage[b][1]=search(list,size_list,k,storage[b][0]);
			}
			for(int c=0;c<size_block;c++){
				if(storage[c][1]>storage[index_max][1]){index_max=c;}
			}
			storage[index_max][0] = list[i];
			for(int d=0;d<size_block;d++){
				storage[d][1]=0;
			}
		}
		printf("\tNo.%d\t",i+1);
		for(z=0;z<size_block;z++){	
			printf("%d\t",storage[z][0]);
		}
		if((i-1)%2==0){
			printf("\n");
		} 
	}
	printf("Page-faults:%d",count); 
}

void LRU(int list [], int block [], int list_size, int block_size){
	int i,j,k,z,temp;
	int count = 0;
	int least_used = -1;
	int medium_used = -1;
	int recent_used = -1;
	for(i=0;i<list_size;i++){
		for(j=0;j<block_size;j++){
			if(list[i]==block[j]){
				if(least_used==list[i]){
					least_used = medium_used;
					medium_used = recent_used;
					recent_used = list[i];
				} else if (medium_used == list[i]){
					medium_used = recent_used;
					recent_used = list[i];
				}
				break;
			}
		}
		if(j==block_size){
			for(int z = 0; z <block_size; z++){
				if(block[z]==least_used){
					block[z]= list[i];
					break;
				}
			}
			least_used = medium_used;
			medium_used = recent_used;
			recent_used = list[i];
			count++;
		}

		printf("\tNO.%d\t",i+1);
		for(z = 0; z < block_size ; z++){	
			printf("%d\t",block[z]);
		}
		printf("\n");
	}
	printf("Page-faults:%d",count);
}

int main(){
	int N,M;
	int pages[20];
	int temp;
	FILE *p1 = fopen("sample.dat","r");
	fscanf(p1,"%d",&N);
	fscanf(p1, "%d", &M);
	for(int i = 0; i<20; i++){
		fscanf(p1,"%d",&temp);
		pages[i] = temp;
		if(temp == -1) break;
  	}

	//int a[20] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
	int frame[M];
	for(int i=0;i<M;i++){
		frame[i]=-1;
	}
	int list_size = sizeof(pages)/sizeof(pages[1]);
	int block_size = sizeof(frame)/sizeof(frame[1]);
	// fifo(pages,frame,list_size,block_size);
	// printf("\n");
	OPT(pages,frame,list_size,block_size);
	printf("\n");
	// LRU(pages,frame,list_size,block_size);
	// printf("\n");

	
	return 0;
}

