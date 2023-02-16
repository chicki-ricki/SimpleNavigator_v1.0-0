#ifdef S21_QUEUE_H

template <typename T>
s21::Queue<T>::Queue(): size_(0), head_(NULL), tail_(NULL)
{}

template <typename T>
s21::Queue<T>&	s21::Queue<T>::operator=(Queue const & rhs)
{
	// if (*this != rhs)
	// {
		size_ = rhs.size_;
		//clear
		while (head_ != nullptr)
			pop();
		QueueItem	*begin = rhs.head_;
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
	// }
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
	if (this == &qq)
		return (*this);
std::cout << "hello from  operator=" << std::endl;
	head_ = qq.head_;
	tail_ = qq.tail_;
	size_ = qq.size_;
	qq.head_ = nullptr;
	qq.tail_ = nullptr;
	qq.size_ = 0;
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
	//?
}

template <typename T>
void	s21::Queue<T>::init()
{
	tail_ = head_;
}

template <typename T>
void	s21::Queue<T>::push(T const &elem)
{
	QueueItem	*q = new QueueItem();
	q->value = elem;
	q->next = NULL;
	if (head_ == NULL)
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
	if (head_ == NULL)
		s21::exitError("Error: queue is empty");
	// T	rez = head_->value;
	head_ = head_->next;
	if (head_ == NULL)
		tail_ = NULL;
	size_--;
	return (head_->value);
}

template <typename T>
T	&s21::Queue<T>::peek()
{
	if (head_ == NULL)
		s21::exitError("Error: queue is empty");
	return (head_->value);
}

#endif