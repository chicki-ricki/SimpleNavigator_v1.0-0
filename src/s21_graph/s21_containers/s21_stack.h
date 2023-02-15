#ifndef S21_STACK_H
# define S21_STACK_H

# include <strings.h>

namespace s21
{
	template <class T>
	class Stack
	{
	public:
		Stack();
		Stack&	operator=(const Stack &);
		Stack(const Stack &);
		~Stack();
		// Stack(T);
		void	init();// - создание пустого стек/очереди
		void	push(T const &);// - добавление элемента в стек/очередь
		T		&pop();// - получение элемента из стека/очереди с его последующим удалением из стека/очереди
		T		&peek();// - получение элемента из стека/очереди без его удаления из стека/очереди
	private:
		T				*arr_;
		T				*top_;
		unsigned int	size_;
	};
}

# include "s21_stack.tpp"

#endif