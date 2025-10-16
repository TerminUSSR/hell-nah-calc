#include <iostream>
#include <string>
#include <sstream>
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
    exit.pop_back();
    return exit;
}
double calc(istream& IN){
    stack<double> stk;
    auto Oper = [&](char g) {
        double a = stk.top();
        stk.pop();
        double b = stk.top();
        stk.pop();
        switch (g) {
        case '+':
            stk.push(a + b);
            break;
        case '-':
            stk.push(b - a);
            break;
        case '*':
            stk.push(a * b);
            break;
        case '/':
            if (a == 0) throw exception("dont divide by zero");
            stk.push(b / a);
            break;
        case '^':
            double c = 1;
            for (int i = 0; i < a; i++) {
                c *= b;
            }
            stk.push(c);
        }
        };
    string c;
    while (IN.peek() != '\n' && IN.peek() != '\0' && !IN.eof()) {
        IN >> c;
        if (c[0] == '_') c[0] = '-';
        try { stk.push(stod(c)); }
        catch (invalid_argument& ia) {
            Oper(c[0]);
        }
    }
    if (stk.size() > 1) throw exception("hell nah");
    return stk.top();
}
double calc(const string& c) {
    istringstream ashot(c);
    return calc(ashot);
}
int main() {
    try { cout << calc(RPN()); }
    catch (exception& ex) {
        cout << ex.what();
    }
}