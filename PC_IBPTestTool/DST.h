#ifndef _DST_H_
#define _DST_H_

#define channelMAX 15

typedef struct channel_fir
{
    
	double ydata[315];//保存每通道的数据
	int xdata[315];

}channel_fir;//310阶FIR滤波器通道数据

typedef struct
{
	int xdata[250];

	int flag;//初始化用
	int ptr;
	long sum;
}channel_Med;//中值滤波保存数据用

typedef struct
{
	double xdata[250];
	int flag;//初始化用
	int ptr;
	double sum;
    double sum_sq; // 数据平方之和   
}channel_STD;//标准差保存数据用

#define MAXDATALEN 250
#define MAXORDER 80
#define MAXOR1 MAXORDER+1
#define MAXLEN MAXDATALEN+1

#define DealDataLen 250





double BubbleSort(double *ListData,int row); 
void Matrix_M1_Multiplication(double*Matrix,double*OutputMatrix,int row,float Coff);
void Matrix_M1_Addition(double*Matrix1,double*Matrix2,double*OutputMatrix,int row,BOOL flag);
void Matrix_MN_Initialization(double Matrix1[][MAXLEN],double Vlaue,int row,int col);




double FindMaxValue(double ListData[],int row);
void DataNrom(double RedData[],double IRData[],int row);  
double Datamean(double ListData[],int row); 
void Matrix_M1_Assign(double Matrix1[],double Matrix2[],int row);
void Matrix_M1_Initialization(double Matrix1[],double Vlaue,int row);
int AdaptiveLsLfilter(int*RedData,int*IrData,int DataLen,int N,double lmda,int Range[2]);

float filter_fir_highpass0_5Hz_250(float x, int num);
float filter_fir_lowpass5Hz_250(float x, int num);

int FliterMed(float x,int Integnum,int chan_num);
float FliterSTD(double x,int Integnum,int chan_num);

void rls_optimized(double *x, double *d, double *w, double *P, double lambda, double delta, int M, int n, double *en) ;

#endif