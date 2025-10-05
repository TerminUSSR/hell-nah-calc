#include <iostream>
#include <string>
#include <stack>
using namespace std;
int main(){
    istream& IN = cin;
    string exit;
    stack<char> stk;
    char c;
    bool lastOp = true;
    auto prec = [](char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return INT_MAX;
        if (op == '(') return INT_MIN;
        if (op == ')') return 0;
        throw exception("unknown operator");
        };
    auto pushOp = [&](char c = '(') {
        while (!stk.empty() && prec(stk.top()) >= prec(c)) {
            exit.push_back(stk.top());
            stk.pop();
        }
        };
    while (IN.peek() != '\n' && IN.peek() != '\0') {
        IN >> c;
        if(isdigit(c)){
            exit.push_back(c);
            lastOp = false;
        }
        else if (lastOp && c != '-' && c != '(') {
                cout << "Hell nah";
                return -1;
        }
        else if (lastOp && c == '-') exit.push_back('_');
        else {
            switch (c) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                pushOp(c);
                stk.push(c);
                lastOp = true;
                break;
            case '(':
                stk.push(c);
                lastOp = true;
                break;
            case ')':
                pushOp(c);
                stk.pop();
                break;
            default:
                throw exception("unknown operator");
            }
        }
    }
    pushOp();
    cout << exit;
}