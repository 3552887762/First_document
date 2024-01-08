#define _CRT_SECURE_NO_WARNINGS
#include <cassert>
#include <limits.h>
#include <string>
#include <iostream>
#include "LinkList.hpp"

using namespace std;

static ListNode* Buynode()
{
	ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	if (nullptr == s) exit(1);
	memset(s, 0, sizeof(ListNode));
	return s;
}

static void* GetElemMem(size_t size)
{
	void* s = malloc(size);
	if (nullptr == s) exit(1);
	memset(s, 0, size);
	return s;
}

static void Freenode(ListNode* p)
{
	free(p);
}

static void InserPrev(ListNode* p, ListNode* s)
{
	s->next = p;
	s->prev = p->prev;
	p->prev = s;
	s->prev->next = s;
}

static void ErasePrev(ListNode* p, ListNode* s)
{
	s->next = p;
	p->prev = s;
}

void InitList(LinkList* plist, size_t elemsize)
{
	assert(plist != nullptr);
	plist->Head = Buynode();
	plist->Head->next = plist->Head->prev = plist->Head;
	plist->cursize = 0;
	plist->elemsize = elemsize;
	plist->Head->data = nullptr;
}

void DestroyList(LinkList* plist)
{
	assert(plist != nullptr);
	ClearList(plist);
	free(plist->Head);
}

size_t GetSize(const LinkList* plist)
{
	assert(plist != nullptr);
	return plist->cursize;
}

bool IsEmpty(const LinkList* plist)
{
	assert(plist != nullptr);
	return GetSize(plist) == 0;
}

void ClearList(LinkList* plist)
{
	assert(plist != nullptr);
	LinkNode* p = plist->Head->next;
	while (p != plist->Head)
	{
		LinkNode* tmp = p;
		p = p->next;
		if (plist->elemsize <= STORESIZE)
		{
			Freenode(tmp);
		}
		else
		{
			free(tmp->data);
			Freenode(tmp);
		}
	
		plist->cursize -= 1;
	}
	plist->Head->next = plist->Head->prev = plist->Head;//构造只有虚拟头节点的循环链表
}

bool InsertList(LinkList* plist, int pos, void* pval)
{
	assert(plist != nullptr);
	assert(pval != nullptr);
	ListNode* p = FindPos(plist, pos);
	if (nullptr == p) return false;
	ListNode* s = Buynode();
	InserPrev(p, s);
	if (plist->elemsize <= STORESIZE)
	{
		memmove(&s->data, pval, plist->elemsize);
	}
	else
	{
		void* newval = GetElemMem(plist->elemsize);
		memmove(newval, pval, plist->elemsize);
		s->data = newval;
	}
	plist->cursize += 1;
	return true;
}

ListNode* FindPos(const LinkList* plist, size_t pos)
{
	assert(nullptr != plist);
	if (0 == pos || pos > GetSize(plist) + 1)return nullptr;
	if (1 == pos)return plist->Head->next;//头插
	if (GetSize(plist) + 1 == pos) return plist->Head;//尾插

	LinkNode* p = plist->Head;

	while (pos--) {
		p = p->next;
	}

	return p;

	//LinkNode* p = plist->Head->next;
	//while (p != plist->Head && pos--) {
	//	p = p->next;
	//}
	//if (p == plist->Head)
	//{
	//	p = nullptr;
	//}
	//return p;
}

bool EraseList(LinkList* plist, int pos)
{
	assert(plist != nullptr);
	LinkNode* p = FindPos(plist, pos);
	if (p == nullptr)return false;
	
	ErasePrev(p->next, p->prev);
	
	if (plist->elemsize <= STORESIZE)
	{
		free(p);
		p = nullptr;
	}
	else
	{
		free(p->data);
		Freenode(p);
		p = nullptr;
	}

	plist->cursize -= 1;
	return true;
}

void Push_back(LinkList* plist, void* pval)
{
	assert(plist != nullptr);
	assert(pval != nullptr);
	InsertList(plist, plist->cursize + 1, pval);

}

void Push_front(LinkList* plist, void* pval)
{
	assert(plist != nullptr);
	assert(pval != nullptr);
	InsertList(plist, 1, pval);
}

//有问题
ListNode* FindValue(const LinkList* plist, void* pval)
{
	assert(plist != nullptr);
	assert(pval != nullptr);
	LinkNode* p = plist->Head->next;
	while (p != plist->Head)
	{
		if (plist->elemsize <= STORESIZE)
		{
			if (memcmp(pval,&p->data,plist->elemsize)==0)
			{
				/*cout << pval << endl;
				cout << &p->data << endl;*/
				return p;
			}
		}
		else
		{
			if (memcmp(pval, p->data, plist->elemsize)==0)
			{

				return p;
			}
		}
		p = p->next;
	}
	return p;
}

void Pop_back(LinkList* plist)
{
	assert(plist != nullptr);
	EraseList(plist, GetSize(plist));
}

void Pop_Front(LinkList* plist)
{
	assert(plist != nullptr);
	EraseList(plist, 1);
}

//疑问
bool GetFront(const LinkList* plist, void* pval)
{
	assert(nullptr != plist);
	assert(nullptr != pval);

	LinkNode* p = plist->Head;
	if (p == p->next)return false;
	if (plist->elemsize <= STORESIZE)
	{
		memcpy(pval, &p->next->data, plist->elemsize);
		//pval = &(p->prev->data); //其实是没有真正指向的，函数结束后 就没了 
		//cout << "测试GetFront：" << *(int*)pval << endl;
	}
	else
	{
		memcpy(pval, p->next->data, plist->elemsize);
		//pval = p->prev->data;
	}

	return true;
}

//有疑问
bool GetBack(const LinkList* plist, void* pval)
{
	assert(nullptr != plist);
	assert(nullptr != pval);

	LinkNode* p = plist->Head;
	if (p == p->next)return false;
	if (plist->elemsize <= STORESIZE)
	{
		memcpy(pval,&p->prev->data,plist->elemsize);
		//pval = &(p->prev->data);//没有真正指向
	}
	else
	{
		memcpy(pval, p->prev->data, plist->elemsize);
		//pval = p->prev->data;
	}

	return true;
}

bool Remove(LinkList* plist, void* pval)
{
	assert(nullptr != plist);
	assert(nullptr != pval);
	ListNode*  p = FindValue(plist, pval);
	if (p == nullptr)return false;
	ErasePrev(p->next, p->prev);
	if (plist->elemsize <= STORESIZE)
	{
		free(p);
		p = nullptr;
	}
	else
	{
		free(p->data);
		Freenode(p);
		p = nullptr;
	}

	plist->cursize -= 1;
	
}

void PrintList(const LinkList* plist, void (*Print)(const void*))
{
	assert(plist != nullptr);
	assert(Print != nullptr);
	LinkNode* p = plist->Head->next;
	while (p != plist->Head)
	{ 
		if (plist->elemsize <= STORESIZE)
		{
			Print(&p->data);
		}
		else
		{
			Print(p->data);
		}
		p = p->next;
	}
	printf("\n");
}

