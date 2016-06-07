#include <iostream>
#include <vector>
#include <deque>
#include <list>
 
int main()
{
    std::cout<<"Hello STL!"<<std::endl;

    typedef std::vector<int> TContainer;
    TContainer a_vector(5, 0);
    
    // Use C-style way to set the values in the container
    for( int i = 0; i < 5; ++i ){
        a_vector[ i ] = i;
        std::cout << "C-style set: " << a_vector[ i ] << std::endl; 
    }

    // Use STL iterator to access the values in the container
    TContainer::iterator a_iter = a_vector.begin();
    while( a_iter != a_vector.end() ){
        std::cout << "STL-style get: " << *a_iter++ <<  std::endl;
    }
    return 0;
}

