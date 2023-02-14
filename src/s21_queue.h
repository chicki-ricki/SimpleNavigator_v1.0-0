#ifndef S21_QUEUE_H
# define S21_QUEUE_H

class Queue
{
public:
	Queue();
	~Queue();
	void	init();
	void	push(Queue &);
	void	pop();
	void	peek();
};

#endif