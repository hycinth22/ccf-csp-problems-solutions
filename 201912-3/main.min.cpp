#include <bits/stdc++.h>
using namespace std;
using element = string;

map<element, int> &operator+=(map<element, int> &a, const map<element, int> &b) {
    for (const auto &p : b) {
        a[p.first] += p.second;
    }
    return a;
}
map<element, int> operator*(int coef, const map<element, int> &b) {
    map<element, int> r;
    for (const auto &p : b) {
        r[p.first] = p.second * coef;
    }
    return r;
}

map<element, int> parseTerm(const string &str);
map<element, int> parseFormula(const string &str);
size_t parseCOEF(const string &str, size_t pos, int &coef);

map<element, int> parseTerm(const string &str) {
    map<element, int> r;
    if (str.front() == '(') {
        return parseFormula(str.substr(1, str.size() - 2));
    }
    ++r[str];
    return r;
}

map<element, int> parseFormula(const string &str) {
    map<element, int> r;
    size_t i = 0;
    int level = 0;
    string term;
    while (i < str.size()) {
        if (level > 0) {
            if (str[i] == '(') {
                ++level;
            } else if (str[i] == ')') {
                --level;
            }
            term += str[i];
            ++i;
        } else {

            // 在level=0，只有小写才代表上一项没有结束。
            if (islower(str[i])) {
                term += str[i];
                ++i;
            } else {
                // level=0，非小写一律代表上一个符号已经结束。
                // 此处处理
                if (!term.empty()) {
                    int co = 0;
                    i += parseCOEF(str, i, co);
                    r += co * parseTerm(term);
                    term.clear();
                }
                if (str[i] == '(') {
                    ++level;
                    term = str[i];
                    ++i;
                } else if (isupper(str[i])) {
                    term = str[i];
                    ++i;
                }
            }

        }

    }
    if (!term.empty()) {
        int co = 0;
        parseCOEF(str, i, co);
        r += co * parseTerm(term);
        term.clear();
    }
    return r;
}

size_t parseCOEF(const string &str, size_t pos, int &coef) {
    if (pos >= str.size()) {
        coef = 1;
        return 0;
    }
    coef = 0;
    size_t i = pos;
    if (isdigit(str[i])) {
        coef = str[i] - '0';
        ++i;
        while (i < str.size() && isdigit(str[i])) {
            coef = coef * 10 + (str[i] - '0');
            ++i;
        }
    } else {
        coef = 1;
    }
    return i - pos;
}

map<element, int> parseExpr(const string &str) {
    map<element, int> r;
    size_t i = 0, ni = str.find('+');
    if (ni == string::npos) {
        int coef, coeflen;
        coeflen = parseCOEF(str, 0, coef);
        r += coef * parseFormula(str.substr(coeflen));
    } else
        while (i != string::npos) {
            int coef, coeflen;
            coeflen = parseCOEF(str, i, coef);
            if (ni != string::npos) {
                r += coef * parseFormula(str.substr(i + coeflen, ni - (i + coeflen)));
            } else {
                r += coef * parseFormula(str.substr(i + coeflen));
            }
            if (ni != string::npos) {
                i = ni + 1;
                ni = str.find('+', i);
            } else {
                i = ni;
            }
        }
    return r;
}

bool legalEquation(const string &str) {
    size_t i = str.find('=');
    if (i == string::npos) return false;
    return parseExpr(str.substr(0, i)) == parseExpr(str.substr(i + 1, str.size()));
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    cin.get();
    while (n--) {
        string e;
        getline(cin, e);
        cout << (legalEquation(e) ? "Y" : "N") << endl;
    }
}
