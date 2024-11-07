#include<iostream>
#include<queue>
#include<string>

void generateBinaryNumbers(size_t n) {
    std::queue<std::string> q;
    
    q.push("1");

    while(n--) {
        std::string currentNumber = q.front();
        q.pop();

        std::cout << currentNumber << " ";

        q.push(currentNumber + "0");
        q.push(currentNumber + "1");
    }
}
