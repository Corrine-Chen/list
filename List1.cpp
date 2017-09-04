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
		return &(operator*());
	}
	Self& operator++()//ǰ��++
	{
		_node=_node->_next;
		return *this;
	}
	Self operator++(int)//����++
	{
		Self p(*this);
		_node=_node->_next;
		retuen p;
	}
	Self& operator--()//ǰ��--
	{
		_node=_node->_prev;
		return *this;
	}
	Self operator--(int)//����--
	{
		LinkType p(*this);
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
	List()//���캯��
	{
		EmptyInit();
	}
	List(SizeType n, const T& data)
	{
		_node=new Node[data];
		LinkType NewNode=_node;
		for(size_t i=0; i<n; i++)
		{
			NewNode->_next = new Node[data];
			NewNode->_prev = _node;
			NewNode->_next->_prev = NewNode;
			_node->_next=NewNode;
			NewNode=NewNode->_next;
		}
		NewNode->_next=_node;
		_node->_prev=NewNode;
	}
	List(const List<T>& t)//�������캯��
	{
		EmptyInit();
		Iterator it =t._node ->_next;
		for(size_t i=0; i<t.Size();i++)
		{
			PushBack(t._node->_data);
			it++;
		}
	}

	~List()//��������
	{
		Clear();
		delete _node;
	}
	List<T>& operator=(const List<T>& l);
	////////////////////////////////////////////
	Iterator Begin()// ����ָ�������һ��Ԫ��֮��ĵ�����ָ�롣
	{
		return _node->_next;
	}
	ConstIterator Begin()const
	{
		return _node->_next;
	}
	Iterator End()//����ָ���������һ��Ԫ��֮��ĵ�����ָ�롣 
	{
		return _node;
	}
	ConstIterator End()const
	{
		return _node;
	}
	bool Empty()//�п�
	{
		return _node==_node->_next;
	}
	SizeType Size()const//��������ʵ��Ԫ�صĸ���
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
	//SizeType MaxSize()const//��������������ɵ����Ԫ������
	
	Reference Front()//���ص�һ��Ԫ�ص�����
	{
		return(*Begin());
	}
	ConstIterator Front()const
	{
		return(*Begin());
	}
	Reference Back()//�������һ��Ԫ�صĺ�һ��ָ��
	{
		return (*(--End()));
	}
	ConstReference Back()const
	{
		return (*(--End()));
	}
	Iterator Insert(Iterator pos, const T& x = T())//�������в���posԪ��
	{
		 LinkType temp=new Node(x);
		 temp->_next=pos._node;
		 temp->_prev=pos._node->_prev;
		 pos._node->_prev->_next=temp;
		 temp->_prev->_next=temp;
		 return temp;
	}
	void PushFront(const T& x)
	{
		Insert(Begin(),x);
	}
	void PushBack(const T& x)
	{
		Insert(End(),x);
	}
	Iterator Erase(Iterator pos)
	{
		Iterator temp = pos._node->_next;
		pos._node->_next->_prev=pos._node->_prev;
		pos._node->_prev->_next=pos._node->_next;
		pos._node->_prev=NULL;
		pos._node->_next=NULL;
		delete pos._node;
		return temp;
	}
	void PopFront()
	{
		Erase(Begin());
	}
	void PopBack()
	{
		Erase(End());
	}
	void ReSize(SizeType newsize, const T& data)//����������С
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
	//void Assign(SizeType n, const T& data)//��n��ֵΪdata������ֵ������
	//{

	//}
	void Clear()//���
	{
		Iterator it = _node->_next;
		while(it!=_node)
		{
			Erase(it);
		}
		_node->_next=_node;
		_node->_prev=_node;
	}
private:
    void EmptyInit()
	{
		_node=new Node;
		_node->_data=0;
		_node->_next=_node;
		_node->_prev=_node;
	}
public:
	LinkType _node;
};
void Funtest()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);

	List<int>::Iterator  it ;
	it= l._node->_next;
	while(it != l._node)
    {
        cout<<*it<<"->";
        ++it;
    }
    cout<<"NULL"<<endl;
}
int main()
{
	Funtest();
	system("pause");
	return 0;
}



