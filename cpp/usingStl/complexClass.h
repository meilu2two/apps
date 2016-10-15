#include<vector>

class complexClass
{
	public:
		complexClass();

    void printAddress();

	private:
		// complexClass( const complexClass& );  // hidden copy-constructor
		int m_baseTypeVar;
		std::vector<int> m_complexTypeVar;
    int* m_baseTypePtr;
};
