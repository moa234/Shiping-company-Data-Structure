#pragma once
template <typename T>
class Node
{
	T data;
	Node<T>* next;
public:
	Node();
	Node(const T& item);
	Node(const T& item,Node<T>* nxt);

};

template<typename T>
Node<T>::Node()
{
}

template<typename T>
Node<T>::Node(const T& item)
{
	data = item;
}

template<typename T>
 Node<T>::Node(const T& item, Node<T>* nxt)
{
	 data = item;
	 next = nxt;
}
