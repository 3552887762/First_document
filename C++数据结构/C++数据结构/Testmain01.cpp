
#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <limits.h>
#include <string>
#include <iostream>
#include "MyList.hpp"
#include "vld.h"
using namespace std;
/*

	MyList ilist;
	sizeof(ilist);//1字节  有空间 不一定有属性 ，但要证明它存在 就要是 占位符

*/
//int main()
//{
//
//	MyList<int> ilist;
//	MyList<double> dlist;
//	cout << sizeof(ilist) <<endl;
//
//}
#include <iostream>
#include <list>
#if 0
int main() {
    MyList<int> myi;
	//myi.insert(myi.begin(), 10, 23);
	//for (auto& x : myi)
	//{
	//	cout << x << endl;
	//}
	//myi.push_back(12);
	//myi.push_back(23);
	//myi.push_back(34);

	for (int i = 0; i < 3; i++) 
	{
		//myi.push_front(i*4+1);
		myi.push_back(i*4+1);
		
	}

	//因为iterator在MyList内所以要::调用
	MyList<int>::iterator it = myi.begin();

	for(; it != myi.end(); ++it)
	{
		cout << *it << endl;
	}
    return 0;
}
#endif

#if 0

#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n, sum;
int l = -1;

struct p
{
	int a;
	int b;

}arr[1000002];

bool cmp(const p x, const p y)
{
	return x.a < y.a;
}

int main()
{
	cin >> n;//3
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i].a >> arr[i].b;

	}
	//
	sort(arr, arr + n, cmp);
	for (int i = 0; i < n; i++)
	{
		cout << arr[i].a <<"  " << arr[i].b << endl;
	}

	for (int i = 0; i < n; i++)
	{
		if (arr[i].a < l)
			continue;
		sum++;
		l = arr[i].b;
	}
	cout << sum << endl;
	return 0;
}
#endif

