
#include "stdafx.h"
#include "DST.h"
#include "math.h"


double err_b[MAXOR1][MAXLEN];
double err_f[MAXOR1][MAXLEN];

double  delta[MAXOR1][MAXLEN];
double  epson_f[MAXOR1][MAXLEN];
double  epson_b[MAXOR1][MAXLEN];
double  rou_a[MAXOR1][MAXLEN];   //中间变量
double gamma[MAXOR1][MAXLEN];  
double s[MAXOR1][MAXLEN];    //自适应滤波器误差信号   (N1*DataLen  矩阵)

double Output[MAXLEN];   //自适应滤波器输出
double Power[100];   //DST功率

double Reddata[MAXLEN];
double Irdata[MAXLEN];



double  Temp1[MAXLEN];
double  Temp2[MAXLEN];

double x[MAXLEN];     //输入信号
double d[MAXLEN];     //期望信号





 /*double gRtable[100]={0.00 , 0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00,
	  0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 
	  0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.00, 	0.56,
	  0.57, 	0.57, 	0.57, 	0.58, 	0.58, 	0.59, 	0.59, 	0.59, 	0.60, 	0.60,
	  0.61, 	0.61, 	0.62, 	0.62, 	0.63, 	0.64, 	0.64, 	0.65, 	0.66, 	0.66,
	  0.67, 	0.68, 	0.69, 	0.70, 	0.70, 	0.71, 	0.72, 	0.73, 	0.73, 	0.75, 	
	  0.75, 	0.76, 	0.77, 	0.78, 	0.79, 	0.80, 	0.81, 	0.82, 	0.82, 	0.84,
	  0.84, 	0.86, 	0.87, 	0.88, 	0.89, 	0.91, 	0.93, 	0.94, 	0.96, 	0.98, 	
	  1.00, 	1.02, 	1.05, 	1.07, 	1.09, 	1.13, 	1.14, 	1.18, 	1.21, 	1.25, 	
	  1.30, 	1.34, 	1.40, 	1.46, 	1.53, 	1.61, 	1.68, 	1.78, 	1.89, 	2.06 
  };*/
double gRtable[100]={
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0.574218750000000,0.578125000000000,0.585937500000000,0.589843750000000,
	0.597656250000000,0.601562500000000,0.605468750000000,0.617187500000000,0.625000000000000,
	0.632812500000000,0.636718750000000,0.644531250000000,0.656250000000000,0.664062500000000,
	0.675781250000000,0.687500000000000,0.703125000000000,0.718750000000000,0.734375000000000,
	0.750000000000000,0.761718750000000,0.777343750000000,0.792968750000000,0.804687500000000,
	0.820312500000000,0.835937500000000,0.851562500000000,0.867187500000000,0.886718750000000,
	0.906250000000000,0.925781250000000,0.945312500000000,0.964843750000000,0.988281250000000,
	1.01171875000000,1.03906250000000,1.06640625000000,1.09765625000000,1.12890625000000,1.15625000000000,
	1.20312500000000,1.25000000000000,1.29296875000000,1.33984375000000,1.39062500000000,1.44531250000000,
	1.51171875000000,1.58593750000000,1.67578125000000,1.80468750000000,1.99609375000000,2.34375000000000,
};





 /***************************************************************************
    //从小到大进行排序,冒泡排序法
 输入：
 ListData   输入输出序列
 row 是数据长度
返回值 med 是中值
				 

 ****************************************************************************/

double BubbleSort(double *ListData,int row)   
{  

	int j,k;
	double temp=0; 
	double med=0;



		for (j=0;j<=row-2;j++){
			for (k=0;k<=row-j-2;k++){
				if (ListData[k]>ListData[k+1]){

                    temp=ListData[k];
					ListData[k]=ListData[k+1];
		   		    ListData[k+1]=temp;

				}
			}
		}


    if (row%2==0)  
	{
        int temp1=row/2;	
		med=(ListData[temp1]+ListData[temp1-1])/2;
		med=med;
	}
	else
	{
	 int temp1=row/2;	
	 med=ListData[temp1];
	}

  return med;
}



 /***************************************************************************
    //求 数组的均值 
 输入：
 ListData   输入输出序列
 row 是数据长度
返回值 Average 是中值
				 

 ****************************************************************************/

double Datamean(double ListData[],int row)   
{  

	int j;
	double Average=0; 
	double Temp;

		for (j=0;j<=row;j++){
              Temp=(100*ListData[j])/row;
              Average=Average+Temp/100;
		}



  return Average;
}

 /***************************************************************************
      求数组中的最大值
 输入：
 ListData   输入输出序列
 row 是数据长度
返回值 MaxValue 是中值
				 

 ****************************************************************************/

 double FindMaxValue(double ListData[],int row)
 {
   
	 double MaxValue=ListData[0];
	 for (int i=0;i<row;i++){
		 if  (MaxValue<ListData[i]){
            MaxValue=ListData[i];
		 }
	 }
 
	 return MaxValue;
 }


 /***************************************************************************
    数据归一化,归一化后数据范围[0 1]
	RedData   是红光信号
    IRData 是红外光信号
	row 是数据长度
				
 ****************************************************************************/
void DataNrom(double RedData[],double IRData[],int row)   
{  
 
   int i;

  double Mred=Datamean(RedData,row);  //均值
  double MIr=Datamean(IRData,row);

  double dcr=MIr/Mred;   //红外/红光

   for (i=0;i<row;i++){      //红光、红外减均值
	  RedData[i]=(RedData[i]-Mred)*dcr;
	  IRData[i]=IRData[i]-MIr;

	  Temp1[i]=fabs(RedData[i]);
	  Temp2[i]= fabs(IRData[i]);
  }

   double max1=FindMaxValue(Temp1,row);
   double max2=FindMaxValue(Temp2,row);

   double max3=max1;    //max1 max2中的最大值
   if (max3<max2){
	   max3=max2;
   }
  
     
    for (i=0;i<row;i++){      
	  RedData[i]=RedData[i]/max3;
	  IRData[i]=IRData[i]/max3;
  }

	//delete[] Temp1;
	//delete[] Temp2;


}



double FilterReddataDST[250];
double FilterIrdataDST[250];
double tempSTDRed;
double tempSTDIr;
 /***************************************************************************
    自适应LSL滤波
	RedData   是红光信号
    IRData 是红外光信号
	DataLen 是信号长度
    
	N是滤波器阶数
	lmda 是滤波器加权系数，一般取0.97


	Range[2] 是一个包含了两个元素的数组，它表示的是自适应滤波计算血氧时取的范围，建议[51 100]
				
 ****************************************************************************/
int AdaptiveLsLfilter(int*RedData,int*IrData,int DataLen,int N,double lmda,int Range[2])
{
   

	
	float currentStdRed = 0.0f;
   float currentStdIr = 0.0f;
	
	for (int i=0;i<DataLen;i++){
        Reddata[i]=(double)(RedData[i]);
		Irdata[i]=(double)(IrData[i]);    //将int型转化为double型
		//分开高低通处理
		//中值滤波
		  FilterReddataDST[i] = FliterMed(Reddata[i],3,3);
		  FilterIrdataDST[i] = FliterMed(Irdata[i],3,4);

		  //低通滤波
		  FilterReddataDST[i] = filter_fir_lowpass5Hz_250(FilterReddataDST[i],3);
		  FilterIrdataDST[i] = filter_fir_lowpass5Hz_250(FilterIrdataDST[i],4);
		  //高通滤波
		  FilterReddataDST[i] = filter_fir_highpass0_5Hz_250(FilterReddataDST[i],3);
		  FilterIrdataDST[i] = filter_fir_highpass0_5Hz_250(FilterIrdataDST[i],4);
		  //标准差计算
	      currentStdRed = FliterSTD(FilterReddataDST[i],250, 3); // 通道1
          currentStdIr = FliterSTD(FilterIrdataDST[i],250, 4);   // 通道2
		  
	}
	 tempSTDRed = currentStdRed /1000.f;
		   tempSTDIr =  currentStdIr/1000.f;
	for (int j=0;j<250;j++)
	   {
		   //归一化
          Reddata[j]=(float)10000.f*(FilterReddataDST[j]/(float)tempSTDRed);
		  Irdata[j]=(float)10000.f*(FilterIrdataDST[j]/(float)tempSTDIr );
	}
	double** RS_test_all = (double**)malloc(250 * sizeof(double*));
    for (int j = 0; j < 250; j++) {
        RS_test_all[j] = (double*)malloc(100 * sizeof(double));
    }
	for (int col = 0; col < 100; col++) {         // 100列 
            for (int row = 0; row < 250; row++) {      // 250行
                // RS_test = red_mean - R_ref' .* ir_mean
                RS_test_all[row][col] = Reddata[row]/10000.f - gRtable[col] * Irdata[row]/10000.f;
				double temp = Reddata[row] - gRtable[col] * Irdata[row];
            }
        }
	//对参考信号进行自适应滤波

	int n = 250;   // 信号长度
    int M = 10;     // 滤波器阶数
    double lambda = 0.99; // 初始遗忘因子
    double delta = 0.001; // 正则化参数

    // 分配内存
    double *x = (double *)malloc(n * sizeof(double));
    double *d = (double *)malloc(n * sizeof(double));
    double *w = (double *)malloc(M * sizeof(double));
    double *P = (double *)malloc(M * M * sizeof(double));
    double *en = (double *)malloc(n * sizeof(double)); // 误差序列
	 double *power =(double *)malloc(100 * sizeof(double));

	for(int i = 0;i<100;i++)
	{
		power[i] = 0;
	}
    // 初始化权重向量 w 为零向量
    for (int i = 0; i < M; i++) {
        w[i] = 0.0;
    }

    // 初始化协方差矩阵 P 为单位矩阵
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            P[i * M + j] = (i == j) ? 1.0 : 0.0;
        }
    }

	double *x_column = (double *)malloc(250 * sizeof(double));
	double *y_column = (double *)malloc(250 * sizeof(double));

    for (int col = 0; col < 100; col++) {
    // 提取当前列数据
    for (int row = 0; row < 250; row++) {
		
        x_column[row] = RS_test_all[row][col];
		y_column[row] = Reddata[row]/10000.f;
		double temp2 = RS_test_all[row][col];
		
    }
	
	// 执行RLS算法
       rls_optimized( x_column, y_column, w, P, lambda, delta, M, n, en);
	   double temppower = 0;
    // 计算平方和
   for(int k = 0;k<250;k++)
   {
        (double)temppower = (double)((double)en[k]* (double)en[k])+temppower;
		
   }
		
         (double)power[col] =  (double)temppower;    
		
	}
	double Max=power[0];
  	int MaxPos=0;
	int oldMaxPos=100;
 	for (int i=0;i<100;i++){
		if (Max<power[i]){
           Max=power[i];
		   MaxPos=i+1;   
		}
	}
	int diffPos = abs(MaxPos-oldMaxPos);
	if (MaxPos < 60) {
    MaxPos = oldMaxPos; // 使用上一次保存的有效位置
    }
	else {
    oldMaxPos = MaxPos; // 更新有效位置（仅当位置>=60时更新）
    }
	 


	return MaxPos;

	//DataNrom(Reddata,Irdata,DataLen);  //红光、红外光归一化  



	//delete[] RedData;
	//delete[] IrData;


    int N1=N+1;
	//int DataLen1=DataLen-1;

 //   int L=Range[1]-Range[0]+1;
	//Matrix_M1_Initialization(Power,0,L);

	//int k=0;
	//for (int r=Range[0];r<Range[1];r++){   // 51~100次运算
 //     k=k+1; 
 // 
 //     double RefSignal[MAXLEN];
	//  //for (i=0;i<DataLen;i++){
 //  //      RefSignal[i]=Irdata[i]-gRtable[r]*Reddata[i];    //产生参考信号
	//  //}
	//
 // 

 //     Matrix_M1_Assign(x,RefSignal,DataLen);   //x=RefSignal
 //     Matrix_M1_Assign(d,Irdata,DataLen);   //d=IrData;
	////  delete[] RefSignal;
	//

	//	 for ( i=0;i<N1;i++){
	//		 for (j=0;j<DataLen;j++){
	//			 s[i][j]=0;
	//			 gamma[i][j]=0;
	//			 err_b[i][j]=0;
	//			 err_f[i][j]=0;
	//			 delta[i][j]=0;
	//			 epson_f[i][j]=0;
	//			 epson_b[i][j]=0;
	//			 rou_a[i][j]=0;

	//		 }
	//	 }



 //      s[0][0]=d[0];
 //      gamma[0][1]=1;     //gamma==1  
 //      int sita=1;


 //    int n1=0;
	//  for (int m=0;m<N;m++){          //赋初值
 //          err_b[m][0]=0; 
 //          delta[m][1]=0.05;      //可以修改
	//	   epson_f[m][1]=sita;
	//	   epson_b[m][0]=sita;
	//	   rou_a[m][0]=0;
	//  }







	//  for (int n=2;n<DataLen;n++){    
 //        err_b[0][n]=x[n];              //初始化
	//	 err_f[0][n]=x[n]; 
	//	 epson_b[0][n]=lmda*epson_f[0][n-1]+x[n]*x[n];
 //        epson_f[0][n]=epson_b[0][n];
	//	 gamma[0][n-1]=1;
	//	 s[0][n]=d[n];

	//	 for (int m=0;m<N;m++){
 //           delta[m][n]=lmda*delta[m][n-1]+err_b[m][n-1]*err_f[m][n]/gamma[m][n-1];  
 //           
	//		epson_b[m][n-1]=lmda*epson_b[m][n-2]+err_b[m][n-1]*err_b[m][n-1]/gamma[m][n-1];
 //           epson_f[m][n]=lmda*epson_f[m][n-1]+err_f[m][n]*err_f[m][n]/gamma[m][n-1];

 //           // k_f[m+1][n]=-delta[m][n]/epson_b[m][n-1];
 //           // k_b[m+1][n]=-delta[m][n]/epson_f[m][n];
	//		 err_f[m+1][n]=err_f[m][n]+(-delta[m][n]/epson_b[m][n-1])*err_b[m][n-1];
 //            err_b[m+1][n]=err_b[m][n-1]+(-delta[m][n]/epson_f[m][n])*err_f[m][n];
	//		 gamma[m+1][n-1]=gamma[m][n-1]-err_b[m][n-1]*err_b[m][n-1]/epson_b[m][n-1];

	//		 
	//		 n1=n-1;
	//		 rou_a[m][n1]=lmda*rou_a[m][n1-1]+s[m][n1]*err_b[m][n1]/gamma[m][n1];
	//		 s[m+1][n1]=s[m][n1]-(rou_a[m][n1]/epson_b[m][n1])*err_b[m][n1];

	//	 }

	//  }

 //      
 //      
 //     
	//	for (i=0;i<DataLen;i++){
 //           Output[i]=s[N][i];        //自适应滤波结果
	//	}
 //     
	//	for (i=N;i<DataLen;i++){
	//	  Power[k]=Power[k]+Output[i]*Output[i];  //DST功率
	//	}

	//		   FILE * gtTestFile1;
 //     gtTestFile1 = fopen("Result.txt","w");
 //    
	//   for (int j=0;j<DataLen;j++){
	//	  _ftprintf(gtTestFile1,_T("%f\t%f\n"),Power[j],Output[j]);
 //    	}
 //     fclose(gtTestFile1);
	//  

 // }


	//double Max=Power[0];
 // 	int MaxPos=0;
 //	for (i=0;i<L;i++){
	//	if (Max<Power[i]){
 //          Max=Power[i];
	//	   MaxPos=i;
	//	}

	//}


  /*int Spo2=MaxPos+Range[0]-1;

  if (MaxPos==0)
  {
	  Spo2=0;
  }*/

//  return Spo2;



}



 /***************************************************************************
    矩阵运算1：   常数*(m*1)的矩阵(OutputMatrix=Matrix*coff)
    Matrix  是输入矩阵
    row 是矩阵长度
	Coff 是矩阵需要乘的系数

	注意：int型 乘以flaot型，的舍入误差
 ****************************************************************************/
void Matrix_M1_Multiplication(double*Matrix,double*OutputMatrix,int row,double Coff)
{
  
	for(int i=0;i<row;i++){
      OutputMatrix[i]=(int)(Matrix[i]*Coff);
	}

}


 /***************************************************************************
    矩阵运算2：   m*1 矩阵的加法或减法(OutputMatrix=Matrix1+Matrix2)
    Matrix  是输入矩阵

    row 是矩阵长度
	flag   是标志位，如果为True,则为加，否则为减

	注意：int型 乘以flaot型，的舍入误差
 ****************************************************************************/

void Matrix_M1_Addition(double*Matrix1,double*Matrix2,double*OutputMatrix,int row,BOOL flag)
{
  
	if (flag==TRUE){
	for(int i=0;i<row;i++){
      OutputMatrix[i]=Matrix1[i]+Matrix2[i];   //加法
	}
	}
	else
	{
	for(int i=0;i<row;i++){
	  OutputMatrix[i]=Matrix1[i]-Matrix2[i];  //减法
	}
	}

}


 /***************************************************************************
    矩阵运算3：   m*1 矩阵赋值（Matrix1=Matrix2）
    Matrix  是输入矩阵

    row 是矩阵长度

 ****************************************************************************/
void Matrix_M1_Assign(double Matrix1[],double Matrix2[],int row)
{

	for (int i=0;i<row;i++){
      Matrix1[i]=Matrix2[i];
	}

}


 /***************************************************************************
    矩阵运算3：   m*1 矩阵初始化 （例如 a[2]={1,1}）
    Matrix  是输入矩阵
    
	Value 是矩阵初始化值
    row 是矩阵长度

 ****************************************************************************/
void Matrix_M1_Initialization(double Matrix1[],double Vlaue,int row)
{

	for (int i=0;i<row;i++){
      Matrix1[i]=Vlaue;
	}

}



 /***************************************************************************
    矩阵运算：   m*n 矩阵初始化 
    Matrix  是输入矩阵
    
	Value 是矩阵初始化值
    row 是矩阵长度
	col 是矩阵列数

 ****************************************************************************/
void Matrix_MN_Initialization(double Matrix1[][MAXLEN],double Vlaue,int row,int col)
{

	for (int i=0;i<row;i++){
		for (int j=0;j<col;j++){
          Matrix1[i][j]=Vlaue;
		}
	}

}

channel_fir FIR_HF0_5_NUM_250[channelMAX] = {0};//为fir滤波器开辟通道
/***************************************************************************
310阶0.5Hz高通Kaiser窗beta=5滤波器：


****************************************************************************/
float filter_fir_highpass0_5Hz_250(float x, int num)
{
	double y=0;

	static channel_fir *chan_p = FIR_HF0_5_NUM_250;

	float coef_b[311] ={ -7.009110413e-05,  -7.670583e-05,-8.364846872e-05,-9.092697292e-05,-9.854925156e-05,
  -0.0001065231263,-0.000114856346,-0.0001235565869,-0.0001326314086,-0.0001420882618,
  -0.0001519344951,-0.0001621773263,-0.000172823813,-0.0001838809258,-0.000195355402,
  -0.0002072538628,-0.0002195827255,-0.0002323482622,-0.0002455565264,-0.0002592132951,
  -0.0002733242873,-0.0002878948289,-0.0003029301588,-0.0003184351372,-0.0003344144498,
  -0.0003508725495,-0.0003678135108,-0.0003852412046,-0.0004031592398,-0.0004215708177,
  -0.0004404789361,-0.0004598862142,-0.0004797950096,-0.0005002073012,-0.000521124748,
  -0.0005425486015,-0.0005644798512,-0.0005869191373,-0.0006098666345,-0.0006333221681,
  -0.0006572852726,-0.0006817550166,-0.0007067300612,-0.0007322087768,-0.0007581890095,
  -0.0007846682565,-0.0008116436657,-0.0008391118608,-0.0008670691168,-0.0008955113008,
  -0.0009244338144,-0.0009538315935,-0.0009836993413,-0.001014031121,-0.001044820645,
  -0.001076061162,-0.001107745571,-0.001139866421,-0.001172415446,-0.001205384498,
  -0.001238764613, -0.00127254636,-0.001306720311, -0.00134127622,-0.001376203494,
  -0.001411491306,-0.001447128132,-0.001483102445,-0.001519401907, -0.00155601406,
  -0.001592925983,-0.001630124287,-0.001667595352,-0.001705325092,-0.001743299072,
  -0.001781502389, -0.00181992026,-0.001858536853,-0.001897336682,-0.001936303568,
  -0.001975421095,-0.002014672384,-0.002054040786, -0.00209350884,-0.002133059083,
  -0.002172673587,-0.002212334657,-0.002252023667,-0.002291722456,-0.002331412397,
  -0.002371074399,-0.002410689602, -0.00245023868, -0.00248970231,-0.002529061167,
  -0.002568295691,-0.002607385861, -0.00264631235,-0.002685054904, -0.00272359373,
   -0.00276190904,-0.002799980808,-0.002837788779,-0.002875313163,-0.002912533935,
  -0.002949431073,-0.002985984785,-0.003022175282,-0.003057982773,-0.003093387466,
  -0.003128370037,-0.003162910929,-0.003196990816,-0.003230590839,-0.003263691906,
   -0.00329627539,-0.003328322666,-0.003359815571,-0.003390736179,-0.003421066329,
  -0.003450788558,-0.003479886102,-0.003508341499,-0.003536138218,-0.003563260194,
  -0.003589691361,-0.003615416121,-0.003640419105,-0.003664685879,-0.003688201541,
  -0.003710952355,-0.003732924815,-0.003754105186, -0.00377448136,-0.003794040764,
  -0.003812771756,-0.003830662696,-0.003847703105,-0.003863882273,-0.003879190655,
  -0.003893618938, -0.00390715804,-0.003919799812,-0.003931536805,-0.003942361567,
  -0.003952267114,-0.003961247858,-0.003969298676,-0.003976413514,-0.003982588649,
  -0.003987820353,-0.003992105369,-0.003995440435, -0.00399782462,-0.003999255598,
     0.9959334135,-0.003999255598, -0.00399782462,-0.003995440435,-0.003992105369,
  -0.003987820353,-0.003982588649,-0.003976413514,-0.003969298676,-0.003961247858,
  -0.003952267114,-0.003942361567,-0.003931536805,-0.003919799812, -0.00390715804,
  -0.003893618938,-0.003879190655,-0.003863882273,-0.003847703105,-0.003830662696,
  -0.003812771756,-0.003794040764, -0.00377448136,-0.003754105186,-0.003732924815,
  -0.003710952355,-0.003688201541,-0.003664685879,-0.003640419105,-0.003615416121,
  -0.003589691361,-0.003563260194,-0.003536138218,-0.003508341499,-0.003479886102,
  -0.003450788558,-0.003421066329,-0.003390736179,-0.003359815571,-0.003328322666,
   -0.00329627539,-0.003263691906,-0.003230590839,-0.003196990816,-0.003162910929,
  -0.003128370037,-0.003093387466,-0.003057982773,-0.003022175282,-0.002985984785,
  -0.002949431073,-0.002912533935,-0.002875313163,-0.002837788779,-0.002799980808,
   -0.00276190904, -0.00272359373,-0.002685054904, -0.00264631235,-0.002607385861,
  -0.002568295691,-0.002529061167, -0.00248970231, -0.00245023868,-0.002410689602,
  -0.002371074399,-0.002331412397,-0.002291722456,-0.002252023667,-0.002212334657,
  -0.002172673587,-0.002133059083, -0.00209350884,-0.002054040786,-0.002014672384,
  -0.001975421095,-0.001936303568,-0.001897336682,-0.001858536853, -0.00181992026,
  -0.001781502389,-0.001743299072,-0.001705325092,-0.001667595352,-0.001630124287,
  -0.001592925983, -0.00155601406,-0.001519401907,-0.001483102445,-0.001447128132,
  -0.001411491306,-0.001376203494, -0.00134127622,-0.001306720311, -0.00127254636,
  -0.001238764613,-0.001205384498,-0.001172415446,-0.001139866421,-0.001107745571,
  -0.001076061162,-0.001044820645,-0.001014031121,-0.0009836993413,-0.0009538315935,
  -0.0009244338144,-0.0008955113008,-0.0008670691168,-0.0008391118608,-0.0008116436657,
  -0.0007846682565,-0.0007581890095,-0.0007322087768,-0.0007067300612,-0.0006817550166,
  -0.0006572852726,-0.0006333221681,-0.0006098666345,-0.0005869191373,-0.0005644798512,
  -0.0005425486015,-0.000521124748,-0.0005002073012,-0.0004797950096,-0.0004598862142,
  -0.0004404789361,-0.0004215708177,-0.0004031592398,-0.0003852412046,-0.0003678135108,
  -0.0003508725495,-0.0003344144498,-0.0003184351372,-0.0003029301588,-0.0002878948289,
  -0.0002733242873,-0.0002592132951,-0.0002455565264,-0.0002323482622,-0.0002195827255,
  -0.0002072538628,-0.000195355402,-0.0001838809258,-0.000172823813,-0.0001621773263,
  -0.0001519344951,-0.0001420882618,-0.0001326314086,-0.0001235565869,-0.000114856346,
  -0.0001065231263,-9.854925156e-05,-9.092697292e-05,-8.364846872e-05,  -7.670583e-05,
  -7.009110413e-05 };
	
	y = coef_b[0] * x;  // 当前输入项
    for (int i = 0; i < 310; i++) {
        y += coef_b[i + 1] * chan_p[num].xdata[i];
    }

    // 更新历史数据: 旧数据后移，新数据插入
    for (int i = 309; i > 0; i--) {
        chan_p[num].xdata[i] = chan_p[num].xdata[i - 1];
    }
    chan_p[num].xdata[0] = x;
	return y;
}


channel_fir FIR_LF5_NUM_250[channelMAX] = {0};//为fir滤波器开辟通道
/***************************************************************************
259阶5Hz低通Kaiser窗beta=5滤波器：


****************************************************************************/
float filter_fir_lowpass5Hz_250(float x, int num)
{
	double y=0;

	static channel_fir *chan_p = FIR_LF5_NUM_250;

	float coef_b[260] ={-4.828638703e-05,-4.247633115e-05,-3.396723696e-05,-2.259969733e-05,-8.278342648e-06,
  9.018869605e-06,2.923248394e-05,5.221479296e-05,7.772477693e-05,0.0001054250388,
  0.0001348808873,0.0001655618835,0.0001968458964,0.0002280257904,0.0002583188179,
  0.0002868786978, 0.000312810269,0.0003351865453,0.0003530679678,0.0003655236505,
  0.0003716540814,0.0003706151037,0.0003616424219,0.0003440763976,0.0003173863806,
  0.0002811940794,0.0002352954325,0.0001796801225,0.0001145484566,4.032488505e-05,
  -4.233244545e-05,-0.0001325264311,-0.0002291205892,-0.0003307437873,-0.0004358002334,
  -0.0005424853298,-0.0006488065701,-0.0007526105619,-0.0008516150992,-0.0009434458916,
  -0.001025678706,-0.001095884363,-0.001151678502,-0.001190772164,-0.001211025519,
  -0.001210501534, -0.00118751917,-0.001140705543,-0.001069044927, -0.00097192463,
  -0.0008491753833,-0.000701106037,-0.0005285314983,-0.0003327919112,-0.0001157637671,
  0.0001201390696,0.0003719742526,0.0006362905842,0.0009091584361, 0.001186211011,
   0.001462696469, 0.001733540208, 0.001993417274,  0.00223683333, 0.002458214294,
     0.0026520018, 0.002812754828, 0.002935255645, 0.003014617134, 0.003046389902,
   0.003026670543, 0.002952203853, 0.002820480149, 0.002629826777, 0.002379489131,
   0.002069699811, 0.001701737172, 0.001277967123,0.0008018711233,0.0002780561917,
  -0.000287753006,-0.0008887398872,-0.001517040888,-0.002163809491,-0.002819298068,
  -0.003472958691,-0.004113560542,-0.004729323089,-0.005308063701,-0.005837357603,
  -0.006304708309,-0.006697726436,-0.007004313637,-0.007212848868,-0.007312376052,
  -0.007292786613,-0.007144998293,-0.006861124188,-0.006434630137,-0.005860476289,
  -0.005135245156,-0.004257247318, -0.00322660571,-0.002045318019,-0.0007172923652,
  0.0007516408223, 0.002353745745, 0.004079424776, 0.005917287432,  0.00785425026,
   0.009875655174,  0.01196542289,  0.01410621498,  0.01627963036,  0.01846641116,
    0.02064666711,  0.02280011214,   0.0249063056,  0.02694491111,  0.02889593877,
     0.0307400059,  0.03245857731,  0.03403420746,  0.03545076028,  0.03669361398,
    0.03774987161,   0.0386085026,  0.03926051036,  0.03969903663,  0.03991946578,
    0.03991946578,  0.03969903663,  0.03926051036,   0.0386085026,  0.03774987161,
    0.03669361398,  0.03545076028,  0.03403420746,  0.03245857731,   0.0307400059,
    0.02889593877,  0.02694491111,   0.0249063056,  0.02280011214,  0.02064666711,
    0.01846641116,  0.01627963036,  0.01410621498,  0.01196542289, 0.009875655174,
    0.00785425026, 0.005917287432, 0.004079424776, 0.002353745745,0.0007516408223,
  -0.0007172923652,-0.002045318019, -0.00322660571,-0.004257247318,-0.005135245156,
  -0.005860476289,-0.006434630137,-0.006861124188,-0.007144998293,-0.007292786613,
  -0.007312376052,-0.007212848868,-0.007004313637,-0.006697726436,-0.006304708309,
  -0.005837357603,-0.005308063701,-0.004729323089,-0.004113560542,-0.003472958691,
  -0.002819298068,-0.002163809491,-0.001517040888,-0.0008887398872,-0.000287753006,
  0.0002780561917,0.0008018711233, 0.001277967123, 0.001701737172, 0.002069699811,
   0.002379489131, 0.002629826777, 0.002820480149, 0.002952203853, 0.003026670543,
   0.003046389902, 0.003014617134, 0.002935255645, 0.002812754828,   0.0026520018,
   0.002458214294,  0.00223683333, 0.001993417274, 0.001733540208, 0.001462696469,
   0.001186211011,0.0009091584361,0.0006362905842,0.0003719742526,0.0001201390696,
  -0.0001157637671,-0.0003327919112,-0.0005285314983,-0.000701106037,-0.0008491753833,
   -0.00097192463,-0.001069044927,-0.001140705543, -0.00118751917,-0.001210501534,
  -0.001211025519,-0.001190772164,-0.001151678502,-0.001095884363,-0.001025678706,
  -0.0009434458916,-0.0008516150992,-0.0007526105619,-0.0006488065701,-0.0005424853298,
  -0.0004358002334,-0.0003307437873,-0.0002291205892,-0.0001325264311,-4.233244545e-05,
  4.032488505e-05,0.0001145484566,0.0001796801225,0.0002352954325,0.0002811940794,
  0.0003173863806,0.0003440763976,0.0003616424219,0.0003706151037,0.0003716540814,
  0.0003655236505,0.0003530679678,0.0003351865453, 0.000312810269,0.0002868786978,
  0.0002583188179,0.0002280257904,0.0001968458964,0.0001655618835,0.0001348808873,
  0.0001054250388,7.772477693e-05,5.221479296e-05,2.923248394e-05,9.018869605e-06,
  -8.278342648e-06,-2.259969733e-05,-3.396723696e-05,-4.247633115e-05,-4.828638703e-05 };

	y = coef_b[0] * x;  // 当前输入项
    for (int i = 0; i < 259; i++) {
        y += coef_b[i + 1] * chan_p[num].xdata[i];
    }

    // 更新历史数据: 旧数据后移，新数据插入
    for (int i = 258; i > 0; i--) {
        chan_p[num].xdata[i] = chan_p[num].xdata[i - 1];
    }
    chan_p[num].xdata[0] = x;
	return y;
}

channel_Med Chan_Med[channelMAX]={0};//开辟通道
int FliterMed(float x,int Integnum,int chan_num)
{
	long ly;int y;
	static channel_Med* chan_p=Chan_Med;

	int temp[250];    // 临时排序数组
    int n = 0;        // 有效数据计数
    int i, j;

    // 初始化
    if (chan_p[chan_num].flag == 0) {
        chan_p[chan_num].ptr = 0;
        for (i = 0; i < Integnum; i++) {
            chan_p[chan_num].xdata[i] = x;  // 初始填充当前值
        }
        chan_p[chan_num].flag = 1;
    }

    // 更新数据：新值覆盖最旧数据
    chan_p[chan_num].xdata[chan_p[chan_num].ptr] = x;
    if (++chan_p[chan_num].ptr >= Integnum) {
        chan_p[chan_num].ptr = 0;
    }

    // 复制有效数据到临时数组
    n = Integnum;  // 窗口始终满（初始化后）
    for (i = 0; i < n; i++) {
        temp[i] = chan_p[chan_num].xdata[i];
    }

    // 冒泡排序（小 → 大）
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (temp[j] > temp[j + 1]) {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    // 计算中值
    int median;
    if (n % 2 == 1) {
        median = temp[(n-1) / 2];  // 奇数取中间
    } else {
        // 偶数取中间
        median = (temp[n / 2]);
    }

    return median;
		///Integnum;//32点的滑动积分

	//if(ly>650000)/*检查寄存器过载*/
	//{
	//	y=650000;
	//}
	//else
	//{
	//	y=(int)ly;
	//}
	//return ly;

}

channel_STD Chan_STD[channelMAX]={0};
float FliterSTD(double x,int Integnum,int chan_num)
{
	
    static channel_STD* chan_p = Chan_STD;
    const int window_size = 250; // 明确窗口大小

    // 初始化检查（保留）
    if(chan_p[chan_num].flag == 0) {
        chan_p[chan_num].ptr = 0;
        chan_p[chan_num].sum = 0;
        chan_p[chan_num].sum_sq = 0;
    }

    // === 核心修改：实现真正的滑动窗口 ===
    if(chan_p[chan_num].flag >= window_size) 
    {
        // 移除旧数据点
        double old_value = chan_p[chan_num].xdata[chan_p[chan_num].ptr];
        chan_p[chan_num].sum -= old_value;
        chan_p[chan_num].sum_sq -= (long long)(old_value * old_value);
    }
    else
    {
        // 增加新点计数
        chan_p[chan_num].flag++;
    }

    // 添加新数据
    chan_p[chan_num].xdata[chan_p[chan_num].ptr] = x;
    chan_p[chan_num].sum += x;
    chan_p[chan_num].sum_sq += (long long)(x * x);

    // 更新环形缓冲区指针
    chan_p[chan_num].ptr = (chan_p[chan_num].ptr + 1) % window_size;

    // 不足窗口大小时返回0
    if(chan_p[chan_num].flag < window_size)
        return 0.0f;

    // 计算标准差（无偏估计）
    double mean = chan_p[chan_num].sum / window_size;
    double variance = (chan_p[chan_num].sum_sq - window_size * mean * mean) / (window_size - 1);
    
    return (variance > 0) ? (float)(sqrt(variance) * 1000) : 0.0f;



	//long ly;int y;
	//static channel_STD* chan_p=Chan_STD;

	//if(chan_p[chan_num].flag==0)
	//{
	//	chan_p[chan_num].ptr=0;
	//	chan_p[chan_num].sum=0;
	//	chan_p[chan_num].sum_sq = 0;
	//}

	//
	//// 当缓冲区已满时，先移除旧数据
 //   if(chan_p[chan_num].flag >= 250)
 //   {
 //       double old_value = chan_p[chan_num].xdata[chan_p[chan_num].ptr];
 //       //chan_p[chan_num].sum -= old_value;
	//	chan_p[chan_num].sum = 0;
 //       //chan_p[chan_num].sum_sq -= (long long)(old_value * old_value);
	//	chan_p[chan_num].sum_sq = 0;
	//	chan_p[chan_num].flag = 0;
 //   }

 //   // 存储新数据并更新统计值
 //   chan_p[chan_num].xdata[chan_p->ptr] = x;
 //   chan_p[chan_num].sum += x;
 //   chan_p[chan_num].sum_sq += (long long)(x * x);
 //   
 //   // 更新环形缓冲区指针
 //   chan_p[chan_num].ptr = (chan_p[chan_num].ptr + 1) % 250;
 //   
 //   // 更新计数器（不超过250）
 //   if(chan_p[chan_num].flag < 250) 
 //       chan_p[chan_num].flag++;
 //   
 //   // 未积累足够数据时返回0
 //   if(chan_p[chan_num].flag < 250)
 //       return 0.0f;
 //   
 //   // 计算标准差（使用250个数据点）
 //   double variance = (250.0 * chan_p[chan_num].sum_sq - chan_p[chan_num].sum * chan_p[chan_num].sum) / (250.0 * 249.0);
 //   
 //   // 处理负方差（数值误差）
 //   if(variance < 0) 
 //       variance = 0;
 //   
 //   // 计算标准差（放大1000倍返回）
 //   return (float)(sqrt(variance) * 1000);


	
		///Integnum;//32点的滑动积分


	//if(ly>650000)/*检查寄存器过载*/
	//{
	//	y=650000;
	//}
	//else
	//{
	//	y=(int)ly;
	//}
	//return ly;

}



void rls_optimized(double *x, double *d, double *w, double *P, double lambda, double delta, int M, int n, double *en) 
{
 
    double lambda_min = 0.95;
    double lambda_max = 0.999;
    double avg_factor = 0.995;
    double error_energy = 0.0;
    double e, denom, trP, wu;
    int i, j, k;

    // 为中间变量分配内存
    double *u = (double *)malloc(M * sizeof(double));
    double *pi_k = (double *)malloc(M * sizeof(double));
    double *K = (double *)malloc(M * sizeof(double));
    double *A = (double *)malloc(M * M * sizeof(double)); // 外积矩阵 K * pi_k^T
    double *P_tmp = (double *)malloc(M * M * sizeof(double));

    // 初始化前M-1个误差为0
    for (k = 0; k < M; k++) {
        en[k] = 0.0;
    }

    // 主循环：从索引 M 到 n-1 (对应MATLAB的k=M:n)
    for (k = M; k <= n; k++) {
        // 1. 构建输入向量 u = [x(k), x(k-1), ..., x(k-M+1)]
        for (i = 0; i < M; i++) {
            u[i] = x[k - i - 1]; // 注意: C索引从0开始, MATLAB从1开始
        }

        // 2. 计算 pi_k = P * u (列优先存储)
        memset(pi_k, 0, M * sizeof(double));
        for (i = 0; i < M; i++) {
            for (j = 0; j < M; j++) {
                // 列优先: P[i + j*M] 对应MATLAB的P(i+1, j+1)
                pi_k[i] += P[i + j*M] * u[j];
            }
        }

        // 3. 计算分母 denom = lambda + u^T * pi_k
        denom = lambda;
        for (i = 0; i < M; i++) {
            denom += u[i] * pi_k[i];
        }

        // 4. 计算Kalman增益 K
        if (denom < 1e-10) {
            for (i = 0; i < M; i++) {
                K[i] = pi_k[i] * 1e5;
            }
        } else {
            for (i = 0; i < M; i++) {
                K[i] = pi_k[i] / denom;
            }
        }

        // 5. 计算后验误差 e = d(k) - w^T * u
        wu = 0.0;
        for (i = 0; i < M; i++) {
            wu += w[i] * u[i];
        }
        e = d[k-1] - wu; // d[k-1]对应MATLAB的d(k)
        en[k-1] = e;

        // 6. 动态调整遗忘因子 lambda
        error_energy = avg_factor * error_energy + (1 - avg_factor) * (e * e);
        if (error_energy > 1e-6) {
            double new_lambda = 1 - 0.1 * error_energy;
            if (new_lambda < lambda_min) new_lambda = lambda_min;
            if (new_lambda > lambda_max) new_lambda = lambda_max;
            lambda = new_lambda;
        }

        // 7. 更新权重 w = w + K * e
        for (i = 0; i < M; i++) {
            w[i] += K[i] * e;
        }

        // 8. 计算外积矩阵 A = K * pi_k^T (列优先存储)
        for (i = 0; i < M; i++) {
            for (j = 0; j < M; j++) {
                // 列优先: A[i + j*M] = K[i] * pi_k[j]
                A[i + j*M] = K[i] * pi_k[j];
            }
        }

        // 9. 计算临时协方差矩阵 P_tmp = (P - A) / lambda
        for (i = 0; i < M * M; i++) {
            P_tmp[i] = (P[i] - A[i]) / lambda;
        }

        // 10. 对称化P_tmp: P = 0.5 * (P_tmp + P_tmp^T)
        for (i = 0; i < M; i++) {
            for (j = 0; j < M; j++) {
                // 列优先索引: [i + j*M] 和 [j + i*M] 是对称位置
                P[i + j*M] = 0.5 * (P_tmp[i + j*M] + P_tmp[j + i*M]);
            }
        }

        // 11. 正则化复位：若迹(trP) > 1/delta，则 P = P + (1/delta)*I
        trP = 0.0;
        for (i = 0; i < M; i++) {
            trP += P[i + i*M]; // 对角线元素
        }
        if (trP > 1.0 / delta) {
            for (i = 0; i < M; i++) {
                P[i + i*M] += 1.0 / delta;
            }
        }
    }

    // 释放内存
    free(u);
    free(pi_k);
    free(K);
    free(A);
    free(P_tmp);

}