#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_multifit_nlin.h>

#include <critfunc.h>

//color terminal
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KBLU  "\x1B[34m"

//main function
int main (int argc, char* argv[]){
//==================varaibles
FILE *infile;
struct points data;
int i,j,k;
const gsl_multifit_fdfsolver_type* T;	//
gsl_multifit_fdfsolver* s;	//solver
gsl_multifit_function_fdf f;	//function
int status;
size_t n;	//points number
size_t p=5;	//parameters number


printf("%s Find parameters %s \n",KBLU,KNRM);
//need 2 parameters
if(argc<2){
	printf("\t %s  Usage critprop <points> <func set> %s\n",KRED,KNRM);
	return 1;
}
/*if(argv[2]=="1"){*/
/*	p=(size_t)5;	//A,B0,B1,Tc,roc*/
/*}*/
//get numbers of lines
infile=fopen(argv[1],"r");
if (infile==0){
	printf("%s  %s file open error %s \n",KRED,argv[1],KNRM);
	return 1;
}
fscanf(infile,"%d",&data.n);
//read points
printf("/t rol /t rov /t T\n");
for(i=0;i<data.n;i++){
	data.rol=(float*)calloc(data.n,sizeof(float));
	data.rov=(float*)calloc(data.n,sizeof(float));
	data.t=(float*)calloc(data.n,sizeof(float));
	fscanf(infile,"%f%f%f\n",&data.rol[i],&data.rov[i],&data.t[i]);
	printf("%f %f %f \n",data.rol[i],data.rov[i],data.t[i]);
}
fclose(infile);
n=(size_t)(data.n*2);
p=(size_t)5;
//
gsl_matrix* covar=gsl_matrix_alloc(p,p);
T=gsl_multifit_fdfsolver_lmsder;
s=gsl_multifit_fdfsolver_alloc(T,n,p);
//gsl_multifit_fdfsolver_set (s,&f,&x.vector);


free(data.rol);
free(data.rov);
free(data.t);
return 0;
}
