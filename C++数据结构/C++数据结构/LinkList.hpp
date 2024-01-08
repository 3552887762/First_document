#ifndef LINKLIST_HPP
#define LINKLIST_HPP
#define STORESIZE 4

typedef struct LinkNode
{
	struct LinkNode* prev;
	struct LinkNode* next;
	void* data;// 4 �ֽ�  �����Դ��������͵��������� malloc()�ռ䣬�����ݵ���ȥ
}ListNode, * pListNode;

typedef struct
{
	pListNode Head;//����ͷ�ڵ� �ڱ��ڵ�
	int cursize;//��¼�ڵ����
	size_t elemsize;// �洢�������� �Ĵ�С char short int 
					//long int(��ͬ��������) ��С��һ��
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
extern void PrintList(const LinkList *plist, void (*Print)(const void*));//����ָ��
#endif