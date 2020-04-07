// A Bison parser, made by GNU Bison 3.5.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.tab.hh"


// Unqualified %code blocks.
#line 40 "parser.y"

    #include "driver/driver.hpp"

    std::shared_ptr<block> program_block;

    visitor_pprint v_pprint;
#line 104 "parser.y"

    #define DEBUG_PARSER
    #undef DEBUG_PARSER

#line 57 "parser.tab.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 148 "parser.tab.cc"


  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 49: // array_access
        value.YY_MOVE_OR_COPY< std::unique_ptr<array_access> > (YY_MOVE (that.value));
        break;

      case 40: // stmts
      case 41: // program
      case 42: // block
        value.YY_MOVE_OR_COPY< std::unique_ptr<block> > (YY_MOVE (that.value));
        break;

      case 30: // "decimal"
        value.YY_MOVE_OR_COPY< std::unique_ptr<decimal> > (YY_MOVE (that.value));
        break;

      case 35: // expr
      case 36: // literals
      case 37: // binop_expr
      case 38: // unaryop_expr
      case 39: // compare_expr
        value.YY_MOVE_OR_COPY< std::unique_ptr<expression> > (YY_MOVE (that.value));
        break;

      case 31: // "fraction"
        value.YY_MOVE_OR_COPY< std::unique_ptr<fraction> > (YY_MOVE (that.value));
        break;

      case 29: // "identifier"
      case 34: // identifier
        value.YY_MOVE_OR_COPY< std::unique_ptr<identifier> > (YY_MOVE (that.value));
        break;

      case 43: // stmt
      case 44: // conditional
      case 45: // for_loop
      case 46: // for_range
        value.YY_MOVE_OR_COPY< std::unique_ptr<statement> > (YY_MOVE (that.value));
        break;

      case 47: // call_args
        value.YY_MOVE_OR_COPY< std::unique_ptr<std::vector<std::unique_ptr<expression>>> > (YY_MOVE (that.value));
        break;

      case 32: // "stringlit"
        value.YY_MOVE_OR_COPY< std::unique_ptr<stringlit> > (YY_MOVE (that.value));
        break;

      case 48: // var_decl
        value.YY_MOVE_OR_COPY< std::unique_ptr<variable_declaration> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 49: // array_access
        value.move< std::unique_ptr<array_access> > (YY_MOVE (that.value));
        break;

      case 40: // stmts
      case 41: // program
      case 42: // block
        value.move< std::unique_ptr<block> > (YY_MOVE (that.value));
        break;

      case 30: // "decimal"
        value.move< std::unique_ptr<decimal> > (YY_MOVE (that.value));
        break;

      case 35: // expr
      case 36: // literals
      case 37: // binop_expr
      case 38: // unaryop_expr
      case 39: // compare_expr
        value.move< std::unique_ptr<expression> > (YY_MOVE (that.value));
        break;

      case 31: // "fraction"
        value.move< std::unique_ptr<fraction> > (YY_MOVE (that.value));
        break;

      case 29: // "identifier"
      case 34: // identifier
        value.move< std::unique_ptr<identifier> > (YY_MOVE (that.value));
        break;

      case 43: // stmt
      case 44: // conditional
      case 45: // for_loop
      case 46: // for_range
        value.move< std::unique_ptr<statement> > (YY_MOVE (that.value));
        break;

      case 47: // call_args
        value.move< std::unique_ptr<std::vector<std::unique_ptr<expression>>> > (YY_MOVE (that.value));
        break;

      case 32: // "stringlit"
        value.move< std::unique_ptr<stringlit> > (YY_MOVE (that.value));
        break;

      case 48: // var_decl
        value.move< std::unique_ptr<variable_declaration> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 49: // array_access
        value.copy< std::unique_ptr<array_access> > (that.value);
        break;

      case 40: // stmts
      case 41: // program
      case 42: // block
        value.copy< std::unique_ptr<block> > (that.value);
        break;

      case 30: // "decimal"
        value.copy< std::unique_ptr<decimal> > (that.value);
        break;

      case 35: // expr
      case 36: // literals
      case 37: // binop_expr
      case 38: // unaryop_expr
      case 39: // compare_expr
        value.copy< std::unique_ptr<expression> > (that.value);
        break;

      case 31: // "fraction"
        value.copy< std::unique_ptr<fraction> > (that.value);
        break;

      case 29: // "identifier"
      case 34: // identifier
        value.copy< std::unique_ptr<identifier> > (that.value);
        break;

      case 43: // stmt
      case 44: // conditional
      case 45: // for_loop
      case 46: // for_range
        value.copy< std::unique_ptr<statement> > (that.value);
        break;

      case 47: // call_args
        value.copy< std::unique_ptr<std::vector<std::unique_ptr<expression>>> > (that.value);
        break;

      case 32: // "stringlit"
        value.copy< std::unique_ptr<stringlit> > (that.value);
        break;

      case 48: // var_decl
        value.copy< std::unique_ptr<variable_declaration> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 49: // array_access
        value.move< std::unique_ptr<array_access> > (that.value);
        break;

      case 40: // stmts
      case 41: // program
      case 42: // block
        value.move< std::unique_ptr<block> > (that.value);
        break;

      case 30: // "decimal"
        value.move< std::unique_ptr<decimal> > (that.value);
        break;

      case 35: // expr
      case 36: // literals
      case 37: // binop_expr
      case 38: // unaryop_expr
      case 39: // compare_expr
        value.move< std::unique_ptr<expression> > (that.value);
        break;

      case 31: // "fraction"
        value.move< std::unique_ptr<fraction> > (that.value);
        break;

      case 29: // "identifier"
      case 34: // identifier
        value.move< std::unique_ptr<identifier> > (that.value);
        break;

      case 43: // stmt
      case 44: // conditional
      case 45: // for_loop
      case 46: // for_range
        value.move< std::unique_ptr<statement> > (that.value);
        break;

      case 47: // call_args
        value.move< std::unique_ptr<std::vector<std::unique_ptr<expression>>> > (that.value);
        break;

      case 32: // "stringlit"
        value.move< std::unique_ptr<stringlit> > (that.value);
        break;

      case 48: // var_decl
        value.move< std::unique_ptr<variable_declaration> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 29: // "identifier"
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<identifier> > (); }
#line 503 "parser.tab.cc"
        break;

      case 30: // "decimal"
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<decimal> > (); }
#line 509 "parser.tab.cc"
        break;

      case 31: // "fraction"
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<fraction> > (); }
#line 515 "parser.tab.cc"
        break;

      case 32: // "stringlit"
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<stringlit> > (); }
#line 521 "parser.tab.cc"
        break;

      case 34: // identifier
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<identifier> > (); }
#line 527 "parser.tab.cc"
        break;

      case 35: // expr
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<expression> > (); }
#line 533 "parser.tab.cc"
        break;

      case 36: // literals
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<expression> > (); }
#line 539 "parser.tab.cc"
        break;

      case 37: // binop_expr
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<expression> > (); }
#line 545 "parser.tab.cc"
        break;

      case 38: // unaryop_expr
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<expression> > (); }
#line 551 "parser.tab.cc"
        break;

      case 39: // compare_expr
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<expression> > (); }
#line 557 "parser.tab.cc"
        break;

      case 40: // stmts
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<block> > (); }
#line 563 "parser.tab.cc"
        break;

      case 41: // program
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<block> > (); }
#line 569 "parser.tab.cc"
        break;

      case 42: // block
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<block> > (); }
#line 575 "parser.tab.cc"
        break;

      case 43: // stmt
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<statement> > (); }
#line 581 "parser.tab.cc"
        break;

      case 44: // conditional
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<statement> > (); }
#line 587 "parser.tab.cc"
        break;

      case 45: // for_loop
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<statement> > (); }
#line 593 "parser.tab.cc"
        break;

      case 46: // for_range
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<statement> > (); }
#line 599 "parser.tab.cc"
        break;

      case 47: // call_args
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<std::vector<std::unique_ptr<expression>>> > (); }
#line 605 "parser.tab.cc"
        break;

      case 48: // var_decl
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<variable_declaration> > (); }
#line 611 "parser.tab.cc"
        break;

      case 49: // array_access
#line 100 "parser.y"
                 { yyo << yysym.value.template as < std::unique_ptr<array_access> > (); }
#line 617 "parser.tab.cc"
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 49: // array_access
        yylhs.value.emplace< std::unique_ptr<array_access> > ();
        break;

      case 40: // stmts
      case 41: // program
      case 42: // block
        yylhs.value.emplace< std::unique_ptr<block> > ();
        break;

      case 30: // "decimal"
        yylhs.value.emplace< std::unique_ptr<decimal> > ();
        break;

      case 35: // expr
      case 36: // literals
      case 37: // binop_expr
      case 38: // unaryop_expr
      case 39: // compare_expr
        yylhs.value.emplace< std::unique_ptr<expression> > ();
        break;

      case 31: // "fraction"
        yylhs.value.emplace< std::unique_ptr<fraction> > ();
        break;

      case 29: // "identifier"
      case 34: // identifier
        yylhs.value.emplace< std::unique_ptr<identifier> > ();
        break;

      case 43: // stmt
      case 44: // conditional
      case 45: // for_loop
      case 46: // for_range
        yylhs.value.emplace< std::unique_ptr<statement> > ();
        break;

      case 47: // call_args
        yylhs.value.emplace< std::unique_ptr<std::vector<std::unique_ptr<expression>>> > ();
        break;

      case 32: // "stringlit"
        yylhs.value.emplace< std::unique_ptr<stringlit> > ();
        break;

      case 48: // var_decl
        yylhs.value.emplace< std::unique_ptr<variable_declaration> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 118 "parser.y"
                    {

                program_block = std::move(yystack_[0].value.as < std::unique_ptr<block> > ());
                program_block->accept(v_pprint);

                }
#line 913 "parser.tab.cc"
    break;

  case 3:
#line 129 "parser.y"
                          {

                yylhs.value.as < std::unique_ptr<block> > () = std::make_unique<block>();

                yylhs.value.as < std::unique_ptr<block> > ()->statements.emplace_back(std::move(yystack_[0].value.as < std::unique_ptr<statement> > ()));
                yylhs.value.as < std::unique_ptr<block> > ()->accept(v_pprint);

                }
#line 926 "parser.tab.cc"
    break;

  case 4:
#line 137 "parser.y"
                               {

                yystack_[1].value.as < std::unique_ptr<block> > ()->statements.emplace_back(std::move(yystack_[0].value.as < std::unique_ptr<statement> > ()));

                // i added this because i std::move everytime and this moves the $block also
                // so i std::move back $meow to block to retain the address of main block
                // it was becoming null before, added null check in main.cpp as well
                // - shadowleaf

                yylhs.value.as < std::unique_ptr<block> > () = std::move(yystack_[1].value.as < std::unique_ptr<block> > ());

                }
#line 943 "parser.tab.cc"
    break;

  case 5:
#line 153 "parser.y"
                   {
                yylhs.value.as < std::unique_ptr<statement> > () = std::make_unique<expr_statement>(std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                yylhs.value.as < std::unique_ptr<statement> > ()->accept(v_pprint);
                }
#line 952 "parser.tab.cc"
    break;

  case 6:
#line 157 "parser.y"
                       {
                yylhs.value.as < std::unique_ptr<statement> > () = std::move(yystack_[0].value.as < std::unique_ptr<variable_declaration> > ());
                }
#line 960 "parser.tab.cc"
    break;

  case 7:
#line 160 "parser.y"
                          {
                yylhs.value.as < std::unique_ptr<statement> > () = std::move(yystack_[0].value.as < std::unique_ptr<statement> > ());
                 }
#line 968 "parser.tab.cc"
    break;

  case 8:
#line 163 "parser.y"
                       {
                yylhs.value.as < std::unique_ptr<statement> > () = std::move(yystack_[0].value.as < std::unique_ptr<statement> > ());
                yylhs.value.as < std::unique_ptr<statement> > ()->accept(v_pprint);
                }
#line 977 "parser.tab.cc"
    break;

  case 9:
#line 167 "parser.y"
                        {
                yylhs.value.as < std::unique_ptr<statement> > () = std::move(yystack_[0].value.as < std::unique_ptr<statement> > ());
                yylhs.value.as < std::unique_ptr<statement> > ()->accept(v_pprint);    
            }
#line 986 "parser.tab.cc"
    break;

  case 10:
#line 176 "parser.y"
                                                         {
                yylhs.value.as < std::unique_ptr<statement> > () = std::make_unique<for_loop>(std::move(yystack_[6].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[4].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<block> > ()));
            }
#line 994 "parser.tab.cc"
    break;

  case 11:
#line 181 "parser.y"
                                                            {
                yylhs.value.as < std::unique_ptr<statement> > () = std::make_unique<for_range>(std::move(yystack_[4].value.as < std::unique_ptr<identifier> > ()), std::move(yystack_[1].value.as < std::unique_ptr<decimal> > ()), std::move(yystack_[0].value.as < std::unique_ptr<block> > ()));
            }
#line 1002 "parser.tab.cc"
    break;

  case 12:
#line 188 "parser.y"
                            {
                    yylhs.value.as < std::unique_ptr<block> > () = std::move(yystack_[1].value.as < std::unique_ptr<block> > ());
                    yylhs.value.as < std::unique_ptr<block> > ()->accept(v_pprint);
                    }
#line 1011 "parser.tab.cc"
    break;

  case 13:
#line 196 "parser.y"
                                               {
                    yylhs.value.as < std::unique_ptr<statement> > () = std::make_unique<conditional>(std::move(yystack_[3].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[2].value.as < std::unique_ptr<block> > ()), std::move(yystack_[0].value.as < std::unique_ptr<block> > ()));
                    yylhs.value.as < std::unique_ptr<statement> > ()->accept(v_pprint);
                    }
#line 1020 "parser.tab.cc"
    break;

  case 14:
#line 200 "parser.y"
                                  {
                    yylhs.value.as < std::unique_ptr<statement> > () = std::make_unique<conditional>(std::move(yystack_[1].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<block> > ()));
                    yylhs.value.as < std::unique_ptr<statement> > ()->accept(v_pprint);
                }
#line 1029 "parser.tab.cc"
    break;

  case 15:
#line 208 "parser.y"
                                        {
                yylhs.value.as < std::unique_ptr<variable_declaration> > () = std::make_unique<variable_declaration>(std::move(yystack_[1].value.as < std::unique_ptr<identifier> > ()), std::move(yystack_[0].value.as < std::unique_ptr<identifier> > ()));
                yylhs.value.as < std::unique_ptr<variable_declaration> > ()->accept(v_pprint);
            }
#line 1038 "parser.tab.cc"
    break;

  case 16:
#line 212 "parser.y"
                                                 {
                yylhs.value.as < std::unique_ptr<variable_declaration> > () = std::make_unique<variable_declaration>(std::move(yystack_[3].value.as < std::unique_ptr<identifier> > ()), std::move(yystack_[2].value.as < std::unique_ptr<identifier> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                yylhs.value.as < std::unique_ptr<variable_declaration> > ()->accept(v_pprint);
            }
#line 1047 "parser.tab.cc"
    break;

  case 17:
#line 220 "parser.y"
                         {
                
                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[0].value.as < std::unique_ptr<decimal> > ());
                // LOG_S(INFO) << "found decimal at " << @1.begin.line << "." << @1.begin.column;
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                
                }
#line 1059 "parser.tab.cc"
    break;

  case 18:
#line 227 "parser.y"
                         {

                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[0].value.as < std::unique_ptr<fraction> > ());
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                
                }
#line 1070 "parser.tab.cc"
    break;

  case 19:
#line 233 "parser.y"
                          {

                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[0].value.as < std::unique_ptr<stringlit> > ());
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);

            }
#line 1081 "parser.tab.cc"
    break;

  case 20:
#line 243 "parser.y"
                                  {

                yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<assignment>(std::move(yystack_[2].value.as < std::unique_ptr<identifier> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);

                }
#line 1092 "parser.tab.cc"
    break;

  case 21:
#line 250 "parser.y"
                                           {
                // function call

                yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<function_call>(std::move(yystack_[3].value.as < std::unique_ptr<identifier> > ()), std::move(yystack_[1].value.as < std::unique_ptr<std::vector<std::unique_ptr<expression>>> > ()));
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);

                }
#line 1104 "parser.tab.cc"
    break;

  case 22:
#line 257 "parser.y"
                         {
                // just an identifier

                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[0].value.as < std::unique_ptr<identifier> > ());
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);

                }
#line 1116 "parser.tab.cc"
    break;

  case 23:
#line 265 "parser.y"
                       {

                // literal, either decimal or fractional

                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[0].value.as < std::unique_ptr<expression> > ());

                }
#line 1128 "parser.tab.cc"
    break;

  case 24:
#line 272 "parser.y"
                         {

                // some binary operation (numeric, not boolean)

                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[0].value.as < std::unique_ptr<expression> > ());
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                }
#line 1140 "parser.tab.cc"
    break;

  case 25:
#line 279 "parser.y"
                           {
                // a and or not, unary boolean expression

                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[0].value.as < std::unique_ptr<expression> > ());
                }
#line 1150 "parser.tab.cc"
    break;

  case 26:
#line 284 "parser.y"
                           {
                // a comparison expression

                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[0].value.as < std::unique_ptr<expression> > ());
                }
#line 1160 "parser.tab.cc"
    break;

  case 27:
#line 289 "parser.y"
                           {
                // accessing an element of array

                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[0].value.as < std::unique_ptr<array_access> > ());
                }
#line 1170 "parser.tab.cc"
    break;

  case 28:
#line 294 "parser.y"
                           { 
                yylhs.value.as < std::unique_ptr<expression> > () = std::move(yystack_[1].value.as < std::unique_ptr<expression> > ());
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                }
#line 1179 "parser.tab.cc"
    break;

  case 29:
#line 300 "parser.y"
                           { yylhs.value.as < std::unique_ptr<identifier> > () = std::move(yystack_[0].value.as < std::unique_ptr<identifier> > ()); yylhs.value.as < std::unique_ptr<identifier> > ()->accept(v_pprint); }
#line 1185 "parser.tab.cc"
    break;

  case 30:
#line 305 "parser.y"
                                   {
                yylhs.value.as < std::unique_ptr<std::vector<std::unique_ptr<expression>>> > () = std::make_unique<std::vector<std::unique_ptr<expression>>>();
                }
#line 1193 "parser.tab.cc"
    break;

  case 31:
#line 308 "parser.y"
                   {
                yylhs.value.as < std::unique_ptr<std::vector<std::unique_ptr<expression>>> > () = std::make_unique<std::vector<std::unique_ptr<expression>>>();
                yylhs.value.as < std::unique_ptr<std::vector<std::unique_ptr<expression>>> > ()->push_back(std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                }
#line 1202 "parser.tab.cc"
    break;

  case 32:
#line 312 "parser.y"
                                      {
                yystack_[2].value.as < std::unique_ptr<std::vector<std::unique_ptr<expression>>> > ()->push_back(std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                yylhs.value.as < std::unique_ptr<std::vector<std::unique_ptr<expression>>> > () = std::move(yystack_[2].value.as < std::unique_ptr<std::vector<std::unique_ptr<expression>>> > ());
                }
#line 1211 "parser.tab.cc"
    break;

  case 33:
#line 320 "parser.y"
                                          {
                    yylhs.value.as < std::unique_ptr<array_access> > () = std::make_unique<array_access>(std::move(yystack_[3].value.as < std::unique_ptr<identifier> > ()), std::move(yystack_[1].value.as < std::unique_ptr<expression> > ()));
                    yylhs.value.as < std::unique_ptr<array_access> > ()->accept(v_pprint);
                    }
#line 1220 "parser.tab.cc"
    break;

  case 34:
#line 324 "parser.y"
                                            {
                    yylhs.value.as < std::unique_ptr<array_access> > () = std::make_unique<array_access>(std::move(yystack_[3].value.as < std::unique_ptr<array_access> > ()), std::move(yystack_[1].value.as < std::unique_ptr<expression> > ()));
                    yylhs.value.as < std::unique_ptr<array_access> > ()->accept(v_pprint);
                }
#line 1229 "parser.tab.cc"
    break;

  case 35:
#line 332 "parser.y"
                              {

                yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<binary_operator>('&', std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()), yylhs.location);
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);

                }
#line 1240 "parser.tab.cc"
    break;

  case 36:
#line 338 "parser.y"
                             {

                yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<binary_operator>('|', std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()), yylhs.location);
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);

                }
#line 1251 "parser.tab.cc"
    break;

  case 37:
#line 344 "parser.y"
                            {
                yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<binary_operator>('+', std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()), yylhs.location);
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);

                }
#line 1261 "parser.tab.cc"
    break;

  case 38:
#line 349 "parser.y"
                            {
                yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<binary_operator>('-', std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()), yylhs.location);
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                }
#line 1270 "parser.tab.cc"
    break;

  case 39:
#line 353 "parser.y"
                            {
                yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<binary_operator>('*', std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()), yylhs.location);
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                }
#line 1279 "parser.tab.cc"
    break;

  case 40:
#line 357 "parser.y"
                            {
                yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<binary_operator>('/', std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()), yylhs.location);
                yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                }
#line 1288 "parser.tab.cc"
    break;

  case 41:
#line 364 "parser.y"
                                  {
                        yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<comp_operator>(">", std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                        yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                    }
#line 1297 "parser.tab.cc"
    break;

  case 42:
#line 368 "parser.y"
                                   {
                        yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<comp_operator>(">=", std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                        yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                    }
#line 1306 "parser.tab.cc"
    break;

  case 43:
#line 372 "parser.y"
                                  {

                        yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<comp_operator>("<", std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                        yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                    }
#line 1316 "parser.tab.cc"
    break;

  case 44:
#line 377 "parser.y"
                                   {

                        yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<comp_operator>("<=", std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                        yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                    }
#line 1326 "parser.tab.cc"
    break;

  case 45:
#line 382 "parser.y"
                                   {

                        yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<comp_operator>("==", std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                        yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                    }
#line 1336 "parser.tab.cc"
    break;

  case 46:
#line 387 "parser.y"
                                   {

                        yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<comp_operator>("!=", std::move(yystack_[2].value.as < std::unique_ptr<expression> > ()), std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()));
                        yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                }
#line 1346 "parser.tab.cc"
    break;

  case 47:
#line 396 "parser.y"
                             {
                    yylhs.value.as < std::unique_ptr<expression> > () = std::make_unique<unary_operator>('!', std::move(yystack_[0].value.as < std::unique_ptr<expression> > ()), yylhs.location);
                    yylhs.value.as < std::unique_ptr<expression> > ()->accept(v_pprint);
                    }
#line 1355 "parser.tab.cc"
    break;


#line 1359 "parser.tab.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -71;

  const signed char parser::yytable_ninf_ = -1;

  const short
  parser::yypact_[] =
  {
      48,    70,   -10,    70,    70,   -22,   -71,   -71,   -71,    -6,
     228,   -71,   -71,   -71,   -71,    48,     9,   -71,   -71,   -71,
     -71,   -71,    -8,   -71,   228,    70,     8,    91,   108,     5,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,   -71,   -71,    70,   125,    12,
      48,     7,   -71,    70,   228,   228,    -9,   142,   228,   228,
     243,   243,    64,    64,   228,   228,   228,   228,   228,   228,
     168,    70,    -7,    42,     3,   228,   -71,    70,   -71,   -71,
     194,     3,   -71,   -71,   228,    70,   -71,   211,     3,   -71
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,    29,    17,    18,    19,    22,
       5,    23,    24,    25,    26,     2,     0,     3,     7,     8,
       9,     6,    27,    29,    47,     0,     0,     0,     0,    15,
       0,    30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     4,     1,     0,     0,     0,
       0,    14,    28,     0,    20,    31,     0,     0,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    46,    45,
       0,     0,     0,     0,     0,    16,    21,     0,    33,    34,
       0,     0,    12,    13,    32,     0,    11,     0,     0,    10
  };

  const signed char
  parser::yypgoto_[] =
  {
     -71,    20,    -1,   -71,   -71,   -71,   -71,   -25,   -71,   -70,
     -14,   -71,   -71,   -71,   -71,   -71,   -71
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    51,
      17,    18,    19,    20,    56,    21,    22
  };

  const signed char
  parser::yytable_[] =
  {
      24,    45,    27,    28,    83,    30,    25,    29,    76,    46,
      31,    86,    47,    77,    32,    49,    53,    74,    89,    23,
      72,    50,    26,    81,    48,    73,     0,     0,     0,    54,
      55,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,     0,     0,    70,     1,     2,     0,
       0,     3,    75,     1,     2,     0,     0,     3,     4,    45,
       0,    82,     0,     0,     4,     0,     0,    33,    34,     0,
      80,     5,     6,     7,     8,     1,    84,     5,     6,     7,
       8,     0,     0,     0,    87,     0,     4,    39,    40,    41,
      42,    43,    44,     0,    33,    34,     0,     0,     0,    23,
       6,     7,     8,    35,    36,    37,    38,     0,     0,    50,
       0,    33,    34,     0,    39,    40,    41,    42,    43,    44,
      35,    36,    37,    38,     0,    52,     0,     0,    33,    34,
       0,    39,    40,    41,    42,    43,    44,    35,    36,    37,
      38,     0,     0,     0,     0,    33,    34,    71,    39,    40,
      41,    42,    43,    44,    35,    36,    37,    38,     0,     0,
       0,     0,     0,    78,     0,    39,    40,    41,    42,    43,
      44,    33,    34,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,    38,     0,     0,     0,     0,     0,    79,
       0,    39,    40,    41,    42,    43,    44,    33,    34,     0,
       0,     0,     0,     0,     0,     0,    35,    36,    37,    38,
       0,     0,     0,     0,    33,    34,    85,    39,    40,    41,
      42,    43,    44,    35,    36,    37,    38,     0,    88,     0,
       0,    33,    34,     0,    39,    40,    41,    42,    43,    44,
      35,    36,    37,    38,     0,     0,    33,    34,     0,     0,
       0,    39,    40,    41,    42,    43,    44,    37,    38,     0,
       0,     0,     0,     0,     0,     0,    39,    40,    41,    42,
      43,    44
  };

  const signed char
  parser::yycheck_[] =
  {
       1,    15,     3,     4,    74,    11,    16,    29,    17,     0,
      16,    81,    20,    22,    20,     7,    11,    10,    88,    29,
       8,    18,     2,    30,    25,    50,    -1,    -1,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    47,     5,     6,    -1,
      -1,     9,    53,     5,     6,    -1,    -1,     9,    16,    73,
      -1,    19,    -1,    -1,    16,    -1,    -1,     3,     4,    -1,
      71,    29,    30,    31,    32,     5,    77,    29,    30,    31,
      32,    -1,    -1,    -1,    85,    -1,    16,    23,    24,    25,
      26,    27,    28,    -1,     3,     4,    -1,    -1,    -1,    29,
      30,    31,    32,    12,    13,    14,    15,    -1,    -1,    18,
      -1,     3,     4,    -1,    23,    24,    25,    26,    27,    28,
      12,    13,    14,    15,    -1,    17,    -1,    -1,     3,     4,
      -1,    23,    24,    25,    26,    27,    28,    12,    13,    14,
      15,    -1,    -1,    -1,    -1,     3,     4,    22,    23,    24,
      25,    26,    27,    28,    12,    13,    14,    15,    -1,    -1,
      -1,    -1,    -1,    21,    -1,    23,    24,    25,    26,    27,
      28,     3,     4,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    13,    14,    15,    -1,    -1,    -1,    -1,    -1,    21,
      -1,    23,    24,    25,    26,    27,    28,     3,     4,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      -1,    -1,    -1,    -1,     3,     4,    22,    23,    24,    25,
      26,    27,    28,    12,    13,    14,    15,    -1,    17,    -1,
      -1,     3,     4,    -1,    23,    24,    25,    26,    27,    28,
      12,    13,    14,    15,    -1,    -1,     3,     4,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    28,    14,    15,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,
      27,    28
  };

  const signed char
  parser::yystos_[] =
  {
       0,     5,     6,     9,    16,    29,    30,    31,    32,    34,
      35,    36,    37,    38,    39,    40,    41,    43,    44,    45,
      46,    48,    49,    29,    35,    16,    34,    35,    35,    29,
      11,    16,    20,     3,     4,    12,    13,    14,    15,    23,
      24,    25,    26,    27,    28,    43,     0,    20,    35,     7,
      18,    42,    17,    11,    35,    35,    47,    35,    35,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    35,
      35,    22,     8,    40,    10,    35,    17,    22,    21,    21,
      35,    30,    19,    42,    35,    22,    42,    35,    17,    42
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    33,    41,    40,    40,    43,    43,    43,    43,    43,
      45,    46,    42,    44,    44,    48,    48,    36,    36,    36,
      35,    35,    35,    35,    35,    35,    35,    35,    35,    34,
      47,    47,    47,    49,    49,    37,    37,    37,    37,    37,
      37,    39,    39,    39,    39,    39,    39,    38
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       9,     6,     3,     5,     3,     2,     4,     1,     1,     1,
       3,     4,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     1,     3,     4,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"and\"", "\"or\"",
  "\"not\"", "\"for\"", "\"in\"", "\"range\"", "\"if\"", "\"else\"",
  "\"=\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"(\"", "\")\"", "\"{\"",
  "\"}\"", "\"[\"", "\"]\"", "\",\"", "\">\"", "\">=\"", "\"<\"", "\"<=\"",
  "\"!=\"", "\"==\"", "\"identifier\"", "\"decimal\"", "\"fraction\"",
  "\"stringlit\"", "$accept", "identifier", "expr", "literals",
  "binop_expr", "unaryop_expr", "compare_expr", "stmts", "program",
  "block", "stmt", "conditional", "for_loop", "for_range", "call_args",
  "var_decl", "array_access", YY_NULLPTR
  };


  const short
  parser::yyrline_[] =
  {
       0,   118,   118,   129,   137,   153,   157,   160,   163,   167,
     176,   181,   188,   196,   200,   208,   212,   220,   227,   233,
     243,   250,   257,   265,   272,   279,   284,   289,   294,   300,
     305,   308,   312,   320,   324,   332,   338,   344,   349,   353,
     357,   364,   368,   372,   377,   382,   387,   396
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1746 "parser.tab.cc"

#line 423 "parser.y"


void yy::parser::error (const location_type& l, const std::string& m) {
  std::cerr << l << ": " << m << '\n';
}
