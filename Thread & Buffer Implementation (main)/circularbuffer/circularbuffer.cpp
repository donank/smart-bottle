#include "circularbuffer.h"
    
template<class T>
bool Circularbuffer<T>::empty() const {
    //if head and tail are equal, we are empty
	return (!full_ && (head_ == tail_));
}

template<class T>
bool Circularbuffer<T>::full() const
{
	//If tail is ahead the head by 1, we are full
	return full_;
}

template<class T>
void Circularbuffer<T>::reset()
{
	std::lock_guard<std::mutex> lock(mutex_);
	head_ = tail_;
	full_ = false;
}

template<class T>
size_t Circularbuffer<T>::capacity() const
{
	return max_size_;
}

template<class T>
size_t Circularbuffer<T>::size() const
{
	size_t size = max_size_;

	if(!full_)
	{
		if(head_ >= tail_)
		{
			size = head_ - tail_;
		}
		else
		{
			size = max_size_ + head_ - tail_;
		}
	}

	return size;
}

template<class T>
void Circularbuffer<T>::put(T item)
{
	std::lock_guard<std::mutex> lock(mutex_);

	buf_[head_] = item;

	if(full_)
	{
		tail_ = (tail_ + 1) % max_size_;
	}

	head_ = (head_ + 1) % max_size_;

	full_ = head_ == tail_;
}

template<class T>
T Circularbuffer<T>::get()
{
	std::lock_guard<std::mutex> lock(mutex_);

	if(empty())
	{
		return T();
	}

	//Read data and advance the tail (we now have a free space)
	auto val = buf_[tail_];
	full_ = false;
	tail_ = (tail_ + 1) % max_size_;

	return val;
}

