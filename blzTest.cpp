/******************************************************************************
 * Author      : Gao Peng
 * Date        : 2020-6-2
 * modify      : 2021-6-4
 * version     : 1.0
 * Description : 给板栗仔的测试
 ******************************************************************************/
#include <iostream>

using std::cout;
using std::endl;
class mySet{
public:
    int* data;
    int len;
    mySet(int* data, int len){
        this->data = data;
        this->len = len;
    }
    void print(const char* description){
        cout << description << ": ";
        for (int i = 0; i < len; ++i) {
            cout << data[i] << ' ';
        }
        cout << endl;
    }
    mySet operator+(const mySet& ms){
        int* add = new int[ms.len + len];
        for (int i = 0; i < len; ++i) {
            add[i] = data[i];
        }
        int count = len;
        for (int i = 0; i < ms.len; ++i) {
            bool hasEqual = false;
            for (int j = 0; j < len; ++j) {
                if(ms.data[i] == data[j]) {
                    hasEqual = true;
                    break;
                }
            }
            if(!hasEqual)
                add[count++] = ms.data[i];
        }
        return mySet(add,count);
    }
    mySet operator-(const mySet& ms){
        int* diff = new int[len];
        int count = 0;
        for (int i = 0; i < len; ++i) {
            bool hasEqual = false;
            for (int j = 0; j < ms.len; ++j) {
                if(ms.data[i] == data[j]) {
                    hasEqual = true;
                    break;
                }
            }
            if(!hasEqual)
                diff[count++] = data[i];
        }
        return mySet(diff,count);
    }
    mySet operator*(const mySet& ms){
        int* cross = new int[len];
        int count = 0;
        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < ms.len; ++j) {
                if(data[i] == ms.data[j]) {
                    cross[count++] = data[i];
                    break;
                }
            }
        }
        return mySet(cross,count);
    }
};

int main55(){
    int data1[5] = {7,2,6,8,4};
    int data2[4] = {2,4,6,9};
    mySet s1(data1,5),s2(data2,4);
    (s1 + s2).print("并集");
    (s1 - s2).print("差集");
    (s1 * s2).print("交集");
}