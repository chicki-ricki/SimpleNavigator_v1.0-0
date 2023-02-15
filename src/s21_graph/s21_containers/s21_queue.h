#ifndef S21_QUEUE_H
# define S21_QUEUE_H

# include <strings.h>
# include <iostream>

namespace s21
{
	template <class T>
	class Queue
	{
	public:
		Queue();
		Queue&	operator=(const Queue &);
		Queue(const Queue &);
		~Queue();
		void	init();
		void	push(T const &);
		T		&pop();
		T		&peek();
	private:
		T				*arr_;
		T				*top_;
		unsigned int	size_;
	};
}

# include "s21_queue.tpp"

#endif