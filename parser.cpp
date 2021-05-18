#include "parser.h"

void Parser::parse()
{
    Symbol a = Symbol(nextToken(), TERM);
    Symbol X = Symbol(E, NONTERM);
    stack.push_back(X);
    cout << " | E" << endl;
    while (!stack.empty())
    {
        if (X.getType() == a.getType() && X.getSymbol() == a.getSymbol())
        {
            accepted.push_back(X);
            stack.pop_back();
            a = Symbol(nextToken(), TERM);
        }
        else if (X.getType() == TERM)
        {
            cout << "syntax error" << endl;
            stack.push_back(Symbol(ERROR, NONTERM));
            break;
        }
        else if (table[X.getSymbol()]
                      [a.getSymbol()] == -1)
        {
            cout << "syntax error" << endl;
            stack.push_back(Symbol(ERROR, NONTERM));
            break;
        }
        else
        {
            vector<Symbol> reverse = rules[table[X.getSymbol()][a.getSymbol()]];
            stack.pop_back();
            for (auto it = reverse.begin(); it != reverse.end() && it->getSymbol() != EPSILON; it++)
            {
                stack.push_back(*it);
            }
        }
        printLM();
        X = stack.back();
    }
}

void Parser::printLM()
{
    for (Symbol symb : accepted)
    {
        symb.printSymbol();
    }
    cout << " | ";
    for (auto it = stack.rbegin(); it != stack.rend(); it++)
        (*it).printSymbol();
    cout << endl;
}

terminal Parser::nextToken()
{
    string current;
    inputFile >> current;
    switch (current[0])
    {
    case '+':
    {
        return static_cast<terminal>(1);
    }
    case '*':
    {
        return static_cast<terminal>(2);
    }
    case '(':
    {
        return static_cast<terminal>(3);
    }
    case ')':
    {
        return static_cast<terminal>(4);
    }
    case 'i':
    {
        return static_cast<terminal>(0);
    }
    default:
    {
        if (current.empty())
            return static_cast<terminal>(5);
    }
    }
}
