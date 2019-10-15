/**
 * <h1>Scanner</h1>
 *
 * <p>A language-independent framework class.  This abstract scanner class
 * will be implemented by language-specific subclasses.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef WCI_FRONTEND_SCANNER_H_
#define WCI_FRONTEND_SCANNER_H_

#include "Source.h"
#include "Token.h"

namespace wci { namespace frontend {

using namespace std;

class Scanner
{
public:
    /**
     * Constructor
     * @param source the source to be used with this scanner.
     */
    Scanner(Source *source) : source(source), token(nullptr) {}

    /**
     * Destructor.
     */
    virtual ~Scanner() {}

    /**
     * @return the current token.
     */
    Token *current_token() { return token; }

    /**
     * @param prev_token the previous token.
     * @return the next token from the source.
     * @throw a string message if an error occurred.
     */
    Token *next_token(Token *prev_token) throw (string)
    {
        if (prev_token != nullptr) delete prev_token;
        token = extract_token();
        return token;
    }

    /**
     * @return the current character from the source.
     * @throw a string message if an error occurred.
     */
    char current_char() throw (string) { return source->current_char(); }

    /**
     * @return the next character from the source.
     * @throw a string message if an error occurred.
     */
    char next_char() throw (string) { return source->next_char(); }

    /**
     * Call the source's at_eol() method.
     * @return true if at the end of the source line, else return false.
     * @throw a string message if an error occurred.
     */
    bool at_eol() throw (string) { return source->at_eol(); }

    /**
     * Call the source's at_eof() method.
     * @return true if at the end of the source file, else return false.
     * @throw a string message if an error occurred.
     */
    bool at_eof() throw (string) { return source->at_eof(); }

    /**
     * Call the source's skip_to_next_line() method.
     * @throw a string message if an error occurred.
     */
    void skip_to_next_line() throw (string) { source->skip_to_next_line(); }

protected:
    Source *source;

    /**
     * Extract the next token from the source.
     * Implemented by the language-specific scanner subclasses.
     * @return the token.
     * @throw a string message if an error occurred.
     */
    virtual Token *extract_token() throw (string) = 0;

private:
    Token *token;
};

}} // namespace wci::frontend

#endif /* WCI_FRONTEND_SCANNER_H_ */
