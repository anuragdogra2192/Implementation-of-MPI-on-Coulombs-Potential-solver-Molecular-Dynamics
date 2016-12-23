#include <cstring>
#include <iostream>
#include <cmath>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;
//DEFINING CLASS  
class Assignment
{
	private:
	int N;
	double *Fx,*Fy,*Fz,*U;
	int i,j,k;
	double *q,*x,*y,*z;
	public:
	void input_data();
	void force_calculator();
	void Energy_calculator();
};
void Assignment::input_data()
{	
	N = 1000;
	q=(double*)malloc((N)*sizeof(double));
	x=(double*)malloc((N)*sizeof(double));
	y=(double*)malloc((N)*sizeof(double));
	z=(double*)malloc((N)*sizeof(double));
	ifstream infile;//INFILE IS THE OBJECT OF ifstream class
	infile.open("input_001000.dat");//OPEN A FILE IN READ MODE ONLY 
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
	/*for(i=0;i<N;i++)
	{	
		cout<<q[i]<<" "<<x[i]<<" "<<y[i]<<" "<<z[i]<<endl;
	}*/
}
void Assignment::force_calculator()
{	
	double xij,yij,zij,rij;
	double foxij= 0,foyij= 0,fozij = 0;
	Fx=(double*)malloc((N)*sizeof(double));
	Fy=(double*)malloc((N)*sizeof(double));
	Fz=(double*)malloc((N)*sizeof(double));
	U=(double*)malloc((N)*sizeof(double));
	for(i = 0;i < N;i++)
	{	
		Fx[i]=0;
		Fy[i]=0;
		Fz[i]=0;
		U[i]=0;
	}
	for(i = 0;i < N-1;i++)
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
						
						/*Fx[j] = Fx[j] - foxij;
						Fy[j] = Fy[j] - foyij;
						Fz[j] = Fz[j] - fozij;*/
						
						U[i] = U[i] + 2*(q[j]/rij);
	
					}
				}
			}	
} 
void Assignment::Energy_calculator()
{	
	double Ec = 0;
	for(i=0;i<N;i++)
	{	
		Ec = Ec + q[i]*U[i];
	}
	Ec = Ec/2;
	cout<<"Ec "<<Ec<<endl;
}

int main()
{	
	Assignment A1;
	A1.input_data();
	A1.force_calculator();
	A1.Energy_calculator();
}
	
	 
