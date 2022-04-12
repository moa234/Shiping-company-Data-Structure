#pragma once
#include "Node.h"
template<typename T>
class PqNode : public Node<T>
{
	int weight;
public:
	PqNode();
	PqNode(const T& item);
	PqNode(const T& item, int w);
	PqNode(const T& item, Node<T>* nxt);
	void SetWeight(int w);
	int GetWeight();
};

template<typename T>
PqNode<T>::PqNode()
{
}

template<typename T>
 PqNode<T>::PqNode(const T& item):Node(item)
{
}

 template<typename T>
 PqNode<T>::PqNode(const T& item, int w): Node(item)
 {
	 weight = w;
 }

 template<typename T>
 PqNode<T>::PqNode(const T& item, Node<T>* nxt): Node(item,nxt)
 {
 }

 template<typename T>
 void PqNode<T>::SetWeight(int w)
 {
	 weight = w;
 }

 template<typename T>
 int PqNode<T>::GetWeight()
 {
	 return weight;
 }
