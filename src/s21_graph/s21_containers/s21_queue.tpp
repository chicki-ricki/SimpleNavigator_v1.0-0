#ifdef S21_QUEUE_H

template <typename T>
s21::Queue<T>::Queue(): size_(0), head_(nullptr), tail_(nullptr)
{}

template <typename T>
s21::Queue<T>&	s21::Queue<T>::operator=(Queue const & rhs)
{

	this->Clear();
	s21::Queue<T>::Copy(rhs);
	return (*this);
}

template <typename T>
s21::Queue<T>::Queue(const Queue &src): Queue()
{
	*this = src;
}

template <typename T>
s21::Queue<T>&	s21::Queue<T>::operator=(Queue &&qq)
{
	// if (this == &qq)
	// 	return (*this);
std::cout << "hello from  operator=" << std::endl;
	this->Clear();
	s21::Queue<T>::Copy(qq);
	qq->Clear();
	return (*this);
}

template <typename T>
s21::Queue<T>::Queue(Queue &&qq): Queue()
{
	std::cout << "hello from  &&qq" << std::endl;
	*this = qq;
}

template <typename T>
s21::Queue<T>::Queue(std::initializer_list<T> const& init) :Queue()
{
	for (auto it = init.begin(); it != init.end(); it++)
		push(*it);
}

template <typename T>
s21::Queue<T>::~Queue()
{
	this->Clear();
}

template <typename T>
void	s21::Queue<T>::init()
{
	tail_ = head_;
	size_ = -1;
}

template <typename T>
void	s21::Queue<T>::push(T const &elem)
{
	QueueItem	*q = new QueueItem();
	q->value = elem;
	q->next = nullptr;
	if (head_ == nullptr)
		tail_ = head_ = q;
	else
	{
		tail_->next = q;
		tail_ = q;
	}
	size_++;
}

template <typename T>
T	&s21::Queue<T>::pop()
{
	QueueItem	*ret = head_;

	if (head_ == nullptr)
		s21::exitError("Error: queue is empty");
	head_ = head_->next;
	if (head_ == nullptr)
		tail_ = nullptr;
	size_--;
	return (ret->value);
}

template <typename T>
T	&s21::Queue<T>::peek()
{
	if (head_ == nullptr)
		s21::exitError("Error: queue is empty");
	return (head_->value);
}

template <typename T>
unsigned int	s21::Queue<T>::getSize()
{
	return (size_);
}

template <typename T>
void	s21::Queue<T>::Copy(Queue const & rhs)
{
	QueueItem	*begin = rhs.head_;

	size_ = rhs.size_;
	while (begin != nullptr)
	{
		QueueItem	*tmp = new QueueItem();
		tmp->next = nullptr;
		tmp->value = begin->value;
		if (head_ == nullptr)
			head_ = tail_ = tmp;
		else
		{
			tail_->next = tmp;
			tail_ = tmp;
		}
		begin = begin->next;
	}
}

template <typename T>
void	s21::Queue<T>::Clear()
{
	while (head_ != nullptr)
		pop();
	tail_ = nullptr;
	size_ = 0;
}

#endif