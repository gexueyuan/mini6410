/**********************************************************
*实验要求：     掌握汇编代码初始化c环境并跳转到main函数的过程，
*             学会在c代码中调用汇编函数的方法，以及理解编译器
*             处理c函数参数和返回值的方式。
*功能描述：     本程序在汇编初始化代码中完成了必要的数据初始化
*             和栈的初始化工作，跳到c语言main函数后调用了在汇编
*             文件中定义的函数，请大家使用反汇编工具分析函数传
*             参和函数返回的过程。
*日    期：   2011-3-10
*作    者：   国嵌
**********************************************************/
//下面这些函数调用时，那些函数会用到堆栈？它们的返回值是怎么传回来的？
extern int asmSum(int, int);
int cSum(int x, int y);
int cSumargs(int a1, int a2, int a3, int a4, int a5);

/*
 * c语言入口函数
 * */
void  Main(void)
{  
	int a, b, sum;
	a = 1;
	b = 2;
	sum = 0;
   	sum=cSumargs(1,3,5,7,9);  //参数更长又会怎么样？
   	sum = 0;
   	//计算1+3+5+7+9     结果应该是sum=0x19
   	while(a<10)
   	{
 		sum = asmSum(a, sum);   
    	a = cSum(a, b);  			  			
   	}  	
}

int cSum(int x, int y)
{
	return (x+y);
}

int cSumargs(int a1, int a2, int a3, int a4, int a5)
{
	return(a1+a2+a3+a4+a5);
}
