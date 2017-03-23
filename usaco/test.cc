/*
ID: stapark1
PROG: test
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ofstream fout("test.out");
    std::ifstream fin("test.in");
    int a, b;
    fin >> a >> b;
    fout << a+b << std::endl;
    return 0;
}
