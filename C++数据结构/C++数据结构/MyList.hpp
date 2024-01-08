#pragma once
#ifndef MY_LIST_HPP
#define MY_LIST_HPP

template<class _Ty>

/*
全局变量：
	与线程有关
	1、直接使用
	2、封装了方法
*/

class MyList 	//双链表
{
public:

	using value_type = _Ty;
	using pointer = _Ty*;
	using const_pointer = const _Ty*;
	using reference = _Ty&;//引用、指代
	using const_reference = const _Ty&;

private:
	//先定义 两个 
	struct _Node;

	using _Nodeptr = _Node*;	//指针类型
	
	struct _Node
	{
		_Nodeptr _Prev, _Next; //指针类型
		_Ty _Value;
	};

	struct _Acc
	{
		//typedef _Node*& _Nodepref;
		using _Nodepref = _Node*&;//问这是什么？ 指针的别名 （引用值）
		/*
			int &p[10];  数组：10个int类型的引用		引用没内存空间，所以产生了矛盾 错
			int *p[10];  数组：10个int类型的指针		对
		*/

		//可以修改 可以 获得
		// int x = _Acc::_Value(p); 可以这样获取
		// _Acc::_Value(p) = 100; 也可以给它修改
		static _Ty& _Value(_Nodeptr ptr)
		{//引用形式
			return ptr->_Value;
		}

		/*
		Node *s = Acc::_Prev(p);
		_Acc::_Prev(p) = nullptr; 为什么可以赋值 因为 是指针的引用
		*/
		static _Nodepref _Prev(_Nodeptr ptr) 
		{
			return ptr->_Prev;
		}

		static _Nodepref _Next(_Nodeptr ptr)
		{
			return ptr->_Next;
		}

	};

private:
	_Nodeptr _Head;
	size_t _Size;
	static _Nodeptr _Buynode(_Nodeptr _Parg = nullptr, _Nodeptr _Narg = nullptr)
	{

		//_Nodeptr s = (_Nodeptr)malloc(sizeof(_Nodeptr));  这个错的，因为 _Nodeptr 是指针类型，sizeof 是4字节 
		_Nodeptr s = (_Nodeptr)malloc(sizeof(*s));
		if (nullptr == s)exit(EXIT_FAILURE);
		//memset(s, 0, sizeof(*s));
		_Acc::_Prev(s) = (_Parg == nullptr ? s : _Parg);
		_Acc::_Next(s) = (_Narg == nullptr ? s : _Narg);
		return s;
	}

	static void Freenode(_Nodeptr p)
	{
		free(p);
	}
public:

	class const_iterator 
	{
	protected:
		_Nodeptr _Ptr;
	public:
		const_iterator(_Nodeptr _P = nullptr) :_Ptr(_P){}

		~const_iterator(){}
	
		const_reference operator*() const
		{
			return _Acc::_Value(_Ptr);
		}
	
		const_pointer operator->() const
		{
			//return &**this;  //*this => **this => &**this
			return &_Acc::_Value(this->_Ptr);
		}

		const_iterator& operator++()
		{//前置++
			//this->_Ptr = _Ptr->_Next;
			_Ptr = _Acc::_Next(this->_Ptr);
			return *this;
		}

		//
		const_iterator operator++(int)
		{//后置++  先取值 再跑
			const_iterator _tmp = *this;
			++* this;
			return _tmp;
		}

		const_iterator& operator--()
		{
			_Ptr = _Acc::_Prev(this->_Ptr);
			return *this;
		}

		const_iterator& operator--(int)
		{
			const_iterator _tmp = *this;
			--* this;
			return _tmp;
		}

		bool operator==(const const_iterator& x) const
		{
			return (this->_Ptr == x._Ptr);
		}
		bool operator!=(const const_iterator& x) const
		{
			return !(*this == x);
		}

		_Nodeptr MyNode() const
		{
			return _Ptr;
		};

	};

	class iterator :public const_iterator
	{
	public:
		iterator(_Nodeptr _P = nullptr) :const_iterator(_P) {}

		~iterator() {}

		reference operator*() const
		{
			return _Acc::_Value(const_iterator::_Ptr);
		}

		pointer operator->() const
		{
			//return &_Acc::_Value(this->_Ptr);
			return &**this;
		}

		iterator& operator++()
		{
			//this->_Ptr = _Ptr->_Next;
			const_iterator::_Ptr = _Acc::_Next(const_iterator::_Ptr);
			return *this;
		}

		iterator operator++(int)
		{
			iterator _tmp = *this;
			++* this;
			return _tmp;
		}

		iterator& operator--()
		{
			const_iterator::_Ptr = _Acc::_Prev(const_iterator::_Ptr);
			return *this;
		}

		iterator operator--(int)
		{
			iterator _tmp = *this;
			--* this;
			return _tmp;
		}

		bool operator==(const iterator& _X) const
		{
			return (const_iterator::_Ptr == _X._Ptr);
		}

		bool operator!=(const iterator& _X) const
		{
			return !(*this == _X);
		}

	};

public:

	iterator insert(const_iterator pos, const _Ty& value)
	{
		_Nodeptr p = pos.MyNode();
		_Acc::_Prev(p) = _Buynode(_Acc::_Prev(p), p);//3个步骤
		p = _Acc::_Prev(p);
		//p->prev->next = p;
		_Acc::_Next(_Acc::_Prev(p)) = p;
		new(&_Acc::_Value(p)) _Ty(value);
		_Size += 1;
		return iterator(p);
		/*tmp->_Value = value;
		tmp->_Next = _Acc::_Prev();
		tmp->_Next->_Prev = tmp;
		tmp->_Prev = _Acc::_Next();
		tmp->_Prev->_Next = tmp;*/
	}

	void insert(const_iterator pos, size_t count, const _Ty& value)
	{//注意 这是size_t 注意前置--和后置--
		while(count--)
		{
			insert(pos, value);		
		}
	}

	iterator push_back(const _Ty& val)
	{//尾插
		return insert(end(), val);
	}

	iterator push_front(const _Ty& val)
	{//尾插
		return insert(begin(), val);
	}

	MyList() 
		:_Head(_Buynode()), _Size(0)
	{
	
	}

	~MyList()
	{
		clear();
		Freenode(_Head);
	}

	size_t size()const { return _Size; }

	bool empty() const { return size() == 0; }

	iterator begin() { return iterator(_Acc::_Next(_Head)); }

	iterator end() { return iterator(_Head); }

	iterator erase(iterator pos)
	{
		_Nodeptr p = (pos++).MyNode();//直接处理了 非法化
		_Acc::_Next(_Acc::_Prev(p)) = _Acc::_Next(p);
		_Acc::_Prev(_Acc::_Next(p)) = _Acc::_Prev(p);

		(&_Acc::_Value(p))->~_Ty();
		//(_Acc::_Value(p)).~_Ty();  牵扯到继承关系
		Freenode(p);
		_Size -= 1;
		return pos;
	}

	void pop_back()
	{
		erase(--end());
	}

	void pop_front()
	{
		erase(begin());
	}

	void erase(iterator _F, iterator _L)
	{
		for (; _F != _L;)
		{
			erase(_F++);//如果 使用前置++  迭代器会失效
		}
	}

	void clear()
	{
		erase(begin(), end());
	}

	iterator find(const _Ty& val) const
	{
		iterator p = begin();

		while (p++ != end() && *p != val)++p;

		return p;
	}

	void remove(const _Ty& val)
	{
		iterator p = find(val);

		if(p != end())
		{
			erase(p);
		}

	}

	//const_iterator begin() 
	//{
	//	return const_iterator(_Acc::_Next(_Head)); 
	//}

	//const_iterator end() { return const_iterator(_Head); }


};
#endif 
