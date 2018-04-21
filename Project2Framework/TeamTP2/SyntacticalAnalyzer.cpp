/*******************************************************************************
* Assignment: Project 2 - Syntactic Analyzer for Scheme to C++ Translator      *
* Author:Ian Davidson & Andre Kuplian                                          *
* Date: Spring 2018                                                            *
* File: SyntacticalAnalyzer.cpp                                                *
*                                                                              *
* Description: This file contains the syntactical analyzer for the scheme lang.*
* A recursive top down parser, using a lexical analyzer, without error recovery*
*******************************************************************************/

//use external file to build all first and follows sets then include from here


#include <iostream>
#include <iomanip>
#include <fstream>
#include "SyntacticalAnalyzer.h"

using namespace std;

/*******************************************************************************
* Function: SyntacticialAnalyzer                                               *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will get the first token and initilize			   *
* lexical analysis                            								   *
*******************************************************************************/
SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	string name = filename;
	string p2name = name.substr (0, name.length()-3) + ".p2"; 
	p2file.open (p2name.c_str());
	token = lex->GetToken();
	int errors = Program ();
}

/*******************************************************************************
* Function:  Deconstructor                                                     *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will deconstruct lex and close output to *.p2     *
*******************************************************************************/
SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
	p2file.close ();
}

/*******************************************************************************
* Function: Program                                                            *
*                                                                              *
* Parameters:                                                                  *
* Return value:  Int value of errors found                                     *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "program"                                                 *
*******************************************************************************/
int SyntacticalAnalyzer::Program ()
{
//program=> define, more_defines, EOF_T

	p2file << "Entering Program function; current token is: "
					<< lex->GetTokenName (token) << endl;
	int errors = 0;
	// token should be in firsts of Program
	// Body of function goes here.
	p2file << "Using Rule 1" << endl;
	
	if(token == LPAREN_T){
	
		errors += define ();
		
		errors += more_defines ();
	
	}else{

		errors++;
		lex->ReportError ("missing first opening paren at beggingn of program; found: " + lex->GetTokenName (token) );
	
	}

	if (token != EOF_T)
	{
		errors++;
		lex->ReportError ("Missing end of file at end of program");
	}
	// token should be in follows of Program
	p2file << "Exiting Program function; current token is: "
					<< lex->GetTokenName (token) << endl;
	return errors;
}



/*******************************************************************************
* Function: define                                                             *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "define"                                                  *
*******************************************************************************/

//rule 2 <def> => LPAREN_T, DEFINE_T LPAREN_T IDENT_T <param_list> RPAREN_T <stmt> <stmt_list> RPAREN_T

//todo: figure out if we should check for firsts of the functin we are about to call and
//go into. B/c we are going to do the same check inside the function, seems like we would skip over rules
//Or maybe it doesnt play a difference if we dont have error recovery. :P
int SyntacticalAnalyzer::define ()
{

	p2file << "Entering function: define() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure

	//rule 2 <def> => LPAREN_T, DEFINE_T LPAREN_T IDENT_T <param_list> RPAREN_T <stmt> <stmt_list> RPAREN_T
	p2file << "Using Rule 2" << endl;
	if(token == LPAREN_T){
		token = lex->GetToken();
	}else{
		errors++;
		lex->ReportError("expecting first LPAREN_T at middle of define, found: "  + lex->GetTokenName (token));
	}

	if(token == DEFINE_T){
		token = lex->GetToken();
	}else{
		errors++;
		lex->ReportError("expecting first DEFINE_T at middle of define, found: "  + lex->GetTokenName (token));
	}


	if(token == LPAREN_T){
		token = lex->GetToken();
	}else{
		errors++;
		lex->ReportError("expecting second LPAREN_T at begining of define, found: "  + lex->GetTokenName (token));
	}	

	
	if(token == IDENT_T){

		token = lex->GetToken();
	}else{
		errors++;
		lex->ReportError("expecting first IDENT_T, found: " + lex->GetTokenName(token));
	}

	//if member of first of param_list
	//not sure if this should be checked for here or if we should just call param_list and do this checking there :/
	errors += param_list();

	if(token == RPAREN_T){
		token = lex->GetToken();
	}else{
		errors++;
		lex->ReportError("expecting first RPAREN_T, found: " + lex->GetTokenName(token));
	}

	errors += stmt();


	errors += stmt_list();

	if(token == RPAREN_T){
		token = lex->GetToken();
	}else{
		errors++;
		lex->ReportError("expecting second RPAREN_T, found: " + lex->GetTokenName(token));
	}

	p2file << "Exiting define function; current token is: "
			<< lex->GetTokenName (token) << endl;

	return errors;

}



/*******************************************************************************
* Function: more_defines                                                       *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "more_defines"                                            *
*******************************************************************************/
int SyntacticalAnalyzer::more_defines ()
{
	/*
3. <more_defines> -> <define> <more_defines>
4. <more_defines> -> λ

	*/
	p2file << "Entering function: more_defines() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure

	if (token == LPAREN_T){ //first of define
		

		//fosho rule 3
		p2file << "Using Rule 3" << endl;
		errors += define();

		errors += more_defines();



	}else if (token == EOF_T){    //follows of more_defines 
		//being the lambda definition
		//do nothing we coo
		p2file << "Using Rule 4" << endl;

	}else {
		errors++;
		lex->ReportError("expecting first or follows of define; found: " + lex->GetTokenName(token));
	}

	p2file << "Exiting function: more_defines() with current token: " << lex->GetTokenName(token) << endl; //exiting funct name

	return errors;

}




/*******************************************************************************
* Function: stmt_list                                                          *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "stmt_list"                                               *
*******************************************************************************/
int SyntacticalAnalyzer::stmt_list ()
{
/*
	5. <stmt_list> -> <stmt> <stmt_list>
	6. <stmt_list> -> λ
	
*/

p2file << "Entering function: stmt_list() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
int errors = 0;
//check if current token is in first and follows of respective


//do specific rule related procedure


if(token == IDENT_T || token == LPAREN_T || token == NUMLIT_T || token == STRLIT_T || token == QUOTE_T){
	
	p2file << "Using Rule 5" << endl;

	errors+= stmt();

	errors+= stmt_list();

}else if (token == RPAREN_T){
	//we chillin lambda case
	p2file << "Using Rule 6" << endl;

}else{

	errors++;
	lex->ReportError("Expected the first of stmt_list but found: " + lex->GetTokenName(token));

}


p2file << "Exiting function: stmt_list() with current token: " << lex->GetTokenName(token) << endl; //exit funct name

return errors;

	
}




/*******************************************************************************
* Function: stmt                                                               *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "stmt"                                                    *
*******************************************************************************/
int SyntacticalAnalyzer::stmt ()
{

	/*

	7. <stmt> -> <literal>
	8. <stmt> -> IDENT_T
	9. <stmt> -> LPAREN_T <action> RPAREN_T

	*/

	p2file << "Entering function: stmt() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure

	//if first of literal:
	if(token == NUMLIT_T || token == STRLIT_T || token == QUOTE_T){
		p2file << "Using Rule 7" << endl;
		errors+= literal();
	}
	else if (token == IDENT_T)
	{
		p2file << "Using Rule 8" << endl;
		token = lex->GetToken();

	}
	else if(token == LPAREN_T){

		p2file << "Using Rule 9" << endl;
		token = lex->GetToken();
	
		errors+= action();

		if( token == RPAREN_T){

			token = lex->GetToken(); 

		}else{
			errors++;
			lex->ReportError("Expected RPAREN_T but got: " + lex->GetTokenName(token));
		}

	}else{
		errors++;
		lex->ReportError("expected the first of stmt but got: " + lex->GetTokenName(token));
	}

	p2file << "Exiting function: stmt() with current token: " << lex->GetTokenName(token) << endl; //enter funct name

	return errors;

}



/*******************************************************************************
* Function: literal                                                            *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "literal"                                                 *
*******************************************************************************/
int SyntacticalAnalyzer::literal ()
{
/*

10. <literal> -> NUMLIT_T
11. <literal> -> STRLIT_T
12. <literal> -> QUOTE_T <quoted_lit>

*/

	p2file << "Entering function: literal() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure
	if(token == NUMLIT_T || token == STRLIT_T)
	{
		if(token == NUMLIT_T){
			p2file << "Using Rule 10" << endl;
		}else if(token == STRLIT_T){
			p2file << "Using Rule 11" << endl;
		}
		token = lex->GetToken();
	}
	else if(token == QUOTE_T)
	{
		p2file << "Using Rule 12" << endl;
		token = lex->GetToken();

		errors += quoted_lit();
	}
	else
	{
		errors++;
		lex->ReportError("expected First of literal but got: " + lex->GetTokenName(token));
	}


	p2file << "Exiting function: literal() with current token: " << lex->GetTokenName(token) << endl; //enter funct name

	return errors;

	
}




/*******************************************************************************
* Function: quoted_lit                                                         *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "quoted_lit"                                              *
*******************************************************************************/
int SyntacticalAnalyzer::quoted_lit ()
{

	/*
	13. <quoted_lit> -> <any_other_token>
	
	*/

	p2file << "Entering function: quoted_lit() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective

	p2file << "Using Rule 13" << endl;
	//do specific rule related procedure
	errors += any_other_token();


	p2file << "Exiting function: quoted_lit() with current token: " << lex->GetTokenName(token) << endl; //enter funct name

	return errors;
}

/*******************************************************************************
* Function: more_tokens                                                        *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "more_tokens"                                             *
*******************************************************************************/
int SyntacticalAnalyzer::more_tokens ()
{
/*

14. <more_tokens> -> <any_other_token> <more_tokens>
15. <more_tokens> -> λ

*/

	p2file << "Entering function: more_tokens() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	//make iterator to figure if token is member of any_other_token firsts'
	//bc first of any_other_token is grossly huge
	set<token_type>::iterator itr1 = any_other_token_firsts.find(token);

	if (itr1 != any_other_token_firsts.end())
	{//token is a first of any_o_t
		p2file << "Using Rule 14" << endl;
		errors += any_other_token();

		errors += more_tokens();



	}
	else if(token == RPAREN_T)
	{ //follows of more_tokens
		//lambda case we coo
		p2file << "Using Rule 15" << endl;
	}
	else
	{
		errors++;
		lex->ReportError("Expecting first of more_tokens; got: " + lex->GetTokenName(token));
	}


	p2file << "Exiting function: more_tokens() with current token: " << lex->GetTokenName(token) << endl; //enter funct name

	return errors;
}



/*******************************************************************************
* Function: param_list                                                         *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "param_list"                                              *
*******************************************************************************/
int SyntacticalAnalyzer::param_list ()
{

/*

	16. <param_list> -> IDENT_T <param_list>
	17. <param_list> -> λ

*/	
	p2file << "Entering function: param_list() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure
	if(token == IDENT_T){
		p2file << "Using Rule 16" << endl;
		token = lex->GetToken();

		errors += param_list();

	}else if(token == RPAREN_T){ //follows of param_list
	//dont do shit here
		p2file << "Using Rule 17" << endl;

	}else{
		errors++;
		lex->ReportError("Expected first of param_list; found: " + lex->GetTokenName(token));
	}

	p2file << "Exiting function: param_list() with current token: " << lex->GetTokenName(token) << endl; //enter funct name

	return errors;
}




/*******************************************************************************
* Function: else_part                                                          *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "else_part"                                               *
*******************************************************************************/
int SyntacticalAnalyzer::else_part ()
{	/*
	18. <else_part> -> <stmt>
	19. <else_part> -> λ
	*/

	p2file << "Entering function: else_part() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure
	if(token == IDENT_T || token == LPAREN_T || token == NUMLIT_T || token == STRLIT_T || token == QUOTE_T){//first of stmt
		p2file << "Using Rule 18" << endl;
		errors += stmt();

	}else if(token == RPAREN_T){
		//do nothing
		p2file << "Using Rule 19" << endl;

	}else{
		errors++;
		lex->ReportError("Expected first of else_part; found: " + lex->GetTokenName(token));

	}

	p2file << "Exiting function: else_part() with current token: " << lex->GetTokenName(token) << endl; //enter funct name

	return errors;

}



/*******************************************************************************
* Function: stmt_pair                                                          *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "stmt_pair"                                               *
*******************************************************************************/
int SyntacticalAnalyzer::stmt_pair()
{
	/*
20. <stmt_pair> -> LPAREN_T <stmt_pair_body>
21. <stmt_pair> -> λ
	*/
	
	p2file << "Entering function: stmt_pair() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure
	if(token == LPAREN_T){
		p2file << "Using Rule 20" << endl;
		token = lex->GetToken();

		errors += stmt_pair_body();
	}else if(token == RPAREN_T){
		//do nothing
		p2file << "Using Rule 21" << endl;
	}else {
		errors++;
		lex->ReportError("Expected first of stmt_pair; got: " + lex->GetTokenName(token));
	}


	p2file << "Exiting function: stmt_pair() with current token: " << lex->GetTokenName(token) << endl; //enter funct name

	return errors;

}



/*******************************************************************************
* Function: stmt_pair_body                                                     *
*                                                                              *
* Parameters:                                                                  *
* Return value: Int value of errors found                                      *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::stmt_pair_body()
{

/*
	22. <stmt_pair_body> -> <stmt> <stmt> RPAREN_T <stmt_pair>
	23. <stmt_pair_body> -> ELSE_T <stmt> RPAREN_T
*/

	p2file << "Entering function: stmt_pair_body() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective
	if (token == ELSE_T){
		p2file << "Using Rule 22" << endl;
		token = lex->GetToken();

		errors += stmt();

		if(token == RPAREN_T){
			token = lex->GetToken();
		}else{
			errors++;
			lex->ReportError("Expected first of stmt_pair_body; found: " + lex->GetTokenName(token));
		}
	} 
	else if (token == IDENT_T || token == LPAREN_T || token == NUMLIT_T || token == STRLIT_T || token == QUOTE_T){
		p2file << "Using Rule 21" << endl;
		errors += stmt();
		errors += stmt();
		if(token == RPAREN_T){
			token = lex->GetToken();
		}else{
			errors++;
			lex->ReportError("Expected first of stmt_pair_body; found: " + lex->GetTokenName(token));
		}
		errors += stmt_pair();
	}
	else{
		errors++;
		lex->ReportError("Expected first of stmt_pair_body; found: " + lex->GetTokenName(token));
	}
	//do specific rule related procedure


	p2file << "Exiting function: stmt_pair_body() with current token: " << lex->GetTokenName(token) << endl; //enter funct name


	return errors;

}



/*******************************************************************************
* Function: action                                                             *
*                                                                              *
* Parameters:                                                                  *
* Return value:   Int value of errors found                                    *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "action"                                                  *
*******************************************************************************/
int SyntacticalAnalyzer::action()
{
/*
	type 1
24. <action> -> IF_T <stmt> <stmt> <else_part>

	type2
25. <action> -> COND_T LPAREN_T <stmt_pair_body>

	type3
26. <action> -> LISTOP_T <stmt>
31. <action> -> NUMBERP_T <stmt>
32. <action> -> SYMBOLP_T <stmt>
33. <action> -> LISTP_T <stmt>
34. <action> -> ZEROP_T <stmt>
35. <action> -> NULLP_T <stmt>
30. <action> -> NOT_T <stmt>
36. <action> -> STRINGP_T <stmt>
48. <action> -> DISPLAY_T <stmt>

	type4
27. <action> -> CONS_T <stmt> <stmt>
41. <action> -> MODULO_T <stmt> <stmt>

	type5
38. <action> -> MINUS_T <stmt> <stmt_list>
39. <action> -> DIV_T <stmt> <stmt_list>
	
	type6
28. <action> -> AND_T <stmt_list>
29. <action> -> OR_T <stmt_list>
37. <action> -> PLUS_T <stmt_list>
40. <action> -> MULT_T <stmt_list>
42. <action> -> EQUALTO_T <stmt_list>
43. <action> -> GT_T <stmt_list>
44. <action> -> LT_T <stmt_list>
45. <action> -> GTE_T <stmt_list>
46. <action> -> LTE_T <stmt_list>
47. <action> -> IDENT_T <stmt_list>

	type7
49. <action> -> NEWLINE_T


*/
	p2file << "Entering function: action() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure

	//type1
	if(token == IF_T){
		//24. <action> -> IF_T <stmt> <stmt> <else_part>
		p2file << "Using Rule 24" << endl;

		token = lex->GetToken();

		errors+= stmt();
		errors+= stmt();
		errors+= else_part();

	//type2
	}else if(token == COND_T){
		//25. <action> -> COND_T LPAREN_T <stmt_pair_body>
		p2file << "Using Rule 25" << endl;
		token = lex->GetToken();

		if(token == LPAREN_T){
			token = lex->GetToken();
			errors += stmt_pair_body();

		}else{
			errors++;
			lex->ReportError("Expected first of action, found: " + lex->GetTokenName(token));
		}
	//type3	
	}else if(token == LISTOP_T || token == NUMBERP_T || token == SYMBOLP_T || token == LISTP_T || token == ZEROP_T || token == NULLP_T || token == NOT_T || token == STRINGP_T || token == DISPLAY_T){
	/*
26. <action> -> LISTOP_T <stmt>
31. <action> -> NUMBERP_T <stmt>
32. <action> -> SYMBOLP_T <stmt>
33. <action> -> LISTP_T <stmt>
34. <action> -> ZEROP_T <stmt>
35. <action> -> NULLP_T <stmt>
30. <action> -> NOT_T <stmt>
36. <action> -> STRINGP_T <stmt>
48. <action> -> DISPLAY_T <stmt>
	*/
		if(token == LISTOP_T){
			p2file << "Using Rule 26" << endl;
		}else if(token == NUMBERP_T){
			p2file << "Using Rule 31" << endl;
		}else if(token == SYMBOLP_T){
			p2file << "Using Rule 32" << endl;
		}else if(token == LISTP_T){
			p2file << "Using Rule 33" << endl;
		}else if(token == ZEROP_T){
			p2file << "Using Rule 34" << endl;
		}else if(token == NULLP_T){
			p2file << "Using Rule 35" << endl;
		}else if(token == NOT_T){
			p2file << "Using Rule 30" << endl;
		}else if(token == STRINGP_T){
			p2file << "Using Rule 36" << endl;
		}else if(token == DISPLAY_T){
			p2file << "Using Rule 48" << endl;
		}

	
		token = lex->GetToken();
		errors += stmt();
		

	
	//type4
	}else if(token == CONS_T || token == MODULO_T){/*
27. <action> -> CONS_T <stmt> <stmt>
41. <action> -> MODULO_T <stmt> <stmt>
	*/
		if( token == CONS_T){
			p2file << "Using Rule 27" << endl;
		}else if(token == MODULO_T){
			p2file << "Using Rule 41" << endl;
		}
		token = lex->GetToken();
		errors += stmt();
		errors += stmt();
	
	}else if(token == MINUS_T || token  == DIV_T){
	//type5
// 38. <action> -> MINUS_T <stmt> <stmt_list>
// 39. <action> -> DIV_T <stmt> <stmt_list>
		if( token == MINUS_T){
			p2file << "Using Rule 38" << endl;
		}else if(token == DIV_T){
			p2file << "Using Rule 39" << endl;
		}

		token = lex->GetToken();
		errors += stmt();
		errors += stmt_list();


	}else if(token == AND_T || token  == OR_T || token  == PLUS_T || token  == MULT_T || token  == EQUALTO_T || token  == GT_T || token  == LT_T || token  == GTE_T || token  == LTE_T || token == IDENT_T){
	//type 6 
// 28. <action> -> AND_T <stmt_list>
// 29. <action> -> OR_T <stmt_list>
// 37. <action> -> PLUS_T <stmt_list>
// 40. <action> -> MULT_T <stmt_list>
// 42. <action> -> EQUALTO_T <stmt_list>
// 43. <action> -> GT_T <stmt_list>
// 44. <action> -> LT_T <stmt_list>
// 45. <action> -> GTE_T <stmt_list>
// 46. <action> -> LTE_T <stmt_list>
// 47. <action> -> IDENT_T <stmt_list>
		if(token == AND_T){
			p2file << "Using Rule 28" << endl;
		}else if(token == OR_T){
			p2file << "Using Rule 29" << endl;
		}else if(token == PLUS_T){
			p2file << "Using Rule 37" << endl;
		}else if(token == MULT_T){
			p2file << "Using Rule 40" << endl;
		}else if(token == EQUALTO_T){
			p2file << "Using Rule 42" << endl;
		}else if(token == GT_T){
			p2file << "Using Rule 43" << endl;
		}else if(token == LT_T){
			p2file << "Using Rule 44" << endl;
		}else if(token == GTE_T){
			p2file << "Using Rule 45" << endl;
		}else if(token == LTE_T){
			p2file << "Using Rule 46" << endl;
		}else if(token == IDENT_T){
			p2file << "Using Rule 47" << endl;
		}

		token = lex->GetToken();

		errors += stmt_list();

	}else if(token == NEWLINE_T){
	//type7
	// 49. <action> -> NEWLINE_T
		token = lex->GetToken();
	}else{
		errors++;
		lex->ReportError("Expected one of the firsts of action; somehow found: " + lex->GetTokenName(token));
	}

	p2file << "Exiting function: action() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	return errors;

}


/*******************************************************************************
* Function: any_other_token                                                    *
*                                                                              *
* Parameters:                                                                  *
* Return value:  Int value of errors found                                     *
* Description: This function will apply the grammar rules defined below for the*
* non-terminal state "any_other_token"                                         *
*******************************************************************************/
int SyntacticalAnalyzer::any_other_token()
{
	/*
type1
50. <any_other_token> -> LPAREN_T <more_tokens> RPAREN_T

type 2
79. <any_other_token> -> QUOTE_T <any_other_token>

type 3
51. <any_other_token> -> IDENT_T
52. <any_other_token> -> NUMLIT_T
53. <any_other_token> -> STRLIT_T
54. <any_other_token> -> CONS_T
55. <any_other_token> -> IF_T
56. <any_other_token> -> DISPLAY_T
57. <any_other_token> -> NEWLINE_T
58. <any_other_token> -> LISTOP_T
59. <any_other_token> -> AND_T
60. <any_other_token> -> OR_T
61. <any_other_token> -> NOT_T
62. <any_other_token> -> DEFINE_T
63. <any_other_token> -> NUMBERP_T
64. <any_other_token> -> SYMBOLP_T
65. <any_other_token> -> LISTP_T
66. <any_other_token> -> ZEROP_T
67. <any_other_token> -> NULLP_T
68. <any_other_token> -> STRINGP_T
69. <any_other_token> -> PLUS_T
70. <any_other_token> -> MINUS_T
71. <any_other_token> -> DIV_T
72. <any_other_token> -> MULT_T
73. <any_other_token> -> MODULO_T
74. <any_other_token> -> EQUALTO_T
75. <any_other_token> -> GT_T
76. <any_other_token> -> LT_T
77. <any_other_token> -> GTE_T
78. <any_other_token> -> LTE_T
80. <any_other_token> -> COND_T
81. <any_other_token> -> ELSE_T
	*/
p2file << "Entering function: any_other_token() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
int errors = 0;
//check if current token is in first and follows of respective
if(token == LPAREN_T){//type1
	// 50. <any_other_token> -> LPAREN_T <more_tokens> RPAREN_T
	p2file << "Using Rule 50" << endl;
	token = lex->GetToken();
	errors += more_tokens();
	if(token == RPAREN_T){
		token = lex->GetToken();
	}else{
		errors++;
		lex->ReportError("Expected first of any_other_token; found: " + lex->GetTokenName(token));
	}
}else if(token == QUOTE_T){//type 2
	//79. <any_other_token> -> QUOTE_T <any_other_token>
	p2file << "Using Rule 79" << endl;
	token = lex->GetToken();
	errors += any_other_token();
}else if(token == IDENT_T || token == NUMLIT_T || token == STRLIT_T || token == CONS_T || token == IF_T || token == DISPLAY_T || token == NEWLINE_T || token == LISTOP_T || token == AND_T || token == OR_T || token == NOT_T || token == DEFINE_T || token == NUMBERP_T || token == SYMBOLP_T || token == LISTP_T || token == ZEROP_T || token == NULLP_T || token == STRINGP_T || token == PLUS_T || token == MINUS_T || token == DIV_T || token == MULT_T || token == MODULO_T || token == EQUALTO_T || token == GT_T || token == LT_T || token == GTE_T || token == LTE_T || token == COND_T || token == ELSE_T){//type3
	//type3
/*
51. <any_other_token> -> IDENT_T
52. <any_other_token> -> NUMLIT_T
53. <any_other_token> -> STRLIT_T
54. <any_other_token> -> CONS_T
55. <any_other_token> -> IF_T
56. <any_other_token> -> DISPLAY_T
57. <any_other_token> -> NEWLINE_T
58. <any_other_token> -> LISTOP_T
59. <any_other_token> -> AND_T
60. <any_other_token> -> OR_T
61. <any_other_token> -> NOT_T
62. <any_other_token> -> DEFINE_T
63. <any_other_token> -> NUMBERP_T
64. <any_other_token> -> SYMBOLP_T
65. <any_other_token> -> LISTP_T
66. <any_other_token> -> ZEROP_T
67. <any_other_token> -> NULLP_T
68. <any_other_token> -> STRINGP_T
69. <any_other_token> -> PLUS_T
70. <any_other_token> -> MINUS_T
71. <any_other_token> -> DIV_T
72. <any_other_token> -> MULT_T
73. <any_other_token> -> MODULO_T
74. <any_other_token> -> EQUALTO_T
75. <any_other_token> -> GT_T
76. <any_other_token> -> LT_T
77. <any_other_token> -> GTE_T
78. <any_other_token> -> LTE_T
80. <any_other_token> -> COND_T
81. <any_other_token> -> ELSE_T
*/
	if(token == IDENT_T){
		p2file << "Using Rule 51" << endl;
	}else if(token == NUMLIT_T){
		p2file << "Using Rule 52" << endl;
	}else if(token == STRLIT_T){
		p2file << "Using Rule 53" << endl;
	}else if(token == CONS_T){
		p2file << "Using Rule 54" << endl;
	}else if(token == IF_T){
		p2file << "Using Rule 55" << endl;
	}else if(token == DISPLAY_T){
		p2file << "Using Rule 56" << endl;
	}else if(token == NEWLINE_T){
		p2file << "Using Rule 57" << endl;
	}else if(token == LISTOP_T){
		p2file << "Using Rule 58" << endl;
	}else if(token == AND_T){
		p2file << "Using Rule 59" << endl;
	}else if(token == OR_T){
		p2file << "Using Rule 60" << endl;
	}else if(token == NOT_T){
		p2file << "Using Rule 61" << endl;
	}else if(token == DEFINE_T){
		p2file << "Using Rule 62" << endl;
	}else if(token == NUMBERP_T){
		p2file << "Using Rule 63" << endl;
	}else if(token == SYMBOLP_T){
		p2file << "Using Rule 64" << endl;
	}else if(token == LISTP_T){
		p2file << "Using Rule 65" << endl;
	}else if(token == ZEROP_T){
		p2file << "Using Rule 66" << endl;
	}else if(token == NULLP_T){
		p2file << "Using Rule 67" << endl;
	}else if(token == STRINGP_T){
		p2file << "Using Rule 68" << endl;
	}else if(token == PLUS_T){
		p2file << "Using Rule 69" << endl;
	}else if(token == MINUS_T){
		p2file << "Using Rule 70" << endl;
	}else if(token == DIV_T){
		p2file << "Using Rule 71" << endl;
	}else if(token == MULT_T){
		p2file << "Using Rule 72" << endl;
	}else if(token == MODULO_T){
		p2file << "Using Rule 73" << endl;
	}else if(token == EQUALTO_T){
		p2file << "Using Rule 74" << endl;
	}else if(token == GT_T){
		p2file << "Using Rule 75" << endl;
	}else if(token == LT_T){
		p2file << "Using Rule 76" << endl;
	}else if(token == GTE_T){
		p2file << "Using Rule 77" << endl;
	}else if(token == LTE_T){
		p2file << "Using Rule 78" << endl;
	}else if(token == COND_T){
		p2file << "Using Rule 80" << endl;
	}else if(token == ELSE_T){
		p2file << "Using Rule 81" << endl;
	}
	/*
70. <any_other_token> -> MINUS_T
71. <any_other_token> -> DIV_T
72. <any_other_token> -> MULT_T
73. <any_other_token> -> MODULO_T
74. <any_other_token> -> EQUALTO_T
75. <any_other_token> -> GT_T
76. <any_other_token> -> LT_T
77. <any_other_token> -> GTE_T
78. <any_other_token> -> LTE_T
80. <any_other_token> -> COND_T
81. <any_other_token> -> ELSE_T
	*/


	token = lex->GetToken();
}else{
	errors++;
	lex->ReportError("Expected first of any_other_token, found: " + lex->GetTokenName(token));
}



//do specific rule related procedure


p2file << "Exiting function: any_other_token() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
return errors;

}





