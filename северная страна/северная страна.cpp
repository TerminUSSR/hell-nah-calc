#include <iostream>
#include <string>
#include <stack>
using namespace std;
string RPN(istream& IN = cin) {
    string exit;
    stack<char> stk;
    char c;
    int skCount = 0;
    bool lastOp = true;
    auto prec = [](char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == '^') return INT_MAX;
        if (op == '(') return INT_MIN;
        if (op == ')') return 0;
        };
    auto pushOp = [&](char c = '(') {
        while (!stk.empty() && prec(stk.top()) >= prec(c)) {
            if (stk.top() == '(') throw exception("close your skobkas");
            exit.push_back(stk.top());
            exit.push_back(' ');
            stk.pop();
        }
        };
    while (IN.peek() != '\n' && IN.peek() != '\0') {
        if (!lastOp && IN.peek() == '(') c = '*';
        else IN >> c;
        if (isdigit(c) && lastOp) {
            exit.push_back(c);
            if (!isdigit(IN.peek())) { 
                exit.push_back(' ');
                lastOp = false;
            };
        }
        else if (lastOp && c != '-' && c != '(') {
            throw exception("Hell nah");
        }
        else if (lastOp && c == '-') { 
            exit.push_back('_');
            if (IN.peek() == '(') {
                exit.push_back('1');
                exit.push_back(' ');
                lastOp = false;
            }
        }
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
                skCount++;
                break;
            case ')':
                if (skCount <= 0) {
                    throw exception("open your skobkas");
                }
                pushOp(c);
                stk.pop();
                if (isdigit(IN.peek())) {
                    pushOp('*');
                    stk.push('*');
                    lastOp = true;
                }
                break;
            default:
                throw exception("unknown operator");
            }
        }
    }
    if (lastOp) {
        throw exception("lack of arguments");
    }
    pushOp();
    return exit;
}
double calc(istream& IN){
    stack<double> stk;
    string c;
    IN >> c;
    try { stk.push(stod(c)); }
    catch (out_of_range& oor) {
        //вернуть дабл
    }
    catch (invalid_argument& ia) {
        //s
    }
}
int main(){
    cout << RPN();
}