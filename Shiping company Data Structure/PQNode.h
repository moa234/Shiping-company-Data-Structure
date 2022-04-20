#pragma once
template <typename T>
class PQNode
{
	T data;
	double weight;
public:
	PQNode();
	PQNode(const T& item);
	PQNode(const T& item, double w);
	T getitem() const;
	void setitem(const T& item);
	void SetWeight(double w);
	double GetWeight();
};

template<typename T>
PQNode<T>::PQNode()
{
}

template<typename T>
PQNode<T>::PQNode(const T& item)
{
	data = item;
}


template<typename T>
PQNode<T>::PQNode(const T& item, double w)
{
	data = item;
	weight = w;
}


template<typename T>
T PQNode<T>::getitem() const
{
	return data;
}


template<typename T>
void PQNode<T>::setitem(const T& item)
{
	data = item;
}
template<typename T>
void PQNode<T>::SetWeight(double w)
{
	weight = w;
}



template<typename T>
double PQNode<T>::GetWeight()
{
	return weight;
}