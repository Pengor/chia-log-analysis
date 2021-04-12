all: chia-log-analysis

chia-log-analysis: main.cpp
	g++ -std=c++17 main.cpp -o chia-log-analysis -Wall -Wextra -Werror

clean:
	rm chia-log-analysis