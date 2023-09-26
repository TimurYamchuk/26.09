#include <iostream>
#include <ctime>

using namespace std;

class Reel {
private:
    char symbols[5] = {'$', '7', 'B', 'C', 'D'};
    char* reels;
    int front;
    int rear;

public:
    Reel(int s) {
        reels = new char[s];
        front = -1;
        rear = -1;
    }

    ~Reel() {
        delete[] reels;
    }

    void Enqueue(char symbol) {
        if (IsFull()) {
            Dequeue();
        }

        if (IsEmpty()) {
            front = 0;
        }

        rear = (rear + 1) % 3;
        reels[rear] = symbol;
    }

    char Dequeue() {
        if (IsEmpty()) {
            throw runtime_error("Queue is empty");
        }

        char dequeuedSymbol = reels[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % 3;
        }

        return dequeuedSymbol;
    }

    bool IsEmpty() {
        return front == -1;
    }

    bool IsFull() {
        return (rear + 1) % 3 == front;
    }

    char Spin() {
        return symbols[rand() % 5];
    }
};

int main() {
    srand(1234);

    double balance = rand() % 5000 + 1000;
    double price = 100;

    cout << "Your Current Balance = " << balance << endl;
    cout << "The Game cost = " << price << endl;

    Reel reelsQueue(3);

    cout << "Welcome to the Game!" << endl;
    cout << "Press Enter to play. Press any other key to exit." << endl;

    while (cin.get() == '\n') {
        if (balance >= price) {
            balance -= price;

            char results[3];
            for (int i = 0; i < 3; i++) {
                char result = reelsQueue.Spin();
                cout << "Reel " << i + 1 << ": " << result << endl;
                results[i] = result;
            }

            for (int i = 0; i < 3; i++) {
                reelsQueue.Enqueue(results[i]);
            }

            if (reelsQueue.IsEmpty()) {
                cout << "You didn't win anything. Balance: $" << balance << endl;
            } else if (reelsQueue.IsFull()) {
                char symbol1 = reelsQueue.Dequeue();
                char symbol2 = reelsQueue.Dequeue();
                char symbol3 = reelsQueue.Dequeue();

                if (symbol1 == symbol2 && symbol2 == symbol3) {
                    double winAmount = price * 10;
                    balance += winAmount;
                    cout << "Congratulations! You won $" << winAmount << "! Balance: $" << balance << endl;
                } else if (symbol1 == symbol2 || symbol2 == symbol3 || symbol1 == symbol3) {
                    double halfWin = price / 2;
                    balance += halfWin;
                    cout << "Congratulations! You won $" << halfWin << "! Balance: $" << balance << endl;
                } else {
                    cout << "You didn't win this time. Balance: $" << balance << endl;
                }
            }
        } else {
            cout << "Not enough balance to play. Balance: $" << balance << endl;
        }
    }

    return 0;
}
