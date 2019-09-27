/**
 * <h1>IfStatementParser</h1>
 *
 * <p>Parse a Pascal IF statement.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include <string>
#include "WhenStatementParser.h"
#include "StatementParser.h"
#include "AssignmentStatementParser.h"
#include "ExpressionParser.h"
#include "../PascalParserTD.h"
#include "../PascalToken.h"
#include "../PascalError.h"
#include "../../Token.h"
#include "../../../intermediate/ICodeNode.h"
#include "../../../intermediate/ICodeFactory.h"
#include "../../../intermediate/icodeimpl/ICodeNodeImpl.h"

namespace wci { namespace frontend { namespace pascal { namespace parsers {

using namespace std;
using namespace wci::frontend::pascal;
using namespace wci::intermediate;
using namespace wci::intermediate::icodeimpl;

bool WhenStatementParser::INITIALIZED = false;

EnumSet<PascalTokenType> WhenStatementParser::WHEN_SET;

void WhenStatementParser::initialize()
{
    if (INITIALIZED) return;

    WHEN_SET = StatementParser::STMT_START_SET;
    WHEN_SET.insert(PascalTokenType::WHEN);

    EnumSet<PascalTokenType>::iterator it;
    for (it  = StatementParser::STMT_FOLLOW_SET.begin();
         it != StatementParser::STMT_FOLLOW_SET.end();
         it++)
    {
        WHEN_SET.insert(*it);
    }

    INITIALIZED = true;
}

WhenStatementParser::WhenStatementParser(PascalParserTD *parent)
    : StatementParser(parent)
{
    initialize();
}

ICodeNode *WhenStatementParser::parse_statement(Token *token) throw (string)
{
    token = next_token(token);  // consume the IF

    // Create an IF node.
    ICodeNode *when_node =
            ICodeFactory::create_icode_node((ICodeNodeType) NT_IF);


    // Parse the expression.
    // The IF node adopts the expression subtree as its first child.
    ExpressionParser expression_parser(this);
    when_node->add_child(expression_parser.parse_statement(token));

    // Synchronize at the THEN.
    token = synchronize(WHEN_SET);
    if (token->get_type() == (TokenType) PT_RIGHT_ARROW)
    {
        token = next_token(token);  // consume the RIGHT_ARROW
    }
    else {
        error_handler.flag(token, MISSING_RIGHT_ARROW, this);
    }

    // Parse the THEN statement.
    // The IF node adopts the statement subtree as its second child.
    /*StatementParser statement_parser(this);
    when_node->add_child(statement_parser.parse_statement(token));*/

    return when_node;
}

}}}}  // namespace wci::frontend::pascal::parsers
