#include "symbol.h"
class Parser
{
	ifstream &inputFile;
	vector<vector<Symbol>> rules{
		{Symbol(E_, NONTERM), Symbol(T, NONTERM)},						   // E -> E'T
		{Symbol(E_, NONTERM), Symbol(T, NONTERM), Symbol(PLUS, TERM)},	   // E' -> +TE'
		{Symbol(EPSILON, TERM)},										   // E' -> e
		{Symbol(T_, NONTERM), Symbol(F, NONTERM)},						   // T -> FT'
		{Symbol(T_, NONTERM), Symbol(F, NONTERM), Symbol(ASTERISK, TERM)}, // T' -> *FT'
		{Symbol(EPSILON, TERM)},										   // T' -> e
		{Symbol(RPAREN, TERM), Symbol(E, NONTERM), Symbol(LPAREN, TERM)},  // F -> (E)
		{Symbol(ID, TERM)}												   // F -> id
	};
	vector<vector<int>> table{
		//    id    +    *    (    )    $
		{0, -1, -1, 0, -1, -1}, // E
		{-1, 1, -1, -1, 2, 2},	// E'
		{3, -1, -1, 3, -1, -1}, // T
		{-1, 5, 4, -1, 5, 5},	// T'
		{7, -1, -1, 6, -1, -1}	// F
	};
	vector<Symbol> stack;
	vector<Symbol> accepted;

public:
	Parser(ifstream &file) : inputFile(file) {}
	void parse();
	terminal nextToken();
	void printLM();
};
