#include<stdio.h>
#include <math.h>
#include <string.h>

struct Cache {
	int hits;
	int misses;
	int reads;
	int writes;
	int cache_size;
	int block_size;
	int numLines;
	int writepolicy;
};

int main(int arg, char *argv[]){
	FILE *file;
	if(arg != 7){
		printf("error\n");
		return 0;
		}
	else{
		file = fopen(argv[6], "r");
	}
	if(file == 0){
		printf("error\n");
		return 0;
	}
	double cachesize  = atoi(argv[1]);
	char *associ = argv[2];
	int blocksize = atoi(argv[3]);
	char *replace = argv[4];
	char *write = argv[5];
	char line[256];
	int tagbit;
	int setbit;
	

	 long long blockoff = log2(blocksize);
	
	char hex[11];
	char wr;
	int i;
	int rp;
	int wp;
    while (fgets(line, sizeof(line), file)) {
	wr = line[11];
	i = 0;
	for(i ; i <10;i++){
	hex[i] = line[i+13];
	
	}
	hex[10] = '\0'; 

    }
	if(strcmp(replace,"FIFO") != 0 && strcmp(replace,"LRU") != 0){
		printf("error\n");
		return 0;
	}
	if(strcmp(write,"wb") != 0 && strcmp(write,"wt") != 0){
                printf("error\n");
                return 0;
        }
	 if(strcmp(replace,"FIFO") == 0){
                rp = 1;
        }
	else{
		rp = 0;
	}
        if(strcmp(write,"wb") == 0){
                wp = 1;
        }
	else{
		wp = 0;
	}

	
	long long ip;
	char bol = 'f';
	long long tag;
	long long  bbit; //block bits
	long long sbit; //set bits
	long long setindex;
	int miss = 0;
	int hit = 0;
	int writecount = 0;
	int read = 0;
	file = fopen(argv[6], "r");
	if(strcmp(associ,"direct") == 0){
		long long bitcomp = pow(2,blockoff+1); // made for bitwise comparison
                bitcomp = bitcomp-1; // to make it all 111111
		long long numsets = cachesize / blocksize;
		setindex = log2(numsets);
		long long setcomp = pow(2,setindex);
		setcomp = setcomp - 1;
		
		int wbcheck[numsets];	
		long long cash[numsets];
		int o = 0;
		int z = 0;
		
		
		for(o= 0; o < numsets;o++){
			
				
			cash[o] = 123456789;
		
	
		}
		
		for(o = 0; o < numsets;o++){
			wbcheck[o] = 0;
		}
		
	
		while (fgets(line, sizeof(line), file)) {
			if(line[0] == '#'){
			
			}
		else{
			
       			wr = line[11];
        		i = 0;
        		for(i ; i <8;i++){
        		hex[i] = line[i+15];
		
		        }
		        hex[8] = '\0';
			long long address = (long long)strtol(hex, NULL,16);
			
			bbit = address & bitcomp;
			sbit = (address >> blockoff) & setcomp;
			tag = address >> (setindex + blockoff);
	
		
		if(wr == 'W'){
			
			if(cash[sbit] == tag){
				hit++;
				wbcheck[sbit] = 1;
				if(wp == 0){
					writecount++;
				
				}
			}
			else{
				miss++;
				if(wp == 1 && (cash[sbit] != 123456789) && wbcheck[sbit] == 1){
					writecount++;
				}
				else if(wp == 0){
					writecount++;
				}
				read++;
				cash[sbit] = tag;
				
			}
				
		}
		else{
			if(cash[sbit] == tag){
				hit++;
			}
			else{
				miss++;
				if(wp == 1 && (cash[sbit] != 123456789) && wbcheck[sbit] <= 1 ){
					writecount = writecount + wbcheck[sbit];
				}
				read++;
				cash[sbit] = tag;
				wbcheck[sbit] = 0;
			}
			
	

		}
		}	
   		}

	}
	else if(strstr(associ,"assoc") != NULL){
		int i;
		long long bitcomp = pow(2,blockoff+2); // made for bitwise comparison
                bitcomp = bitcomp-1; // to make it all 111111
                long long numsets = cachesize / blocksize;
                long long cash[numsets];
		long long temp2;
                int o;
                int z;
		int counter = 0;
		long long tempy;
		int writecheck[numsets];
                for(o= 0; o < numsets;o++){
                        

                                cash[o] = -1;
                        
                }
		o = 0;
		int sort[numsets];
		for(o; o < numsets; o++){
			sort[o] = 0;
		}
		
		int fifocount = 0;
		
		while (fgets(line, sizeof(line), file)) {
                        if(line[0] == '#'){

                        }
                else{
                        wr = line[11];
                        i = 0;
			if(strlen(line) ==  23){	
                        for(i ; i <8;i++){
                        hex[i] = line[i+15];
			
                        }
			
                        hex[7] = '\0';
			
			}
			else{ 
				for(i ; i <9;i++){
                        hex[i] = line[i+15];

                        }
           
                        hex[8] = '\0';
			
	
	

			}
			
			long long address;
			sscanf(hex, "%x", &address);
                      
			
			
                        bbit = address & bitcomp;
                        tag = address >> (blockoff);
			
			
			bol = 'f';
                        
                      
                if(wr == 'W'){
			if(wp == 0){
				writecount++;
			}
			int e = 0;
			while( e < numsets && bol == 'f'){
				if(cash[e] == tag){
					bol = 't';
				}else{
		
				e++;
				}
			}
			if(bol == 'f'){
				miss++;
				read++;
				e = 0;
				while( e < numsets && bol == 'f'){
	                                if(cash[e] == -1){
        	                                bol = 't';
        	                        }
					else{
					e++;
					}
                       		}
				if( bol == 'f'){
					if(rp == 1 ){
					
						cash[fifocount] = tag;
						
						if(wp == 1 && writecheck[fifocount] == 1){
							writecount++;
						}
						writecheck[fifocount] = 0;
						fifocount++;
                                                if(fifocount == numsets){
                                                        fifocount = 0;
                                                }

						
						
					}
					else{ // LRU
						int lowest = sort[0];
						i = 0;
                                               	int lowestindex = 0;
						for(i; i < numsets; i++){
							if(sort[i] < lowest){
								lowestindex = i;
								lowest = sort[i];
							}
						}
                                                cash[lowestindex] = tag;
						counter++;
						sort[lowestindex] = counter;
                                                if(wp == 1 && writecheck[lowestindex] == 1){
                                                        writecount++;
                                                }
                                                writecheck[lowestindex] = 0;
                                                
						

						
					}
				}
				else{
					if(rp == 0){
						
						i = 0;
                                                counter++;
						sort[e] = counter;

					}
					cash[e] = tag;
				}
	
			}
			else{
				if(rp == 0){
				
					counter++;
					sort[e] = counter;
					
				}
				hit++;
				writecheck[e] = 1;
			}
    		}
		else{
			int e = 0;
                        while( e < numsets && bol == 'f'){
                                if(cash[e] == tag){
                                        bol = 't';
                                }
				else{
				e++;
				}
                        }
			if(bol == 'f'){
				 miss++;
                                read++;
                                e = 0;
                                while( e < numsets && bol == 'f'){
                                        if(cash[e] == -1){
                                                bol = 't';
                                        }
					else{
					e++;
					}
                                }
                                if( bol == 'f'){
                                        if(rp == 1){
						
                                                cash[fifocount] = tag;
						if(wp == 1 && writecheck[fifocount] == 1){
                                                writecount++;
						}
						writecheck[fifocount] = 0;
						fifocount++;
                                                if(fifocount == numsets){
                                                        fifocount = 0;
                                                }


                                        }
                                        else{ // LRU
						
						i = 0;
						int lowest = sort[0];
                                                i = 0;
                                                int lowestindex = 0;
                                                for(i; i < numsets; i++){
                                                        if(sort[i] < lowest){
                                                                lowestindex = i;
                                                                lowest = sort[i];
                                                        }
                                                }
                                                cash[lowestindex] = tag;
                                                counter++;
                                                sort[lowestindex] = counter;

						if(wp == 1 && writecheck[lowestindex] == 1){
							writecount++;
						}
						writecheck[lowestindex] = 0;
						i = 0;
				
		
						
                                        }
		
	
				}
				else{
					if(rp == 0){
						
                                                i = 0;
						counter++;
						sort[e] = counter;
                                        }

					cash[e] = tag;
				}
			}
			else{
				
				if(rp == 0){
                                        i = 0;
                                       	counter++;
					sort[e] = counter;

                                }

				hit++;
			}
		}
	}	
        }
	} 
	else{
		printf("error\n");
		return 0;
		
		int setasoc;
		long long bitcomp = pow(2,blockoff+1); // made for bitwise comparison
                bitcomp = bitcomp-1; // to make it all 111111
                int o;
		char *p = associ;
		while (*p) {
			if(isdigit(*p)){
				setasoc = strtol(p, &p, 10);
				
			}
			else{
				p++;
			}
		}
		int count = 0;	
                int z;
		int dif = 1;
		long long arr[100];
		arr[0] = tag;
		long long numsets = ((cachesize /  setasoc)/ blocksize);
		long long cash[numsets][setasoc];
		setindex = log2(numsets);
                long long setcomp = pow(2,setindex);
                setcomp = setcomp - 1;
		int fifocount[numsets];
		
			
		int writecheck[numsets][setasoc];
		o = 0;	
		for(o; o < numsets; o++){
			fifocount[o] = 0;
		}
		int q;
		int d;
		for(q=0; q< numsets; q++){
			for(d = 0; d < setasoc; d++){
				cash[q][d] = -1;
			}
		}
		while (fgets(line, sizeof(line), file)) {
                        if(line[0] == '#'){

                        }
                else{
                        wr = line[11];
                        i = 0;
		
			
                      	i = 0;
                        for(i ; i <8;i++){
                        hex[i] = line[i+15];

                        }
                        hex[8] = '\0';
                        long long address = (long long)strtol(hex, NULL,16);


                        bbit = address & bitcomp;
                        sbit = (address >> blockoff) & setcomp;
                        tag = address >> (setindex + blockoff);
			bol = 'f';
				
                     
                        
			
                        if(wr == 'W'){
				d = 0;
				
				while( d < setasoc && bol == 'f'){
					if(cash[sbit][d] == tag){
						bol = 't';
						
					}
					else{
						
						d++;
					}
				}
				if(bol == 'f'){
					
					miss++;
					read++;
					d = 0;
					while( d < setasoc && bol == 'f'){
						if(cash[sbit][d] == -1){
							bol = 't';
						}
						else{
							d++;
						}
					}
					if(bol == 'f'){
						writecount++;
						if(rp == 1 ){ // FIFO change
							
							int ghost = fifocount[sbit];	
							cash[sbit][ghost] = tag;
							fifocount[sbit]++;
							if(fifocount[sbit] == setasoc){
								fifocount[sbit] = 0;
							}	
						}
						else{   //LRU
						}
					}
					else{
						
						cash[sbit][d] = tag;
						if(wp == 0){
						   writecount++;
						}
					}
					
				}
				else{
					hit++;
					if(wp == 0){
					writecount++;
					}
				
				}
				

		}
		else{
		

			
			d = 0;
                        while( d < setasoc && bol == 'f'){
                              if(cash[sbit][d] == tag){
                                  bol = 't';
	                         }
                              else{
                                    d++;
                                }
                       }
			
			if(bol == 'f'){
				
				miss++;
				read++;		
				
				
				d = 0;
				while( d < setasoc && bol == 'f'){
					if(cash[sbit][d] == -1){
						bol = 't';
					}
					else{
						d++;
					}
				}
				
				if(bol == 'f'){
					if(rp == 1){
					
						int te = fifocount[sbit];
						
						cash[sbit][te] = tag;
						if(wp == 1){
						writecount++;
						}
						
						fifocount[sbit]++;
						if(fifocount[sbit] == setasoc){
						fifocount[sbit] = 0;
						}


					}
				}
				else{
					cash[d][sbit] = tag;
					
				}
			}
			else{
			
			hit++;
			}

			
			




		


		}
				
	}
}
	}
	
	fclose(file);
	printf("Memory reads: %d\n",read);
	printf("Memory writes: %d\n", writecount);
	printf("Cache hits: %d\n", hit);
	printf("Cache misses: %d\n", miss);
	return 0; 


}


