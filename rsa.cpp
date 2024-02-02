#include <iostream>
#include <vector>

std::vector<int> int_to_vec(int n) {
    std::vector<int> res{};
    while (n>0) {
        res.push_back(n%10);
        n /= 10;
    }
    return res;
}

void vector_out(std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i];
    }
}

class big_integer {
    public:
        std::vector<int> digits;
        big_integer(int n) {
            digits = int_to_vec(n);
        }
        //big_integer::
        void out() { vector_out((*this).digits); }
        friend big_integer operator * (big_integer num1, big_integer num2);
        friend big_integer operator + (big_integer n1, big_integer n2);
};

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

/*
big_integer operator + (big_integer n1, big_integer n2) {
    
}
*/

int main() {
    
    //cheat sheet
    /*
    //step 1: defining keys
    int p = 3;
    int q = 7;
    int n = p*q;
    int phi = (p-1)*(q-1);
    int e = 5;
    int d = 17;

    int op[2] = {e, n};
    int cl[2] = {d, n};
    std::cout << op[0] << ' ' << cl[1] << std::endl;
    std::cout << cl[0] << ' ' << cl[1] << std::endl;
    */

   big_integer p = big_integer(3);
   big_integer q = big_integer(7);
   big_integer n = p*q;
   n.out(); std::cout << std::endl;

   //deprecated
   /*
   int p_int = 3;
   int q_int = 7;
   std::vector<int> p_minus{p_int - 1};
   std::vector<int> q_minus{q_int - 1};
   //std::vector<int> phi = multiply(p_minus, q_minus);

   std::vector<int> e{5};
   std::vector<int> d{17};

   std::vector<int> op[2] = {e, e};
   std::vector<int> cl[2] = {d, d};
   vector_out(op[0]); std::cout << ' '; vector_out(op[1]); std::cout << std::endl;
   vector_out(cl[0]); std::cout << ' '; vector_out(cl[1]);
   */
   return 0;
}



