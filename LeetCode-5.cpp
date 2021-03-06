/*************************************************************************
    > File Name: LeetCode-5.cpp
    > Author: ltw
    > Mail: 3245849061@qq.com 
    > Created Time: Tue 19 May 2020 07:05:33 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;

/***
	*最长回文子串
	*马拉车算法
	*首先我们需要考虑对应可能出现的情况，回文子串可以是奇数个也可以是偶数个，我们采用的处理办法就是首尾要加上一个#字符，然后每一个字符每隔一个都要加上#字符
***/
class Solution {
public:
    string get_new_str(string &s) {
        string new_s = "#";
		//处理字符串，为#a#b#c#b#这种类似的
        for (int i = 0; i < s.size(); i++) {
            new_s += s[i];
            new_s += "#";
        }
        return new_s;
    }
    string longestPalindrome(string s) {
        int r[2010];
        string new_s = get_new_str(s);
        int ans = 0, ind = 0;
        for (int i = 0, j = 0, p = 0; new_s[i]; i++) {
            r[i] = 1;//每一次从第一个位置开始处理，对称中心为j,最左边对应为p`,对应最右边为p, 对应的r[i]位置可以在字串左边，字串右边，或者字串外面
            if (i <= p && i + r[2 * j - i] - 1 < p) {
                r[i] = r[2 * j - i];//对应小于最右边的位置
            } else {
				//对应i在p的外面，回文中心就跳到对应的就跳到p右边
                r[i] = max(1, p - i + 1);
                while (i >= r[i] && i + r[i] < new_s.size() && new_s[i + r[i]] == new_s[i - r[i]]) {
					//当满足在上一个p后面且对应的位置加上回文半径小于对应的字符串的长度，且左右两边相等情况
                    r[i]++;//对应回文半径加一
                }
            }
            if (i + r[i] - 1 > p) {
                j = i, p = i + r[i] - 1;
            }
			//记录对应的回文半径ans,以及对应回文中心ind
            if (r[i] > ans) {
                ans = r[i], ind = i;
            }
        }
		//sub_str就是截断字符串中从对应起点到终点位置的字串
        string sub_str = new_s.substr(ind - ans + 1, 2 * ans - 1);
        string ret = "";
		//得到的子串就是带有#，需要处理一下
        for (int i = 1; i < sub_str.size(); i += 2) ret += sub_str[i];
        return ret;
    }
};
