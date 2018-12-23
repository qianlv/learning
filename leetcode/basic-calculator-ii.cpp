#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        stack<char> op_st;
        int val = 0;
        for (auto c : s) {
            if (isInteger(c)) {
                val = val * 10 + c - '0';
            } else if (c == '+' || c == '-' || c == '*' || c == '/') {
                st.push(val);
                val = 0;
                if (op_st.empty()) {
                    op_st.push(c);
                } else {
                    while(!op_st.empty()) {
                        char top_op = op_st.top();
                        if ((top_op == '+' || top_op == '-') && (c == '*' || c == '/')) {
                            break;
                        } else {
                            int r = st.top();
                            st.pop();
                            int l = st.top();
                            st.pop();
                            st.push(singleCalculate(top_op, l, r));
                            op_st.pop();
                        }
                    }
                    op_st.push(c);
                }
            }
        }

        st.push(val);
        while (!op_st.empty()) {
            char top_op = op_st.top();
            // std::cout << top_op << std::endl;
            int r = st.top();
            st.pop();
            int l = st.top();
            st.pop();
            st.push(singleCalculate(top_op, l, r));
            op_st.pop();
        }
        return st.top();
    }

    bool isInteger(char s) {
        return s >= '0' && s <= '9';
    }

    int singleCalculate(char c, int l, int r) {
        if (c == '+') {
            return l + r;
        }
        if (c == '-') {
            return l - r;
        }
        if (c == '*') {
            return l * r;
        }
        if (c == '/') {
            return l / r;
        }
        return -1;
    }
};

int main(void)
{
    Solution sol = Solution();
    std::cout << sol.calculate("1*2-3/4+5*6-7*8+9/10") << std::endl;
    std::cout << sol.calculate("3/2") << std::endl;
    std::cout << sol.calculate("3") << std::endl;
    std::cout << sol.calculate("3 + 2 * 2") << std::endl;
    std::cout << sol.calculate("3 + 5 / 2") << std::endl;
    return 0;
}
