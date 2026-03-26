/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int yylex(void);
extern int yyparse(void);
extern FILE *yyin;
extern int line_no;

static FILE *outfile;
static int indent_level = 0;
static int include_stdio = 0;
static int include_math = 0;
static int include_bool = 0;

static void emit_indent(void);
static void emit_line(const char *fmt, ...);
static char *dupstr(const char *s);
static char *fmtstr(const char *fmt, ...);
static void emit_include(const char *header);

void yyerror(const char *s);

#line 97 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENT = 3,                      /* IDENT  */
  YYSYMBOL_NUMBER = 4,                     /* NUMBER  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_HEADER = 6,                     /* HEADER  */
  YYSYMBOL_INCLUDE = 7,                    /* INCLUDE  */
  YYSYMBOL_DEFINE = 8,                     /* DEFINE  */
  YYSYMBOL_MAIN = 9,                       /* MAIN  */
  YYSYMBOL_TYPE_INT = 10,                  /* TYPE_INT  */
  YYSYMBOL_TYPE_FLOAT = 11,                /* TYPE_FLOAT  */
  YYSYMBOL_TYPE_DOUBLE = 12,               /* TYPE_DOUBLE  */
  YYSYMBOL_TYPE_LONG = 13,                 /* TYPE_LONG  */
  YYSYMBOL_TYPE_CHAR = 14,                 /* TYPE_CHAR  */
  YYSYMBOL_TYPE_BOOL = 15,                 /* TYPE_BOOL  */
  YYSYMBOL_TYPE_VOID = 16,                 /* TYPE_VOID  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_PRINT = 18,                     /* PRINT  */
  YYSYMBOL_IF = 19,                        /* IF  */
  YYSYMBOL_ELIF = 20,                      /* ELIF  */
  YYSYMBOL_ELSE = 21,                      /* ELSE  */
  YYSYMBOL_THEN = 22,                      /* THEN  */
  YYSYMBOL_FOR = 23,                       /* FOR  */
  YYSYMBOL_WHILE_KW = 24,                  /* WHILE_KW  */
  YYSYMBOL_BREAK_KW = 25,                  /* BREAK_KW  */
  YYSYMBOL_CONTINUE_KW = 26,               /* CONTINUE_KW  */
  YYSYMBOL_ASSIGN = 27,                    /* ASSIGN  */
  YYSYMBOL_AND = 28,                       /* AND  */
  YYSYMBOL_OR = 29,                        /* OR  */
  YYSYMBOL_NOT = 30,                       /* NOT  */
  YYSYMBOL_LE = 31,                        /* LE  */
  YYSYMBOL_GE = 32,                        /* GE  */
  YYSYMBOL_EQ = 33,                        /* EQ  */
  YYSYMBOL_NE = 34,                        /* NE  */
  YYSYMBOL_35_ = 35,                       /* '<'  */
  YYSYMBOL_36_ = 36,                       /* '>'  */
  YYSYMBOL_37_ = 37,                       /* '+'  */
  YYSYMBOL_38_ = 38,                       /* '-'  */
  YYSYMBOL_39_ = 39,                       /* '*'  */
  YYSYMBOL_40_ = 40,                       /* '/'  */
  YYSYMBOL_41_ = 41,                       /* '%'  */
  YYSYMBOL_UMINUS = 42,                    /* UMINUS  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* '{'  */
  YYSYMBOL_46_ = 46,                       /* '}'  */
  YYSYMBOL_47_ = 47,                       /* ';'  */
  YYSYMBOL_48_ = 48,                       /* ','  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_top_items = 51,                 /* top_items  */
  YYSYMBOL_top_item = 52,                  /* top_item  */
  YYSYMBOL_include_directive = 53,         /* include_directive  */
  YYSYMBOL_define_directive = 54,          /* define_directive  */
  YYSYMBOL_function_def = 55,              /* function_def  */
  YYSYMBOL_56_1 = 56,                      /* $@1  */
  YYSYMBOL_main_block = 57,                /* main_block  */
  YYSYMBOL_58_2 = 58,                      /* $@2  */
  YYSYMBOL_compound_tail = 59,             /* compound_tail  */
  YYSYMBOL_stmt_list = 60,                 /* stmt_list  */
  YYSYMBOL_stmt = 61,                      /* stmt  */
  YYSYMBOL_block_stmt = 62,                /* block_stmt  */
  YYSYMBOL_63_3 = 63,                      /* $@3  */
  YYSYMBOL_if_stmt = 64,                   /* if_stmt  */
  YYSYMBOL_65_4 = 65,                      /* $@4  */
  YYSYMBOL_if_tail = 66,                   /* if_tail  */
  YYSYMBOL_67_5 = 67,                      /* $@5  */
  YYSYMBOL_68_6 = 68,                      /* $@6  */
  YYSYMBOL_while_stmt = 69,                /* while_stmt  */
  YYSYMBOL_70_7 = 70,                      /* $@7  */
  YYSYMBOL_for_stmt = 71,                  /* for_stmt  */
  YYSYMBOL_72_8 = 72,                      /* $@8  */
  YYSYMBOL_declaration = 73,               /* declaration  */
  YYSYMBOL_opt_init = 74,                  /* opt_init  */
  YYSYMBOL_assignment = 75,                /* assignment  */
  YYSYMBOL_return_stmt = 76,               /* return_stmt  */
  YYSYMBOL_print_stmt = 77,                /* print_stmt  */
  YYSYMBOL_break_stmt = 78,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 79,             /* continue_stmt  */
  YYSYMBOL_call_expr = 80,                 /* call_expr  */
  YYSYMBOL_arg_list_opt = 81,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 82,                  /* arg_list  */
  YYSYMBOL_param_list_opt = 83,            /* param_list_opt  */
  YYSYMBOL_param_list = 84,                /* param_list  */
  YYSYMBOL_param = 85,                     /* param  */
  YYSYMBOL_opt_expr = 86,                  /* opt_expr  */
  YYSYMBOL_expr = 87,                      /* expr  */
  YYSYMBOL_type = 88                       /* type  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   228

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  161

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    41,     2,     2,
      43,    44,    39,    37,    48,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    47,
      35,     2,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    54,    54,    58,    59,    63,    64,    65,    69,    77,
      85,    84,    94,    93,   102,   112,   113,   117,   121,   125,
     129,   133,   137,   141,   145,   146,   147,   148,   149,   156,
     155,   165,   164,   173,   175,   174,   181,   180,   190,   189,
     199,   198,   207,   215,   218,   225,   232,   239,   246,   253,
     260,   268,   271,   278,   282,   290,   293,   300,   304,   311,
     319,   322,   329,   333,   337,   341,   345,   349,   353,   357,
     361,   365,   369,   373,   377,   381,   385,   389,   393,   397,
     401,   405,   412,   416,   420,   424,   428,   432,   436
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENT", "NUMBER",
  "STRING_LITERAL", "HEADER", "INCLUDE", "DEFINE", "MAIN", "TYPE_INT",
  "TYPE_FLOAT", "TYPE_DOUBLE", "TYPE_LONG", "TYPE_CHAR", "TYPE_BOOL",
  "TYPE_VOID", "RETURN", "PRINT", "IF", "ELIF", "ELSE", "THEN", "FOR",
  "WHILE_KW", "BREAK_KW", "CONTINUE_KW", "ASSIGN", "AND", "OR", "NOT",
  "LE", "GE", "EQ", "NE", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "UMINUS", "'('", "')'", "'{'", "'}'", "';'", "','", "$accept", "program",
  "top_items", "top_item", "include_directive", "define_directive",
  "function_def", "$@1", "main_block", "$@2", "compound_tail", "stmt_list",
  "stmt", "block_stmt", "$@3", "if_stmt", "$@4", "if_tail", "$@5", "$@6",
  "while_stmt", "$@7", "for_stmt", "$@8", "declaration", "opt_init",
  "assignment", "return_stmt", "print_stmt", "break_stmt", "continue_stmt",
  "call_expr", "arg_list_opt", "arg_list", "param_list_opt", "param_list",
  "param", "opt_expr", "expr", "type", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-107)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -107,    35,   202,  -107,    30,    34,    -4,  -107,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,    37,
    -107,     0,    -2,     1,     2,  -107,  -107,     0,     0,     0,
    -107,   145,     3,   209,     0,  -107,  -107,   131,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -107,     5,    10,  -107,    44,    16,    11,   145,  -107,
     156,    61,    15,    15,   167,   167,    15,    15,   -29,   -29,
    -107,  -107,  -107,  -107,    18,   209,  -107,  -107,     0,  -107,
      59,  -107,  -107,   145,   -11,     0,    22,     0,    24,     0,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
      14,    33,    39,    40,    60,    78,    79,    88,  -107,     0,
     145,     0,    81,     0,   116,  -107,  -107,  -107,  -107,  -107,
    -107,  -107,  -107,    54,  -107,   145,    64,    82,    85,   145,
    -107,  -107,     0,  -107,  -107,  -107,     0,  -107,   145,  -107,
      99,  -107,    -6,     0,     0,    83,  -107,   114,   102,  -107,
      84,   155,  -107,  -107,  -107,  -107,  -107,  -107,  -107,    -6,
    -107
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,    82,    83,    84,
      85,    86,    87,    88,     3,     5,     6,     7,     2,     0,
       8,     0,     0,     0,    62,    63,    64,     0,     0,     0,
      65,     9,     0,    55,    51,    80,    81,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     0,    56,    57,     0,     0,    52,    53,    66,
      78,    79,    74,    75,    76,    77,    72,    73,    67,    68,
      69,    70,    71,    16,     0,     0,    59,    50,     0,    13,
       0,    10,    58,    54,     0,     0,     0,     0,     0,     0,
      48,    49,    29,    14,    28,    15,    24,    25,    26,    27,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
      46,    51,     0,    60,     0,    16,    17,    18,    19,    20,
      22,    23,    21,    43,    11,    45,     0,     0,     0,    61,
      38,    30,     0,    42,    47,    31,    60,    16,    44,    16,
       0,    39,    33,    60,     0,     0,    32,     0,     0,    36,
       0,     0,    16,    40,    34,    37,    16,    16,    41,    33,
      35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -106,  -107,  -107,  -107,  -107,  -107,  -107,    42,  -107,  -107,
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,
    -107,   146,   117,  -107,  -107,  -107,   152,  -102,   -21,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,    15,    16,    17,   108,    18,    73,
      79,    80,    95,    96,   115,    97,   139,   146,   157,   152,
      98,   137,    99,   156,   100,   133,   101,   102,   103,   104,
     105,    30,    56,    57,    52,    53,    54,   128,   129,    55
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      31,    19,   124,    24,    25,    26,    35,    36,    37,   131,
      48,    49,    50,    58,   144,   145,   109,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      27,   141,    34,   142,   140,     3,    20,    21,    28,    22,
      23,   147,    32,    29,    33,    34,   155,    76,    51,    74,
     158,   159,    46,    47,    48,    49,    50,    83,    75,    78,
      77,   116,    84,    81,   110,   111,   112,   113,   114,     7,
       8,     9,    10,    11,    12,    13,    85,    86,    87,   107,
     117,   132,    88,    89,    90,    91,   118,   119,   125,    38,
      58,   123,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,   127,    92,    93,    94,   120,   134,    38,
      39,   138,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,   148,   151,   121,   122,   135,   149,   153,
      38,    39,   136,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    38,    39,   143,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,   150,    38,
      39,   130,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    38,    39,    59,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    40,    41,
     154,   160,    44,    45,    46,    47,    48,    49,    50,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     7,
       8,     9,    10,    11,    12,    13,   106,    82,   126
};

static const yytype_uint8 yycheck[] =
{
      21,     2,   108,     3,     4,     5,    27,    28,    29,   115,
      39,    40,    41,    34,    20,    21,    27,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      30,   137,    43,   139,   136,     0,     6,     3,    38,    43,
       3,   143,    44,    43,    43,    43,   152,     3,    45,    44,
     156,   157,    37,    38,    39,    40,    41,    78,    48,    48,
      44,    47,     3,    45,    85,    43,    87,    43,    89,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    80,
      47,    27,    23,    24,    25,    26,    47,    47,   109,    28,
     111,     3,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    22,    45,    46,    47,    47,    44,    28,
      29,   132,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,   144,    22,    47,    47,    45,    45,    45,
      28,    29,    47,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    28,    29,    47,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    44,    28,
      29,    45,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    28,    29,    44,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    31,    32,
      45,   159,    35,    36,    37,    38,    39,    40,    41,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    10,
      11,    12,    13,    14,    15,    16,    80,    75,   111
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    52,    53,    54,    55,    57,    88,
       6,     3,    43,     3,     3,     4,     5,    30,    38,    43,
      80,    87,    44,    43,    43,    87,    87,    87,    28,    29,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    45,    83,    84,    85,    88,    81,    82,    87,    44,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    58,    44,    48,     3,    44,    48,    59,
      60,    45,    85,    87,     3,    17,    18,    19,    23,    24,
      25,    26,    45,    46,    47,    61,    62,    64,    69,    71,
      73,    75,    76,    77,    78,    79,    80,    88,    56,    27,
      87,    43,    87,    43,    87,    63,    47,    47,    47,    47,
      47,    47,    47,     3,    59,    87,    81,    22,    86,    87,
      45,    59,    27,    74,    44,    45,    47,    70,    87,    65,
      86,    59,    59,    47,    20,    21,    66,    86,    87,    45,
      44,    22,    68,    45,    45,    59,    72,    67,    59,    59,
      66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    53,    54,
      56,    55,    58,    57,    59,    60,    60,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    63,
      62,    65,    64,    66,    67,    66,    68,    66,    70,    69,
      72,    71,    73,    74,    74,    75,    76,    77,    78,    79,
      80,    81,    81,    82,    82,    83,    83,    84,    84,    85,
      86,    86,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    88,    88,    88,    88,    88,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     1,     1,     2,     3,
       0,     8,     0,     6,     2,     2,     0,     2,     2,     2,
       2,     2,     2,     2,     1,     1,     1,     1,     1,     0,
       3,     0,     7,     0,     0,     7,     0,     4,     0,     5,
       0,    11,     3,     0,     2,     3,     2,     4,     1,     1,
       4,     0,     1,     1,     3,     0,     1,     1,     3,     2,
       0,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 8: /* include_directive: INCLUDE HEADER  */
#line 70 "parser.y"
      {
          emit_include((yyvsp[0].str));
          free((yyvsp[0].str));
      }
#line 1569 "parser.tab.c"
    break;

  case 9: /* define_directive: DEFINE IDENT expr  */
#line 78 "parser.y"
      {
          emit_line("#define %s %s", (yyvsp[-1].str), (yyvsp[0].str));
      }
#line 1577 "parser.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 85 "parser.y"
      {
          emit_line("%s %s(%s) {", (yyvsp[-5].str), (yyvsp[-4].str), (yyvsp[-2].str));
          indent_level++;
      }
#line 1586 "parser.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 94 "parser.y"
      {
          emit_line("int main() {");
          indent_level++;
      }
#line 1595 "parser.tab.c"
    break;

  case 14: /* compound_tail: stmt_list '}'  */
#line 103 "parser.y"
      {
          if (indent_level > 0) {
              indent_level--;
          }
          emit_line("}");
      }
#line 1606 "parser.tab.c"
    break;

  case 17: /* stmt: declaration ';'  */
#line 118 "parser.y"
      {
          emit_line("%s;", (yyvsp[-1].str));
      }
#line 1614 "parser.tab.c"
    break;

  case 18: /* stmt: assignment ';'  */
#line 122 "parser.y"
      {
          emit_line("%s;", (yyvsp[-1].str));
      }
#line 1622 "parser.tab.c"
    break;

  case 19: /* stmt: return_stmt ';'  */
#line 126 "parser.y"
      {
          emit_line("%s;", (yyvsp[-1].str));
      }
#line 1630 "parser.tab.c"
    break;

  case 20: /* stmt: print_stmt ';'  */
#line 130 "parser.y"
      {
          emit_line("%s;", (yyvsp[-1].str));
      }
#line 1638 "parser.tab.c"
    break;

  case 21: /* stmt: call_expr ';'  */
#line 134 "parser.y"
      {
          emit_line("%s;", (yyvsp[-1].str));
      }
#line 1646 "parser.tab.c"
    break;

  case 22: /* stmt: break_stmt ';'  */
#line 138 "parser.y"
      {
          emit_line("%s;", (yyvsp[-1].str));
      }
#line 1654 "parser.tab.c"
    break;

  case 23: /* stmt: continue_stmt ';'  */
#line 142 "parser.y"
      {
          emit_line("%s;", (yyvsp[-1].str));
      }
#line 1662 "parser.tab.c"
    break;

  case 28: /* stmt: ';'  */
#line 150 "parser.y"
      {
      }
#line 1669 "parser.tab.c"
    break;

  case 29: /* $@3: %empty  */
#line 156 "parser.y"
      {
          emit_line("{");
          indent_level++;
      }
#line 1678 "parser.tab.c"
    break;

  case 31: /* $@4: %empty  */
#line 165 "parser.y"
      {
          emit_line("if (%s) {", (yyvsp[-2].str));
          indent_level++;
      }
#line 1687 "parser.tab.c"
    break;

  case 34: /* $@5: %empty  */
#line 175 "parser.y"
      {
          emit_line("else if (%s) {", (yyvsp[-2].str));
          indent_level++;
      }
#line 1696 "parser.tab.c"
    break;

  case 36: /* $@6: %empty  */
#line 181 "parser.y"
      {
          emit_line("else {");
          indent_level++;
      }
#line 1705 "parser.tab.c"
    break;

  case 38: /* $@7: %empty  */
#line 190 "parser.y"
      {
          emit_line("while (%s) {", (yyvsp[-1].str));
          indent_level++;
      }
#line 1714 "parser.tab.c"
    break;

  case 40: /* $@8: %empty  */
#line 199 "parser.y"
      {
          emit_line("for (%s; %s; %s) {", (yyvsp[-6].str), (yyvsp[-4].str), (yyvsp[-2].str));
          indent_level++;
      }
#line 1723 "parser.tab.c"
    break;

  case 42: /* declaration: type IDENT opt_init  */
#line 208 "parser.y"
      {
          (yyval.str) = fmtstr("%s %s%s", (yyvsp[-2].str), (yyvsp[-1].str), (yyvsp[0].str));
      }
#line 1731 "parser.tab.c"
    break;

  case 43: /* opt_init: %empty  */
#line 215 "parser.y"
      {
          (yyval.str) = dupstr("");
      }
#line 1739 "parser.tab.c"
    break;

  case 44: /* opt_init: ASSIGN expr  */
#line 219 "parser.y"
      {
          (yyval.str) = fmtstr(" = %s", (yyvsp[0].str));
      }
#line 1747 "parser.tab.c"
    break;

  case 45: /* assignment: IDENT ASSIGN expr  */
#line 226 "parser.y"
      {
          (yyval.str) = fmtstr("%s = %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1755 "parser.tab.c"
    break;

  case 46: /* return_stmt: RETURN expr  */
#line 233 "parser.y"
      {
          (yyval.str) = fmtstr("return %s", (yyvsp[0].str));
      }
#line 1763 "parser.tab.c"
    break;

  case 47: /* print_stmt: PRINT '(' arg_list_opt ')'  */
#line 240 "parser.y"
      {
          (yyval.str) = fmtstr("printf(%s)", (yyvsp[-1].str));
      }
#line 1771 "parser.tab.c"
    break;

  case 48: /* break_stmt: BREAK_KW  */
#line 247 "parser.y"
      {
          (yyval.str) = dupstr("break");
      }
#line 1779 "parser.tab.c"
    break;

  case 49: /* continue_stmt: CONTINUE_KW  */
#line 254 "parser.y"
      {
          (yyval.str) = dupstr("continue");
      }
#line 1787 "parser.tab.c"
    break;

  case 50: /* call_expr: IDENT '(' arg_list_opt ')'  */
#line 261 "parser.y"
      {
          (yyval.str) = fmtstr("%s(%s)", (yyvsp[-3].str), (yyvsp[-1].str));
      }
#line 1795 "parser.tab.c"
    break;

  case 51: /* arg_list_opt: %empty  */
#line 268 "parser.y"
      {
          (yyval.str) = dupstr("");
      }
#line 1803 "parser.tab.c"
    break;

  case 52: /* arg_list_opt: arg_list  */
#line 272 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1811 "parser.tab.c"
    break;

  case 53: /* arg_list: expr  */
#line 279 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1819 "parser.tab.c"
    break;

  case 54: /* arg_list: arg_list ',' expr  */
#line 283 "parser.y"
      {
          (yyval.str) = fmtstr("%s, %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1827 "parser.tab.c"
    break;

  case 55: /* param_list_opt: %empty  */
#line 290 "parser.y"
      {
          (yyval.str) = dupstr("");
      }
#line 1835 "parser.tab.c"
    break;

  case 56: /* param_list_opt: param_list  */
#line 294 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1843 "parser.tab.c"
    break;

  case 57: /* param_list: param  */
#line 301 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1851 "parser.tab.c"
    break;

  case 58: /* param_list: param_list ',' param  */
#line 305 "parser.y"
      {
          (yyval.str) = fmtstr("%s, %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1859 "parser.tab.c"
    break;

  case 59: /* param: type IDENT  */
#line 312 "parser.y"
      {
          (yyval.str) = fmtstr("%s %s", (yyvsp[-1].str), (yyvsp[0].str));
      }
#line 1867 "parser.tab.c"
    break;

  case 60: /* opt_expr: %empty  */
#line 319 "parser.y"
      {
          (yyval.str) = dupstr("");
      }
#line 1875 "parser.tab.c"
    break;

  case 61: /* opt_expr: expr  */
#line 323 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1883 "parser.tab.c"
    break;

  case 62: /* expr: IDENT  */
#line 330 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1891 "parser.tab.c"
    break;

  case 63: /* expr: NUMBER  */
#line 334 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1899 "parser.tab.c"
    break;

  case 64: /* expr: STRING_LITERAL  */
#line 338 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1907 "parser.tab.c"
    break;

  case 65: /* expr: call_expr  */
#line 342 "parser.y"
      {
          (yyval.str) = (yyvsp[0].str);
      }
#line 1915 "parser.tab.c"
    break;

  case 66: /* expr: '(' expr ')'  */
#line 346 "parser.y"
      {
          (yyval.str) = fmtstr("(%s)", (yyvsp[-1].str));
      }
#line 1923 "parser.tab.c"
    break;

  case 67: /* expr: expr '+' expr  */
#line 350 "parser.y"
      {
          (yyval.str) = fmtstr("%s + %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1931 "parser.tab.c"
    break;

  case 68: /* expr: expr '-' expr  */
#line 354 "parser.y"
      {
          (yyval.str) = fmtstr("%s - %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1939 "parser.tab.c"
    break;

  case 69: /* expr: expr '*' expr  */
#line 358 "parser.y"
      {
          (yyval.str) = fmtstr("%s * %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1947 "parser.tab.c"
    break;

  case 70: /* expr: expr '/' expr  */
#line 362 "parser.y"
      {
          (yyval.str) = fmtstr("%s / %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1955 "parser.tab.c"
    break;

  case 71: /* expr: expr '%' expr  */
#line 366 "parser.y"
      {
          (yyval.str) = fmtstr("%s %% %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1963 "parser.tab.c"
    break;

  case 72: /* expr: expr '<' expr  */
#line 370 "parser.y"
      {
          (yyval.str) = fmtstr("%s < %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1971 "parser.tab.c"
    break;

  case 73: /* expr: expr '>' expr  */
#line 374 "parser.y"
      {
          (yyval.str) = fmtstr("%s > %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1979 "parser.tab.c"
    break;

  case 74: /* expr: expr LE expr  */
#line 378 "parser.y"
      {
          (yyval.str) = fmtstr("%s <= %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1987 "parser.tab.c"
    break;

  case 75: /* expr: expr GE expr  */
#line 382 "parser.y"
      {
          (yyval.str) = fmtstr("%s >= %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 1995 "parser.tab.c"
    break;

  case 76: /* expr: expr EQ expr  */
#line 386 "parser.y"
      {
          (yyval.str) = fmtstr("%s == %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 2003 "parser.tab.c"
    break;

  case 77: /* expr: expr NE expr  */
#line 390 "parser.y"
      {
          (yyval.str) = fmtstr("%s != %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 2011 "parser.tab.c"
    break;

  case 78: /* expr: expr AND expr  */
#line 394 "parser.y"
      {
          (yyval.str) = fmtstr("%s && %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 2019 "parser.tab.c"
    break;

  case 79: /* expr: expr OR expr  */
#line 398 "parser.y"
      {
          (yyval.str) = fmtstr("%s || %s", (yyvsp[-2].str), (yyvsp[0].str));
      }
#line 2027 "parser.tab.c"
    break;

  case 80: /* expr: NOT expr  */
#line 402 "parser.y"
      {
          (yyval.str) = fmtstr("!%s", (yyvsp[0].str));
      }
#line 2035 "parser.tab.c"
    break;

  case 81: /* expr: '-' expr  */
#line 406 "parser.y"
      {
          (yyval.str) = fmtstr("-%s", (yyvsp[0].str));
      }
#line 2043 "parser.tab.c"
    break;

  case 82: /* type: TYPE_INT  */
#line 413 "parser.y"
      {
          (yyval.str) = dupstr("int");
      }
#line 2051 "parser.tab.c"
    break;

  case 83: /* type: TYPE_FLOAT  */
#line 417 "parser.y"
      {
          (yyval.str) = dupstr("float");
      }
#line 2059 "parser.tab.c"
    break;

  case 84: /* type: TYPE_DOUBLE  */
#line 421 "parser.y"
      {
          (yyval.str) = dupstr("double");
      }
#line 2067 "parser.tab.c"
    break;

  case 85: /* type: TYPE_LONG  */
#line 425 "parser.y"
      {
          (yyval.str) = dupstr("long int");
      }
#line 2075 "parser.tab.c"
    break;

  case 86: /* type: TYPE_CHAR  */
#line 429 "parser.y"
      {
          (yyval.str) = dupstr("char");
      }
#line 2083 "parser.tab.c"
    break;

  case 87: /* type: TYPE_BOOL  */
#line 433 "parser.y"
      {
          (yyval.str) = dupstr("bool");
      }
#line 2091 "parser.tab.c"
    break;

  case 88: /* type: TYPE_VOID  */
#line 437 "parser.y"
      {
          (yyval.str) = dupstr("void");
      }
#line 2099 "parser.tab.c"
    break;


#line 2103 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 442 "parser.y"


static void emit_indent(void) {
    for (int i = 0; i < indent_level; i++) {
        fputs("    ", outfile);
    }
}

static void emit_line(const char *fmt, ...) {
    va_list ap;
    emit_indent();
    va_start(ap, fmt);
    vfprintf(outfile, fmt, ap);
    va_end(ap);
    fputc('\n', outfile);
}

static char *dupstr(const char *s) {
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (!copy) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    memcpy(copy, s, len);
    return copy;
}

static char *fmtstr(const char *fmt, ...) {
    va_list ap;
    va_list copy;
    int needed;
    char *buf;

    va_start(ap, fmt);
    va_copy(copy, ap);
    needed = vsnprintf(NULL, 0, fmt, copy);
    va_end(copy);

    if (needed < 0) {
        va_end(ap);
        fprintf(stderr, "Formatting error\n");
        exit(1);
    }

    buf = malloc((size_t)needed + 1);
    if (!buf) {
        va_end(ap);
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }

    vsnprintf(buf, (size_t)needed + 1, fmt, ap);
    va_end(ap);
    return buf;
}

static void emit_include(const char *header) {
    if (strcmp(header, "<stdio.h>") == 0) {
        if (include_stdio) return;
        include_stdio = 1;
    } else if (strcmp(header, "<math.h>") == 0) {
        if (include_math) return;
        include_math = 1;
    } else if (strcmp(header, "<stdbool.h>") == 0) {
        if (include_bool) return;
        include_bool = 1;
    }

    emit_line("#include %s", header);
}

void yyerror(const char *s) {
    fprintf(stderr, "Parse error on line %d: %s\n", line_no, s);
}

int main(int argc, char **argv) {
    const char *input_path = (argc > 1) ? argv[1] : "input.txt";
    const char *output_path = (argc > 2) ? argv[2] : "output.c";
    FILE *infile = fopen(input_path, "r");

    if (!infile) {
        fprintf(stderr, "Error: Cannot open %s\n", input_path);
        return 1;
    }

    outfile = fopen(output_path, "w");
    if (!outfile) {
        fprintf(stderr, "Error: Cannot create %s\n", output_path);
        fclose(infile);
        return 1;
    }

    fprintf(outfile, "#include <stdio.h>\n");
    fprintf(outfile, "#include <math.h>\n");
    fprintf(outfile, "#include <stdbool.h>\n\n");
    include_stdio = 1;
    include_math = 1;
    include_bool = 1;

    yyin = infile;
    if (yyparse() != 0) {
        fclose(infile);
        fclose(outfile);
        return 1;
    }

    fclose(infile);
    fclose(outfile);

    printf("output.c generated successfully.\n");
    printf("Total lines processed: %d\n", line_no);
    return 0;
}
