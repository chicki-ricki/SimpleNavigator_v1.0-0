#ifndef S21_STACK_H
# define S21_STACK_H

# include <strings.h>

# include "s21_utils.h"

namespace s21
{
	template <class T>
	class Stack
	{
	public:
		Stack();
		Stack&	operator=(const Stack &);
		Stack(const Stack &);
		Stack&	operator=(Stack &&);
		Stack(Stack &&);							//конструктор перемещения
		Stack(std::initializer_list<T> const& init);//конструктор со списком инициализации
		~Stack();
		void			init();// - создание пустого стек/очереди
		void			push(T const &);// - добавление элемента в стек/очередь
		T				&pop();// - получение элемента из стека/очереди с его последующим удалением из стека/очереди
		T				&peek();// - получение элемента из стека/очереди без его удаления из стека/очереди
		unsigned int	getSize();
	private:
		void	Copy(Stack &);
		void	Clear();
		struct StackItem
		{
			T			value;
			StackItem	*next;
		};
		unsigned int	size_;
		StackItem		*head_;
	};
}

# include "s21_stack.tpp"

#endif