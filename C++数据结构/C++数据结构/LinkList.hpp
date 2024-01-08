#ifndef LINKLIST_HPP
#define LINKLIST_HPP
#define STORESIZE 4

typedef struct LinkNode
{
	struct LinkNode* prev;
	struct LinkNode* next;
	void* data;// 4 字节  它可以处理多个类型的数据类型 malloc()空间，把数据导进去
}ListNode, * pListNode;

typedef struct
{
	pListNode Head;//虚拟头节点 哨兵节点
	int cursize;//记录节点个数
	size_t elemsize;// 存储数据类型 的大小 char short int 
					//long int(不同编译器下) 大小不一定
	 // long int; long long; float; double; long double;
}LinkList;

extern void InitList(LinkList* plist, size_t elemsize);
extern void DestroyList(LinkList* plist);
extern size_t GetSize(const LinkList* plist);
extern bool IsEmpty(const LinkList* plist);
extern void ClearList(LinkList* plist);
extern ListNode* FindPos(const LinkList* plist, size_t pos);
extern bool InsertList(LinkList* plist, size_t pos, void* pval);
extern void Push_back(LinkList* plist, void* pval);
extern void Push_front(LinkList* plist, void* pval);
extern ListNode* FindValue(const LinkList* plist, void* pval);
extern bool EraseList(LinkList* plist, int pos);
extern void Pop_back(LinkList* plist);
extern void Pop_Front(LinkList* plist);
extern bool GetFront(const LinkList* plist, void* pval);
extern bool GetBack(const LinkList* plist, void* pval);
extern bool Remove(LinkList* plist, void* pval);
extern void PrintList(const LinkList *plist, void (*Print)(const void*));//函数指针
#endif