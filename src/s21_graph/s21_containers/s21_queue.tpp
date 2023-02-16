#ifdef S21_QUEUE_H_

template <typename T>
s21::Queue<T>::Queue(): size_(0), head_(NULL), tail_(NULL)
{}

template <typename T>
s21::Queue<T>&	s21::Queue<T>::operator=(const Queue & rhs)
{
	size_ = rhs.size_;
	head_ = rhs.head_;
	tail_ = rhs.tail_;
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