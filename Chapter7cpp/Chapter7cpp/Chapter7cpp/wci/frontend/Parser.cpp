/**
 * <h1>Parser</h1>
 *
 * <p>A language-independent framework class.  This abstract parser class
 * will be implemented by language-specific subclasses.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include "Parser.h"
#include "../intermediate/SymTabStack.h"
#include "../intermediate/SymTabFactory.h"

namespace wci { namespace frontend {

MessageHandler Parser::message_handler;
SymTabStack *Parser::symtab_stack = SymTabFactory::create_symtab_stack();

}} // namespace wci::frontend
