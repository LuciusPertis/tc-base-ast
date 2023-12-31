/**
 ** \file parse/fwd.hh
 ** \brief Forward declarations for the parse module.
 */

#ifndef PARSE_FWD_HH
# define PARSE_FWD_HH

# include <misc/variant.hh>

// From ast/.
namespace ast
{
  class Exp;
  class DecsList;
}

namespace parse
{
  // From scantiger.hh.
  class yyFlexLexer;

  // From parsetiger.yy.
  class parser;

  // From location.hh.
  class location;

  // From tiger-parser.hh.
  class TigerParser;

  // From tweast.hh
  class Tweast;

  /// Result of a parse: an Exp (*.tig) or a DecsList (*.tih).
  typedef misc::variant<ast::Exp*, ast::DecsList*> ast_type;
}

#endif // !PARSE_FWD_HH
