#include <cstring>
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <mpi.h>

using namespace std;
//DEFINING CLASS  
class Assignment
{
	private:
	int N;
	double *Fx,*Fy,*Fz,*U,*Fxsum,*Fysum,*Fzsum;
	int i,j,k;
	int rank,size,t,start,end;
	double *q,*x,*y,*z;
	public:
	void input_data();
	void force_calculator(int,int);
	void Energy_calculator();
	void output();
};
void Assignment::input_data()
{	
	N = 114537;
	q=(double*)malloc((N)*sizeof(double));
	x=(double*)malloc((N)*sizeof(double));
	y=(double*)malloc((N)*sizeof(double));
	z=(double*)malloc((N)*sizeof(double));
	ifstream infile;//INFILE IS THE OBJECT OF ifstream class
	infile.open("input_114537.dat");//OPEN A FILE IN READ MODE ONLY 
        //ERROR CHECK IF THERE IS PROBLEM IN OPENING A FILE 
	if (infile.fail())
	{
		cerr<<"Error in opening file"<<endl;//FOR SHOWING ERROR MESSAGE IN OPENING FILE IN TERMINAL 
		exit(1);
	} 
	for(i=0;i<N;i++)
	{	
		infile>>q[i]>>x[i]>>y[i]>>z[i];
	}
	infile.close();
	/*for(i=0;i<N;i++)
	{	
		cout<<q[i]<<" "<<x[i]<<" "<<y[i]<<" "<<z[i]<<endl;
	}*/
}
void Assignment::force_calculator(int r,int s)
{	
	rank = r,size = s;
	double xij,yij,zij,rij;
	double foxij= 0,foyij= 0,fozij = 0;
	Fx=(double*)malloc((N)*sizeof(double));
	Fy=(double*)malloc((N)*sizeof(double));
	Fz=(double*)malloc((N)*sizeof(double));
	U=(double*)malloc((N)*sizeof(double));
	t = N/size;
	start = rank*t;
	end = ((rank+1)*t)-1;
	if(rank==size-1); 
	for(i = 0;i < N;i++)
	{	
		Fx[i]=0;
		Fy[i]=0;
		Fz[i]=0;
		U[i]=0;
	}
	for(i = start;i<=end;i++)
			{	//Anurag Dogra
				for(j=i;j<N;j++)
				{	 	
					if(i!=j)   
					{	
						xij = x[i] - x[j];
						yij = y[i] - y[j];
						zij = z[i] - z[j];
						
						//Distance calculation
						rij = sqrt((xij*xij)+(yij*yij)+(zij*zij));

						foxij = foxij + ((q[i]*q[j]*xij)/(rij*rij*rij));
						foyij = foyij + ((q[i]*q[j]*yij)/(rij*rij*rij));
						fozij = fozij + ((q[i]*q[j]*zij)/(rij*rij*rij));
						
						Fx[i] = Fx[i] + foxij;
						Fy[i] = Fy[i] + foyij;
						Fz[i] = Fz[i] + fozij;
						
						Fx[j] = Fx[j] - foxij;
						Fy[j] = Fy[j] - foyij;
						Fz[j] = Fz[j] - fozij;
						
						U[i] = U[i] + 2*(q[j]/rij);
	
					}
				}
			}
	if (rank==0)
	{
		Fxsum=(double*)malloc((N)*sizeof(double));
        	Fysum=(double*)malloc((N)*sizeof(double));
        	Fzsum=(double*)malloc((N)*sizeof(double));
		for(i = 0;i < N;i++)
        	{
                	Fxsum[i]=0;
                	Fysum[i]=0;
                	Fzsum[i]=0;
        	}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(Fx,Fxsum,N,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(Fy,Fysum,N,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(Fz,Fzsum,N,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);	
} 
void Assignment::Energy_calculator()
{	
	double Ec = 0;
	for(i=0;i<N;i++)
	{	
		Ec = Ec + q[i]*U[i];
	}
	double sum_Ec;
	Ec = Ec/2;
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Reduce(&Ec,&sum_Ec,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank==0)
	{	
		cout<<"Ec "<<sum_Ec<<endl;
	}
}
void Assignment::output()
{
	if(rank==0)
	{
		ofstream foutput("forces.out");
		foutput<<"Force Fx  "<<"Force Fy  "<<"Force Fz  \n";
		for(i=0;i<N;i++)
		{	
			foutput<<Fxsum[i]<<" "<<Fysum[i]<<" "<<Fzsum[i]<<endl;
			//cout<<Fxsum[i]<<" "<<Fysum[i]<<" "<<Fzsum[i]<<endl;
			
		}
		
	}
}
int main(int argc,char **argv)
{	
	MPI_Init(&argc, &argv);
	int rank,size;
	Assignment A1;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
        MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	double starttime, endtime;
       	starttime = MPI_Wtime();
	A1.input_data();
	A1.force_calculator(rank,size);
	A1.Energy_calculator();
	A1.output();
	MPI_Barrier(MPI_COMM_WORLD);
	endtime   = MPI_Wtime();
	if(rank==0)
	{	
		cout<<"Time \n "<<endtime-starttime;
	}
	MPI_Finalize();
        return 0;
}	 
