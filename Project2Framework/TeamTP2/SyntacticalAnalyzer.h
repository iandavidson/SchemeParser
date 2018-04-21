/*******************************************************************************
* Assignment: Project 2 - Syntactic Analyzer for Scheme to C++ Translator      *
* Author:                                                                      *
* Date: Spring 2018                                                            *
* File: SyntacticalAnalyzer.h                                                  *
*                                                                              *
* Description: This file contains the                                          *
*******************************************************************************/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include <set>
#include "LexicalAnalyzer.h"

using namespace std;


/*******************************************************************************
* Type: token_type                                                             *
*                                                                              *
* Description: The token_type enumerated type is used to identify the tokens   *
*              associated with the lexemes scanned from an input file.         *
*******************************************************************************/

/*
enum token_type {NONE = -1, LAMBDA, IDENT_T, NUMLIT_T, STRLIT_T, CONS_T, IF_T,
		 COND_T, DISPLAY_T, NEWLINE_T, LISTOP_T, AND_T, OR_T, NOT_T,
		 DEFINE_T, NUMBERP_T, SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T,
		 STRINGP_T, MODULO_T, ELSE_T, PLUS_T, MINUS_T, DIV_T, MULT_T,
		 EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, LPAREN_T, RPAREN_T, QUOTE_T,
		 ERROR_T, EOF_T, MAX_TOKENS};


*/



/*******************************************************************************
* Type: first and follows sets                                                 *
*                                                                              *
* Description:  This should contain the all of the  sets of first and follows  *
* for the nonterminal states.												   *
*******************************************************************************/

static set<token_type> program_firsts = {LPAREN_T};
static set<token_type> program_follows = {};

static set<token_type> define_firsts = {LPAREN_T};
static set<token_type> define_follows = {LPAREN_T, EOF_T};

static set<token_type> more_defines_firsts = {LPAREN_T, EOF_T};
static set<token_type> more_defines_follows = {EOF_T};

static set<token_type> stmt_list_firsts = {IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T};
static set<token_type> stmt_list_follows = {RPAREN_T};

static set<token_type> stmt_firsts = {IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T};
static set<token_type> stmt_follows = {IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T, RPAREN_T};

static set<token_type> literal_firsts = {NUMLIT_T, STRLIT_T, QUOTE_T};
static set<token_type> literal_follows = {IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T, RPAREN_T};

static set<token_type> quoted_lit_firsts = {LPAREN_T, IDENT_T, NUMLIT_T, STRLIT_T, CONS_T, IF_T, DISPLAY_T, NEWLINE_T, LISTOP_T, AND_T, OR_T, NOT_T, DEFINE_T, NUMBERP_T, SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T, MODULO_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, QUOTE_T, COND_T, ELSE_T};
static set<token_type> quoted_lit_follows = {IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T, RPAREN_T};

static set<token_type> more_tokens_firsts = {LPAREN_T, IDENT_T, NUMLIT_T, STRLIT_T, CONS_T, IF_T, DISPLAY_T, NEWLINE_T, LISTOP_T, AND_T, OR_T, NOT_T, DEFINE_T, NUMBERP_T, SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T, MODULO_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, QUOTE_T, COND_T, ELSE_T};
static set<token_type> more_tokens_follows = {RPAREN_T};

static set<token_type> param_list_firsts = {IDENT_T};
static set<token_type> param_list_follows = {RPAREN_T};

static set<token_type> else_part_firsts = {IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T};
static set<token_type> else_part_follows = {RPAREN_T};

static set<token_type> stmt_pair_firsts = {LPAREN_T, RPAREN_T};
static set<token_type> stmt_pair_follows = {RPAREN_T};

static set<token_type> stmt_pair_body_firsts = {ELSE_T, IDENT_T, LPAREN_T, NUMLIT_T, STRLIT_T, QUOTE_T};
static set<token_type> stmt_pair_body_follows = {RPAREN_T};

static set<token_type> action_firsts = {IF_T, COND_T, LISTOP_T, CONS_T, AND_T, OR_T, NOT_T, NUMBERP_T, SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T, MODULO_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, IDENT_T, DISPLAY_T, NEWLINE_T};
static set<token_type> action_follows = {RPAREN_T};

static set<token_type> any_other_token_firsts = {LPAREN_T, IDENT_T, NUMLIT_T, STRLIT_T, CONS_T, IF_T, DISPLAY_T, NEWLINE_T, LISTOP_T, AND_T, OR_T, NOT_T, DEFINE_T, NUMBERP_T, SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T, MODULO_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, QUOTE_T, COND_T, ELSE_T};
static set<token_type> any_other_token_follows = {LPAREN_T, IDENT_T, NUMLIT_T, STRLIT_T, CONS_T, IF_T, DISPLAY_T, NEWLINE_T, LISTOP_T, AND_T, OR_T, NOT_T, DEFINE_T, NUMBERP_T, SYMBOLP_T, LISTP_T, ZEROP_T, NULLP_T, STRINGP_T, PLUS_T, MINUS_T, DIV_T, MULT_T, MODULO_T, EQUALTO_T, GT_T, LT_T, GTE_T, LTE_T, QUOTE_T, COND_T, ELSE_T, RPAREN_T};




class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
	~SyntacticalAnalyzer ();
    private:
	LexicalAnalyzer * lex;
	ofstream p2file;
	token_type token;
	int Program ();
	int define();
	int more_defines();
	int stmt_list();
	int stmt();
	int literal();
	int quoted_lit();
	int more_tokens();
	int param_list();
	int else_part();
	int stmt_pair();
	int stmt_pair_body();
	int action();
	int any_other_token();
};
	
#endif
