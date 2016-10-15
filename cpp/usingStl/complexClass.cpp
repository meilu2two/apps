#include"complexClass.h"
#include <iostream>

complexClass::complexClass():m_baseTypeVar( 42 ), m_complexTypeVar( 100, 23 )
{
}

void complexClass::printAddress()
{
  std::cout << "Address of m_baseTypeVar:    " << std::hex << &m_baseTypeVar << std::endl;
  std::cout << "Address of m_complexTypeVar: " << std::hex << &m_complexTypeVar[0] << std::endl;
}
