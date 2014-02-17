%{                                                            /* -*- C++ -*- */

# include <climits>

# include <string>
# include <cerrno>

# include <boost/lexical_cast.hpp>

# include <misc/contract.hh>
# include <misc/symbol.hh>
  // Using misc::escape is very useful to quote non printable characters.
  // For instance
  //
  //    std::cerr << misc::escape('\n') << std::endl;
  //
  // reports about `\n' instead of an actual new-line character.
# include <misc/escape.hh>
# include <parse/tiger-parser.hh>
# include <parse/parsetiger.hh>

  // FIXME: Some code was deleted here.

// Convenient shortcuts.
#define TOKEN_VAL(Type, Value)                  \
  parser::make_ ## Type(Value, tp.location_)

#define TOKEN(Type)                             \
  parser::make_ ## Type(tp.location_)


// Flex uses `0' for end of file.  0 is not a token_type.
#define yyterminate() return TOKEN(EOF)

# define CHECK_EXTENSION()                                      \
  do {                                                          \
    if (!tp.enable_extensions_p_)                               \
      tp.error_ << misc::error::scan                            \
                << tp.location_                                 \
                << ": invalid identifier: `"                    \
                << misc::escape(yytext) << "'" << std::endl;   \
  } while (false)

YY_FLEX_NAMESPACE_BEGIN
%}

%option c++
%option nounput
%option debug
%option batch

%x SC_COMMENT SC_STRING

/* Abbreviations.  */
  /* FIXME: Some code was deleted here. */
%%

 /* The rules.  */
  /* FIXME: Some code was deleted here. */
%%
// Do not use %option noyywrap, because then flex generates the same
// definition of yywrap, but outside the namespaces, so it defines it
// for ::yyFlexLexer instead of ::parse::yyFlexLexer.
int yyFlexLexer::yywrap() { return 1; }

void
yyFlexLexer::scan_open_(std::istream& f)
{
  yypush_buffer_state(YY_CURRENT_BUFFER);
  yy_switch_to_buffer(yy_create_buffer(&f, YY_BUF_SIZE));
}

void
yyFlexLexer::scan_close_()
{
  yypop_buffer_state();
}

YY_FLEX_NAMESPACE_END
