#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

class Queue
{
	// Очередь
	int* Wait;
	// Максимальный размер очереди
	int MaxQueueLength;
	// Текущий размер очереди
	int QueueLength;

public:
	// Конструктор
	Queue(int m);

	//Деструктор
	~Queue();

	// Добавление элемента
	void Add(int c);

	// Извлечение элемента
	int Extract();

	// Очистка очереди
	void Clear();

	// Проверка существования элементов в очереди
	bool IsEmpty();

	// Проверка на переполнение очереди
	bool IsFull();

	// Количество элементов в очереди
	int GetCount();

	//демонстрация очереди
	void Show();
};

void Queue::Show() {
	cout << "\n-------------------------------------\n";
	//демонстрация очереди
	for (int i = 0; i < QueueLength; i++) {
		cout << Wait[i] << " ";
	}
	cout << "\n-------------------------------------\n";
}

Queue::~Queue()
{
	//удаление очереди
	delete[]Wait;
}

Queue::Queue(int m)
{
	//получаем размер
	MaxQueueLength = m;
	//создаем очередь
	Wait = new int[MaxQueueLength];
	// Изначально очередь пуста
	QueueLength = 0;
}

void Queue::Clear()
{
	// Эффективная "очистка" очереди 
	QueueLength = 0;
}

bool Queue::IsEmpty()
{
	// Пуст?
	return QueueLength == 0;
}

bool Queue::IsFull()
{
	// Полон?
	return QueueLength == MaxQueueLength;
}

int Queue::GetCount()
{
	// Количество присутствующих в стеке элементов
	return QueueLength;
}

void Queue::Add(int c)
{
	// Если в очереди есть свободное место, то увеличиваем количество
	// значений и вставляем новый элемент
	if (!IsFull())
		Wait[QueueLength++] = c;
}

int Queue::Extract()
{
	// Если в очереди есть элементы, то возвращаем тот, 
	// который вошел первым и сдвигаем очередь	
	if (!IsEmpty()) {
		//запомнить первый
		int temp = Wait[0];

		//сдвинуть все элементы
		for (int i = 1; i < QueueLength; i++)
			Wait[i - 1] = Wait[i];

		//уменьшить количество
		QueueLength--;
		//Wait[QueueLength - 1] = temp;

		//вернуть первый(нулевой)
		return temp;
		//return 1;
	}

	else // Если в стеке элементов нет
		return -1;
}

void main()
{
	srand(time(0));

	//создание очереди
	Queue QU(25);

	//заполнение части элементов
	for (int i = 0; i < 5; i++) {
		QU.Add(rand() % 50);
	}
	//показ очереди
	QU.Show();

	//извлечение элемента
	QU.Extract();

	//показ очереди
	QU.Show();
	QU.Extract();

	//показ очереди
	QU.Show();
}


