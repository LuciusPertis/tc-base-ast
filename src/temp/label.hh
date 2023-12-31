/**
 ** \file temp/label.hh
 ** \brief Fresh labels.
 */

#ifndef TEMP_LABEL_HH
# define TEMP_LABEL_HH

# include <temp/identifier.hh>

# ifndef MAYBE_EXTERN
#  define MAYBE_EXTERN extern
# endif

namespace temp
{

  template <typename Tag_>
  struct label_traits;

  template <>
  struct label_traits<misc::symbol>
  {
    static const std::string prefix;
    static const int rank;
  };

  template <>
  struct label_traits<unsigned>
  {
    static const std::string prefix;
    static const int rank;
  };

  /// Anonymous and named Label.
  typedef Identifier<label_traits> Label;

  // Static member specialization declaration.
  //
  // Do not use the `Label' typedef to make it clear that template<>
  // is required.
  template<> unsigned Identifier<label_traits>::count_;

  // Explicit template instantiation declarations.
  MAYBE_EXTERN template class Identifier<label_traits>;

  MAYBE_EXTERN template
  std::ostream& operator<<(std::ostream& ostr,
                           const Identifier<label_traits>& obj);
}

namespace misc
{

  // Explicit template instantiation declarations.
  MAYBE_EXTERN template class endo_map<temp::Label>;

  MAYBE_EXTERN template
  std::ostream& operator<<(std::ostream& ostr,
                           const map<temp::Label, temp::Label>& m);
  MAYBE_EXTERN template class list<temp::Label>;
  MAYBE_EXTERN template std::ostream& operator<<(std::ostream& ostr,
                                                 const list<temp::Label>& l);
  MAYBE_EXTERN template bool operator% (const temp::Label& t,
                                        const list<temp::Label>& l);
}

#endif // !TEMP_LABEL_HH
