#include"complexClass.h"
#include <iostream>

complexClass::complexClass():m_baseTypeVar( 42 ), m_complexTypeVar( 100, 23 ), m_baseTypePtr ( &m_complexTypeVar[ 1 ] )
{
}

void complexClass::printAddress()
{
  std::cout << "m_baseTypeVar:       Address = " << &m_baseTypeVar << ", Content = " << m_baseTypeVar << std::endl;
  std::cout << "m_complexTypeVar[0]: Address = " << &m_complexTypeVar[0] << ", Content = " << m_complexTypeVar[0] << std::endl;
  std::cout << "m_baseTypePtr:       Address = " << &m_baseTypePtr << ", Content = " << m_baseTypePtr << std::endl;
  std::cout << "----------" << std::endl;
}
