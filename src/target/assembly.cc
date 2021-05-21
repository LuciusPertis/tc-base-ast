/**
 ** \file target/assembly.cc
 ** \brief Implementation of target::Assembly.
 */

#include <target/assembly.hh>
#include <temp/label.hh>

namespace target
{
  Assembly::Assembly(assem::Layout& layout)
    : layout_(layout)
  {}

  assem::Layout& Assembly::layout_get() { return layout_; }

} // namespace target
