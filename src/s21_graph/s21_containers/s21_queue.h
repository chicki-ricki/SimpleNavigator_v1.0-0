#ifndef S21_QUEUE_H
# define S21_QUEUE_H

# include <strings.h>
# include <iostream>
# include <initializer_list>

# include "s21_utils.h"

namespace s21
{
	template <class T>
	class Queue
	{
	public:
		Queue();									//конструктор по умолчанию
		Queue&	operator=(Queue const &);
		Queue(const Queue &);						//конструктор копирования
		Queue&	operator=(Queue &&);
		Queue(Queue &&);							//конструктор перемещения
		Queue(std::initializer_list<T> const& init);//конструктор со списком инициализации
		~Queue();
		void	init();
		void	push(T const &);
		T		&pop();
		T		&peek();
	private:
		struct QueueItem
		{
			T					value;
			QueueItem	*next;
		};
		unsigned int		size_;
		QueueItem	*head_;
		QueueItem	*tail_;
	};
}

# include "s21_queue.tpp"

#endif