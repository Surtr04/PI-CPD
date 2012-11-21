#include <stdio.h>


int main (int argc, char** argv) {

		int a[2][2] = {
			{1,2},
			{2,1}
		};		
	
		int b[2][2] = {
			{3,2},
			{2,12}
		};

		int c[2][2];


		int i,j,k;

		int acc = 0; 

		for(i = 0; i < 2; i++){
			for (j = 0; j < 2; j++) {
				for(k = 0; k < 2; k++) {
					acc += a[i][k] * b[k][j];
				}
				c[i][j] = acc;
				acc = 0;
			}
		}	

		for(i = 0; i < 2; i++){
			for (j = 0; j < 2; j++) {
				printf("%d ",c[i][j]);
			}
			printf ("\n");
		}		

	return 0;

}