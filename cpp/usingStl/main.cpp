#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include "complexClass.h"

struct generateEquiValues {
  int m_workingValue;
  int m_distance;
  generateEquiValues( int t_startValue, int t_distance ):m_workingValue( t_startValue ), m_distance( t_distance ) {}
  int operator()() {return m_workingValue += m_distance;}
};

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
        std::cout << "STL-style get: " << *a_iter++ << std::endl;
    }

    // Fill vector with equidistant values
    TContainer a_equiVector(10, 0);
    std::generate( a_equiVector.begin(), a_equiVector.end(), generateEquiValues( 55, 100 ) );
    TContainer::iterator a_equiIter = a_equiVector.begin();
	  int a_counter(0);
    while( a_equiIter != a_equiVector.end() ){
        std::cout << "Equidistant vector[" << a_counter++ << "] = " << *a_equiIter++ << std::endl;
    }

  	// let's test some details of copy constructor
    complexClass a_testObject;
  	// complexClass a_secondObject( a_testObject );   // only works with public copy constructor
  	// complexClass a_thirdObject = a_testObject;   // only works with public copy constructor

    // let's test some details of deep or shallow copy
    a_testObject.printAddress();
    std::vector< complexClass > a_vectorOfComplex(10, a_testObject );   // is that a deep or shallow copy of a_testObject
    // print out addresses and content to check deep or shallow copy
    std::vector< complexClass >::iterator a_complIt = a_vectorOfComplex.begin();
    while( a_complIt != a_vectorOfComplex.end() ){
      a_complIt->printAddress();
      ++a_complIt;
    }

    return 0;
}
