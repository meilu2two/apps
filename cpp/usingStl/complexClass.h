#include<vector>

class complexClass
{
	public:
		complexClass( int t_base );

	private:
		complexClass( const complexClass& );  // hidden copy-constructor
		int m_baseTypeVar;
		std::vector<int> m_complexTypeVar;
};

