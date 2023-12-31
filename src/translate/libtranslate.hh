/**
 ** \file translate/libtranslate.hh
 ** \brief Public translate module interface declaration.
 */

#ifndef TRANSLATE_LIBTRANSLATE_HH
# define TRANSLATE_LIBTRANSLATE_HH

# include <iostream>
# include <memory>

# include <ast/fwd.hh>
# include <tree/fwd.hh>
# include <translate/fwd.hh>

#ifdef SWIG
  %rename (translate) swig_translate;

  %inline
  %{
    // Proxy towards translate.
    namespace translate
    {
      tree::Fragments*
      swig_translate (ast::Ast& exp)
      {
        return translate (exp).release ();
      }
    }
  %}
#endif

/// Translation from ast::Ast to tree::Node.
namespace translate
{

  // The name "translate" is used once for the Swig function (see above)
  // and another time as the tc internal function.  To avoid confusing
  // Swig, hide the second.
#ifndef SWIG
  std::unique_ptr<tree::Fragments>
  translate (ast::Ast& the_program
             );
#endif
}

#endif // !TRANSLATE_LIBTRANSLATE_HH
