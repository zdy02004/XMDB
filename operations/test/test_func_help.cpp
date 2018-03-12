#include"../func_help.hpp"
//g++ -g -std=c++11 test_func_help.cpp -o test_func_help.exe

int main(int argc,char * argv[] )
{

 func::test_hash_semi_join();
 std::cout<<"_________________"<<std::endl;
 func::test_hash_anti_semi_join();
 std::cout<<"_________________"<<std::endl;
 func::test_hash_anti_join();



return 0;
}
