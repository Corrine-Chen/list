#pragma once

#include<iostream>
using namespace std;

template<class T>
struct ListNode
{
	ListNode(const T& data = T())
		: _prev(0)
		, _next(0)
		, _data(data)
	{}

	ListNode<T>* _prev;
	ListNode<T>* _next;
	T _data;
};


template<class T, class Ref, class Ptr>
class __ListIterator__
{
	typedef __ListIterator__<T, T&, T*> Iterator;
	typedef __ListIterator__<T, const T&, const T*> ConstIterator;
	typedef __ListIterator__<T, Ref, Ptr> Self;
	typedef ListNode<T>* LinkType;
	typedef Ref Reference;
	typedef Ptr Pointer;

public:
	__ListIterator__(LinkType x = 0)
	{}
	__ListIterator__(const Iterator& x)
		:_node(x._node)
	{}
	bool operator==(const Iterator& x)
	{
		return _node==x._node;
	}
	bool operator!=(const Iterator& x)
	{
		return _node!=x._node;
	}
	Reference operator*()
	{
		return (*_node)._data;
	}
	Pointer operator->()
	{
		return (&operator*());
	}
	Self& operator++()//前置++
	{
		_node=_node->_next;
		return *this;
	}
	Self operator++(int)//后置++
	{
		Self p(*this);
		_node=_node->_next;
		retuen p;
	}
	Self& operator--()//前置--
	{
		_node=_node->_prev;
		return *this;
	}
	Self operator--(int)//后置--
	{
		Self *p(*this);
		_node=_node->_prev;
		return p;
	}
public:
	LinkType _node;
};


template<class T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef T ValueType;
	typedef ValueType& Reference;
	typedef const ValueType& ConstReference;
	typedef ValueType* Pointer;
	typedef const ValueType* ConstPointer;
	typedef Node* LinkType;
	typedef size_t SizeType;
	typedef __ListIterator__<T, T&, T*> Iterator;
	typedef __ListIterator__<T, const T&, const T*> ConstIterator;

public:
	List()//构造函数
	{
		EmptyInit();
	}
	List(SizeType n, const T& data)
	{
		for(size_t i=0; i<n; i++)
		{
			PushBack(data);
		}
	}
	List(const List<T>& 1)//拷贝构造函数
	{
		EmptyInit();
		Iterator it =1._node->_next;
		for(size_t i=0; i<1.Size();i++)
		{
			PushBack(1._node->_data);
			it++;
		}
	}

	~List()//析构函数
	{
		Clear();
		delete _node;
	}
	List<T>& operator=(const List<T>& l);
	////////////////////////////////////////////
	Iterator Begin()// 返回指向链表第一个元素的迭代器指针。
	{
		return _node->_next;
	}
	ConstIterator Begin()const
	{
		return _node->_next;
	}
	Iterator End()//返回指向链表最后一个元素之后的迭代器指针。 
	{
		return _node;
	}
	ConstIterator End()const
	{
		return _node;
	}
	bool Empty()//判空
	{
		return _node==_node->_next;
	}
	SizeType Size()const//返回链表实际元素的个数
	{
		Iterator it(_node->_next);
		size_t t=0;
		while(it!=_node)
		{
			++t;
			++it;
		}
		return t;
	}
	//SizeType MaxSize()const//返回链表可能容纳的最大元素数量
	
	Reference Front()//返回第一个元素的引用
	{
		return(*Begin());
	}
	ConstIterator Front()const
	{
		return(*Begin());
	}
	Reference Back()//返回最后一个元素的后一个指针
	{
		return (*(--End()));
	}
	ConstReference Back()const
	{
		return (*(--End()));
	}
	Iterator Insert(Iterator pos, const T& x = T())//在链表中插入pos元素
	{
		 Iterator p=new Node(x);
		 p._node->_next=pos._node;
		 p._node->_prev=pos._node->prev;
		 pos._node->_prev->_next=p._node;
		 pos._node->prev->=p._node;
		 return tmp;
	}
	void PushFront(const T& x)
	{
		Insert(Begin(),x);
	}
	void PushBack(const T& x)
	{
		Insert(--End(),x);
	}
	Iterator Erase(Iterator pos)
	{
		Iterator ret = pos.node->_next;
		pos._node->_next->_prev=pos._node->_prev;
		pos._node->_prev->_next=pos._node->next;
		pos._node->_prev=NULL;
		pos._node->_next=NULL;
		delete pos._node;
		return ret;
	}
	void PopFront()
	{
		Erase(Begin());
	}
	void PopBack()
	{
		Erase(--End());
	}
	void ReSize(SizeType newsize, const T& data)//调整容器大小
	{
		if(newsize<Size())
		{
			size_t i=Size()-newsize;
			while(i--)
			{
				PopBack();
			}
		}
		else
		{
			size_t j=newsize-Size();
			while(j--);
			{
				PushBack();
			}
		}
	}
	//void Assign(SizeType n, const T& data)//将n个值为data拷贝赋值给链表
	//{

	//}
	void Clear()//清空
	{
		Iterator it = _node->next;
		while(it!=_node)
		{
			Erase(it);
		}
		_node->_next=_node;
		_node->prev=_node;
	}
private:
    void EmptyInit()
	{
		_node=new Node;
		_node->data=0;
		_node->_next=_node;
		_node->_prev=_node;
	}
protected:
	LinkType _node;
};

int main()
{

	system("pause");
	return 0;
}