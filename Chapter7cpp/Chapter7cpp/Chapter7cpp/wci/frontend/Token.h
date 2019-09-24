/**
 * <h1>Token</h1>
 *
 * <p>The framework class that represents a token returned by the scanner.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef WCI_FRONTEND_TOKEN_H_
#define WCI_FRONTEND_TOKEN_H_

#include <string>
#include "Source.h"
#include "../Object.h"

namespace wci { namespace frontend {

using namespace std;
using namespace wci;

/**
 * Types of tokens.
 */
enum class TokenType
{
    // to be "subclassed" by language-specific token types
};

class Token
{
public:
    /**
     * Constructor.
     * @param source the source from where to fetch the token.
     * @throw a string message if an error occurred.
     */
    Token(Source *source) throw (string)
        : type((TokenType) 0), text(""), source(source),
          line_number(source->get_line_number()),
          position(source->get_position())
    {
        value.clear();
    }

    /**
     * Copy constructor.
     */
    Token(const Token& orig) { *this = orig; }

    /**
     * Destructor.
     */
    virtual ~Token() {}

    /**
     * Getter
     * @return the token type
     */
    TokenType get_type() const { return type; }

    /**
     * Getter.
     * @return the token text.
     */
    string get_text() const { return text; }

    /**
     * Getter.
     * @return the token value.
     */
    Object get_value() { return value; }

    /**
     * Getter.
     * @return the source line number.
     */
    int get_line_number() const { return line_number; }

    /**
     * Getter.
     * @return the position.
     */
    int get_position() const { return position; }

protected:
    TokenType type;    // language-specific token type
    string text;       // token text
    Object value;      // token value
    Source *source;    // source
    int line_number;   // line number of the token's source line
    int position;      // position of the first token character

    /**
     * Default method to extract only one-character tokens from the source.
     * Subclasses can override this method to construct language-specific
     * tokens.  After extracting the token, the current source line position
     * will be one beyond the last token character.
     * @throw a string message if an error occurred.
     */
    void extract() throw (string)
    {
        text = to_string(current_char());
        next_char();  // consume current character
    }

    /**
     * @return the current character from the source.
     * @throw a string message if an error occurred.
     */
    char current_char() const throw (string)
    {
        return source->current_char();
    }

    /**
     * @return the next character from the source after moving forward.
     * @throw a string message if an error occurred.
     */
    char next_char() const throw (string)
    {
        return source->next_char();
    }

    /**
     * @return the next character from the source without moving forward.
     * @throw a string message if an error occurred.
     */
    char peek_char() const throw (string)
    {
        return source->peek_char();
    }
};

}} // namespace wci::frontend

#endif /* WCI_FRONTEND_TOKEN_H_ */
