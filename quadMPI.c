#include<stdio.h>
#include<mpi.h>

double func(double);
double approximateArea();

int main(void){
    const int REPEAT = 25;

    double tStart;
    double tEnd;
	
    int count = 0;
    for(count; count < REPEAT; count++){
		
	
    	tStart = MPI_Wtime();
    	//integrationPTP(commSz, myRank);
		tEnd = MPI_Wtime();

		
		printf("COUNT = %d\n", count);
		printf("Time taken = %f milliseconds\n", 1000.0*(tEnd - tStart));	//print wallTimeTaken

	}
}

double approximateArea(){
	const double a=0.0, b=200.0;
	const int  quads = 100;
	double const width = (b-a) / (double) quads;
	
	//if(myRank == commSz - 1){	//final rank leaving this here for ease
	//	quadsPerRank = quads - (quadsPerRank*myRank);
	//}
	
	int startIter = 0;
	int endIter = quads;
	
	double x, y;
    
	double sum;
	int i;
    for(i = startIter; i <= endIter; i++){
		x = a + i * width;
		y = x + width;
		sum += 0.5*width*(func(x) + func(y));
    }
	return sum;
}

