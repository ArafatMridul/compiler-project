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
static char **g_source_lines = NULL;
static int g_source_line_count = 0;

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
    STMT_FOR,
    STMT_SWITCH
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
            int has_init_decl;
            TypeKind init_decl_type;
            char *init_decl_name;
            Expr *init_decl_value;
        } for_stmt;
        struct {
            Expr *expr;
            Branch *cases;
            Stmt *default_branch;
        } switch_stmt;
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
static void semantic_error_at(int line, const char *focus_token, const char *fmt, ...);
static void syntax_error(int line, const char *fmt, ...);
static void print_error_context(int line, const char *focus_token);
static void print_did_you_mean(const char *input, int include_symbols, int include_functions, int include_keywords, int include_types);
static void load_source_lines(const char *path);
static void free_source_lines(void);
static const char *source_line_at(int line);
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
static Stmt *make_switch_stmt(Expr *expr, Branch *cases, Stmt *default_branch, int line);
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
static void emit_expr_prec(FILE *f, Expr *expr, int parent_prec);
static void emit_stmt_list(FILE *f, Stmt *stmt);
static void emit_stmt(FILE *f, Stmt *stmt);
static void emit_expr(FILE *f, Expr *expr);
static void emit_params(FILE *f, Param *params);
static int includes_contains(const char *header);
static void emit_binary_search_helper(FILE *f);
static void emit_array_helpers(FILE *f);
static int stmt_list_needs_switch_break(Stmt *stmt);

#line 367 "compiler.tab.c"

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
  YYSYMBOL_CHOOSE = 27,                    /* CHOOSE  */
  YYSYMBOL_WHEN = 28,                      /* WHEN  */
  YYSYMBOL_BASE_CHOICE = 29,               /* BASE_CHOICE  */
  YYSYMBOL_ASSIGN = 30,                    /* ASSIGN  */
  YYSYMBOL_AND = 31,                       /* AND  */
  YYSYMBOL_OR = 32,                        /* OR  */
  YYSYMBOL_NOT = 33,                       /* NOT  */
  YYSYMBOL_LE = 34,                        /* LE  */
  YYSYMBOL_GE = 35,                        /* GE  */
  YYSYMBOL_EQ = 36,                        /* EQ  */
  YYSYMBOL_NE = 37,                        /* NE  */
  YYSYMBOL_38_ = 38,                       /* '<'  */
  YYSYMBOL_39_ = 39,                       /* '>'  */
  YYSYMBOL_40_ = 40,                       /* '+'  */
  YYSYMBOL_41_ = 41,                       /* '-'  */
  YYSYMBOL_42_ = 42,                       /* '*'  */
  YYSYMBOL_43_ = 43,                       /* '/'  */
  YYSYMBOL_44_ = 44,                       /* '%'  */
  YYSYMBOL_UMINUS = 45,                    /* UMINUS  */
  YYSYMBOL_46_ = 46,                       /* '('  */
  YYSYMBOL_47_ = 47,                       /* ')'  */
  YYSYMBOL_48_ = 48,                       /* ':'  */
  YYSYMBOL_49_ = 49,                       /* '{'  */
  YYSYMBOL_50_ = 50,                       /* '}'  */
  YYSYMBOL_51_ = 51,                       /* ';'  */
  YYSYMBOL_52_ = 52,                       /* '['  */
  YYSYMBOL_53_ = 53,                       /* ']'  */
  YYSYMBOL_54_ = 54,                       /* ','  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_program = 56,                   /* program  */
  YYSYMBOL_top_items = 57,                 /* top_items  */
  YYSYMBOL_extra_stmts_opt = 58,           /* extra_stmts_opt  */
  YYSYMBOL_extra_stmt_list = 59,           /* extra_stmt_list  */
  YYSYMBOL_top_item = 60,                  /* top_item  */
  YYSYMBOL_function_def = 61,              /* function_def  */
  YYSYMBOL_main_block = 62,                /* main_block  */
  YYSYMBOL_block = 63,                     /* block  */
  YYSYMBOL_stmt_list = 64,                 /* stmt_list  */
  YYSYMBOL_stmt = 65,                      /* stmt  */
  YYSYMBOL_if_stmt = 66,                   /* if_stmt  */
  YYSYMBOL_if_tail = 67,                   /* if_tail  */
  YYSYMBOL_switch_stmt = 68,               /* switch_stmt  */
  YYSYMBOL_switch_tail = 69,               /* switch_tail  */
  YYSYMBOL_while_stmt = 70,                /* while_stmt  */
  YYSYMBOL_for_stmt = 71,                  /* for_stmt  */
  YYSYMBOL_param_list_opt = 72,            /* param_list_opt  */
  YYSYMBOL_param_list = 73,                /* param_list  */
  YYSYMBOL_param = 74,                     /* param  */
  YYSYMBOL_arg_list_opt = 75,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 76,                  /* arg_list  */
  YYSYMBOL_opt_expr = 77,                  /* opt_expr  */
  YYSYMBOL_opt_init = 78,                  /* opt_init  */
  YYSYMBOL_expr = 79,                      /* expr  */
  YYSYMBOL_type = 80                       /* type  */
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
#define YYLAST   585

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  90
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  203

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
       2,     2,     2,     2,     2,     2,     2,    44,     2,     2,
      46,    47,    42,    40,    54,    41,     2,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    51,
      38,     2,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    50,     2,     2,     2,     2,
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
      35,    36,    37,    45
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   331,   331,   343,   344,   349,   352,   359,   363,   370,
     374,   378,   383,   389,   397,   405,   409,   417,   422,   428,
     432,   438,   444,   450,   454,   458,   462,   466,   470,   474,
     478,   479,   480,   481,   482,   486,   490,   498,   503,   512,
     522,   536,   550,   559,   569,   583,   597,   604,   608,   621,
     624,   631,   635,   642,   650,   653,   660,   664,   672,   675,
     683,   686,   693,   697,   701,   706,   710,   714,   718,   722,
     726,   730,   734,   738,   742,   746,   750,   754,   758,   762,
     766,   770,   774,   778,   785,   786,   787,   788,   789,   790,
     791
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
  "WHILE_KW", "BREAK_KW", "CONTINUE_KW", "CHOOSE", "WHEN", "BASE_CHOICE",
  "ASSIGN", "AND", "OR", "NOT", "LE", "GE", "EQ", "NE", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS", "'('", "')'", "':'", "'{'",
  "'}'", "';'", "'['", "']'", "','", "$accept", "program", "top_items",
  "extra_stmts_opt", "extra_stmt_list", "top_item", "function_def",
  "main_block", "block", "stmt_list", "stmt", "if_stmt", "if_tail",
  "switch_stmt", "switch_tail", "while_stmt", "for_stmt", "param_list_opt",
  "param_list", "param", "arg_list_opt", "arg_list", "opt_expr",
  "opt_init", "expr", "type", YY_NULLPTR
  };
  return yy_sname[yysymbol];
}
#endif

#define YYPACT_NINF (-140)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-7)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -140,    11,   558,  -140,   -29,    30,    45,     3,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,   150,    51,   174,
    -140,    71,     4,     7,     0,  -140,  -140,    71,    10,    71,
      31,    71,    29,    34,    52,    71,    71,    71,  -140,  -140,
    -140,   202,  -140,  -140,  -140,  -140,  -140,  -140,   353,    97,
      55,    58,    53,  -140,    99,   -23,   502,    57,  -140,    78,
      71,    71,    71,   371,    71,   286,   300,   443,  -140,  -140,
      71,  -140,  -140,   474,   251,  -140,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,  -140,
     -21,   174,    61,   174,  -140,    71,    71,  -140,    71,    60,
     389,    66,    62,   502,   313,  -140,    67,    57,     1,    64,
     502,   115,  -140,   488,  -140,    43,  -140,  -140,   541,   516,
      -2,    -2,    48,    48,    -2,    -2,   -16,   -16,  -140,  -140,
    -140,   116,    68,    74,   174,  -140,   502,   333,   502,  -140,
    -140,  -140,    71,    92,    72,     1,    71,    57,  -140,    71,
      96,    79,  -140,    77,  -140,    57,   101,  -140,   502,    71,
    -140,  -140,   443,  -140,    81,    71,     5,   -14,  -140,    95,
     407,     1,    71,   425,    71,    87,    86,    89,  -140,    57,
    -140,  -140,    91,    71,   459,    57,  -140,    71,  -140,    57,
      93,    57,  -140,    90,  -140,    71,     5,    94,   100,  -140,
    -140,    57,  -140
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,     0,    84,    85,
      86,    87,    88,    89,    90,     3,    11,     0,     0,    49,
       9,     0,     0,     0,    62,    65,    66,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,    35,
       2,     0,    34,     8,    30,    33,    31,    32,     0,     0,
       0,     0,    50,    51,     0,    62,    10,     0,    36,    60,
       0,    54,     0,     0,    54,     0,    58,     0,    28,    29,
       0,    82,    83,     0,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      60,    49,     0,     0,    53,     0,     0,    14,     0,     0,
       0,     0,    55,    56,     0,    25,     0,     0,    39,     0,
      59,     0,    46,     0,    68,     0,    15,    17,    80,    81,
      76,    77,    78,    79,    74,    75,    69,    70,    71,    72,
      73,     0,     0,     0,     0,    52,    64,     0,    61,    22,
      23,    67,     0,    63,     0,    39,     0,     0,    37,    58,
       0,     0,    16,     0,    19,     0,     0,    63,    57,     0,
      26,    38,     0,    41,     0,     0,    43,     0,    12,     0,
       0,    39,    58,     0,     0,     0,     0,     0,    20,     0,
      24,    40,     0,    58,     0,     0,    42,    54,    13,     0,
       0,     0,    45,     0,    47,    58,    43,     0,     0,    44,
      21,     0,    48
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,   -52,  -140,
     -39,  -140,  -139,  -140,   -50,  -140,  -140,    65,  -140,    59,
     -63,  -140,   -99,    69,   -17,     6
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    40,    41,    15,    16,    17,    42,    74,
      43,    44,   148,    45,   176,    46,    47,    51,    52,    53,
     101,   102,   109,    99,   110,    49
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,   106,    75,    59,    56,    97,   161,    95,    18,    98,
      63,     3,    65,   108,    67,   112,   177,    19,    71,    72,
      73,   146,   147,    61,    48,    54,    86,    87,    88,    96,
      60,   131,   181,   174,   175,   117,    20,   178,    84,    85,
      86,    87,    88,   100,   103,   104,    61,   103,    21,    22,
     164,    57,    62,   113,    50,   145,    64,    48,    58,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   111,   182,    55,    25,    26,    66,   136,   137,
      68,   138,    78,    79,   190,    69,    82,    83,    84,    85,
      86,    87,    88,   152,    58,   163,   198,    54,    70,    54,
      90,    91,    94,   168,    35,    92,    38,    93,    98,   134,
     171,   139,    36,   141,   144,   149,   142,    37,   150,   154,
     153,   155,   159,   160,   193,   158,   165,   188,   166,   162,
     167,   169,   172,   192,   179,   185,   186,   194,   189,   196,
     156,   187,   170,   197,   195,   200,   199,   201,   173,   202,
      -5,    23,   135,    24,    25,    26,   133,   184,     0,   132,
       8,     9,    10,    11,    12,    13,    14,    27,    28,    29,
     103,     0,     0,    30,    31,    32,    33,    34,     0,     0,
       0,     0,     0,    35,     8,     9,    10,    11,    12,    13,
      14,    36,     0,     0,     0,     0,    37,     0,     0,    38,
       0,    39,    -6,    23,     0,    24,    25,    26,     0,     0,
       0,     0,     8,     9,    10,    11,    12,    13,    14,    27,
      28,    29,     0,     0,     0,    30,    31,    32,    33,    34,
       0,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,    37,     0,
       0,    38,   115,    39,    24,    25,    26,     0,     0,     0,
       0,     8,     9,    10,    11,    12,    13,    14,    27,    28,
      29,     0,     0,     0,    30,    31,    32,    33,    34,     0,
       0,     0,     0,     0,    35,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,     0,     0,    37,     0,     0,
      38,   116,    39,    55,    25,    26,     0,     0,   107,     0,
       8,     9,    10,    11,    12,    13,    14,    76,    77,     0,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,     0,     0,    35,     0,    38,     0,     0,     0,     0,
       0,    36,     0,     0,    76,    77,    37,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,     0,     0,
       0,     0,     0,     0,    76,    77,   143,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,     0,     0,
       0,     0,     0,     0,    76,    77,   157,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,     0,     0,
       0,     0,    76,    77,    89,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,     0,     0,     0,     0,
      76,    77,   105,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,     0,     0,     0,     0,    76,    77,
     140,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,     0,     0,     0,     0,    76,    77,   180,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
       0,     0,     0,     0,    76,    77,   183,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,     0,     0,
      76,    77,    38,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,     0,    76,    77,   191,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    76,
      77,   114,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    76,    77,   151,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    76,     0,     0,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,     4,     0,     0,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88
};

static const yytype_int16 yycheck[] =
{
      17,    64,    41,     3,    21,    57,   145,    30,     2,    30,
      27,     0,    29,    65,    31,    67,    30,    46,    35,    36,
      37,    20,    21,    46,    41,    19,    42,    43,    44,    52,
      30,    52,   171,    28,    29,    74,     6,    51,    40,    41,
      42,    43,    44,    60,    61,    62,    46,    64,     3,    46,
     149,    47,    52,    70,     3,   107,    46,    74,    51,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    66,   172,     3,     4,     5,    46,    95,    96,
      51,    98,    34,    35,   183,    51,    38,    39,    40,    41,
      42,    43,    44,    50,    51,   147,   195,    91,    46,    93,
       3,    46,     3,   155,    33,    47,    49,    54,    30,    48,
     162,    51,    41,    47,    47,    51,    54,    46,     3,    51,
       4,    47,    30,    51,   187,   142,    30,   179,    49,   146,
      53,    30,    51,   185,    39,    48,    50,   189,    47,   191,
     134,    52,   159,    53,    51,    51,   196,    47,   165,   201,
       0,     1,    93,     3,     4,     5,    91,   174,    -1,    90,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
     187,    -1,    -1,    23,    24,    25,    26,    27,    -1,    -1,
      -1,    -1,    -1,    33,    10,    11,    12,    13,    14,    15,
      16,    41,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,
      -1,    51,     0,     1,    -1,     3,     4,     5,    -1,    -1,
      -1,    -1,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    46,    -1,
      -1,    49,     1,    51,     3,     4,     5,    -1,    -1,    -1,
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    23,    24,    25,    26,    27,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    51,     3,     4,     5,    -1,    -1,    22,    -1,
      10,    11,    12,    13,    14,    15,    16,    31,    32,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    33,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    31,    32,    46,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    53,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    53,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,    31,    32,    51,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      31,    32,    51,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    31,    32,
      51,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    -1,    -1,    31,    32,    51,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,    31,    32,    51,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      31,    32,    49,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    31,    32,    48,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    31,
      32,    47,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    31,    32,    47,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    31,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,     3,    -1,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    56,    57,     0,     3,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    60,    61,    62,    80,    46,
       6,     3,    46,     1,     3,     4,     5,    17,    18,    19,
      23,    24,    25,    26,    27,    33,    41,    46,    49,    51,
      58,    59,    63,    65,    66,    68,    70,    71,    79,    80,
       3,    72,    73,    74,    80,     3,    79,    47,    51,     3,
      30,    46,    52,    79,    46,    79,    46,    79,    51,    51,
      46,    79,    79,    79,    64,    65,    31,    32,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    51,
       3,    46,    47,    54,     3,    30,    52,    63,    30,    78,
      79,    75,    76,    79,    79,    51,    75,    22,    63,    77,
      79,    80,    63,    79,    47,     1,    50,    65,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    52,    78,    72,    48,    74,    79,    79,    79,    51,
      51,    47,    54,    53,    47,    63,    20,    21,    67,    51,
       3,    47,    50,     4,    51,    47,    80,    53,    79,    30,
      51,    67,    79,    63,    77,    30,    49,    53,    63,    30,
      79,    63,    51,    79,    28,    29,    69,    30,    51,    39,
      51,    67,    77,    51,    79,    48,    50,    52,    63,    47,
      77,    48,    63,    75,    63,    51,    63,    53,    77,    69,
      51,    47,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    59,    59,    60,
      60,    60,    61,    61,    62,    63,    63,    64,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    66,    67,
      67,    67,    68,    69,    69,    69,    70,    71,    71,    72,
      72,    73,    73,    74,    75,    75,    76,    76,    77,    77,
      78,    78,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    80,    80,    80,    80,    80,    80,
      80
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     0,     0,     1,     2,     1,     2,
       3,     1,     6,     9,     4,     3,     4,     2,     0,     4,
       6,    10,     4,     4,     7,     3,     5,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     2,     4,     5,     0,
       4,     2,     7,     0,     5,     3,     3,     9,    12,     0,
       1,     1,     3,     2,     0,     1,     1,     3,     0,     1,
       0,     2,     1,     4,     3,     1,     1,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     1,     1,     1,     1,     1,     1,
       1
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
  case 2: /* program: top_items main_block extra_stmts_opt  */
#line 332 "compiler.y"
      {
          if (!g_main_fn) {
              syntax_error(line_no, "missing Start_From_Here() block");
          }
          if ((yyvsp[0].ptr)) {
              g_main_fn->body = stmt_append(g_main_fn->body, (Stmt *)(yyvsp[0].ptr));
          }
      }
#line 1867 "compiler.tab.c"
    break;

  case 5: /* extra_stmts_opt: %empty  */
#line 349 "compiler.y"
            {
                    (yyval.ptr) = NULL;
            }
#line 1875 "compiler.tab.c"
    break;

  case 6: /* extra_stmts_opt: extra_stmt_list  */
#line 353 "compiler.y"
            {
                    (yyval.ptr) = (yyvsp[0].ptr);
            }
#line 1883 "compiler.tab.c"
    break;

  case 7: /* extra_stmt_list: extra_stmt_list stmt  */
#line 360 "compiler.y"
            {
                    (yyval.ptr) = stmt_append((yyvsp[-1].ptr), (yyvsp[0].ptr));
            }
#line 1891 "compiler.tab.c"
    break;

  case 8: /* extra_stmt_list: stmt  */
#line 364 "compiler.y"
            {
                    (yyval.ptr) = (yyvsp[0].ptr);
            }
#line 1899 "compiler.tab.c"
    break;

  case 9: /* top_item: INCLUDE HEADER  */
#line 371 "compiler.y"
            {
                    add_include((yyvsp[0].str), line_no);
            }
#line 1907 "compiler.tab.c"
    break;

  case 10: /* top_item: DEFINE IDENT expr  */
#line 375 "compiler.y"
            {
                    add_define((yyvsp[-1].str), (yyvsp[0].ptr), line_no);
            }
#line 1915 "compiler.tab.c"
    break;

  case 12: /* function_def: type IDENT '(' param_list_opt ')' block  */
#line 384 "compiler.y"
            {
                    add_function(function_new((yyvsp[-4].str), (yyvsp[-5].str), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no, 0));
                    (yyval.ptr) = NULL;
            }
#line 1924 "compiler.tab.c"
    break;

  case 13: /* function_def: IDENT '(' param_list_opt ')' ':' type ASSIGN '>' block  */
#line 390 "compiler.y"
            {
              add_function(function_new((yyvsp[-8].str), (yyvsp[-3].str), (yyvsp[-6].ptr), (yyvsp[0].ptr), line_no, 0));
                    (yyval.ptr) = NULL;
            }
#line 1933 "compiler.tab.c"
    break;

  case 14: /* main_block: MAIN '(' ')' block  */
#line 398 "compiler.y"
      {
          set_main(function_new(strdup("main"), "int", NULL, (yyvsp[0].ptr), line_no, 1));
          (yyval.ptr) = NULL;
      }
#line 1942 "compiler.tab.c"
    break;

  case 15: /* block: '{' stmt_list '}'  */
#line 406 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[-1].ptr);
      }
#line 1950 "compiler.tab.c"
    break;

  case 16: /* block: '{' stmt_list error '}'  */
#line 410 "compiler.y"
            {
                    yyerrok;
                    (yyval.ptr) = (yyvsp[-2].ptr);
            }
#line 1959 "compiler.tab.c"
    break;

  case 17: /* stmt_list: stmt_list stmt  */
#line 418 "compiler.y"
      {
          (yyval.ptr) = stmt_append((yyvsp[-1].ptr), (yyvsp[0].ptr));
      }
#line 1967 "compiler.tab.c"
    break;

  case 18: /* stmt_list: %empty  */
#line 422 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 1975 "compiler.tab.c"
    break;

  case 19: /* stmt: type IDENT opt_init ';'  */
#line 429 "compiler.y"
      {
          (yyval.ptr) = make_decl_stmt((yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[-1].ptr), NULL, line_no);
      }
#line 1983 "compiler.tab.c"
    break;

  case 20: /* stmt: type IDENT '[' NUMBER ']' ';'  */
#line 433 "compiler.y"
            {
                    (yyval.ptr) = make_decl_stmt((yyvsp[-5].str), (yyvsp[-4].str), NULL, NULL, line_no);
                    ((Stmt *)(yyval.ptr))->u.decl.is_array = 1;
                    ((Stmt *)(yyval.ptr))->u.decl.array_size = atoi((yyvsp[-2].str));
            }
#line 1993 "compiler.tab.c"
    break;

  case 21: /* stmt: type IDENT '[' NUMBER ']' ASSIGN '[' arg_list_opt ']' ';'  */
#line 439 "compiler.y"
            {
                    (yyval.ptr) = make_decl_stmt((yyvsp[-9].str), (yyvsp[-8].str), NULL, (ExprList *)(yyvsp[-2].ptr), line_no);
                    ((Stmt *)(yyval.ptr))->u.decl.is_array = 1;
                    ((Stmt *)(yyval.ptr))->u.decl.array_size = atoi((yyvsp[-6].str));
            }
#line 2003 "compiler.tab.c"
    break;

  case 22: /* stmt: IDENT IDENT opt_init ';'  */
#line 445 "compiler.y"
            {
                    semantic_error_at(line_no, (yyvsp[-3].str), "unknown type '%s'", (yyvsp[-3].str));
                    print_did_you_mean((yyvsp[-3].str), 0, 0, 0, 1);
                    (yyval.ptr) = NULL;
            }
#line 2013 "compiler.tab.c"
    break;

  case 23: /* stmt: IDENT ASSIGN expr ';'  */
#line 451 "compiler.y"
      {
          (yyval.ptr) = make_assign_stmt((yyvsp[-3].str), (yyvsp[-1].ptr), line_no);
      }
#line 2021 "compiler.tab.c"
    break;

  case 24: /* stmt: IDENT '[' expr ']' ASSIGN expr ';'  */
#line 455 "compiler.y"
            {
                    (yyval.ptr) = make_index_assign_stmt((yyvsp[-6].str), (yyvsp[-4].ptr), (yyvsp[-1].ptr), line_no);
            }
#line 2029 "compiler.tab.c"
    break;

  case 25: /* stmt: RETURN expr ';'  */
#line 459 "compiler.y"
      {
          (yyval.ptr) = make_return_stmt((yyvsp[-1].ptr), line_no);
      }
#line 2037 "compiler.tab.c"
    break;

  case 26: /* stmt: PRINT '(' arg_list_opt ')' ';'  */
#line 463 "compiler.y"
      {
          (yyval.ptr) = make_print_stmt((yyvsp[-2].ptr), line_no);
      }
#line 2045 "compiler.tab.c"
    break;

  case 27: /* stmt: expr ';'  */
#line 467 "compiler.y"
      {
          (yyval.ptr) = make_expr_stmt((yyvsp[-1].ptr), line_no);
      }
#line 2053 "compiler.tab.c"
    break;

  case 28: /* stmt: BREAK_KW ';'  */
#line 471 "compiler.y"
      {
          (yyval.ptr) = make_break_stmt(line_no);
      }
#line 2061 "compiler.tab.c"
    break;

  case 29: /* stmt: CONTINUE_KW ';'  */
#line 475 "compiler.y"
      {
          (yyval.ptr) = make_continue_stmt(line_no);
      }
#line 2069 "compiler.tab.c"
    break;

  case 34: /* stmt: block  */
#line 483 "compiler.y"
      {
          (yyval.ptr) = make_block_stmt((yyvsp[0].ptr), line_no);
      }
#line 2077 "compiler.tab.c"
    break;

  case 35: /* stmt: ';'  */
#line 487 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 2085 "compiler.tab.c"
    break;

  case 36: /* stmt: error ';'  */
#line 491 "compiler.y"
            {
                    yyerrok;
                    (yyval.ptr) = NULL;
            }
#line 2094 "compiler.tab.c"
    break;

  case 37: /* if_stmt: IF expr block if_tail  */
#line 499 "compiler.y"
            {
                                        IfTail *tail = (IfTail *)(yyvsp[0].ptr);
                                        (yyval.ptr) = make_if_stmt((yyvsp[-2].ptr), (yyvsp[-1].ptr), tail->elifs, tail->else_branch, line_no);
            }
#line 2103 "compiler.tab.c"
    break;

  case 38: /* if_stmt: IF expr THEN block if_tail  */
#line 504 "compiler.y"
            {
                                        IfTail *tail = (IfTail *)(yyvsp[0].ptr);
                                        (yyval.ptr) = make_if_stmt((yyvsp[-3].ptr), (yyvsp[-1].ptr), tail->elifs, tail->else_branch, line_no);
            }
#line 2112 "compiler.tab.c"
    break;

  case 39: /* if_tail: %empty  */
#line 512 "compiler.y"
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
#line 2127 "compiler.tab.c"
    break;

  case 40: /* if_tail: ELIF expr block if_tail  */
#line 523 "compiler.y"
      {
          Branch *node = branch_new((yyvsp[-2].ptr), (yyvsp[-1].ptr), line_no);
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
#line 2145 "compiler.tab.c"
    break;

  case 41: /* if_tail: ELSE block  */
#line 537 "compiler.y"
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
#line 2160 "compiler.tab.c"
    break;

  case 42: /* switch_stmt: CHOOSE '(' expr ')' '{' switch_tail '}'  */
#line 551 "compiler.y"
            {
                    IfTail *tail = (IfTail *)(yyvsp[-1].ptr);
                    (yyval.ptr) = make_switch_stmt((yyvsp[-4].ptr), tail->elifs, tail->else_branch, line_no);
            }
#line 2169 "compiler.tab.c"
    break;

  case 43: /* switch_tail: %empty  */
#line 559 "compiler.y"
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
#line 2184 "compiler.tab.c"
    break;

  case 44: /* switch_tail: WHEN expr ':' block switch_tail  */
#line 570 "compiler.y"
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
#line 2202 "compiler.tab.c"
    break;

  case 45: /* switch_tail: BASE_CHOICE ':' block  */
#line 584 "compiler.y"
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
#line 2217 "compiler.tab.c"
    break;

  case 46: /* while_stmt: WHILE_KW expr block  */
#line 598 "compiler.y"
      {
          (yyval.ptr) = make_while_stmt((yyvsp[-1].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2225 "compiler.tab.c"
    break;

  case 47: /* for_stmt: FOR '(' opt_expr ';' opt_expr ';' opt_expr ')' block  */
#line 605 "compiler.y"
      {
          (yyval.ptr) = make_for_stmt((yyvsp[-6].ptr), (yyvsp[-4].ptr), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
            }
#line 2233 "compiler.tab.c"
    break;

  case 48: /* for_stmt: FOR '(' type IDENT ASSIGN expr ';' opt_expr ';' opt_expr ')' block  */
#line 609 "compiler.y"
            {
                Stmt *loop = make_for_stmt(NULL, (yyvsp[-4].ptr), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
                loop->u.for_stmt.has_init_decl = 1;
                loop->u.for_stmt.init_decl_type = type_from_string((yyvsp[-9].str));
                loop->u.for_stmt.init_decl_name = (yyvsp[-8].str);
                loop->u.for_stmt.init_decl_value = (yyvsp[-6].ptr);
                (yyval.ptr) = loop;
            }
#line 2246 "compiler.tab.c"
    break;

  case 49: /* param_list_opt: %empty  */
#line 621 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 2254 "compiler.tab.c"
    break;

  case 50: /* param_list_opt: param_list  */
#line 625 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2262 "compiler.tab.c"
    break;

  case 51: /* param_list: param  */
#line 632 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2270 "compiler.tab.c"
    break;

  case 52: /* param_list: param_list ',' param  */
#line 636 "compiler.y"
      {
          (yyval.ptr) = param_append((yyvsp[-2].ptr), (yyvsp[0].ptr));
      }
#line 2278 "compiler.tab.c"
    break;

  case 53: /* param: type IDENT  */
#line 643 "compiler.y"
      {
          (yyval.ptr) = param_new((yyvsp[-1].str), (yyvsp[0].str), line_no);
      }
#line 2286 "compiler.tab.c"
    break;

  case 54: /* arg_list_opt: %empty  */
#line 650 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 2294 "compiler.tab.c"
    break;

  case 55: /* arg_list_opt: arg_list  */
#line 654 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2302 "compiler.tab.c"
    break;

  case 56: /* arg_list: expr  */
#line 661 "compiler.y"
      {
          (yyval.ptr) = expr_list_single((yyvsp[0].ptr));
      }
#line 2310 "compiler.tab.c"
    break;

  case 57: /* arg_list: arg_list ',' expr  */
#line 665 "compiler.y"
      {
          (yyval.ptr) = expr_list_append((yyvsp[-2].ptr), (yyvsp[0].ptr));
      }
#line 2318 "compiler.tab.c"
    break;

  case 58: /* opt_expr: %empty  */
#line 672 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 2326 "compiler.tab.c"
    break;

  case 59: /* opt_expr: expr  */
#line 676 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2334 "compiler.tab.c"
    break;

  case 60: /* opt_init: %empty  */
#line 683 "compiler.y"
      {
          (yyval.ptr) = NULL;
      }
#line 2342 "compiler.tab.c"
    break;

  case 61: /* opt_init: ASSIGN expr  */
#line 687 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[0].ptr);
      }
#line 2350 "compiler.tab.c"
    break;

  case 62: /* expr: IDENT  */
#line 694 "compiler.y"
      {
          (yyval.ptr) = make_expr_ident((yyvsp[0].str), line_no);
      }
#line 2358 "compiler.tab.c"
    break;

  case 63: /* expr: IDENT '[' expr ']'  */
#line 698 "compiler.y"
            {
                    (yyval.ptr) = make_expr_index((yyvsp[-3].str), (yyvsp[-1].ptr), line_no);
            }
#line 2366 "compiler.tab.c"
    break;

  case 64: /* expr: IDENT ASSIGN expr  */
#line 702 "compiler.y"
      {
          Expr *lhs = make_expr_ident((yyvsp[-2].str), line_no);
          (yyval.ptr) = make_expr_binary(strdup("="), lhs, (yyvsp[0].ptr), line_no);
      }
#line 2375 "compiler.tab.c"
    break;

  case 65: /* expr: NUMBER  */
#line 707 "compiler.y"
      {
          (yyval.ptr) = make_expr_number((yyvsp[0].str), line_no);
      }
#line 2383 "compiler.tab.c"
    break;

  case 66: /* expr: STRING_LITERAL  */
#line 711 "compiler.y"
      {
          (yyval.ptr) = make_expr_string((yyvsp[0].str), line_no);
      }
#line 2391 "compiler.tab.c"
    break;

  case 67: /* expr: IDENT '(' arg_list_opt ')'  */
#line 715 "compiler.y"
      {
          (yyval.ptr) = make_expr_call((yyvsp[-3].str), (yyvsp[-1].ptr), line_no);
      }
#line 2399 "compiler.tab.c"
    break;

  case 68: /* expr: '(' expr ')'  */
#line 719 "compiler.y"
      {
          (yyval.ptr) = (yyvsp[-1].ptr);
      }
#line 2407 "compiler.tab.c"
    break;

  case 69: /* expr: expr '+' expr  */
#line 723 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("+"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2415 "compiler.tab.c"
    break;

  case 70: /* expr: expr '-' expr  */
#line 727 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("-"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2423 "compiler.tab.c"
    break;

  case 71: /* expr: expr '*' expr  */
#line 731 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("*"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2431 "compiler.tab.c"
    break;

  case 72: /* expr: expr '/' expr  */
#line 735 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("/"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2439 "compiler.tab.c"
    break;

  case 73: /* expr: expr '%' expr  */
#line 739 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("%"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2447 "compiler.tab.c"
    break;

  case 74: /* expr: expr '<' expr  */
#line 743 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("<"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2455 "compiler.tab.c"
    break;

  case 75: /* expr: expr '>' expr  */
#line 747 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup(">"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2463 "compiler.tab.c"
    break;

  case 76: /* expr: expr LE expr  */
#line 751 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("<="), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2471 "compiler.tab.c"
    break;

  case 77: /* expr: expr GE expr  */
#line 755 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup(">="), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2479 "compiler.tab.c"
    break;

  case 78: /* expr: expr EQ expr  */
#line 759 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("=="), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2487 "compiler.tab.c"
    break;

  case 79: /* expr: expr NE expr  */
#line 763 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("!="), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2495 "compiler.tab.c"
    break;

  case 80: /* expr: expr AND expr  */
#line 767 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("&&"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2503 "compiler.tab.c"
    break;

  case 81: /* expr: expr OR expr  */
#line 771 "compiler.y"
      {
          (yyval.ptr) = make_expr_binary(strdup("||"), (yyvsp[-2].ptr), (yyvsp[0].ptr), line_no);
      }
#line 2511 "compiler.tab.c"
    break;

  case 82: /* expr: NOT expr  */
#line 775 "compiler.y"
      {
          (yyval.ptr) = make_expr_unary(strdup("!"), (yyvsp[0].ptr), line_no);
      }
#line 2519 "compiler.tab.c"
    break;

  case 83: /* expr: '-' expr  */
#line 779 "compiler.y"
      {
          (yyval.ptr) = make_expr_unary(strdup("-"), (yyvsp[0].ptr), line_no);
      }
#line 2527 "compiler.tab.c"
    break;

  case 84: /* type: TYPE_INT  */
#line 785 "compiler.y"
                  { (yyval.str) = strdup("int"); }
#line 2533 "compiler.tab.c"
    break;

  case 85: /* type: TYPE_FLOAT  */
#line 786 "compiler.y"
                  { (yyval.str) = strdup("float"); }
#line 2539 "compiler.tab.c"
    break;

  case 86: /* type: TYPE_DOUBLE  */
#line 787 "compiler.y"
                  { (yyval.str) = strdup("double"); }
#line 2545 "compiler.tab.c"
    break;

  case 87: /* type: TYPE_LONG  */
#line 788 "compiler.y"
                  { (yyval.str) = strdup("long int"); }
#line 2551 "compiler.tab.c"
    break;

  case 88: /* type: TYPE_CHAR  */
#line 789 "compiler.y"
                  { (yyval.str) = strdup("char"); }
#line 2557 "compiler.tab.c"
    break;

  case 89: /* type: TYPE_BOOL  */
#line 790 "compiler.y"
                  { (yyval.str) = strdup("bool"); }
#line 2563 "compiler.tab.c"
    break;

  case 90: /* type: TYPE_VOID  */
#line 791 "compiler.y"
                  { (yyval.str) = strdup("void"); }
#line 2569 "compiler.tab.c"
    break;


#line 2573 "compiler.tab.c"

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

#line 794 "compiler.y"


static const char *k_language_keywords[] = {
    "Start_From_Here",
    "IF", "ELIF", "ELSE", "THEN",
    "FOR", "until_false", "snap", "next_iter",
    "give_back", "console.out",
    "#=>", "#denote",
    "BOTH", "EITHER", "NEGATE",
    "CHOOSE", "WHEN", "BASE_CHOICE"
};

static const char *k_language_types[] = {
    "num", "fnum", "dnum", "lonum", "ch", "bol", "empty",
    "int", "float", "double", "long", "char", "bool", "void"
};

static const char *k_builtin_functions[] = {
    "binary_search",
    "sort", "find", "map", "filter", "reduce",
    "raise_to", "square_root", "magnitude", "round_down", "round_up", "ln",
    "SIN", "COS", "TAN"
};

static int min3(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

static int edit_distance_ci(const char *a, const char *b, int max_dist) {
    if (!a || !b) return max_dist + 1;
    size_t n = strlen(a);
    size_t m = strlen(b);
    size_t diff = n > m ? n - m : m - n;
    if ((int)diff > max_dist) return max_dist + 1;

    int *prev = malloc((m + 1) * sizeof(int));
    int *curr = malloc((m + 1) * sizeof(int));
    if (!prev || !curr) {
        free(prev);
        free(curr);
        return max_dist + 1;
    }

    for (size_t j = 0; j <= m; j++) prev[j] = (int)j;

    for (size_t i = 1; i <= n; i++) {
        curr[0] = (int)i;
        int row_min = curr[0];
        for (size_t j = 1; j <= m; j++) {
            int cost = tolower((unsigned char)a[i - 1]) == tolower((unsigned char)b[j - 1]) ? 0 : 1;
            curr[j] = min3(prev[j] + 1, curr[j - 1] + 1, prev[j - 1] + cost);
            if (curr[j] < row_min) row_min = curr[j];
        }
        if (row_min > max_dist) {
            free(prev);
            free(curr);
            return max_dist + 1;
        }
        int *tmp = prev;
        prev = curr;
        curr = tmp;
    }

    int dist = prev[m];
    free(prev);
    free(curr);
    return dist;
}

static void consider_candidate(const char *input, const char *candidate, const char **best, int *best_dist) {
    if (!input || !candidate || !best || !best_dist) return;
    if (strcmp(input, candidate) == 0) return;
    int dist = edit_distance_ci(input, candidate, 3);
    if (dist < *best_dist) {
        *best = candidate;
        *best_dist = dist;
    }
}

static const char *source_line_at(int line) {
    if (line <= 0 || line > g_source_line_count || !g_source_lines) return NULL;
    return g_source_lines[line - 1];
}

static void print_error_context(int line, const char *focus_token) {
    const char *src = source_line_at(line);
    if ((!src || src[0] == '\0') && current_line_text[0] != '\0') {
        src = current_line_text;
    }
    if (!src || src[0] == '\0') return;

    fprintf(stderr, "  %s\n", src);
    fprintf(stderr, "  ");

    int col = 0;
    if (focus_token && focus_token[0] != '\0') {
        const char *pos = strstr(src, focus_token);
        if (pos) col = (int)(pos - src);
    }

    for (int i = 0; i < col; i++) {
        fputc(src[i] == '\t' ? '\t' : ' ', stderr);
    }
    fputc('^', stderr);

    if (focus_token && focus_token[0] != '\0') {
        size_t n = strlen(focus_token);
        for (size_t i = 1; i < n; i++) {
            fputc('~', stderr);
        }
    }
    fputc('\n', stderr);
}

static void print_did_you_mean(const char *input, int include_symbols, int include_functions, int include_keywords, int include_types) {
    const char *best = NULL;
    int best_dist = 4;
    if (!input || !input[0]) return;

    if (include_keywords) {
        size_t n = sizeof(k_language_keywords) / sizeof(k_language_keywords[0]);
        for (size_t i = 0; i < n; i++) {
            consider_candidate(input, k_language_keywords[i], &best, &best_dist);
        }
    }

    if (include_types) {
        size_t n = sizeof(k_language_types) / sizeof(k_language_types[0]);
        for (size_t i = 0; i < n; i++) {
            consider_candidate(input, k_language_types[i], &best, &best_dist);
        }
    }

    if (include_functions) {
        size_t n = sizeof(k_builtin_functions) / sizeof(k_builtin_functions[0]);
        for (size_t i = 0; i < n; i++) {
            consider_candidate(input, k_builtin_functions[i], &best, &best_dist);
        }
        for (Function *fn = g_functions; fn; fn = fn->next) {
            consider_candidate(input, fn->name, &best, &best_dist);
        }
        if (g_main_fn) {
            consider_candidate(input, g_main_fn->name, &best, &best_dist);
        }
    }

    if (include_symbols) {
        for (Scope *scope = scope_stack; scope; scope = scope->parent) {
            for (Symbol *sym = scope->symbols; sym; sym = sym->next) {
                consider_candidate(input, sym->name, &best, &best_dist);
            }
        }
    }

    if (best) {
        fprintf(stderr, "  hint: did you mean '%s'?\n", best);
    }
}

static void load_source_lines(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return;

    char buf[4096];
    while (fgets(buf, sizeof(buf), f)) {
        size_t len = strlen(buf);
        while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
            buf[--len] = '\0';
        }
        char **next = realloc(g_source_lines, (g_source_line_count + 1) * sizeof(*g_source_lines));
        if (!next) {
            fclose(f);
            return;
        }
        g_source_lines = next;
        g_source_lines[g_source_line_count] = strdup(buf);
        if (!g_source_lines[g_source_line_count]) {
            fclose(f);
            return;
        }
        g_source_line_count++;
    }

    fclose(f);
}

static void free_source_lines(void) {
    if (!g_source_lines) return;
    for (int i = 0; i < g_source_line_count; i++) {
        free(g_source_lines[i]);
    }
    free(g_source_lines);
    g_source_lines = NULL;
    g_source_line_count = 0;
}

static void syntax_error(int line, const char *fmt, ...) {
    va_list ap;
    syntax_error_count++;
    fprintf(stderr, "Syntax error on line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    print_error_context(line, (line == last_token_line) ? last_token_text : NULL);
}

static void semantic_error(int line, const char *fmt, ...) {
    va_list ap;
    fprintf(stderr, "Semantic error on line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    print_error_context(line, (line == last_token_line) ? last_token_text : NULL);
    semantic_error_count++;
}

static void semantic_error_at(int line, const char *focus_token, const char *fmt, ...) {
    va_list ap;
    fprintf(stderr, "Semantic error on line %d: ", line);
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    fputc('\n', stderr);
    print_error_context(line, focus_token);
    semantic_error_count++;
}

static void yyerror(const char *s) {
    syntax_error_count++;
    if (last_token_text[0] != '\0') {
        fprintf(stderr, "Syntax error on line %d near '%s': %s\n", last_token_line, last_token_text, s);
    } else {
        fprintf(stderr, "Syntax error on line %d: %s\n", line_no, s);
    }
    print_error_context(last_token_line > 0 ? last_token_line : line_no, last_token_text);
    if (isalpha((unsigned char)last_token_text[0]) || last_token_text[0] == '_') {
        print_did_you_mean(last_token_text, 1, 1, 1, 1);
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
    stmt->u.for_stmt.has_init_decl = 0;
    stmt->u.for_stmt.init_decl_type = T_UNKNOWN;
    stmt->u.for_stmt.init_decl_name = NULL;
    stmt->u.for_stmt.init_decl_value = NULL;
    return stmt;
}

static Stmt *make_switch_stmt(Expr *expr, Branch *cases, Stmt *default_branch, int line) {
    Stmt *stmt = stmt_new(STMT_SWITCH, line);
    stmt->u.switch_stmt.expr = expr;
    stmt->u.switch_stmt.cases = cases;
    stmt->u.switch_stmt.default_branch = default_branch;
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
                semantic_error_at(expr->line, expr->text, "undeclared identifier '%s'", expr->text);
                print_did_you_mean(expr->text, 1, 1, 1, 0);
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
                semantic_error_at(expr->line, expr->text, "undeclared array '%s'", expr->text);
                print_did_you_mean(expr->text, 1, 0, 0, 0);
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
                    semantic_error_at(expr->line, array_expr->text, "undeclared array '%s'", array_expr->text);
                    print_did_you_mean(array_expr->text, 1, 0, 0, 0);
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
            if (strcmp(expr->text, "sort") == 0 ||
                strcmp(expr->text, "find") == 0 ||
                strcmp(expr->text, "map") == 0 ||
                strcmp(expr->text, "filter") == 0 ||
                strcmp(expr->text, "reduce") == 0) {
                int argc = count_args(expr->args);
                ExprList *first = expr->args;
                Expr *array_expr = first ? first->expr : NULL;

                if (!array_expr || array_expr->kind != EXPR_IDENT) {
                    semantic_error(expr->line, "%s first argument must be an array name", expr->text);
                    expr->inferred = T_ERROR;
                    break;
                }

                Symbol *arr_sym = lookup_symbol(array_expr->text);
                if (!arr_sym) {
                    semantic_error_at(expr->line, array_expr->text, "undeclared array '%s'", array_expr->text);
                    print_did_you_mean(array_expr->text, 1, 0, 0, 0);
                    expr->inferred = T_ERROR;
                    break;
                }
                if (!arr_sym->is_array) {
                    semantic_error(expr->line, "%s expects an array as first argument, got '%s'", expr->text, array_expr->text);
                    expr->inferred = T_ERROR;
                    break;
                }
                if (arr_sym->type != T_INT) {
                    semantic_error(expr->line, "%s currently supports only int arrays", expr->text);
                }

                expr->array_size = arr_sym->array_size;

                if (strcmp(expr->text, "sort") == 0) {
                    if (argc != 1) {
                        semantic_error(expr->line, "sort expects 1 argument: array");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    expr->inferred = T_VOID;
                    break;
                }

                if (strcmp(expr->text, "find") == 0) {
                    if (argc != 2) {
                        semantic_error(expr->line, "find expects 2 arguments: array and target value");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    ExprList *second = first->next;
                    TypeKind target_type = infer_expr(second ? second->expr : NULL);
                    if (!is_numeric(target_type)) {
                        semantic_error(expr->line, "find target must be numeric");
                    }
                    expr->inferred = T_INT;
                    break;
                }

                if (strcmp(expr->text, "map") == 0) {
                    if (argc != 2) {
                        semantic_error(expr->line, "map expects 2 arguments: array and unary function");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    ExprList *second = first->next;
                    Expr *fn_expr = second ? second->expr : NULL;
                    if (!fn_expr || fn_expr->kind != EXPR_IDENT) {
                        semantic_error(expr->line, "map second argument must be a function name");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    Function *fn = find_function(fn_expr->text);
                    if (!fn) {
                        semantic_error_at(expr->line, fn_expr->text, "call to undefined function '%s'", fn_expr->text);
                        print_did_you_mean(fn_expr->text, 0, 1, 0, 0);
                        expr->inferred = T_ERROR;
                        break;
                    }
                    if (count_params(fn->params) != 1) {
                        semantic_error(expr->line, "map callback '%s' must accept exactly 1 parameter", fn->name);
                    } else {
                        Param *p = fn->params;
                        if (!is_numeric(p->type) || !is_numeric(fn->return_type)) {
                            semantic_error(expr->line, "map callback '%s' must be numeric -> numeric", fn->name);
                        }
                    }
                    expr->inferred = T_VOID;
                    break;
                }

                if (strcmp(expr->text, "filter") == 0) {
                    if (argc != 2) {
                        semantic_error(expr->line, "filter expects 2 arguments: array and predicate function");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    ExprList *second = first->next;
                    Expr *fn_expr = second ? second->expr : NULL;
                    if (!fn_expr || fn_expr->kind != EXPR_IDENT) {
                        semantic_error(expr->line, "filter second argument must be a function name");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    Function *fn = find_function(fn_expr->text);
                    if (!fn) {
                        semantic_error_at(expr->line, fn_expr->text, "call to undefined function '%s'", fn_expr->text);
                        print_did_you_mean(fn_expr->text, 0, 1, 0, 0);
                        expr->inferred = T_ERROR;
                        break;
                    }
                    if (count_params(fn->params) != 1) {
                        semantic_error(expr->line, "filter callback '%s' must accept exactly 1 parameter", fn->name);
                    } else {
                        Param *p = fn->params;
                        if (!is_numeric(p->type) || !is_bool_like(fn->return_type)) {
                            semantic_error(expr->line, "filter callback '%s' must be numeric -> bool-like", fn->name);
                        }
                    }
                    expr->inferred = T_INT;
                    break;
                }

                if (strcmp(expr->text, "reduce") == 0) {
                    if (argc != 3) {
                        semantic_error(expr->line, "reduce expects 3 arguments: array, binary function, initial value");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    ExprList *second = first->next;
                    ExprList *third = second ? second->next : NULL;
                    Expr *fn_expr = second ? second->expr : NULL;
                    Expr *init_expr = third ? third->expr : NULL;
                    if (!fn_expr || fn_expr->kind != EXPR_IDENT) {
                        semantic_error(expr->line, "reduce second argument must be a function name");
                        expr->inferred = T_ERROR;
                        break;
                    }
                    Function *fn = find_function(fn_expr->text);
                    if (!fn) {
                        semantic_error_at(expr->line, fn_expr->text, "call to undefined function '%s'", fn_expr->text);
                        print_did_you_mean(fn_expr->text, 0, 1, 0, 0);
                        expr->inferred = T_ERROR;
                        break;
                    }
                    if (count_params(fn->params) != 2) {
                        semantic_error(expr->line, "reduce callback '%s' must accept exactly 2 parameters", fn->name);
                    } else {
                        Param *p1 = fn->params;
                        Param *p2 = p1 ? p1->next : NULL;
                        if (!is_numeric(p1->type) || !is_numeric(p2 ? p2->type : T_ERROR) || !is_numeric(fn->return_type)) {
                            semantic_error(expr->line, "reduce callback '%s' must be (numeric, numeric) -> numeric", fn->name);
                        }
                    }
                    TypeKind init_type = infer_expr(init_expr);
                    if (!is_numeric(init_type)) {
                        semantic_error(expr->line, "reduce initial value must be numeric");
                    }
                    expr->inferred = T_INT;
                    break;
                }
            }
            /* Built-in math-like helpers from the custom language */
            if (strcmp(expr->text, "raise_to") == 0 ||
                strcmp(expr->text, "square_root") == 0 ||
                strcmp(expr->text, "magnitude") == 0 ||
                strcmp(expr->text, "round_down") == 0 ||
                strcmp(expr->text, "round_up") == 0 ||
                strcmp(expr->text, "ln") == 0 ||
                strcmp(expr->text, "SIN") == 0 ||
                strcmp(expr->text, "COS") == 0 ||
                strcmp(expr->text, "TAN") == 0) {
                /* Treat these as int-returning numeric helpers to match 'num' variables. */
                ExprList *arg = expr->args;
                while (arg) {
                    infer_expr(arg->expr);
                    arg = arg->next;
                }
                expr->inferred = T_INT;
                break;
            }
            Function *fn = find_function(expr->text);
            if (!fn) {
                semantic_error_at(expr->line, expr->text, "call to undefined function '%s'", expr->text);
                print_did_you_mean(expr->text, 0, 1, 0, 0);
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
            } else if (!strcmp(expr->op, "=")) {
                if (!type_compatible(left, right)) {
                    semantic_error(expr->line, "assignment requires compatible types");
                    expr->inferred = T_ERROR;
                } else {
                    expr->inferred = left;
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
                semantic_error_at(stmt->line, stmt->u.assign.name, "assignment to undeclared variable '%s'", stmt->u.assign.name);
                print_did_you_mean(stmt->u.assign.name, 1, 0, 0, 0);
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
                semantic_error_at(stmt->line, stmt->u.index_assign.name, "assignment to undeclared array '%s'", stmt->u.index_assign.name);
                print_did_you_mean(stmt->u.index_assign.name, 1, 0, 0, 0);
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
            push_scope();
            if (stmt->u.for_stmt.has_init_decl) {
                if (stmt->u.for_stmt.init_decl_type == T_VOID) {
                    semantic_error(stmt->line, "variable '%s' cannot have type void", stmt->u.for_stmt.init_decl_name);
                }
                if (stmt->u.for_stmt.init_decl_value) {
                    TypeKind init_type = infer_expr(stmt->u.for_stmt.init_decl_value);
                    if (!type_compatible(stmt->u.for_stmt.init_decl_type, init_type)) {
                        semantic_error(stmt->line,
                                       "cannot initialize '%s' of type %s with %s",
                                       stmt->u.for_stmt.init_decl_name,
                                       type_name(stmt->u.for_stmt.init_decl_type),
                                       type_name(init_type));
                    }
                }
                scope_add_symbol(stmt->u.for_stmt.init_decl_name, stmt->u.for_stmt.init_decl_type, stmt->line);
            } else if (stmt->u.for_stmt.init) {
                infer_expr(stmt->u.for_stmt.init);
            }
            if (stmt->u.for_stmt.cond) {
                TypeKind cond_type = infer_expr(stmt->u.for_stmt.cond);
                if (!is_bool_like(cond_type)) {
                    semantic_error(stmt->line, "for condition must be boolean-like");
                }
            }
            if (stmt->u.for_stmt.post) infer_expr(stmt->u.for_stmt.post);
            analyze_stmt_list(stmt->u.for_stmt.body);
            pop_scope();
            break;
        }
        case STMT_SWITCH: {
            TypeKind cond_type = infer_expr(stmt->u.switch_stmt.expr);
            if (!is_integral(cond_type)) {
                semantic_error(stmt->line, "switch expression must be integral");
            }
            for (Branch *br = stmt->u.switch_stmt.cases; br; br = br->next) {
                TypeKind case_type = infer_expr(br->cond);
                if (!type_compatible(cond_type, case_type)) {
                    semantic_error(br->line, "case label type must match switch expression type");
                }
                push_scope();
                analyze_stmt_list(br->body);
                pop_scope();
            }
            if (stmt->u.switch_stmt.default_branch) {
                push_scope();
                analyze_stmt_list(stmt->u.switch_stmt.default_branch);
                pop_scope();
            }
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

static int expr_precedence(Expr *expr) {
    if (!expr) return 0;

    switch (expr->kind) {
        case EXPR_IDENT:
        case EXPR_NUMBER:
        case EXPR_STRING:
        case EXPR_CALL:
        case EXPR_INDEX:
            return 100;
        case EXPR_UNARY:
            return 90;
        case EXPR_BINARY:
            if (!strcmp(expr->op, "=")) return 10;
            if (!strcmp(expr->op, "||")) return 20;
            if (!strcmp(expr->op, "&&")) return 30;
            if (!strcmp(expr->op, "==") || !strcmp(expr->op, "!=")) return 40;
            if (!strcmp(expr->op, "<") || !strcmp(expr->op, ">") || !strcmp(expr->op, "<=") || !strcmp(expr->op, ">=")) return 50;
            if (!strcmp(expr->op, "+") || !strcmp(expr->op, "-")) return 60;
            if (!strcmp(expr->op, "*") || !strcmp(expr->op, "/") || !strcmp(expr->op, "%")) return 70;
            return 50;
    }
    return 0;
}

static void emit_expr_prec(FILE *f, Expr *expr, int parent_prec) {
    if (!expr) return;

    int prec = expr_precedence(expr);
    int need_parens = prec < parent_prec;
    if (need_parens) fputc('(', f);

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
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "sort") == 0) {
                ExprList *first = expr->args;
                fprintf(f, "array_sort_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d", expr->array_size);
                } else {
                    fputs(", 0", f);
                }
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "find") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                fprintf(f, "array_find_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "map") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                fprintf(f, "array_map_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "filter") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                fprintf(f, "array_filter_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            if (strcmp(expr->text, "reduce") == 0) {
                ExprList *first = expr->args;
                ExprList *second = first ? first->next : NULL;
                ExprList *third = second ? second->next : NULL;
                fprintf(f, "array_reduce_int(");
                emit_expr_prec(f, first ? first->expr : NULL, 0);
                if (expr->array_size > 0) {
                    fprintf(f, ", %d, ", expr->array_size);
                } else {
                    fputs(", 0, ", f);
                }
                emit_expr_prec(f, second ? second->expr : NULL, 0);
                fputs(", ", f);
                emit_expr_prec(f, third ? third->expr : NULL, 0);
                fputc(')', f);
                break;
            }
            const char *fname = expr->text;
            if (strcmp(fname, "raise_to") == 0) fname = "pow";
            else if (strcmp(fname, "square_root") == 0) fname = "sqrt";
            else if (strcmp(fname, "magnitude") == 0) fname = "abs";
            else if (strcmp(fname, "round_down") == 0) fname = "floor";
            else if (strcmp(fname, "round_up") == 0) fname = "ceil";
            else if (strcmp(fname, "ln") == 0) fname = "logf";
            else if (strcmp(fname, "SIN") == 0) fname = "sinf";
            else if (strcmp(fname, "COS") == 0) fname = "cosf";
            else if (strcmp(fname, "TAN") == 0) fname = "tanf";
            fprintf(f, "%s(", fname);
            for (ExprList *arg = expr->args; arg; arg = arg->next) {
                emit_expr_prec(f, arg->expr, 0);
                if (arg->next) fputs(", ", f);
            }
            fputc(')', f);
            break;
        }
        case EXPR_INDEX:
            fprintf(f, "%s[", expr->text);
            emit_expr_prec(f, expr->index, 0);
            fputc(']', f);
            break;
        case EXPR_BINARY: {
            int child_prec = prec;
            emit_expr_prec(f, expr->left, child_prec);
            fprintf(f, " %s ", expr->op);
            emit_expr_prec(f, expr->right, child_prec);
            break;
        }
        case EXPR_UNARY:
            fprintf(f, "%s", expr->op);
            emit_expr_prec(f, expr->left, prec);
            break;
    }

    if (need_parens) fputc(')', f);
}

static void emit_expr(FILE *f, Expr *expr) {
    emit_expr_prec(f, expr, 0);
}

static void emit_stmt_list(FILE *f, Stmt *stmt) {
    for (Stmt *it = stmt; it; it = it->next) {
        emit_stmt(f, it);
    }
}

static int stmt_list_needs_switch_break(Stmt *stmt) {
    if (!stmt) return 1;
    Stmt *last = stmt;
    while (last->next) last = last->next;
    return last->kind != STMT_BREAK && last->kind != STMT_RETURN;
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
            if (stmt->u.for_stmt.has_init_decl) {
                fprintf(f, "%s %s", type_name(stmt->u.for_stmt.init_decl_type), stmt->u.for_stmt.init_decl_name);
                if (stmt->u.for_stmt.init_decl_value) {
                    fputs(" = ", f);
                    emit_expr(f, stmt->u.for_stmt.init_decl_value);
                }
            } else if (stmt->u.for_stmt.init) {
                emit_expr(f, stmt->u.for_stmt.init);
            }
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
        case STMT_SWITCH:
            emit_indent(f);
            fputs("switch (", f);
            emit_expr(f, stmt->u.switch_stmt.expr);
            fputs(") {\n", f);
            indent_level++;
            for (Branch *br = stmt->u.switch_stmt.cases; br; br = br->next) {
                emit_indent(f);
                fputs("case ", f);
                emit_expr(f, br->cond);
                fputs(":\n", f);
                indent_level++;
                emit_stmt_list(f, br->body);
                if (stmt_list_needs_switch_break(br->body)) {
                    emit_indent(f);
                    fputs("break;\n", f);
                }
                indent_level--;
            }
            if (stmt->u.switch_stmt.default_branch) {
                emit_indent(f);
                fputs("default:\n", f);
                indent_level++;
                emit_stmt_list(f, stmt->u.switch_stmt.default_branch);
                if (stmt_list_needs_switch_break(stmt->u.switch_stmt.default_branch)) {
                    emit_indent(f);
                    fputs("break;\n", f);
                }
                indent_level--;
            }
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

static void emit_array_helpers(FILE *f) {
    fputs("static void array_sort_int(int arr[], int n) {\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        for (int j = 0; j + 1 < n - i; j++) {\n", f);
    fputs("            if (arr[j] > arr[j + 1]) {\n", f);
    fputs("                int t = arr[j];\n", f);
    fputs("                arr[j] = arr[j + 1];\n", f);
    fputs("                arr[j + 1] = t;\n", f);
    fputs("            }\n", f);
    fputs("        }\n", f);
    fputs("    }\n", f);
    fputs("}\n\n", f);

    fputs("static int array_find_int(int arr[], int n, int target) {\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        if (arr[i] == target) return i;\n", f);
    fputs("    }\n", f);
    fputs("    return -1;\n", f);
    fputs("}\n\n", f);

    fputs("static void array_map_int(int arr[], int n, int (*op)(int)) {\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        arr[i] = op(arr[i]);\n", f);
    fputs("    }\n", f);
    fputs("}\n\n", f);

    fputs("static int array_filter_int(int arr[], int n, int (*pred)(int)) {\n", f);
    fputs("    int write_idx = 0;\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        if (pred(arr[i])) {\n", f);
    fputs("            arr[write_idx++] = arr[i];\n", f);
    fputs("        }\n", f);
    fputs("    }\n", f);
    fputs("    return write_idx;\n", f);
    fputs("}\n\n", f);

    fputs("static int array_reduce_int(int arr[], int n, int (*op)(int, int), int init) {\n", f);
    fputs("    int acc = init;\n", f);
    fputs("    for (int i = 0; i < n; i++) {\n", f);
    fputs("        acc = op(acc, arr[i]);\n", f);
    fputs("    }\n", f);
    fputs("    return acc;\n", f);
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
    emit_include(outf, "<stdlib.h>");
    emit_include(outf, "<stdbool.h>");
    emit_binary_search_helper(outf);
    emit_array_helpers(outf);
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

    load_source_lines(input_path);

    FILE *infile = fopen(input_path, "r");
    if (!infile) {
        fprintf(stderr, "Error: cannot open %s\n", input_path);
        free_source_lines();
        return 1;
    }

    yyin = infile;
    yyparse();

    fclose(infile);

    analyze_program();

    if (semantic_error_count > 0 || syntax_error_count > 0) {
        free_source_lines();
        return 1;
    }

    emit_program(output_path);
    free_source_lines();
    return 0;
}
