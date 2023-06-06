#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <stack>
#include <cstddef>

using namespace std;

double pok = 0;
struct Stack{
    char zn;
    double num;
    Stack *next;
};

Stack *top1 = nullptr, *top2 = nullptr;

int error(string s) {
    int ex = 0;
    int cif = 0;
    int bal = 0;
    for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                bal++;
            }
            if (s[i] == ')') {
                bal -= 1;
            }
            if (bal < 0) {
                ex = 1;
            }
    }
    if (bal != 0) {
        ex = 1;
    }
    for (int i = 0; i < s.length()-1; i++) {
        if (s[i] == '/' && s[i+1] == '+' ||
            s[i] == '/' && s[i+1] == '-' ||
            s[i] == '/' && s[i+1] == '*' ||
            s[i] == '/' && s[i+1] == '/' ||
            s[i] == '/' && s[i+1] == '^' ||
            s[i] == '+' && s[i+1] == '+' ||
            s[i] == '+' && s[i+1] == '-' ||
            s[i] == '+' && s[i+1] == '*' ||
            s[i] == '+' && s[i+1] == '/' ||
            s[i] == '+' && s[i+1] == '^' ||
            s[i] == '-' && s[i+1] == '+' ||
            s[i] == '-' && s[i+1] == '-' ||
            s[i] == '-' && s[i+1] == '*' ||
            s[i] == '-' && s[i+1] == '/' ||
            s[i] == '-' && s[i+1] == '^' ||
            s[i] == '*' && s[i+1] == '+' ||
            s[i] == '*' && s[i+1] == '-' ||
            s[i] == '*' && s[i+1] == '*' ||
            s[i] == '*' && s[i+1] == '/' ||
            s[i] == '*' && s[i+1] == '^' ||
            s[i] == '^' && s[i+1] == '-' ||
            s[i] == '^' && s[i+1] == '+' ||
            s[i] == '^' && s[i+1] == '*' ||
            s[i] == '^' && s[i+1] == '/' ||
            s[i] == '^' && s[i+1] == '^' ||
            s[i] == '(' && s[i+1] == ')') {
                ex = 1;
            }
    }
    if (s[0] == '+' || s[0] == '*' || s[0] == '/') {
        ex = 1;
    }
    int n = s.length()-1;
    if (s[n] == '+' || s[n] == '*' || s[n] == '/') {
        ex = 1;
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == '(' && s[i+1] == '+' ||
            s[i] == '(' && s[i+1] == '/' ||
            s[i] == '(' && s[i+1] == '*') {
               ex = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == '+' && s[i+1] == ')' ||
            s[i] == '-' && s[i+1] == ')' ||
            s[i] == '/' && s[i+1] == ')' ||
            s[i] == '*' && s[i+1] == ')') {
               ex = 1;
        }
    }
    for (int i = 0; i < s.length()-1; i++) {
        if (s[i] >= '0' && s[i] <= '9' && s[i+1] == '(') {
            ex = 1;
        }
        if (s[i+1] >= '0' && s[i+1] <= '9' && s[i] == ')') {
            ex = 1;
        }
    }
    for (int i = 0; i < s.length(); i ++) {
        if (s[i] >= '0' && s[i] <= '9') {
            cif++;
        }
    }
    if (cif == 0) {
        ex = 1;
    }
    for (int i = 0; i < s.length(); i++) {
        if (s[i] > '9' && s[i] != '+' && s[i] != '(' && s[i] != ')'
            && s[i] != '-' && s[i] != '*' && s[i] != '/'
            && s[i] != '^' && s[i] != 's' && s[i] != 'c'
            && s[i] != 't' && s[i] != 'q' && s[i] != 'l' && s[i] != 'x' && s[i] != '.') {
                ex = 1;
        }
        if (s[i] < '0' && s[i] != '+' && s[i] != '(' && s[i] != ')'
            && s[i] != '-' && s[i] != '*' && s[i] != '/'
            && s[i] != '^' && s[i] != 's' && s[i] != 'c'
            && s[i] != 't' && s[i] != 'q' && s[i] != 'l' && s[i] != 'x' && s[i] != '.') {
                ex = 1;
        }
    }
    return ex;
}
void push(Stack *&top, char zn, double num) {
    Stack *p = new(Stack);
    p -> num = num;
    p -> zn = zn;
    p -> next = top;
    top = p;
}
Stack pop(Stack *&top) {
    Stack t = *top;
    top = top -> next;
    return t;
}
void apply(char zn) {
    double c;
    double ESP = 0.0000001;
    if (zn == 's' || zn == 'c' || zn == 't' || zn == 'q' || zn == 'l') {
        double a = pop(top1).num;
        if (zn == 's') {
            c = sin(a);
        }
        if (zn == 'c') {
            c = cos(a);
        }
        if (zn == 't') {
            if (fabs(cos(a)) != ESP) {
                c = tan(a);
            } else {
                pok++;
                return;
            }
        }

        if (zn == 'q') {
            if (a > (0 - ESP)) {
                c = sqrt(a);
            } else {
                pok++;
                return;
            }
        }
        if (zn == 'l') {
            if (a > ESP) {
                c = log(a);
            } else {
                pok++;
                return;

            }
        }
    } else {
        double b = pop(top1).num;
        double a = pop(top1).num;
        if (zn == '+') {
            c = a + b;
        }
        if (zn == '-') {
            c = a - b;
        }
        if (zn == '*') {
            c = a * b;
        }
        if (zn == '/') {
            if (abs(b) < ESP) {
            pok++;
            return;
            }
            c = a / b;
        }
        if (zn == '^') {
            c = pow(a, b);
        }
    }
    push(top1, '@', c);
    return;
}
int pri(char ele) {
    int a;
    if (ele == '(') {
        a = 0;
    }
    if (ele == '+' || ele == '-') {
        a = 1;
    }
    if (ele == '/' || ele == '*') {
        a = 2;
    }
    if (ele == '^') {
        a = 3;
    }
    if (ele == 's' || ele == 'l' ||
        ele == 'c' || ele == 'q' ||
        ele == 't') {
        a = 4;
    }
    return a;
}
void replaceall(string &s, string s1, string s2) {
    size_t in = s.find(s1);
    while (in != std::string::npos) {
        s.replace(in, s1.length(), s2);
        in = s.find(s1, in + s2.length());
    }
}
int calc(string s, double &ans) {
    if (s[0] == '-') {
        s = '0' + s;
    }
    string ss;
    for (int i = 0; i < s.length(); i++) {
        if (i < s.length() - 1 && s[i] == '(' && s[i+1] == '-') {
            ss += s[i];
            ss += '0';
        } else {
            ss += s[i];
        }
    }
    s = ss;
    replaceall(s, "sin", "s");
    replaceall(s, "ln", "l");
    replaceall(s, "sqrt", "q");
    replaceall(s, "cos", "c");
    replaceall(s, "tg", "t");
    if(error(s) == 1) {
        return(-1);
    }


    for  (int i = 0; i < s.length(); i++) {
            if (s[i] >= '0' && s[i] <= '9') {
                double x = 0;
                while (s[i] >= '0' && s[i] <= '9') {
                    x *= 10;
                    x += (s[i] - '0');
                    i++;
                }
                if (s[i] == '.'){
                    i++;
                    double t = 10;
                    int j = i;
                    while (s[j] >= '0' && s[i] <= '9') {
                        double r = s[j] - '0';
                        x += r/t;
                        t *= 10;
                        j++;
                        i++;
                    }

                }
                push(top1, '@', x);
            }
            if (s[i] == '(') {
                push(top2, s[i], 0.0);
            }
            if (s[i] == ')') {
                while ((*top2).zn != '(') {
                     apply(pop(top2).zn);
                     if (pok > 0) {
                        pok = 0;
                        return -1;
                     }
                }
                pop(top2);
            }
            if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '^'
                || s[i] == '*' || s[i] == 's' || s[i] == 'l'
                || s[i] == 'c' || s[i] == 'q' || s[i] == 't') {
                    while (top2 != nullptr && pri(s[i]) <= pri((*top2).zn)) {
                        apply(pop(top2).zn);
                        if (pok > 0) {
                            pok = 0;
                            return -1;
                        }
                    }
                    push(top2, s[i], 0.0);
            }
    }
    while (top2 != nullptr) {
        apply(pop(top2).zn);
        if (pok > 0) {
            pok = 0;
            return -1;
        }
    }
    ans = pop(top1).num;
    return 0;
}

