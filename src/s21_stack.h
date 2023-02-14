#ifndef S21_QUEUE_H
# define S21_QUEUE_H

class Stack
{
public:
	Stack(/* args */);
	~Stack();
	void	init();// - создание пустого стек/очереди
	void	push(Stack &);// - добавление элемента в стек/очередь
	void	pop();// - получение элемента из стека/очереди с его последующим удалением из стека/очереди
	void	peek();// - получение элемента из стека/очереди без его удаления из стека/очереди
private:
	/* data */
};


#endif