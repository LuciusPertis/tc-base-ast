/**
 ** \file regalloc/color.cc
 ** \brief Implementation for regalloc/color.hh.
 **/

#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>

#include <misc/algorithm.hh>
#include <regalloc/color.hh>
#include <target/cpu.hh>
#include <temp/temp.hh>

/// Run the 0-ary function \a What, verbosely.
#define DO(What)                                                               \
  do                                                                           \
    {                                                                          \
      if (trace_p_)                                                            \
        std::cerr << "## " #What ": begin.\n";                                 \
      timer_.push("9: " #What);                                                \
      What();                                                                  \
      timer_.pop("9: " #What);                                                 \
      if (trace_p_)                                                            \
        std::cerr << "## " #What ": end.\n";                                   \
  } while (false)

namespace regalloc
{
  Color::Color(assem::ProcFrag& frag,
               const target::Cpu& cpu,
               const temp::TempMap& tempmap,
               const temp::temp_set_type& already_spilled,
               bool coalesce_p,
               bool trace_p)
    : ig_(
      InterferenceGraph(frag.file_name(), frag.instrs_get(), tempmap, trace_p))
    , cpu_(cpu)
    , nb_regs_(cpu_.nb_regs())
    , asm_proc_frag_(frag)
    , trace_p_(trace_p)
    , coalesce_p_(coalesce_p)
    , degree_(boost::num_vertices(ig_))
    , move_list_(boost::num_vertices(ig_))
    , alias_(boost::num_vertices(ig_))
    , color_(boost::num_vertices(ig_))
    , already_spilled_(already_spilled)
  {
    timer_ << ig_.timer_get();
    // Pre-treatments.
    DO(precolor);
    DO(import_nodes);
    if (coalesce_p)
      DO(import_moves);
    DO(degrees_compute);
    DO(priorities_compute);
    DO(make_work_list);
  }

  void Color::import_nodes()
  {
    for (auto [i, end] = boost::vertices(ig_); i != end; ++i)
      if (!(*i % precolored_))
        initial_ += *i;
  }

  void Color::import_moves()
  {
    work_list_moves_ = ig_.moves_get();
    for (const move_type& m : work_list_moves_)
      {
        move_list_[m.first].insert(m);
        move_list_[m.second].insert(m);
      }
  }

  void Color::precolor()
  {
    // FIXME: Some code was deleted here.
  }

  void Color::priorities_compute()
  {
    // FIXME: Some code was deleted here.
  }

  void Color::degrees_compute()
  {
    // FIXME: Some code was deleted here.
  }

  void Color::add_edge(const node_type u, const node_type v)
  {
    // FIXME: Some code was deleted here.
  }

  void Color::make_work_list(const node_type n)
  {
    // FIXME: Some code was deleted here.
  }

  void Color::make_work_list()
  {
    // FIXME: Some code was deleted here.
  }

  Color::node_set_type Color::adjacent(const node_type n) const
  {
    // FIXME: Some code was deleted here.
  }

  bool Color::adjacent(const node_type a, const node_type b) const
  {
    // FIXME: Some code was deleted here.
  }

  Color::move_set_type Color::node_moves(const node_type n) const
  {
    // FIXME: Some code was deleted here.
  }

  bool Color::move_related(const node_type n) const
  {
    // FIXME: Some code was deleted here.
  }

  bool Color::coalesce_briggs_p(const node_type a, const node_type b) const
  {
    // FIXME: Some code was deleted here.
  }

  bool Color::coalesce_george_p(const node_type a, const node_type b) const
  {
    // FIXME: Some code was deleted here.
  }

  void Color::coalesce()
  {
    // FIXME: Some code was deleted here.
  }

  void Color::add_work_list(const node_type u)
  {
    // FIXME: Some code was deleted here.
  }

  Color::node_type Color::get_alias(const node_type a) const
  {
    // FIXME: Some code was deleted here.
  }

  void Color::combine(const node_type u, const node_type v)
  {
    // FIXME: Some code was deleted here.
  }

  void Color::freeze_moves(const node_type u)
  {
    // FIXME: Some code was deleted here.
  }

  void Color::freeze()
  {
    // FIXME: Some code was deleted here.
  }

  // To compute the node with the least priority, avoid float
  // computations which are unsafe, and, in some extent, unstable.
  // Consider for instance the following code, that was designed as a
  // stripped version of a nondeterministic behavior of a previous
  // version of this very function (select_spill).  (You'll have to
  // add the backslashes to the macro by hand.)
  //
  // /tmp % cat foo.c
#if 0
#  include <stdio.h>

#  define TEST(Op)
       if ((num / den) Op quot)
         fprintf(stderr, "1 / 3 " #Op " 1 / 3\n");

     int
     main()
     {
       float quot = 1.0 / 3.0;
       volatile float num = 1.0;
       volatile float den = 3.0;

       TEST(<);
       TEST(<=);
       TEST(>);
       TEST(>=);
       TEST(==);
       TEST(!=);
     }
#endif
  // /tmp % gcc-3.4 foo.c -o foo-c
  // /tmp % ./foo-c
  // 1 / 3 < 1 / 3
  // 1 / 3 <= 1 / 3
  // 1 / 3 != 1 / 3
  void Color::select_spill()
  {
    // FIXME: Some code was deleted here (A good heuristic can be found in Andrew Appel's book page 237).
  }

  void Color::simplify()
  {
    // FIXME: Some code was deleted here.
  }

  void Color::decrement_degree(node_type n)
  {
    // FIXME: Some code was deleted here.
  }

  void Color::enable_moves(node_type n)
  {
    // FIXME: Some code was deleted here.
  }

  void Color::enable_moves(const node_set_type& nodes)
  {
    // FIXME: Some code was deleted here.
  }

  void Color::assign_color(node_type n)
  {
    // FIXME: Some code was deleted here.
  }

  void Color::assign_colors()
  {
    // FIXME: Some code was deleted here.
  }

  bool Color::operator()()
  {
    if (trace_p_)
      std::cerr << "## color: begin.\n";
    do
      {
        if (trace_p_)
          dump(std::cerr);
        if (!simplify_work_list_.empty())
          DO(simplify);
        else if (!work_list_moves_.empty())
          DO(coalesce);
        else if (!freeze_work_list_.empty())
          DO(freeze);
        else if (!spill_work_list_.empty())
          DO(select_spill);
    } while (!simplify_work_list_.empty() || !work_list_moves_.empty()
             || !freeze_work_list_.empty() || !spill_work_list_.empty());

    // Pop the entire stack, assigning colors.
    DO(assign_colors);
    if (trace_p_)
      std::cerr << "## color: end.\n";

    return spilled_nodes_.empty();
  }

  const temp::temp_set_type Color::spilled_get() const
  {
    temp::temp_set_type res;
    for (const node_type& n : spilled_nodes_)
      res.insert(ig_[n]);
    return res;
  }

  temp::TempMap Color::tempmap_get() const
  {
    temp::TempMap res;
    // FIXME: Some code was deleted here.
    return res;
  }

  const misc::timer& Color::timer_get() const { return timer_; }

  void Color::trace(const std::string& what, const node_type& n) const
  {
    if (trace_p_)
      {
        dump(std::cerr, n);
        std::cerr << '\t' << what << '\n';
      }
  }

  void Color::trace(const std::string& what, const move_type& m) const
  {
    if (trace_p_)
      {
        dump(std::cerr, m);
        std::cerr << '\t' << what << '\n';
      }
  }

  void Color::dump(std::ostream& ostr, const node_type& n) const
  {
    // ostr << n << " (" << *ig_[n] << ")";
    ostr << ig_[n]; //  << " (" << degree_[n] << ")";
    if (n % colored_nodes_)
      std::cerr << " (" << color_[n] << ')';
  }

  void Color::dump(std::ostream& ostr, const node_set_type& s) const
  {
    for (auto i = s.begin(); i != s.end(); ++i)
      {
        if (i != s.begin())
          ostr << " ";
        dump(ostr, *i);
      }
  }

  void Color::dump(std::ostream& ostr, const node_list_type& s) const
  {
    for (auto i = s.begin(); i != s.end(); ++i)
      {
        if (i != s.begin())
          ostr << " ";
        dump(ostr, *i);
      }
  }

  void Color::dump(std::ostream& ostr, const move_type& s) const
  {
    dump(ostr, s.first);
    ostr << ":=";
    dump(ostr, s.second);
  }

  void Color::dump(std::ostream& ostr, const move_set_type& s) const
  {
    for (auto i = s.begin(); i != s.end(); ++i)
      {
        if (i != s.begin())
          ostr << " ";
        dump(ostr, *i);
      }
  }

  void Color::dump(std::ostream& ostr) const
  {
#define REPORT(Title, What)                                                    \
  do                                                                           \
    {                                                                          \
      ostr << Title << " (" << (What).size() << "): ";                         \
      dump(ostr, What);                                                        \
      ostr << '\n';                                                            \
  } while (0)

    size_t size = 0;
    size += precolored_.size();
    size += initial_.size();
    size += simplify_work_list_.size();
    size += freeze_work_list_.size();
    size += spill_work_list_.size();
    size += spilled_nodes_.size();
    size += coalesced_nodes_.size();
    size += colored_nodes_.size();
    size += select_stack_.size();

    ostr << "===================="
         << " Nodes " << ig_.name_get() << " (" << size << ") "
         << "====================\n";

    REPORT("Precolor   ", precolored_);
    REPORT("Initial    ", initial_);
    REPORT("Simplify WL", simplify_work_list_);
    REPORT("Freeze WL  ", freeze_work_list_);
    REPORT("Spill WL   ", spill_work_list_);
    REPORT("Spilled    ", spilled_nodes_);
    REPORT("Coalesced  ", coalesced_nodes_);
    REPORT("Colored    ", colored_nodes_);
    REPORT("Select     ", select_stack_);

    if (coalesce_p_)
      {
        size = 0;
        size += coalesced_moves_.size();
        size += constrained_moves_.size();
        size += frozen_moves_.size();
        size += work_list_moves_.size();
        size += active_moves_.size();

        ostr << "--------------------"
             << " Moves " << ig_.name_get() << " (" << size << ") "
             << "--------------------\n";

        REPORT("Coalesced  ", coalesced_moves_);
        REPORT("Constrained", constrained_moves_);
        REPORT("Frozen     ", frozen_moves_);
        REPORT("Moves WL   ", work_list_moves_);
        REPORT("Active     ", active_moves_);
      }
#undef REPORT
  }

} // namespace regalloc

#undef DO
