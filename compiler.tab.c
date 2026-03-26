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
#line 1 "compiler.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>

extern int yylex(void);
extern FILE *yyin;
extern int line_no;
extern char last_token_text[];
extern int last_token_line;
extern char current_line_text[];

static FILE *outf;
static int indent_level = 0;
static int syntax_error_count = 0;
static int semantic_error_count = 0;
static struct Function *current_function = NULL;

typedef enum {
    T_INT,
    T_FLOAT,
    T_DOUBLE,
    T_LONG,
    T_CHAR,
    T_BOOL,
    T_VOID,
    T_STRING,
    T_UNKNOWN,
    T_ERROR
} TypeKind;

typedef struct Expr Expr;
typedef struct ExprList ExprList;
typedef struct Param Param;
typedef struct Stmt Stmt;
typedef struct Branch Branch;
typedef struct Function Function;
typedef struct Include Include;
typedef struct Define Define;
typedef struct Symbol Symbol;
typedef struct Scope Scope;
typedef struct IfTail IfTail;

typedef enum {
    EXPR_IDENT,
    EXPR_NUMBER,
    EXPR_STRING,
    EXPR_CALL,
    EXPR_INDEX,
    EXPR_BINARY,
    EXPR_UNARY
} ExprKind;

typedef enum {
    STMT_DECL,
    STMT_ASSIGN,
    STMT_INDEX_ASSIGN,
    STMT_RETURN,
    STMT_PRINT,
    STMT_BREAK,
    STMT_CONTINUE,
    STMT_EXPR,
    STMT_BLOCK,
    STMT_IF,
    STMT_WHILE,
    STMT_FOR
} StmtKind;

struct Expr {
    int line;
    ExprKind kind;
    TypeKind inferred;
    int is_array;
    int array_size;
    char *text;
    char *op;
    Expr *left;
    Expr *right;
    Expr *index;
    ExprList *args;
};

struct ExprList {
    Expr *expr;
    ExprList *next;
};

struct Param {
    char *name;
    TypeKind type;
    int line;
    Param *next;
};

struct Branch {
    Expr *cond;
    Stmt *body;
    int line;
    Branch *next;
};

struct Stmt {
    int line;
    StmtKind kind;
    Stmt *next;
    union {
        struct {
            TypeKind type;
            char *name;
            int is_array;
            int array_size;
            Expr *init;
            ExprList *array_init;
        } decl;
        struct {
            char *name;
            Expr *value;
        } assign;
        struct {
            char *name;
            Expr *index;
            Expr *value;
        } index_assign;
        struct {
            Expr *expr;
        } ret;
        struct {
            ExprList *args;
        } print;
        struct {
            Expr *expr;
        } expr_stmt;
        struct {
            Stmt *stmts;
        } block;
        struct {
            Expr *cond;
            Stmt *then_branch;
            Branch *elifs;
            Stmt *else_branch;
        } if_stmt;
        struct {
            Expr *cond;
            Stmt *body;
        } while_stmt;
        struct {
            Expr *init;
            Expr *cond;
            Expr *post;
            Stmt *body;
        } for_stmt;
    } u;
};

struct Function {
    char *name;
    TypeKind return_type;
    Param *params;
    Stmt *body;
    int line;
    int is_main;
    Function *next;
};

struct Include {
    char *header;
    int line;
    Include *next;
};

struct Define {
    char *name;
    Expr *value;
    int line;
    Define *next;
};

struct Symbol {
    char *name;
    TypeKind type;
    int is_array;
    int array_size;
    int is_function;
    TypeKind return_type;
    Param *params;
    Symbol *next;
};

struct Scope {
    Symbol *symbols;
    Scope *parent;
};

struct IfTail {
    Branch *elifs;
    Stmt *else_branch;
};

static Include *g_includes = NULL;
static Include *g_includes_tail = NULL;
static Define *g_defines = NULL;
static Define *g_defines_tail = NULL;
static Function *g_functions = NULL;
static Function *g_functions_tail = NULL;
static Function *g_main_fn = NULL;
static Scope *scope_stack = NULL;

static void yyerror(const char *s);
static void semantic_error(int line, const char *fmt, ...);
static void syntax_error(int line, const char *fmt, ...);
static TypeKind type_from_string(const char *name);
static const char *type_name(TypeKind type);
static int is_numeric(TypeKind type);
static int is_integral(TypeKind type);
static int is_bool_like(TypeKind type);
static int type_compatible(TypeKind expected, TypeKind actual);
static TypeKind numeric_promote(TypeKind left, TypeKind right);
static Expr *make_expr_ident(char *name, int line);
static Expr *make_expr_number(char *text, int line);
static Expr *make_expr_string(char *text, int line);
static Expr *make_expr_call(char *name, ExprList *args, int line);
static Expr *make_expr_index(char *name, Expr *index, int line);
static Expr *make_expr_binary(char *op, Expr *left, Expr *right, int line);
static Expr *make_expr_unary(char *op, Expr *expr, int line);
static ExprList *expr_list_single(Expr *expr);
static ExprList *expr_list_append(ExprList *list, Expr *expr);
static Param *param_new(const char *type_name, char *name, int line);
static Param *param_append(Param *list, Param *node);
static Branch *branch_new(Expr *cond, Stmt *body, int line);
static Stmt *stmt_new(StmtKind kind, int line);
static Stmt *stmt_append(Stmt *list, Stmt *node);
static Stmt *make_decl_stmt(const char *type_name, char *name, Expr *init, ExprList *array_init, int line);
static Stmt *make_assign_stmt(char *name, Expr *value, int line);
static Stmt *make_index_assign_stmt(char *name, Expr *index, Expr *value, int line);
static Stmt *make_return_stmt(Expr *expr, int line);
static Stmt *make_print_stmt(ExprList *args, int line);
static Stmt *make_expr_stmt(Expr *expr, int line);
static Stmt *make_block_stmt(Stmt *stmts, int line);
static Stmt *make_if_stmt(Expr *cond, Stmt *then_branch, Branch *elifs, Stmt *else_branch, int line);
static Stmt *make_while_stmt(Expr *cond, Stmt *body, int line);
static Stmt *make_for_stmt(Expr *init, Expr *cond, Expr *post, Stmt *body, int line);
static Stmt *make_break_stmt(int line);
static Stmt *make_continue_stmt(int line);
static Function *function_new(char *name, const char *return_type_name, Param *params, Stmt *body, int line, int is_main);
static void add_include(char *header, int line);
static void add_define(char *name, Expr *value, int line);
static void add_function(Function *fn);
static void set_main(Function *fn);
static Scope *push_scope(void);
static void pop_scope(void);
static Symbol *scope_lookup(Scope *scope, const char *name);
static Symbol *lookup_symbol(const char *name);
static Symbol *scope_add_symbol(const char *name, TypeKind type, int line);
static Function *find_function(const char *name);
static void add_function_symbol(const Function *fn);
static void analyze_program(void);
static void analyze_function(Function *fn);
static void analyze_stmt_list(Stmt *stmt);
static void analyze_stmt(Stmt *stmt);
static TypeKind infer_expr(Expr *expr);
static void emit_program(const char *path);
static void emit_include(FILE *f, const char *header);
static void emit_indent(FILE *f);
static void emit_stmt_list(FILE *f, Stmt *stmt);
static void emit_stmt(FILE *f, Stmt *stmt);
static void emit_expr(FILE *f, Expr *expr);
static void emit_params(FILE *f, Param *params);
static int includes_contains(const char *header);
static void emit_binary_search_helper(FILE *f);

#line 345 "compiler.tab.c"

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

#include "compiler.tab.h"
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
  YYSYMBOL_48_ = 48,                       /* '['  */
  YYSYMBOL_49_ = 49,                       /* ']'  */
  YYSYMBOL_50_ = 50,                       /* ','  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_top_items = 53,                 /* top_items  */
  YYSYMBOL_top_item = 54,                  /* top_item  */
  YYSYMBOL_function_def = 55,              /* function_def  */
  YYSYMBOL_main_block = 56,                /* main_block  */
  YYSYMBOL_block = 57,                     /* block  */
  YYSYMBOL_stmt_list = 58,                 /* stmt_list  */
  YYSYMBOL_stmt = 59,                      /* stmt  */
  YYSYMBOL_if_stmt = 60,                   /* if_stmt  */
  YYSYMBOL_if_tail = 61,                   /* if_tail  */
  YYSYMBOL_while_stmt = 62,                /* while_stmt  */
  YYSYMBOL_for_stmt = 63,                  /* for_stmt  */
  YYSYMBOL_param_list_opt = 64,            /* param_list_opt  */
  YYSYMBOL_param_list = 65,                /* param_list  */
  YYSYMBOL_param = 66,                     /* param  */
  YYSYMBOL_arg_list_opt = 67,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 68,                  /* arg_list  */
  YYSYMBOL_opt_expr = 69,                  /* opt_expr  */
  YYSYMBOL_opt_init = 70,                  /* opt_init  */
  YYSYMBOL_expr = 71,                      /* expr  */
  YYSYMBOL_type = 72                       /* type  */
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
#define YYLAST   365

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

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
      43,    44,    39,    37,    50,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    47,
      35,     2,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    49,     2,     2,     2,     2,     2,     2,
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
       0,   306,   306,   315,   316,   320,   324,   328,   332,   340,
     348,   352,   360,   365,   371,   375,   381,   387,   392,   396,
     400,   404,   408,   412,   416,   420,   421,   422,   423,   427,
     431,   439,   448,   458,   472,   486,   493,   501,   504,   511,
     515,   522,   530,   533,   540,   544,   552,   555,   563,   566,
     573,   577,   581,   585,   589,   593,   597,   601,   605,   609,
     613,   617,   621,   625,   629,   633,   637,   641,   645,   649,
     653,   660,   661,   662,   663,   664,   665,   666
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  static const char *const yy_sname[] =
  {
  "end of file", "error", "invalid token", "IDENT", "NUMBER",
  "STRING_LITERAL", "HEADER", "INCLUDE", "DEFINE", "MAIN", "TYPE_INT",
  "TYPE_FLOAT", "TYPE_DOUBLE", "TYPE_LONG", "TYPE_CHAR", "TYPE_BOOL",
  "TYPE_VOID", "RETURN", "PRINT", "IF", "ELIF", "ELSE", "THEN", "FOR",
  "WHILE_KW", "BREAK_KW", "CONTINUE_KW", "ASSIGN", "AND", "OR", "NOT",
  "LE", "GE", "EQ", "NE", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "UMINUS", "'('", "')'", "'{'", "'}'", "';'", "'['", "']'", "','",
  "$accept", "program", "top_items", "top_item", "function_def",
  "main_block", "block", "stmt_list", "stmt", "if_stmt", "if_tail",
  "while_stmt", "for_stmt", "param_list_opt", "param_list", "param",
  "arg_list_opt", "arg_list", "opt_expr", "opt_init", "expr", "type", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-104)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -104,    12,   349,  -104,    30,    45,     9,  -104,  -104,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,  -104,    52,  -104,    28,
      13,    35,   -38,  -104,  -104,    28,    28,    28,   289,    19,
     140,    28,    28,  -104,  -104,   275,    28,    28,    28,    28,
      28,    28,    28,    28,    28,    28,    28,    28,    28,  -104,
    -104,    37,    32,  -104,    77,    40,    38,   289,    66,  -104,
     314,   303,    36,    36,     6,     6,    36,    36,    21,    21,
    -104,  -104,  -104,   119,    19,   140,  -104,  -104,    28,  -104,
     -31,     8,    28,    44,    28,    46,    28,    61,    62,  -104,
    -104,  -104,  -104,  -104,  -104,  -104,   158,    88,  -104,  -104,
     289,  -104,  -104,    65,    28,    28,   175,    28,   195,    28,
     260,  -104,  -104,  -104,   -18,    28,    63,   209,   139,  -104,
      67,    19,    69,   289,  -104,    89,    71,   289,  -104,  -104,
      85,    74,    49,    28,    64,  -104,    28,  -104,    28,    19,
    -104,    78,   -13,   226,   246,  -104,    28,    80,  -104,  -104,
      19,    82,    28,    49,    19,    90,  -104,  -104,    93,  -104
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,    71,    72,    73,
      74,    75,    76,    77,     3,     7,     2,     0,     5,     0,
       0,     0,    50,    52,    53,     0,     0,     0,     6,     0,
      37,    42,     0,    69,    70,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       9,     0,    38,    39,     0,     0,    43,    44,     0,    55,
      67,    68,    63,    64,    65,    66,    61,    62,    56,    57,
      58,    59,    60,     0,     0,     0,    41,    54,     0,    51,
       0,    50,     0,     0,     0,     0,     0,     0,     0,    10,
      29,    28,    12,    25,    26,    27,     0,     0,     8,    40,
      45,    11,    30,    48,     0,     0,     0,    42,     0,    46,
       0,    23,    24,    22,    48,     0,     0,     0,     0,    20,
       0,     0,     0,    47,    35,     0,     0,    49,    17,    18,
      51,     0,    32,    46,     0,    14,     0,    21,     0,     0,
      31,     0,     0,     0,     0,    34,    46,     0,    15,    19,
       0,     0,    42,    32,     0,     0,    33,    36,     0,    16
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -104,  -104,  -104,  -104,  -104,  -104,   -71,  -104,  -104,  -104,
     -12,  -104,  -104,  -104,  -104,    72,  -103,  -104,   -93,    34,
     -19,    -1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,    15,    16,    50,    73,    92,    93,
     140,    94,    95,    51,    52,    53,    55,    56,   122,   116,
      57,    54
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      28,    17,    91,    98,   120,    31,    33,    34,    35,   115,
      32,   103,     3,    58,   147,   101,   102,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
     125,    22,    23,    24,   148,   104,    18,    38,    39,   124,
     141,    42,    43,    44,    45,    46,    47,    48,    19,   155,
     132,    31,    20,   151,    96,    21,   105,    29,    25,   100,
      46,    47,    48,   106,    49,   108,    26,   110,   145,   138,
     139,    27,    97,    44,    45,    46,    47,    48,    30,   153,
      76,    74,    75,   157,    77,   117,   118,   107,    78,   109,
     123,   114,   115,   134,    36,    37,   127,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,   111,   112,
     128,   131,   136,   142,   123,    79,   133,   143,   135,   144,
      80,   137,    81,    23,    24,   146,   154,   123,   152,     7,
       8,     9,    10,    11,    12,    13,    82,    83,    84,   158,
     159,   156,    85,    86,    87,    88,     0,    99,   126,    25,
       7,     8,     9,    10,    11,    12,    13,    26,     0,     0,
       0,     0,    27,     0,    49,    89,    90,    36,    37,     0,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,     0,     0,     0,    36,    37,   130,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
       0,     0,     0,    36,    37,   113,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,   121,     0,     0,
       0,     0,   119,    36,    37,     0,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    36,    37,     0,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,     0,    36,    37,   129,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,   150,     0,
       0,     0,     0,   149,    36,    37,     0,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    36,    37,
       0,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,     0,    36,    37,    49,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    36,    37,    59,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    36,     0,     0,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13
};

static const yytype_int16 yycheck[] =
{
      19,     2,    73,    74,   107,    43,    25,    26,    27,    27,
      48,     3,     0,    32,    27,    46,    47,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      48,     3,     4,     5,    47,    27,     6,    31,    32,   110,
     133,    35,    36,    37,    38,    39,    40,    41,     3,   152,
     121,    43,    43,   146,    73,     3,    48,    44,    30,    78,
      39,    40,    41,    82,    45,    84,    38,    86,   139,    20,
      21,    43,    73,    37,    38,    39,    40,    41,    43,   150,
       3,    44,    50,   154,    44,   104,   105,    43,    50,    43,
     109,     3,    27,     4,    28,    29,   115,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    47,    47,
      47,    44,    27,    49,   133,    49,    47,   136,    47,   138,
       1,    47,     3,     4,     5,    47,    44,   146,    48,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    49,
      47,   153,    23,    24,    25,    26,    -1,    75,   114,    30,
      10,    11,    12,    13,    14,    15,    16,    38,    -1,    -1,
      -1,    -1,    43,    -1,    45,    46,    47,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    28,    29,    49,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    28,    29,    47,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    22,    -1,    -1,
      -1,    -1,    47,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    -1,    28,    29,    47,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    22,    -1,
      -1,    -1,    -1,    47,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    28,    29,
      -1,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    -1,    28,    29,    45,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    28,    29,    44,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    28,    -1,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,    53,     0,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    54,    55,    56,    72,     6,     3,
      43,     3,     3,     4,     5,    30,    38,    43,    71,    44,
      43,    43,    48,    71,    71,    71,    28,    29,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    45,
      57,    64,    65,    66,    72,    67,    68,    71,    71,    44,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    58,    44,    50,     3,    44,    50,    49,
       1,     3,    17,    18,    19,    23,    24,    25,    26,    46,
      47,    57,    59,    60,    62,    63,    71,    72,    57,    66,
      71,    46,    47,     3,    27,    48,    71,    43,    71,    43,
      71,    47,    47,    47,     3,    27,    70,    71,    71,    47,
      67,    22,    69,    71,    57,    48,    70,    71,    47,    47,
      49,    44,    57,    47,     4,    47,    27,    47,    20,    21,
      61,    69,    49,    71,    71,    57,    47,    27,    47,    47,
      22,    69,    48,    57,    44,    67,    61,    57,    49,    47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    55,    56,
      57,    57,    58,    58,    59,    59,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    60,    61,    61,    61,    62,    63,    64,    64,    65,
      65,    66,    67,    67,    68,    68,    69,    69,    70,    70,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    72,    72,    72,    72,    72,    72
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     3,     1,     6,     4,
       3,     4,     2,     0,     4,     6,    10,     4,     4,     7,
       3,     5,     2,     2,     2,     1,     1,     1,     1,     1,
       2,     5,     0,     5,     2,     3,     9,     0,     1,     1,
       3,     2,     0,     1,     1,     3,     0,     1,     0,     2,
       1,     4,     1,     1,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     1,     1,     1,     1,     1,     1
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
          = yysize + yystrlen (yysymbol_name (yyarg[yyi]));
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
          yyp = yystpcpy (yyp, yysymbol_name (yyarg[yyi++]));
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
  case 2: /* program: top_items main_block  */
#line 307 "compiler.y"
      {
          if (!g_main_fn) {
              syntax_error(line_no, "missing Start_From_Here() block");
          }
      }
#line 1767 "compiler.tab.c"
    break;

  case 5: /* top_item: INCLUDE HEADER  */
#line 321 "compiler.y"
      {
          add_include((yyvsp[0].str), line_no);
      }
#line 1775 "compiler.tab.c"
    break;

  case 6: /* top_item: DEFINE IDENT expr  */
#line 325 "compiler.y"
      {
          add_define((yyvsp[-1].str), (yyvsp[0].ptr), line_no);
      }
#line 1783 "compiler.tab.c"
    break;

  case 8: /* function_def: type IDENT '(' param_list_opt ')' block  */
#line 333 "compiler.y"
      {
          add_function(function_new((yyvsp[-4].str), (yyvsp[-5].str), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no, 0));
          (yyval.ptr) = NULL;
      }
#line 1792 "compiler.tab.c"
    break;

  case 9: /* main_block: MAIN '(' ')' block  */
#line 341 "compiler.y"
      {
          set_main(function_new(strdup("main"), "int", NULL, (yyvsp[0].ptr), line_no, 1));
          (yyval.ptr) = NULL;
      }
#line 1801 "compiler.tab.c"
    break;

  case 10: /* block: '{' stmt_list '}'  */
#line 349 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[-1].ptr);
      }
#line 1809 "compiler.tab.c"
    break;

  case 11: /* block: '{' stmt_list error '}'  */
#line 353 "compiler.y"
            {
                    yyerrok;
                    (yyval.ptr) = (yyvsp[-2].ptr);
            }
#line 1818 "compiler.tab.c"
    break;

  case 12: /* stmt_list: stmt_list stmt  */
#line 361 "compiler.y"
      {
          (yyval.ptr) = stmt_append((yyvsp[-1].ptr), (yyvsp[0].ptr));
      }
#line 1826 "compiler.tab.c"
    break;

  case 13: /* stmt_list: %empty  */
#line 365 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 1834 "compiler.tab.c"
    break;

  case 14: /* stmt: type IDENT opt_init ';'  */
#line 372 "compiler.y"
      {
          (yyval.ptr) = make_decl_stmt((yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[-1].ptr), NULL, line_no);
      }
#line 1842 "compiler.tab.c"
    break;

  case 15: /* stmt: type IDENT '[' NUMBER ']' ';'  */
#line 376 "compiler.y"
            {
                    (yyval.ptr) = make_decl_stmt((yyvsp[-5].str), (yyvsp[-4].str), NULL, NULL, line_no);
                    ((Stmt *)(yyval.ptr))->u.decl.is_array = 1;
                    ((Stmt *)(yyval.ptr))->u.decl.array_size = atoi((yyvsp[-2].str));
            }
#line 1852 "compiler.tab.c"
    break;

  case 16: /* stmt: type IDENT '[' NUMBER ']' ASSIGN '[' arg_list_opt ']' ';'  */
#line 382 "compiler.y"
            {
                    (yyval.ptr) = make_decl_stmt((yyvsp[-9].str), (yyvsp[-8].str), NULL, (ExprList *)(yyvsp[-2].ptr), line_no);
                    ((Stmt *)(yyval.ptr))->u.decl.is_array = 1;
                    ((Stmt *)(yyval.ptr))->u.decl.array_size = atoi((yyvsp[-6].str));
            }
#line 1862 "compiler.tab.c"
    break;

  case 17: /* stmt: IDENT IDENT opt_init ';'  */
#line 388 "compiler.y"
            {
                    semantic_error(line_no, "unknown type '%s'", (yyvsp[-3].str));
                    (yyval.ptr) = NULL;
            }
#line 1871 "compiler.tab.c"
    break;

  case 18: /* stmt: IDENT ASSIGN expr ';'  */
#line 393 "compiler.y"
      {
          (yyval.ptr) = make_assign_stmt((yyvsp[-3].str), (yyvsp[-1].ptr), line_no);
      }
#line 1879 "compiler.tab.c"
    break;

  case 19: /* stmt: IDENT '[' expr ']' ASSIGN expr ';'  */
#line 397 "compiler.y"
            {
                    (yyval.ptr) = make_index_assign_stmt((yyvsp[-6].str), (yyvsp[-4].ptr), (yyvsp[-1].ptr), line_no);
            }
#line 1887 "compiler.tab.c"
    break;

  case 20: /* stmt: RETURN expr ';'  */
#line 401 "compiler.y"
      {
          (yyval.ptr) = make_return_stmt((yyvsp[-1].ptr), line_no);
      }
#line 1895 "compiler.tab.c"
    break;

  case 21: /* stmt: PRINT '(' arg_list_opt ')' ';'  */
#line 405 "compiler.y"
      {
          (yyval.ptr) = make_print_stmt((yyvsp[-2].ptr), line_no);
      }
#line 1903 "compiler.tab.c"
    break;

  case 22: /* stmt: expr ';'  */
#line 409 "compiler.y"
      {
          (yyval.ptr) = make_expr_stmt((yyvsp[-1].ptr), line_no);
      }
#line 1911 "compiler.tab.c"
    break;

  case 23: /* stmt: BREAK_KW ';'  */
#line 413 "compiler.y"
      {
          (yyval.ptr) = make_break_stmt(line_no);
      }
#line 1919 "compiler.tab.c"
    break;

  case 24: /* stmt: CONTINUE_KW ';'  */
#line 417 "compiler.y"
      {
          (yyval.ptr) = make_continue_stmt(line_no);
      }
#line 1927 "compiler.tab.c"
    break;

  case 28: /* stmt: block  */
#line 424 "compiler.y"
      {
          (yyval.ptr) = make_block_stmt((yyvsp[0].ptr), line_no);
      }
#line 1935 "compiler.tab.c"
    break;

  case 29: /* stmt: ';'  */
#line 428 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 1943 "compiler.tab.c"
    break;

  case 30: /* stmt: error ';'  */
#line 432 "compiler.y"
            {
                    yyerrok;
                    (yyval.ptr) = NULL;
            }
#line 1952 "compiler.tab.c"
    break;

  case 31: /* if_stmt: IF expr THEN block if_tail  */
#line 440 "compiler.y"
      {
                    IfTail *tail = (IfTail *)(yyvsp[0].ptr);
                    (yyval.ptr) = make_if_stmt((yyvsp[-3].ptr), (yyvsp[-1].ptr), tail->elifs, tail->else_branch, line_no);
      }
#line 1961 "compiler.tab.c"
    break;

  case 32: /* if_tail: %empty  */
#line 448 "compiler.y"
      {
          IfTail *tail = malloc(sizeof(IfTail));
          if (!tail) {
              fprintf(stderr, "Out of memory\n");
              exit(1);
          }
          tail->elifs = NULL;
          tail->else_branch = NULL;
          (yyval.ptr) = tail;
      }
#line 1976 "compiler.tab.c"
    break;

  case 33: /* if_tail: ELIF expr THEN block if_tail  */
#line 459 "compiler.y"
      {
          Branch *node = branch_new((yyvsp[-3].ptr), (yyvsp[-1].ptr), line_no);
          IfTail *tail = (IfTail *)(yyvsp[0].ptr);
          node->next = tail->elifs;
          IfTail *out = malloc(sizeof(IfTail));
          if (!out) {
              fprintf(stderr, "Out of memory\n");
              exit(1);
          }
          out->elifs = node;
          out->else_branch = tail->else_branch;
          (yyval.ptr) = out;
      }
#line 1994 "compiler.tab.c"
    break;

  case 34: /* if_tail: ELSE block  */
#line 473 "compiler.y"
      {
          IfTail *out = malloc(sizeof(IfTail));
          if (!out) {
              fprintf(stderr, "Out of memory\n");
              exit(1);
          }
          out->elifs = NULL;
          out->else_branch = (yyvsp[0].ptr);
          (yyval.ptr) = out;
      }
#line 2009 "compiler.tab.c"
    break;

  case 35: /* while_stmt: WHILE_KW expr block  */
#line 487 "compiler.y"
      {
          (yyval.ptr) = make_while_stmt((yyvsp[-1].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2017 "compiler.tab.c"
    break;

  case 36: /* for_stmt: FOR '(' opt_expr ';' opt_expr ';' opt_expr ')' block  */
#line 494 "compiler.y"
      {
          (yyval.ptr) = make_for_stmt((yyvsp[-6].ptr), (yyvsp[-4].ptr), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2025 "compiler.tab.c"
    break;

  case 37: /* param_list_opt: %empty  */
#line 501 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 2033 "compiler.tab.c"
    break;

  case 38: /* param_list_opt: param_list  */
#line 505 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2041 "compiler.tab.c"
    break;

  case 39: /* param_list: param  */
#line 512 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2049 "compiler.tab.c"
    break;

  case 40: /* param_list: param_list ',' param  */
#line 516 "compiler.y"
      {
          (yyval.ptr) = param_append((yyvsp[-2].ptr), (yyvsp[0].ptr));
      }
#line 2057 "compiler.tab.c"
    break;

  case 41: /* param: type IDENT  */
#line 523 "compiler.y"
      {
          (yyval.ptr) = param_new((yyvsp[-1].str), (yyvsp[0].str), line_no);
      }
#line 2065 "compiler.tab.c"
    break;

  case 42: /* arg_list_opt: %empty  */
#line 530 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 2073 "compiler.tab.c"
    break;

  case 43: /* arg_list_opt: arg_list  */
#line 534 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2081 "compiler.tab.c"
    break;

  case 44: /* arg_list: expr  */
#line 541 "compiler.y"
      {
          (yyval.ptr) = expr_list_single((yyvsp[0].ptr));
      }
#line 2089 "compiler.tab.c"
    break;

  case 45: /* arg_list: arg_list ',' expr  */
#line 545 "compiler.y"
      {
          (yyval.ptr) = expr_list_append((yyvsp[-2].ptr), (yyvsp[0].ptr));
      }
#line 2097 "compiler.tab.c"
    break;

  case 46: /* opt_expr: %empty  */
#line 552 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 2105 "compiler.tab.c"
    break;

  case 47: /* opt_expr: expr  */
#line 556 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2113 "compiler.tab.c"
    break;

  case 48: /* opt_init: %empty  */
#line 563 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 2121 "compiler.tab.c"
    break;

  case 49: /* opt_init: ASSIGN expr  */
#line 567 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2129 "compiler.tab.c"
    break;

  case 50: /* expr: IDENT  */
#line 574 "compiler.y"
      {
          (yyval.ptr) = make_expr_ident((yyvsp[0].str), line_no);
      }
#line 2137 "compiler.tab.c"
    break;

  case 51: /* expr: IDENT '[' expr ']'  */
#line 578 "compiler.y"
            {
                    (yyval.ptr) = make_expr_index((yyvsp[-3].str), (yyvsp[-1].ptr), line_no);
            }
#line 2145 "compiler.tab.c"
    break;

  case 52: /* expr: NUMBER  */
#line 582 "compiler.y"
      {
          (yyval.ptr) = make_expr_number((yyvsp[0].str), line_no);
      }
#line 2153 "compiler.tab.c"
    break;

  case 53: /* expr: STRING_LITERAL  */
#line 586 "compiler.y"
      {
          (yyval.ptr) = make_expr_string((yyvsp[0].str), line_no);
      }
#line 2161 "compiler.tab.c"
    break;

  case 54: /* expr: IDENT '(' arg_list_opt ')'  */
#line 590 "compiler.y"
      {
          (yyval.ptr) = make_expr_call((yyvsp[-3].str), (yyvsp[-1].ptr), line_no);
      }
#line 2169 "compiler.tab.c"
    break;

  case 55: /* expr: '(' expr ')'  */
#line 594 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[-1].ptr);
      }
#line 2177 "compiler.tab.c"
    break;

  case 56: /* expr: expr '+' expr  */
#line 598 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("+"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2185 "compiler.tab.c"
    break;

  case 57: /* expr: expr '-' expr  */
#line 602 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("-"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2193 "compiler.tab.c"
    break;

  case 58: /* expr: expr '*' expr  */
#line 606 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("*"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2201 "compiler.tab.c"
    break;

  case 59: /* expr: expr '/' expr  */
#line 610 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("/"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2209 "compiler.tab.c"
    break;

  case 60: /* expr: expr '%' expr  */
#line 614 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("%"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2217 "compiler.tab.c"
    break;

  case 61: /* expr: expr '<' expr  */
#line 618 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("<"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2225 "compiler.tab.c"
    break;

  case 62: /* expr: expr '>' expr  */
#line 622 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup(">"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2233 "compiler.tab.c"
    break;

  case 63: /* expr: expr LE expr  */
#line 626 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("<="), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2241 "compiler.tab.c"
    break;

  case 64: /* expr: expr GE expr  */
#line 630 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup(">="), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2249 "compiler.tab.c"
    break;

  case 65: /* expr: expr EQ expr  */
#line 634 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("=="), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2257 "compiler.tab.c"
    break;

  case 66: /* expr: expr NE expr  */
#line 638 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("!="), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2265 "compiler.tab.c"
    break;

  case 67: /* expr: expr AND expr  */
#line 642 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("&&"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2273 "compiler.tab.c"
    break;

  case 68: /* expr: expr OR expr  */
#line 646 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("||"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2281 "compiler.tab.c"
    break;

  case 69: /* expr: NOT expr  */
#line 650 "compiler.y"
      {
          (yyval.ptr) = make_expr_unary(strdup("!"), (yyvsp[0].ptr), line_no);
      }
#line 2289 "compiler.tab.c"
    break;

  case 70: /* expr: '-' expr  */
#line 654 "compiler.y"
      {
          (yyval.ptr) = make_expr_unary(strdup("-"), (yyvsp[0].ptr), line_no);
      }
#line 2297 "compiler.tab.c"
    break;

  case 71: /* type: TYPE_INT  */
#line 660 "compiler.y"
                  { (yyval.str) = strdup("int"); }
#line 2303 "compiler.tab.c"
    break;

  case 72: /* type: TYPE_FLOAT  */
#line 661 "compiler.y"
                  { (yyval.str) = strdup("float"); }
#line 2309 "compiler.tab.c"
    break;

  case 73: /* type: TYPE_DOUBLE  */
#line 662 "compiler.y"
                  { (yyval.str) = strdup("double"); }
#line 2315 "compiler.tab.c"
    break;

  case 74: /* type: TYPE_LONG  */
#line 663 "compiler.y"
                  { (yyval.str) = strdup("long int"); }
#line 2321 "compiler.tab.c"
    break;

  case 75: /* type: TYPE_CHAR  */
#line 664 "compiler.y"
                  { (yyval.str) = strdup("char"); }
#line 2327 "compiler.tab.c"
    break;

  case 76: /* type: TYPE_BOOL  */
#line 665 "compiler.y"
                  { (yyval.str) = strdup("bool"); }
#line 2333 "compiler.tab.c"
    break;

  case 77: /* type: TYPE_VOID  */
#line 666 "compiler.y"
                  { (yyval.str) = strdup("void"); }
#line 2339 "compiler.tab.c"
    break;


#line 2343 "compiler.tab.c"

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

#line 669 "compiler.y"


static void syntax_error(int line, const char *fmt, ...) {
    va_list ap;
    syntax_error_count++;
    fprintf(stderr, "Syntax error on line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
}

static void semantic_error(int line, const char *fmt, ...) {
    va_list ap;
    fprintf(stderr, "Semantic error on line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    semantic_error_count++;
}

static void yyerror(const char *s) {
    syntax_error_count++;
    if (last_token_text[0] != '\0') {
        fprintf(stderr, "Syntax error on line %d near '%s': %s\n", last_token_line, last_token_text, s);
    } else {
        fprintf(stderr, "Syntax error on line %d: %s\n", line_no, s);
    }

    if (current_line_text[0] != '\0') {
        fprintf(stderr, "  %s\n", current_line_text);
    }
}

static const char *type_name(TypeKind type) {
    switch (type) {
        case T_INT: return "int";
        case T_FLOAT: return "float";
        case T_DOUBLE: return "double";
        case T_LONG: return "long int";
        case T_CHAR: return "char";
        case T_BOOL: return "bool";
        case T_VOID: return "void";
        case T_STRING: return "string";
        case T_UNKNOWN: return "unknown";
        case T_ERROR: return "error";
    }
    return "unknown";
}

static int is_numeric(TypeKind type) {
    return type == T_INT || type == T_FLOAT || type == T_DOUBLE || type == T_LONG || type == T_CHAR;
}

static int is_integral(TypeKind type) {
    return type == T_INT || type == T_LONG || type == T_CHAR;
}

static int is_bool_like(TypeKind type) {
    return type == T_BOOL || is_numeric(type);
}

static int type_compatible(TypeKind expected, TypeKind actual) {
    if (expected == T_ERROR || actual == T_ERROR) return 1;
    if (expected == actual) return 1;
    if (expected == T_UNKNOWN || actual == T_UNKNOWN) return 1;
    return 0;
}

static TypeKind numeric_promote(TypeKind left, TypeKind right) {
    if (left == T_ERROR || right == T_ERROR) return T_ERROR;
    if (left == T_DOUBLE || right == T_DOUBLE) return T_DOUBLE;
    if (left == T_FLOAT || right == T_FLOAT) return T_FLOAT;
    if (left == T_LONG || right == T_LONG) return T_LONG;
    return T_INT;
}

static Expr *alloc_expr(ExprKind kind, int line) {
    Expr *expr = calloc(1, sizeof(*expr));
    if (!expr) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    expr->kind = kind;
    expr->line = line;
    expr->inferred = T_UNKNOWN;
    expr->is_array = 0;
    expr->array_size = 0;
    expr->index = NULL;
    return expr;
}

static Expr *make_expr_ident(char *name, int line) {
    Expr *expr = alloc_expr(EXPR_IDENT, line);
    expr->text = name;
    return expr;
}

static Expr *make_expr_number(char *text, int line) {
    Expr *expr = alloc_expr(EXPR_NUMBER, line);
    expr->text = text;
    return expr;
}

static Expr *make_expr_string(char *text, int line) {
    Expr *expr = alloc_expr(EXPR_STRING, line);
    expr->text = text;
    return expr;
}

static Expr *make_expr_call(char *name, ExprList *args, int line) {
    Expr *expr = alloc_expr(EXPR_CALL, line);
    expr->text = name;
    expr->args = args;
    return expr;
}

static Expr *make_expr_index(char *name, Expr *index, int line) {
    Expr *expr = alloc_expr(EXPR_INDEX, line);
    expr->text = name;
    expr->index = index;
    return expr;
}

static Expr *make_expr_binary(char *op, Expr *left, Expr *right, int line) {
    Expr *expr = alloc_expr(EXPR_BINARY, line);
    expr->op = op;
    expr->left = left;
    expr->right = right;
    return expr;
}

static Expr *make_expr_unary(char *op, Expr *expr_node, int line) {
    Expr *expr = alloc_expr(EXPR_UNARY, line);
    expr->op = op;
    expr->left = expr_node;
    return expr;
}

static ExprList *expr_list_single(Expr *expr) {
    ExprList *list = calloc(1, sizeof(*list));
    if (!list) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    list->expr = expr;
    return list;
}

static ExprList *expr_list_append(ExprList *list, Expr *expr) {
    if (!list) return expr_list_single(expr);
    ExprList *tail = list;
    while (tail->next) tail = tail->next;
    tail->next = expr_list_single(expr);
    return list;
}

static TypeKind type_from_string(const char *name) {
    if (!name) return T_UNKNOWN;
    if (strcmp(name, "int") == 0) return T_INT;
    if (strcmp(name, "float") == 0) return T_FLOAT;
    if (strcmp(name, "double") == 0) return T_DOUBLE;
    if (strcmp(name, "long int") == 0) return T_LONG;
    if (strcmp(name, "char") == 0) return T_CHAR;
    if (strcmp(name, "bool") == 0) return T_BOOL;
    if (strcmp(name, "void") == 0) return T_VOID;
    return T_UNKNOWN;
}

static Param *param_new(const char *type_name, char *name, int line) {
    Param *param = calloc(1, sizeof(*param));
    if (!param) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    param->type = type_from_string(type_name);
    param->name = name;
    param->line = line;
    return param;
}

static Param *param_append(Param *list, Param *node) {
    if (!list) return node;
    Param *tail = list;
    while (tail->next) tail = tail->next;
    tail->next = node;
    return list;
}

static Branch *branch_new(Expr *cond, Stmt *body, int line) {
    Branch *branch = calloc(1, sizeof(*branch));
    if (!branch) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    branch->cond = cond;
    branch->body = body;
    branch->line = line;
    return branch;
}

static Stmt *stmt_new(StmtKind kind, int line) {
    Stmt *stmt = calloc(1, sizeof(*stmt));
    if (!stmt) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    stmt->kind = kind;
    stmt->line = line;
    return stmt;
}

static Stmt *stmt_append(Stmt *list, Stmt *node) {
    if (!list) return node;
    Stmt *tail = list;
    while (tail->next) tail = tail->next;
    tail->next = node;
    return list;
}

static Stmt *make_decl_stmt(const char *type_name, char *name, Expr *init, ExprList *array_init, int line) {
    Stmt *stmt = stmt_new(STMT_DECL, line);
    stmt->u.decl.type = type_from_string(type_name);
    stmt->u.decl.name = name;
    stmt->u.decl.init = init;
    stmt->u.decl.is_array = 0;
    stmt->u.decl.array_size = 0;
    stmt->u.decl.array_init = array_init;
    return stmt;
}

static Stmt *make_assign_stmt(char *name, Expr *value, int line) {
    Stmt *stmt = stmt_new(STMT_ASSIGN, line);
    stmt->u.assign.name = name;
    stmt->u.assign.value = value;
    return stmt;
}

static Stmt *make_index_assign_stmt(char *name, Expr *index, Expr *value, int line) {
    Stmt *stmt = stmt_new(STMT_INDEX_ASSIGN, line);
    stmt->u.index_assign.name = name;
    stmt->u.index_assign.index = index;
    stmt->u.index_assign.value = value;
    return stmt;
}

static Stmt *make_return_stmt(Expr *expr, int line) {
    Stmt *stmt = stmt_new(STMT_RETURN, line);
    stmt->u.ret.expr = expr;
    return stmt;
}

static Stmt *make_print_stmt(ExprList *args, int line) {
    Stmt *stmt = stmt_new(STMT_PRINT, line);
    stmt->u.print.args = args;
    return stmt;
}

static Stmt *make_expr_stmt(Expr *expr, int line) {
    Stmt *stmt = stmt_new(STMT_EXPR, line);
    stmt->u.expr_stmt.expr = expr;
    return stmt;
}

static Stmt *make_block_stmt(Stmt *stmts, int line) {
    Stmt *stmt = stmt_new(STMT_BLOCK, line);
    stmt->u.block.stmts = stmts;
    return stmt;
}

static Stmt *make_if_stmt(Expr *cond, Stmt *then_branch, Branch *elifs, Stmt *else_branch, int line) {
    Stmt *stmt = stmt_new(STMT_IF, line);
    stmt->u.if_stmt.cond = cond;
    stmt->u.if_stmt.then_branch = then_branch;
    stmt->u.if_stmt.elifs = elifs;
    stmt->u.if_stmt.else_branch = else_branch;
    return stmt;
}

static Stmt *make_while_stmt(Expr *cond, Stmt *body, int line) {
    Stmt *stmt = stmt_new(STMT_WHILE, line);
    stmt->u.while_stmt.cond = cond;
    stmt->u.while_stmt.body = body;
    return stmt;
}

static Stmt *make_for_stmt(Expr *init, Expr *cond, Expr *post, Stmt *body, int line) {
    Stmt *stmt = stmt_new(STMT_FOR, line);
    stmt->u.for_stmt.init = init;
    stmt->u.for_stmt.cond = cond;
    stmt->u.for_stmt.post = post;
    stmt->u.for_stmt.body = body;
    return stmt;
}

static Stmt *make_break_stmt(int line) {
    return stmt_new(STMT_BREAK, line);
}

static Stmt *make_continue_stmt(int line) {
    return stmt_new(STMT_CONTINUE, line);
}

static Function *function_new(char *name, const char *return_type_name, Param *params, Stmt *body, int line, int is_main) {
    Function *fn = calloc(1, sizeof(*fn));
    if (!fn) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    fn->name = name;
    fn->return_type = type_from_string(return_type_name);
    fn->params = params;
    fn->body = body;
    fn->line = line;
    fn->is_main = is_main;
    return fn;
}

static int includes_contains(const char *header) {
    for (Include *it = g_includes; it; it = it->next) {
        if (strcmp(it->header, header) == 0) {
            return 1;
        }
    }
    return 0;
}

static void add_include(char *header, int line) {
    (void)line;
    if (includes_contains(header)) {
        free(header);
        return;
    }
    Include *node = calloc(1, sizeof(*node));
    if (!node) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    node->header = header;
    node->line = line;
    if (!g_includes) {
        g_includes = g_includes_tail = node;
    } else {
        g_includes_tail->next = node;
        g_includes_tail = node;
    }
}

static void add_define(char *name, Expr *value, int line) {
    Define *node = calloc(1, sizeof(*node));
    if (!node) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    node->name = name;
    node->value = value;
    node->line = line;
    if (!g_defines) {
        g_defines = g_defines_tail = node;
    } else {
        g_defines_tail->next = node;
        g_defines_tail = node;
    }
}

static void add_function(Function *fn) {
    if (!g_functions) {
        g_functions = g_functions_tail = fn;
    } else {
        g_functions_tail->next = fn;
        g_functions_tail = fn;
    }
}

static void set_main(Function *fn) {
    g_main_fn = fn;
}

static Scope *push_scope(void) {
    Scope *scope = calloc(1, sizeof(*scope));
    if (!scope) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    scope->parent = scope_stack;
    scope_stack = scope;
    return scope;
}

static void pop_scope(void) {
    if (!scope_stack) return;
    Scope *parent = scope_stack->parent;
    Symbol *sym = scope_stack->symbols;
    while (sym) {
        Symbol *next = sym->next;
        free(sym);
        sym = next;
    }
    free(scope_stack);
    scope_stack = parent;
}

static Symbol *scope_lookup(Scope *scope, const char *name) {
    for (Symbol *sym = scope ? scope->symbols : NULL; sym; sym = sym->next) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
    }
    return NULL;
}

static Symbol *lookup_symbol(const char *name) {
    for (Scope *scope = scope_stack; scope; scope = scope->parent) {
        Symbol *sym = scope_lookup(scope, name);
        if (sym) return sym;
    }
    return NULL;
}

static Symbol *scope_add_symbol(const char *name, TypeKind type, int line) {
    if (!scope_stack) {
        push_scope();
    }
    if (scope_lookup(scope_stack, name)) {
        semantic_error(line, "duplicate symbol '%s'", name);
        return NULL;
    }
    Symbol *sym = calloc(1, sizeof(*sym));
    if (!sym) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    sym->name = strdup(name);
    sym->type = type;
    sym->is_array = 0;
    sym->array_size = 0;
    sym->next = scope_stack->symbols;
    scope_stack->symbols = sym;
    return sym;
}

static Function *find_function(const char *name) {
    if (g_main_fn && strcmp(g_main_fn->name, name) == 0) {
        return g_main_fn;
    }
    for (Function *fn = g_functions; fn; fn = fn->next) {
        if (strcmp(fn->name, name) == 0) {
            return fn;
        }
    }
    return NULL;
}

static void add_function_symbol(const Function *fn) {
    if (!scope_stack) {
        push_scope();
    }
    if (scope_lookup(scope_stack, fn->name)) {
        semantic_error(fn->line, "duplicate function '%s'", fn->name);
        return;
    }
    Symbol *sym = calloc(1, sizeof(*sym));
    if (!sym) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    sym->name = strdup(fn->name);
    sym->is_function = 1;
    sym->return_type = fn->return_type;
    sym->params = fn->params;
    sym->is_array = 0;
    sym->array_size = 0;
    sym->next = scope_stack->symbols;
    scope_stack->symbols = sym;
}

static int count_params(Param *params) {
    int count = 0;
    for (Param *p = params; p; p = p->next) count++;
    return count;
}

static int count_args(ExprList *args) {
    int count = 0;
    for (ExprList *e = args; e; e = e->next) count++;
    return count;
}

static TypeKind infer_expr(Expr *expr) {
    if (!expr) return T_UNKNOWN;
    if (expr->inferred != T_UNKNOWN) return expr->inferred;

    switch (expr->kind) {
        case EXPR_IDENT: {
            Symbol *sym = lookup_symbol(expr->text);
            if (!sym) {
                semantic_error(expr->line, "undeclared identifier '%s'", expr->text);
                expr->inferred = T_ERROR;
            } else {
                expr->is_array = sym->is_array;
                expr->array_size = sym->array_size;
                if (sym->is_array) {
                    semantic_error(expr->line, "array '%s' must be indexed before use", expr->text);
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = sym->type;
                }
            }
            break;
        }
        case EXPR_INDEX: {
            Symbol *sym = lookup_symbol(expr->text);
            if (!sym) {
                semantic_error(expr->line, "undeclared array '%s'", expr->text);
                expr->inferred = T_ERROR;
                break;
            }
            if (!sym->is_array) {
                semantic_error(expr->line, "'%s' is not an array", expr->text);
                expr->inferred = T_ERROR;
                break;
            }
            TypeKind idx_type = infer_expr(expr->index);
            if (!is_integral(idx_type)) {
                semantic_error(expr->line, "array index for '%s' must be an integer", expr->text);
            }
            expr->inferred = sym->type;
            break;
        }
        case EXPR_NUMBER:
            expr->inferred = strchr(expr->text, '.') ? T_DOUBLE : T_INT;
            break;
        case EXPR_STRING:
            expr->inferred = T_STRING;
            break;
        case EXPR_CALL: {
            if (strcmp(expr->text, "binary_search") == 0) {
                int argc = count_args(expr->args);
                if (argc != 2) {
                    semantic_error(expr->line, "binary_search expects 2 arguments: array and target value");
                    expr->inferred = T_ERROR;
                    break;
                }
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                if (!first || !second) {
                    expr->inferred = T_ERROR;
                    break;
                }
                Expr *array_expr = first->expr;
                Expr *target_expr = second->expr;
                if (!array_expr || array_expr->kind != EXPR_IDENT) {
                    semantic_error(expr->line, "binary_search first argument must be an array name");
                    expr->inferred = T_ERROR;
                    break;
                }
                Symbol *arr_sym = lookup_symbol(array_expr->text);
                if (!arr_sym) {
                    semantic_error(expr->line, "undeclared array '%s'", array_expr->text);
                    expr->inferred = T_ERROR;
                    break;
                }
                if (!arr_sym->is_array) {
                    semantic_error(expr->line, "binary_search expects an array as first argument, got '%s'", array_expr->text);
                    expr->inferred = T_ERROR;
                    break;
                }
                expr->array_size = arr_sym->array_size;
                if (arr_sym->type != T_INT) {
                    semantic_error(expr->line, "binary_search currently supports only int arrays");
                }
                TypeKind target_type = infer_expr(target_expr);
                if (!is_numeric(target_type)) {
                    semantic_error(expr->line, "binary_search target must be numeric");
                }
                expr->inferred = T_INT;
                break;
            }
            Function *fn = find_function(expr->text);
            if (!fn) {
                semantic_error(expr->line, "call to undefined function '%s'", expr->text);
                expr->inferred = T_ERROR;
                break;
            }
            int expected = count_params(fn->params);
            int actual = count_args(expr->args);
            if (expected != actual) {
                semantic_error(expr->line, "function '%s' expects %d arguments, got %d", expr->text, expected, actual);
            }
            Param *param = fn->params;
            ExprList *arg = expr->args;
            while (param && arg) {
                TypeKind arg_type = infer_expr(arg->expr);
                if (!type_compatible(param->type, arg_type)) {
                    semantic_error(arg->expr ? arg->expr->line : expr->line,
                                   "argument type mismatch for '%s': expected %s, got %s",
                                   param->name,
                                   type_name(param->type),
                                   type_name(arg_type));
                }
                param = param->next;
                arg = arg->next;
            }
            expr->inferred = fn->return_type;
            break;
        }
        case EXPR_BINARY: {
            TypeKind left = infer_expr(expr->left);
            TypeKind right = infer_expr(expr->right);
            if (!strcmp(expr->op, "+") || !strcmp(expr->op, "-") || !strcmp(expr->op, "*") || !strcmp(expr->op, "/")) {
                if (!is_numeric(left) || !is_numeric(right)) {
                    semantic_error(expr->line, "arithmetic operator '%s' requires numeric operands", expr->op);
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = numeric_promote(left, right);
                }
            } else if (!strcmp(expr->op, "%")) {
                if (!is_integral(left) || !is_integral(right)) {
                    semantic_error(expr->line, "operator '%%' requires integral operands");
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = T_INT;
                }
            } else if (!strcmp(expr->op, "<") || !strcmp(expr->op, ">") || !strcmp(expr->op, "<=") || !strcmp(expr->op, ">=") || !strcmp(expr->op, "==") || !strcmp(expr->op, "!=")) {
                if (!type_compatible(left, right) || !type_compatible(right, left)) {
                    semantic_error(expr->line, "comparison operator '%s' requires compatible operands", expr->op);
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = T_BOOL;
                }
            } else if (!strcmp(expr->op, "&&") || !strcmp(expr->op, "||")) {
                if (!is_bool_like(left) || !is_bool_like(right)) {
                    semantic_error(expr->line, "logical operator '%s' requires boolean-like operands", expr->op);
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = T_BOOL;
                }
            } else {
                expr->inferred = T_ERROR;
            }
            break;
        }
        case EXPR_UNARY: {
            TypeKind inner = infer_expr(expr->left);
            if (!strcmp(expr->op, "!")) {
                if (!is_bool_like(inner)) {
                    semantic_error(expr->line, "operator '!' requires a boolean-like operand");
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = T_BOOL;
                }
            } else if (!strcmp(expr->op, "-")) {
                if (!is_numeric(inner)) {
                    semantic_error(expr->line, "unary '-' requires a numeric operand");
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = inner;
                }
            } else {
                expr->inferred = T_ERROR;
            }
            break;
        }
    }

    return expr->inferred;
}

static void analyze_stmt_list(Stmt *stmt) {
    for (Stmt *it = stmt; it; it = it->next) {
        analyze_stmt(it);
    }
}

static void analyze_stmt(Stmt *stmt) {
    if (!stmt) return;

    switch (stmt->kind) {
        case STMT_DECL: {
            if (stmt->u.decl.type == T_VOID) {
                semantic_error(stmt->line, "variable '%s' cannot have type void", stmt->u.decl.name);
            }
            if (stmt->u.decl.is_array) {
                if (stmt->u.decl.array_size <= 0) {
                    semantic_error(stmt->line, "array '%s' must have a positive size", stmt->u.decl.name);
                }
                if (stmt->u.decl.array_init) {
                    int count = 0;
                    for (ExprList *it = stmt->u.decl.array_init; it; it = it->next) {
                        count++;
                        TypeKind elem_type = infer_expr(it->expr);
                        if (!type_compatible(stmt->u.decl.type, elem_type)) {
                            semantic_error(stmt->line,
                                           "array '%s' element type %s does not match %s",
                                           stmt->u.decl.name,
                                           type_name(elem_type),
                                           type_name(stmt->u.decl.type));
                        }
                    }
                    if (stmt->u.decl.array_size > 0 && count != stmt->u.decl.array_size) {
                        semantic_error(stmt->line,
                                       "array '%s' size is %d but initializer has %d elements",
                                       stmt->u.decl.name,
                                       stmt->u.decl.array_size,
                                       count);
                    }
                }
            }
            if (stmt->u.decl.init) {
                TypeKind init_type = infer_expr(stmt->u.decl.init);
                if (!type_compatible(stmt->u.decl.type, init_type)) {
                    semantic_error(stmt->line,
                                   "cannot initialize '%s' of type %s with %s",
                                   stmt->u.decl.name,
                                   type_name(stmt->u.decl.type),
                                   type_name(init_type));
                }
            }
            Symbol *sym = scope_add_symbol(stmt->u.decl.name, stmt->u.decl.type, stmt->line);
            if (sym) {
                sym->is_array = stmt->u.decl.is_array;
                sym->array_size = stmt->u.decl.array_size;
            }
            break;
        }
        case STMT_ASSIGN: {
            Symbol *sym = lookup_symbol(stmt->u.assign.name);
            if (!sym) {
                semantic_error(stmt->line, "assignment to undeclared variable '%s'", stmt->u.assign.name);
                break;
            }
            TypeKind value_type = infer_expr(stmt->u.assign.value);
            if (!type_compatible(sym->type, value_type)) {
                semantic_error(stmt->line,
                               "cannot assign %s to variable '%s' of type %s",
                               type_name(value_type),
                               stmt->u.assign.name,
                               type_name(sym->type));
            }
            break;
        }
        case STMT_INDEX_ASSIGN: {
            Symbol *sym = lookup_symbol(stmt->u.index_assign.name);
            if (!sym) {
                semantic_error(stmt->line, "assignment to undeclared array '%s'", stmt->u.index_assign.name);
                break;
            }
            if (!sym->is_array) {
                semantic_error(stmt->line, "'%s' is not an array", stmt->u.index_assign.name);
                break;
            }
            TypeKind idx_type = infer_expr(stmt->u.index_assign.index);
            if (!is_integral(idx_type)) {
                semantic_error(stmt->line, "array index for '%s' must be an integer", stmt->u.index_assign.name);
            }
            TypeKind value_type = infer_expr(stmt->u.index_assign.value);
            if (!type_compatible(sym->type, value_type)) {
                semantic_error(stmt->line,
                               "cannot assign %s to element of '%s' of type %s",
                               type_name(value_type),
                               stmt->u.index_assign.name,
                               type_name(sym->type));
            }
            break;
        }
        case STMT_RETURN: {
            if (!current_function) {
                semantic_error(stmt->line, "return statement outside of function");
                break;
            }
            TypeKind value_type = infer_expr(stmt->u.ret.expr);
            if (!type_compatible(current_function->return_type, value_type)) {
                semantic_error(stmt->line,
                               "return type mismatch in '%s': expected %s, got %s",
                               current_function->name,
                               type_name(current_function->return_type),
                               type_name(value_type));
            }
            break;
        }
        case STMT_PRINT: {
            for (ExprList *arg = stmt->u.print.args; arg; arg = arg->next) {
                infer_expr(arg->expr);
            }
            break;
        }
        case STMT_EXPR: {
            infer_expr(stmt->u.expr_stmt.expr);
            break;
        }
        case STMT_BLOCK: {
            push_scope();
            analyze_stmt_list(stmt->u.block.stmts);
            pop_scope();
            break;
        }
        case STMT_IF: {
            TypeKind cond_type = infer_expr(stmt->u.if_stmt.cond);
            if (!is_bool_like(cond_type)) {
                semantic_error(stmt->line, "if condition must be boolean-like");
            }
            push_scope();
            analyze_stmt_list(stmt->u.if_stmt.then_branch);
            pop_scope();
            for (Branch *br = stmt->u.if_stmt.elifs; br; br = br->next) {
                TypeKind branch_cond = infer_expr(br->cond);
                if (!is_bool_like(branch_cond)) {
                    semantic_error(br->line, "elif condition must be boolean-like");
                }
                push_scope();
                analyze_stmt_list(br->body);
                pop_scope();
            }
            if (stmt->u.if_stmt.else_branch) {
                push_scope();
                analyze_stmt_list(stmt->u.if_stmt.else_branch);
                pop_scope();
            }
            break;
        }
        case STMT_WHILE: {
            TypeKind cond_type = infer_expr(stmt->u.while_stmt.cond);
            if (!is_bool_like(cond_type)) {
                semantic_error(stmt->line, "while condition must be boolean-like");
            }
            push_scope();
            analyze_stmt_list(stmt->u.while_stmt.body);
            pop_scope();
            break;
        }
        case STMT_FOR: {
            if (stmt->u.for_stmt.init) infer_expr(stmt->u.for_stmt.init);
            if (stmt->u.for_stmt.cond) {
                TypeKind cond_type = infer_expr(stmt->u.for_stmt.cond);
                if (!is_bool_like(cond_type)) {
                    semantic_error(stmt->line, "for condition must be boolean-like");
                }
            }
            if (stmt->u.for_stmt.post) infer_expr(stmt->u.for_stmt.post);
            push_scope();
            analyze_stmt_list(stmt->u.for_stmt.body);
            pop_scope();
            break;
        }
        case STMT_BREAK:
        case STMT_CONTINUE:
            break;
    }
}

static void analyze_function(Function *fn) {
    current_function = fn;
    push_scope();

    for (Param *p = fn->params; p; p = p->next) {
        if (scope_lookup(scope_stack, p->name)) {
            semantic_error(p->line, "duplicate parameter '%s' in function '%s'", p->name, fn->name);
            continue;
        }
        scope_add_symbol(p->name, p->type, p->line);
    }

    analyze_stmt_list(fn->body);
    pop_scope();
    current_function = NULL;
}

static void analyze_program(void) {
    push_scope();

    for (Function *fn = g_functions; fn; fn = fn->next) {
        add_function_symbol(fn);
    }
    if (g_main_fn) {
        add_function_symbol(g_main_fn);
    }

    if (g_main_fn && g_main_fn->return_type != T_INT) {
        semantic_error(g_main_fn->line, "main function must return int");
    }

    for (Function *fn = g_functions; fn; fn = fn->next) {
        analyze_function(fn);
    }
    if (g_main_fn) {
        analyze_function(g_main_fn);
    }

    pop_scope();
}

static void emit_indent(FILE *f) {
    for (int i = 0; i < indent_level; i++) {
        fputs("    ", f);
    }
}

static void emit_expr(FILE *f, Expr *expr) {
    if (!expr) return;

    switch (expr->kind) {
        case EXPR_IDENT:
        case EXPR_NUMBER:
        case EXPR_STRING:
            fputs(expr->text, f);
            break;
        case EXPR_CALL: {
            if (strcmp(expr->text, "binary_search") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                fprintf(f, "binary_search(");
                emit_expr(f, first ? first->expr : NULL);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr(f, second ? second->expr : NULL);
                fputc(')', f);
                break;
            }
            fprintf(f, "%s(", expr->text);
            for (ExprList *arg = expr->args; arg; arg = arg->next) {
                emit_expr(f, arg->expr);
                if (arg->next) fputs(", ", f);
            }
            fputc(')', f);
            break;
        }
        case EXPR_INDEX:
            fprintf(f, "%s[", expr->text);
            emit_expr(f, expr->index);
            fputc(']', f);
            break;
        case EXPR_BINARY:
            fputc('(', f);
            emit_expr(f, expr->left);
            fprintf(f, " %s ", expr->op);
            emit_expr(f, expr->right);
            fputc(')', f);
            break;
        case EXPR_UNARY:
            fprintf(f, "%s", expr->op);
            emit_expr(f, expr->left);
            break;
    }
}

static void emit_stmt_list(FILE *f, Stmt *stmt) {
    for (Stmt *it = stmt; it; it = it->next) {
        emit_stmt(f, it);
    }
}

static void emit_stmt(FILE *f, Stmt *stmt) {
    if (!stmt) return;

    switch (stmt->kind) {
        case STMT_DECL:
            emit_indent(f);
            if (stmt->u.decl.is_array) {
                fprintf(f, "%s %s[%d]", type_name(stmt->u.decl.type), stmt->u.decl.name, stmt->u.decl.array_size);
                if (stmt->u.decl.array_init) {
                    fputs(" = {", f);
                    for (ExprList *it = stmt->u.decl.array_init; it; it = it->next) {
                        emit_expr(f, it->expr);
                        if (it->next) fputs(", ", f);
                    }
                    fputs("}", f);
                }
            } else {
                fprintf(f, "%s %s", type_name(stmt->u.decl.type), stmt->u.decl.name);
                if (stmt->u.decl.init) {
                    fputs(" = ", f);
                    emit_expr(f, stmt->u.decl.init);
                }
            }
            fputs(";\n", f);
            break;
        case STMT_ASSIGN:
            emit_indent(f);
            fprintf(f, "%s = ", stmt->u.assign.name);
            emit_expr(f, stmt->u.assign.value);
            fputs(";\n", f);
            break;
        case STMT_INDEX_ASSIGN:
            emit_indent(f);
            fprintf(f, "%s[", stmt->u.index_assign.name);
            emit_expr(f, stmt->u.index_assign.index);
            fputs("] = ", f);
            emit_expr(f, stmt->u.index_assign.value);
            fputs(";\n", f);
            break;
        case STMT_RETURN:
            emit_indent(f);
            fputs("return ", f);
            emit_expr(f, stmt->u.ret.expr);
            fputs(";\n", f);
            break;
        case STMT_PRINT:
            emit_indent(f);
            fputs("printf(", f);
            for (ExprList *arg = stmt->u.print.args; arg; arg = arg->next) {
                emit_expr(f, arg->expr);
                if (arg->next) fputs(", ", f);
            }
            fputs(");\n", f);
            break;
        case STMT_EXPR:
            emit_indent(f);
            emit_expr(f, stmt->u.expr_stmt.expr);
            fputs(";\n", f);
            break;
        case STMT_BLOCK:
            emit_indent(f);
            fputs("{\n", f);
            indent_level++;
            emit_stmt_list(f, stmt->u.block.stmts);
            indent_level--;
            emit_indent(f);
            fputs("}\n", f);
            break;
        case STMT_IF:
            emit_indent(f);
            fputs("if (", f);
            emit_expr(f, stmt->u.if_stmt.cond);
            fputs(") {\n", f);
            indent_level++;
            emit_stmt_list(f, stmt->u.if_stmt.then_branch);
            indent_level--;
            emit_indent(f);
            fputs("}\n", f);
            for (Branch *br = stmt->u.if_stmt.elifs; br; br = br->next) {
                emit_indent(f);
                fputs("else if (", f);
                emit_expr(f, br->cond);
                fputs(") {\n", f);
                indent_level++;
                emit_stmt_list(f, br->body);
                indent_level--;
                emit_indent(f);
                fputs("}\n", f);
            }
            if (stmt->u.if_stmt.else_branch) {
                emit_indent(f);
                fputs("else {\n", f);
                indent_level++;
                emit_stmt_list(f, stmt->u.if_stmt.else_branch);
                indent_level--;
                emit_indent(f);
                fputs("}\n", f);
            }
            break;
        case STMT_WHILE:
            emit_indent(f);
            fputs("while (", f);
            emit_expr(f, stmt->u.while_stmt.cond);
            fputs(") {\n", f);
            indent_level++;
            emit_stmt_list(f, stmt->u.while_stmt.body);
            indent_level--;
            emit_indent(f);
            fputs("}\n", f);
            break;
        case STMT_FOR:
            emit_indent(f);
            fputs("for (", f);
            if (stmt->u.for_stmt.init) emit_expr(f, stmt->u.for_stmt.init);
            fputs("; ", f);
            if (stmt->u.for_stmt.cond) emit_expr(f, stmt->u.for_stmt.cond);
            fputs("; ", f);
            if (stmt->u.for_stmt.post) emit_expr(f, stmt->u.for_stmt.post);
            fputs(") {\n", f);
            indent_level++;
            emit_stmt_list(f, stmt->u.for_stmt.body);
            indent_level--;
            emit_indent(f);
            fputs("}\n", f);
            break;
        case STMT_BREAK:
            emit_indent(f);
            fputs("break;\n", f);
            break;
        case STMT_CONTINUE:
            emit_indent(f);
            fputs("continue;\n", f);
            break;
    }
}

static void emit_params(FILE *f, Param *params) {
    for (Param *p = params; p; p = p->next) {
        fprintf(f, "%s %s", type_name(p->type), p->name);
        if (p->next) fputs(", ", f);
    }
}

static void emit_include(FILE *f, const char *header) {
    fprintf(f, "#include %s\n", header);
}

static void emit_binary_search_helper(FILE *f) {
    fputs("\nstatic int binary_search(int arr[], int n, int target) {\n", f);
    fputs("    int left = 0;\n", f);
    fputs("    int right = n - 1;\n", f);
    fputs("    while (left <= right) {\n", f);
    fputs("        int mid = left + (right - left) / 2;\n", f);
    fputs("        if (arr[mid] == target) return mid;\n", f);
    fputs("        if (arr[mid] < target) left = mid + 1;\n", f);
    fputs("        else right = mid - 1;\n", f);
    fputs("    }\n", f);
    fputs("    return -1;\n", f);
    fputs("}\n\n", f);
}

static void emit_program(const char *path) {
    outf = fopen(path, "w");
    if (!outf) {
        fprintf(stderr, "Error: cannot create %s\n", path);
        exit(1);
    }

    emit_include(outf, "<stdio.h>");
    emit_include(outf, "<math.h>");
    emit_include(outf, "<stdbool.h>");
    emit_binary_search_helper(outf);
    for (Include *inc = g_includes; inc; inc = inc->next) {
        if (strcmp(inc->header, "<stdio.h>") == 0 || strcmp(inc->header, "<math.h>") == 0 || strcmp(inc->header, "<stdbool.h>") == 0) {
            continue;
        }
        emit_include(outf, inc->header);
    }
    fputc('\n', outf);

    for (Define *def = g_defines; def; def = def->next) {
        fprintf(outf, "#define %s ", def->name);
        emit_expr(outf, def->value);
        fputc('\n', outf);
    }
    if (g_defines) fputc('\n', outf);

    for (Function *fn = g_functions; fn; fn = fn->next) {
        fprintf(outf, "%s %s(", type_name(fn->return_type), fn->name);
        emit_params(outf, fn->params);
        fputs(") {\n", outf);
        indent_level++;
        emit_stmt_list(outf, fn->body);
        indent_level--;
        fputs("}\n\n", outf);
    }

    if (g_main_fn) {
        fprintf(outf, "int main(");
        emit_params(outf, g_main_fn->params);
        fputs(") {\n", outf);
        indent_level++;
        emit_stmt_list(outf, g_main_fn->body);
        indent_level--;
        fputs("}\n", outf);
    }

    fclose(outf);
    printf("output.c generated successfully.\n");
    printf("Total lines processed: %d\n", line_no);
}

int main(int argc, char **argv) {
    const char *input_path = (argc > 1) ? argv[1] : "input.txt";
    const char *output_path = (argc > 2) ? argv[2] : "output.c";

    FILE *infile = fopen(input_path, "r");
    if (!infile) {
        fprintf(stderr, "Error: cannot open %s\n", input_path);
        return 1;
    }

    yyin = infile;
    yyparse();

    fclose(infile);

    analyze_program();

    if (semantic_error_count > 0 || syntax_error_count > 0) {
        return 1;
    }

    emit_program(output_path);
    return 0;
}
