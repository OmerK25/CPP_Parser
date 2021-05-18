#include "symbol.h"

Type Symbol::getType()
{
    return type;
}
int Symbol::getSymbol()
{
    return symbol;
}
void Symbol::printSymbol()
{
    if (type == TERM)
        cout << terminalStrings[symbol] + " ";
    else
        cout << tokenStrings[symbol] + " ";
}