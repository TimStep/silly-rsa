#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> empty{};

std::vector<int> int_to_vec(int n) {
    std::vector<int> res{};
    while (n>0) {
        res.insert(res.begin(), n%10);
        n /= 10;
    }
    return res;
}

void vector_out(std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i];
    }
}

class big_integer { //supports natural numbers only
    public:
        std::vector<int> digits;
        big_integer(int n) {
            digits = int_to_vec(n);
        }
        big_integer() {
            digits = empty;
        }
        //void out() { vector_out((*this).digits);} //deprecated since overloaded cout
        friend big_integer operator * (big_integer num1, big_integer num2);
        //friend big_integer operator *= (big_integer n1, big_integer n2) { return (n1*n2); }
        friend big_integer operator + (big_integer n1, big_integer n2);
        friend big_integer operator - (big_integer n1, big_integer n2);
        int to_int(big_integer n);
};

std::ostream& operator << (std::ostream &os, const big_integer& bi) {
    for (int i = 0; i < bi.digits.size(); i++) {
        os << bi.digits[i];
    }
    return os;
}

/*
int big_integer::to_int(big_integer n) {
    int res = 0;
    int p = 0;
    for (int i = n.digits.size())
}
*/

big_integer operator * (big_integer n1, big_integer n2) {

    big_integer res = big_integer(0);
    res.digits.resize(n1.digits.size() + n2.digits.size());
    std::fill(res.digits.begin(), res.digits.end(), 0);
    //std::cout << res << std::endl; //debug
    for (int i = 0; i < n2.digits.size(); i++) {
        for (int j = 0; j < n1.digits.size(); j++) {
            res.digits[res.digits.size() - 1 - i - j] += n1.digits[n1.digits.size() - 1 - j]*n2.digits[n2.digits.size() - 1 - i];
        }
        
    }
    //std::cout << res << std::endl; //debug
    for (int k = res.digits.size() - 1; k >= 0; k--) {
        res.digits[k-1] += (res.digits[k] / 10);
        res.digits[k] %= 10;
    }
    //std::cout << res << std::endl; //debug
    std::reverse(res.digits.begin(), res.digits.end());
    while (res.digits[res.digits.size() - 1] == 0) {
        res.digits.pop_back();
    }
    std::reverse(res.digits.begin(), res.digits.end());
    return res;
}

big_integer operator + (big_integer n1, big_integer n2) {

    /*
    if (n2.digits.size() >= n1.digits.size()) {
        big_integer res = n2;
    }
    else {
        big_integer res = n1;
        n1 = n2;
        n2 = res;
    }
    */

    while (n1.digits.size() < n2.digits.size()) { n1.digits.insert(n1.digits.begin(), 0); }
    while (n2.digits.size() < n1.digits.size()) { n2.digits.insert(n2.digits.begin(), 0); }
    big_integer res;
    //int delta = n2.digits.size() - n1.digits.size();
    for (int i = n1.digits.size()-1; i > -1; i--) { res.digits.push_back(n1.digits[i] + n2.digits[i]); }
    res.digits.push_back(0);
    for (int i = 0; i < res.digits.size()-1; i++) {
        res.digits[i+1] = (res.digits[i] / 10);
        res.digits[i] %= 10;
    }
    if (res.digits[res.digits.size()-1] == 0) {res.digits.erase(res.digits.end()-1);}
    std::reverse(res.digits.begin(), res.digits.end());
    return res;
}

big_integer operator - (big_integer n1, big_integer n2) { //considering n1>n2
    for (int i = 0; i < n2.digits.size(); i++) { n2.digits[i] *= -1; }
    return (n1 + n2);
}

big_integer pow(big_integer n, int p) {
    big_integer res = big_integer(1);
    //std::cout << res << std::endl;
    big_integer temp;
    while (p > 0) {
        temp = res * n;
        res = temp;
        //std::cout << res << std::endl; //debug
        p -= 1;
    }
    return res;
}

int main() {

    //generate closed and opened keys and check
    int p = 3;
    int q = 7;
    int n = p*q;
    //std::cout << n << std::endl;
    int phi = (p - 1)*(q - 1);
    //std::cout << phi << std::endl;
    int e = 5;
    int d = 17;

    int op[2] = {e, n};
    int cl[2] = {d, n};
    std::cout << op[0] << ' ' << cl[1] << std::endl;
    std::cout << cl[0] << ' ' << cl[1] << std::endl;

    //cypher
    big_integer P = big_integer(19);
    //std::cout << (big_integer(123) * big_integer(56)) << std::endl;
    big_integer cyph = pow(P, 5);
    std::cout << cyph << std::endl;

    return 0;
}



