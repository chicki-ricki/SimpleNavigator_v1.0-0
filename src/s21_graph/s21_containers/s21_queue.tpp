#ifdef S21_QUEUE_H

template <typename T>
s21::Queue<T>::Queue(): arr_(0), top_(0), size_(0)
{}

template <typename T>
s21::Queue<T>&	s21::Queue<T>::operator=(const Queue & rhs)
{
	size_ = rhs->size_;
	arr_ = new T[size_];
	for (int i = 0; i < size_; i++)
		arr_[i] = rhs.arr_[i];
	top_ = rhs->top_;
	return (*this);
}

template <typename T>
s21::Queue<T>::Queue(const Queue &src)
{
	*this = src;
}

template <typename T>
s21::Queue<T>::~Queue()
{
	if (arr_)
		delete [] arr_;
}

// template <typename T>
// s21::Queue<T>::Queue(T elem): arr_(0), top_(0), size_(0)
// {}

template <typename T>
void	s21::Queue<T>::init()
{
	arr_ = new T[size_ + 1];
	bzero(arr_, size_ + 1);
}

template <typename T>
void	s21::Queue<T>::push(T const &elem)
{
	unsigned int	size_new = size_;
	T				*arr_new;

	if (size_ == 0)
	{
		arr_[size_] = elem;
		size_++;
	}
	else
	{
		size_new++;
		arr_new = new T[size_new];
		for (int i = 0; i < size_new; i++)
			arr_new[i] = arr_[i];
		arr_new[size_new - 1] = elem;
		top_ = &arr_new[0];
		if (arr_)
			delete [] arr_;
		arr_ = arr_new;
		size_ = size_new;
	}
}

template <typename T>
T	&s21::Queue<T>::pop()// gthtgbcfnm vfccbd
{
	if (size_ > 0)
	{
		top_++;
		
		for (int i = 0; i < size_; i++)
			arr_[i] = arr_[i + 1];
		size_--;
	}
	return (*top_);
}

template <typename T>
T	&s21::Queue<T>::peek()
{
	return (arr_[0]);
}

#endif