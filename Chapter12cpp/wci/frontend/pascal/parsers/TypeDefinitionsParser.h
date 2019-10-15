/**
 * <h1>TypeDefinitionsParser</h1>
 *
 * <p>Parse Pascal type definitions.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef TYPEDEFINITIONSPARSER_H_
#define TYPEDEFINITIONSPARSER_H_

#include <set>
#include "DeclarationsParser.h"

namespace wci { namespace frontend { namespace pascal { namespace parsers {

using namespace std;
using namespace wci::frontend::pascal;

class TypeDefinitionsParser : public DeclarationsParser
{
public:
    /**
     * Constructor.
     * @param parent the parent parser.
     */
    TypeDefinitionsParser(PascalParserTD *parent);

    /**
     * Parse a type definition.
     * @param token the initial token.
     * @param parent_id the symbol table entry of the parent routine's name.
     * @return nullptr
     * @throw a string message if an error occurred.
     */
    SymTabEntry *parse_declaration(Token *token, SymTabEntry *parent_id)
        throw (string);

private:
    // Synchronization set for a type identifier.
    static EnumSet<PascalTokenType> IDENTIFIER_SET;

    // Synchronization set for the = token.
    static EnumSet<PascalTokenType> EQUALS_SET;

    // Synchronization set for what follows a definition or declaration.
    static EnumSet<PascalTokenType> FOLLOW_SET;

    // Synchronization set for the start of the next definition or declaration.
    static EnumSet<PascalTokenType> NEXT_START_SET;

    static bool INITIALIZED;

    /**
     * Initialize the synchronization set.
     */
    static void initialize();
};

}}}}  // namespace wci::frontend::pascal::parsers

#endif /* TYPEDEFINITIONSPARSER_H_ */
