/*******************************************************************************
* Assignment: Project 2 - Syntactic Analyzer for Scheme to C++ Translator      *
* Author:Ian Davidson & Andre Kuplian                                          *
* Date: Spring 2018                                                            *
* File: SyntacticalAnalyzer.cpp                                                *
*                                                                              *
* Description: This file contains the                                          *
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
* Description: This function will                                              *
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
* Description: This function will                                              *
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
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::Program ()
{
//definitly not done

	p2file << "Entering Program function; current token is: "
					<< lex->GetTokenName (token) << endl;
	int errors = 0;
	// token should be in firsts of Program
	// Body of function goes here.
	p2file << "Using Rule 1" << endl;
	//errors += Define ();
	//errors += More_Defines ();
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
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::define ()
{

	cout << "Entering function: define() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure

	//rule 2 <def> => LPAREN_T, DEFINE_T LPAREN_T IDENT_T <param_list> RPAREN_T <stmt> <stmt_list> RPAREN_T
	




	return errors;

}



/*******************************************************************************
* Function: more_defines                                                       *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::more_defines ()
{
	
	cout << "Entering function: more_defines() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	return errors;

}




/*******************************************************************************
* Function: stmt_list                                                          *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::stmt_list ()
{
cout << "Entering function: stmt_list() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
int errors = 0;
//check if current token is in first and follows of respective


//do specific rule related procedure


return errors;

	
}




/*******************************************************************************
* Function: stmt                                                               *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::stmt ()
{

	cout << "Entering function: stmt() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	return errors;

}



/*******************************************************************************
* Function: literal                                                            *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::literal ()
{
	cout << "Entering function: literal() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	return errors;

	
}




/*******************************************************************************
* Function: quoted_lit                                                         *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::quoted_lit ()
{
	cout << "Entering function: quoted_lit() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	return errors;
}

/*******************************************************************************
* Function: more_tokens                                                        *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::more_tokens ()
{
	cout << "Entering function: more_tokens() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	return errors;
}



/*******************************************************************************
* Function: param_list                                                             *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::param_list ()
{
	cout << "Entering function: param_list() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	return errors;
}






/*******************************************************************************
* Function: else_part                                                          *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::else_part ()
{

	cout << "Entering function: else_part() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	return errors;

}



/*******************************************************************************
* Function: stmt_pair                                                          *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::stmt_pair()
{
	
	cout << "Entering function: stmt_pair() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	return errors;

}



/*******************************************************************************
* Function: stmt_pair_body                                                     *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::stmt_pair_body()
{
	cout << "Entering function: stmt_pair_body() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure



	return errors;
}



/*******************************************************************************
* Function: action                                                             *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::action()
{

	cout << "Entering function: action() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
	int errors = 0;
	//check if current token is in first and follows of respective


	//do specific rule related procedure


	return errors;

}


/*******************************************************************************
* Function: any_other_token                                                          *
*                                                                              *
* Parameters:                                                                  *
* Return value:                                                                *
* Description: This function will                                              *
*******************************************************************************/
int SyntacticalAnalyzer::any_other_token()
{
	
cout << "Entering function: any_other_token() with current token: " << lex->GetTokenName(token) << endl; //enter funct name
int errors = 0;
//check if current token is in first and follows of respective


//do specific rule related procedure


return errors;

}





