#include <iostream>
#include <vector>
#include <algorithm>

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
        friend big_integer operator + (big_integer n1, big_integer n2);
        friend big_integer operator - (big_integer n1, big_integer n2);
};

std::ostream& operator << (std::ostream &os, const big_integer& bi) {
    for (int i = 0; i < bi.digits.size(); i++) {
        os << bi.digits[i];
    }
    return os;
}

big_integer operator * (big_integer num1, big_integer num2) {

    big_integer res = big_integer(0);
    res.digits.resize(num1.digits.size() + num2.digits.size());
    std::fill(res.digits.begin(), res.digits.end(), 0);

    int temp;
    //std::vector<int> buff;

    for (int i = 0; i < num2.digits.size(); i++) {
        temp = 0;
        for (int j = 0; j < num1.digits.size(); j++) {
            temp += num1.digits[i]*num2.digits[j];
            //std::cout << temp << std::endl; debug
        }
        int count = 1;
        while (temp>0) {
            res.digits[res.digits.size()-count] += temp%10;
            temp /= 10;
            count+=1;
        }
        
    }

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

int main() {

   big_integer p = big_integer(3);
   big_integer q = big_integer(7);
   big_integer n = p*q;
   //std::cout << n << std::endl;
   big_integer phi = (p - big_integer(1))*(q - big_integer(1));
   //std::cout << phi << std::endl;
   big_integer e = big_integer(5);
   big_integer d = big_integer(17);

   big_integer op[2] = {e, n};
   big_integer cl[2] = {d, n};
   std::cout << op[0] << ' ' << cl[1] << std::endl;
   std::cout << cl[0] << ' ' << cl[1] << std::endl;

   return 0;
}



