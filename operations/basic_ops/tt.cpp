#include <iostream> 
#include <sstream>
#include <string> 
#include <cstdio> 
using namespace std;
int main() 
{ 
string name="Niels Stroustrup"; 
string s=name.substr(6,10); 
name.replace(0,5,"Nicholas"); 
printf("name:%s\n",name.c_str()); 
} 
