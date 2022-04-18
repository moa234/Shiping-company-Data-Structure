#pragma once
template <typename T>
class Node
{
	T data;
	Node<T>* next;
	double weight;
public:
	Node();
	Node(const T& item);
	Node(const T& item,Node<T>* nxt);
	Node(const T& item, double w);
	Node<T>* getnext() const;
	T getitem() const;
	void setnext(Node<T>* ptr);
	void setitem(const T& item);
	void SetWeight(double w);
	double GetWeight();
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

 template<typename T>
 Node<T>::Node(const T& item, double w)
 {
	 data = item;
	 weight = w;
 }

 template<typename T>
  Node<T>* Node<T>::getnext() const
 {
	 return next;
 }

  template<typename T>
  T Node<T>::getitem() const
  {
	  return data;
  }

  template<typename T>
  void Node<T>::setnext(Node<T>* ptr)
  {
	  next = ptr;
  }

  template<typename T>
  void Node<T>::setitem(const T& item)
  {
		data = item;
  }
  template<typename T>
  void Node<T>::SetWeight(double w)
  {
	  weight = w;
  }
 

  template<typename T>
  double Node<T>::GetWeight()
  {
	  return weight;
  }