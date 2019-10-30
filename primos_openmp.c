#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void main(){
	int until = 100000;
	

	#pragma omp parallel for schedule(guided)

	for(int primo = 0; primo < until; primo++){

		int is_primo = 0;
		int my_rank = omp_get_thread_num();	

		for(int i = 0; i <= primo; i++){
			if(i == 0){continue;}
			if(primo % i == 0){
				is_primo += 1;
			}
		}

		if(is_primo <= 2){
			printf("[%d]: %d É Primo\n",my_rank, primo);
		}
	}
}