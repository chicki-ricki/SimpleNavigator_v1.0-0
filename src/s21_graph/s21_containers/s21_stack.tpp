#ifdef S21_STACK_H

template <typename T>
s21::Stack<T>::Stack(): arr_(0), top_(0), size_(0)
{}

template <typename T>
s21::Stack<T>&	s21::Stack<T>::operator=(const Stack & rhs)
{
	size_ = rhs->size_;
	arr_ = new T[size_];
	for (int i = 0; i < size_; i++)
		arr_[i] = rhs.arr_[i];
	top_ = rhs->top_;
	return (*this);
}

template <typename T>
s21::Stack<T>::Stack(const Stack &src)
{
	*this = src;
}

template <typename T>
s21::Stack<T>::~Stack()
{
	if (arr_)
		delete [] arr_;
}

// template <typename T>
// s21::Stack<T>::Stack(T elem): arr_(0), top_(0), size_(0)
// {}

template <typename T>
void	s21::Stack<T>::init()
{
	arr_ = new T[++size_];
	bzero(arr_, size_ - 1);
}

template <typename T>
void	s21::Stack<T>::push(T const &elem)
{
	unsigned int	size_new = size_;
	T				*arr_new;

	size_new++;
	arr_new = new T[size_new];
	for (int i = 0; i < size_new; i++)
		arr_new[i] = arr_[i];
	arr_new[size_new - 1] = elem;
	top_ = &arr_new[size_new - 1];
	if (arr_)
		delete [] arr_;
	arr_ = arr_new;
	size_ = size_new;
}

template <typename T>
void	s21::Stack<T>::pop()
{
	if (size_ > 0)
	{
		top_--;
		size_--;
	}
}

template <typename T>
T	&s21::Stack<T>::peek()
{
	return (arr_[size_ - 1]);
}

#endif