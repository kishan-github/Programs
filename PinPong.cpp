#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cdn;
bool isPing = true;

void ping() {
	int i = 5;
	while (i > 0) {
		unique_lock<mutex> lock(mtx);
		cdn.wait(lock, [] { return isPing; });
		cout << "PING" << "\n";
		isPing = false;
		cdn.notify_one();
		i--;
	}
}

void pong() {
	int i = 5;
	while (i > 0) {
		unique_lock<mutex> lock(mtx);
		cdn.wait(lock, [] { return !isPing; });
		cout << "PONG" << "\n";
		isPing = true;
		cdn.notify_one();
		i--;
	}
}

void pingpong(bool isMyTurn, string word) {
	int i = 5;
	while (i > 0) {
		unique_lock<mutex> lock(mtx);
		cdn.wait(lock, [=] { return isPing == isMyTurn; });
		cout << word << "\n";
		isPing = !isMyTurn;
		cdn.notify_one();
		i--;
	}
}

class PingPongController {
private:
	mutex mtx;
	condition_variable cdn;
	bool isPing = true;
	int loopCount;

public:
	PingPongController(int count) {
		loopCount = count;
	}

	void run(bool isMyTurn, string word) {
		for (int i = 0; i < loopCount; ++i) {
			unique_lock<mutex> lock(mtx);
			cdn.wait(lock, [&] { return isPing == isMyTurn; });
			cout << word << "\n";
			isPing = !isMyTurn;
			cdn.notify_one();
		}
	}
};

void PingPongUsingSeparateMethods() {
	cout << "Start PingPongUsingSeparateMethods\n";
	thread t1(ping), t2(pong);

	t1.join();
	t2.join();
	cout << "End PingPongUsingSeparateMethods\n";
}

void PingPongUsingSameMethods() {
	cout << "Start PingPongUsingSameMethods\n";
	thread t1(pingpong, true, "PING"), t2(pingpong, false, "PONG");

	t1.join();
	t2.join();
	cout << "End PingPongUsingSameMethods\n";
}

void PingPongUsingControllerClass() {
	cout << "Start PingPongUsingControllerClass\n";
	PingPongController controller(5);
	thread t1([&] { controller.run(true, "PING"); });
	thread t2([&] { controller.run(false, "PONG"); });

	t1.join();
	t2.join();
	cout << "End PingPongUsingControllerClass\n";
}

int main() {
	PingPongUsingSeparateMethods();
	PingPongUsingSameMethods();
	PingPongUsingControllerClass();
	return 0;
}
