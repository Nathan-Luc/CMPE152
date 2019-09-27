/**
 * <h1>Message</h1>
 *
 * <p>Message format.</p>
 *
 * <p>Copyright (c) 2017 by Ronald Mak</p>
 * <p>For instructional purposes only.  No warranties.</p>
 */
#ifndef WCI_MESSAGE_MESSAGE_H_
#define WCI_MESSAGE_MESSAGE_H_

#include <string>
#include <map>
#include "../Object.h"

namespace wci { namespace message {

using namespace std;

/**
 * Types of messages.
 */
enum class MessageType
{
    SOURCE_LINE, SYNTAX_ERROR,
    PARSER_SUMMARY, INTERPRETER_SUMMARY, COMPILER_SUMMARY,
    MISCELLANEOUS, TOKEN,
    AT_LINE, ASSIGN, RUNTIME_ERROR,
};

constexpr MessageType SOURCE_LINE = MessageType::SOURCE_LINE;
constexpr MessageType SYNTAX_ERROR = MessageType::SYNTAX_ERROR;
constexpr MessageType PARSER_SUMMARY = MessageType::PARSER_SUMMARY;
constexpr MessageType INTERPRETER_SUMMARY = MessageType::INTERPRETER_SUMMARY;
constexpr MessageType COMPILER_SUMMARY = MessageType::COMPILER_SUMMARY;
constexpr MessageType MISCELLANEOUS = MessageType::MISCELLANEOUS;
constexpr MessageType TOKEN = MessageType::TOKEN;
constexpr MessageType AT_LINE = MessageType::AT_LINE;
constexpr MessageType ASSIGN = MessageType::ASSIGN;
constexpr MessageType RUNTIME_ERROR = MessageType::RUNTIME_ERROR;

typedef union
{
    struct
    {
        int line_number;
        const char *line_text;
    } source_line;

    struct
    {
        int position;
        const char *token_text;
        const char *error_message;
    } syntax_error;

    struct
    {
        int line_count;
        int error_count;
        double elapsed_time;
    } parser_summary;

    struct
    {
        int execution_count;
        int runtime_errors;
        double elapsed_time;
    } interpreter_summary;

    struct
    {
        int instruction_count;
        double elapsed_time;
    } compiler_summary;

    struct
    {
        const char *variable_name;
        const char *result_value;
    } assign;

    struct
    {
        const char *error_message;
    } runtime_error;
} MessageContent;

class Message
{
public:
    MessageType type;
    int line_number;
    MessageContent content;

    /**
     * Constructor.
     * @param type the message type.
     */
    Message(const MessageType type) : type(type), line_number(0) {}
};

}} // namespace wci::message

#endif /* WCI_MESSAGE_MESSAGE_H_ */
