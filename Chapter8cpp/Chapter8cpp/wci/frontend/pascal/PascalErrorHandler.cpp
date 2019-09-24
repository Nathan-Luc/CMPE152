/**
 * <h1>PascalErrorHandler</h1>
 *
 * <p>Error handler Pascal syntax errors.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#include "PascalErrorHandler.h"
#include "../Token.h"
#include "../Parser.h"
#include "PascalError.h"
#include "../../message/Message.h"

namespace wci { namespace frontend { namespace pascal {

using namespace std;
using namespace wci::frontend;

const int PascalErrorHandler::MAX_ERRORS = 25;
int PascalErrorHandler::error_count = 0;

Message PascalErrorHandler::SYNTAX_ERROR_MESSAGE(SYNTAX_ERROR);

int PascalErrorHandler::get_error_count() const { return error_count; }

void PascalErrorHandler::flag(Token *token, PascalErrorCode error_code,
                              Parser *parser)
{
    // Notify the parser's listeners.
    string error_message = PascalError::SYNTAX_ERROR_MESSAGES[error_code];
    SYNTAX_ERROR_MESSAGE.line_number = token->get_line_number();
    SYNTAX_ERROR_MESSAGE.content.syntax_error.position = token->get_position();
    SYNTAX_ERROR_MESSAGE.content.syntax_error.token_text =
                                            strdup(token->get_text().c_str());
    SYNTAX_ERROR_MESSAGE.content.syntax_error.error_message =
                        PascalError::SYNTAX_ERROR_MESSAGES[error_code].c_str();
    parser->send_message(SYNTAX_ERROR_MESSAGE);

    free(const_cast<char *>(SYNTAX_ERROR_MESSAGE.content.syntax_error.token_text));

    if (++error_count > MAX_ERRORS)
    {
        abort_translation(TOO_MANY_ERRORS, parser);
    }
}

void PascalErrorHandler::abort_translation(PascalErrorCode error_code,
                                           Parser *parser)
{

    // Notify the parser's listeners and then abort.
    string error_message = "FATAL ERROR: " +
                           PascalError::SYNTAX_ERROR_MESSAGES[error_code];
    SYNTAX_ERROR_MESSAGE.line_number = 0;
    SYNTAX_ERROR_MESSAGE.content.syntax_error.position = -1;
    SYNTAX_ERROR_MESSAGE.content.syntax_error.token_text = "";
    SYNTAX_ERROR_MESSAGE.content.syntax_error.error_message = error_message.c_str();
    parser->send_message(SYNTAX_ERROR_MESSAGE);
    exit(-2);
}

}}}  // namespace wci::frontend::pascal
