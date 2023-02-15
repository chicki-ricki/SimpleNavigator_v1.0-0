#ifndef S21_QUEUE_H
# define S21_QUEUE_H

namespace s21
{
	template <class T>
	class Queue
	{
	public:
		Queue();
		~Queue();
		void	init();
		void	push(Queue &);
		void	pop();
		void	peek();
	private:
		std::vector<T>	vec_;
		unsigned int	size_;
	};
}

#endif