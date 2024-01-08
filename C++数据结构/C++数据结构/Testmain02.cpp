#if 0
//void a; 不可以定义变量
void* p; //可以定义指针
//sizeof(void);  //vs编译器下 不可以计算
sizeof(*p);//不可以进行解引用
#endif
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <stdio.h>
using namespace std;
#include"LinkList.hpp"
#if 0
void PrintDouble(const void* p)
{ // void*  p = data;  

	const double* dp = (const double*)p;
	printf("%lf ", *dp);
}
void PrintInt(const void* p)
{// void * p = &data;
	const int* ip = (const int*)p;
	printf("%d ", *ip);
}
int main()
{
	LinkList ilist;
	LinkList dlist;
	InitList(&ilist, sizeof(int));
	InitList(&dlist, sizeof(double));
	int ar[] = { 12,13,14,15,16,17 };
	double dx[] = { 1.22,2.3,3.4,4.5,5.6,6.7,7.8,438.9 };
	int an = sizeof(ar) / sizeof(ar[0]);
	int dn = sizeof(dx) / sizeof(dx[0]);
	for (int i = 0; i < an; ++i)
	{
		Push_back(&ilist, &ar[i]);
	}
	for (int i = 0; i < dn; ++i)
	{
		Push_front(&dlist, &dx[i]);
	}
	/*
	printf("\n");
	
	PrintList(&ilist,PrintInt);
	PrintList(&dlist,PrintDouble);

	ClearList(&ilist);
	ClearList(&dlist);
	for (int i = 0; i < an; ++i)
	{
		Push_back(&ilist, &ar[i]);
	}
	EraseList(&ilist,0);
	Pop_back(&ilist);
	Pop_back(&ilist);
	Pop_Front(&ilist);
	Pop_Front(&ilist);

	PrintList(&ilist, PrintInt);
	*/
	void* p1 = &ar[1];
	void* p2 = &dx[1];//如果 p1 和 p2 指向同一个空间 &ar[0]  那么就会覆盖
	/*
	GetFront(&ilist, &p1);
	GetBack(&ilist,p2);
	for (int i = 0; i < dn; ++i)
	{
		Push_front(&dlist, &dx[i]);
	}

	PrintList(&dlist, PrintDouble);
	printf("===========\n");
	printf("GetFront：%d\n", (int*)p1);
	printf("GetBack：%d\n", *(int*)p2);

	*/
	LinkNode* Findkey_1 = FindValue(&ilist, p1);

	cout << "Findkey_1：" << *(int*)&Findkey_1->data << endl;

	LinkNode* Findkey_2 = FindValue(&dlist, p2);
	cout << "Findkey_2：" << *(double*)Findkey_2->data << endl;

	PrintList(&dlist, PrintDouble);


	//Remove(&ilist, &ar[3]);
	PrintList(&ilist, PrintInt);
	DestroyList(&ilist);
	DestroyList(&dlist);
	return 0;
}

#endif




/*
void func(int& p)
{
	int num = 10;
	p = num;
}
int main()
{

	int arr[3] = { 12,23,34 };
	int p = arr[1];
	func(p);
	cout << p << endl;
}
*/

/*
void func(int x)
{
	printf("func\n");
}

void print(double x)
{
	printf("fund\n");
}

int main(void)
{
	void (*p)(int); //函数指针的定义
	//int (*p)();       //函数指针的另一种定义方式，不过不建议使用
	//int (*p)(int a, int b);   //也可以使用这种方式定义函数指针

	//p = max;    //函数指针初始化
	p = func;
	//int ret = p(10, 15);    //函数指针的调用
	
	//int ret = (*max)(10,15);
	//int ret = (*p)(10,15);
	//以上两种写法与第一种写法是等价的，不过建议使用第一种方式
	/*printf("max = %d \n", p(1));
	printf("print = %d \n", p(2));
	p(1);
	p(2);

	return 0;
}*/


/*
int* func_sum(int n)
{
	if (n < 0)
	{
		printf("error:n must be > 0\n");
		exit(-1);
	}
	//static int sum = 0;
	int sum = 0;

	int* p = &sum;
	for (int i = 0; i < n; i++)
	{
		sum += i;
	}
	return p;
}

int main(void)
{
	int num = 0;
	printf("please input one number:");
	scanf("%d", &num);
	int* p = func_sum(num);
	printf("\n");
	printf("sum:%d\n", *p);
	return 0;
}
*/

/*void void*
int main()
{
	void* p;

	printf("%d\n",sizeof(p));
	return 0;
}
*/
/*memmove
int main()
{
	int arr[3] = { 0 };
	int src = 2;
	void* p = (void*)src;
	//void* p = &src;
	//memmove(arr + 1, &src, sizeof(int));
	memmove(&arr[1], (void*)src, sizeof(int));
	//memmove(arr + 1, (void*)src, sizeof(int));  err

	for (auto x : arr)
	{
		cout << x << " ";
	}
	return 0;
}
*/