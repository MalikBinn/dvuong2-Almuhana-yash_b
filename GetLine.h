#ifndef GetLine_h
#define GetLine_h
/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 */
//****************************************************************************************
//	INCLUDE FILES
#include	<iostream>
#include	<string>

//! std namespace is used in this file.
/*!
  \namespace std
*/
using namespace std;

//****************************************************************************************
//	CONSTANT DEFINITIONS

//****************************************************************************************
//	CLASSES, TYPEDEFS AND STRUCTURES

//****************************************************************************************
//	FUNCTION PROTOTYPES
class GetThis{
	public:
//! A GetLine function, which takes two arguments and return a boolean variable.
/*!
  A function to read a line from the document until new line character is found.
  \param stream istream& type variable which tells the name of the file stream from which text is read
  \param text string&  type variable where read line is to be stored
  \return a flag which shows whether read operation is successful or not
  \sa 
*/
bool	GetLine(istream& stream, string& text);
//! A GetLine function, which takes three arguments and return a boolean variable.
/*!
  A function to read a line from the document until character is delimeters is encountered.
  \param stream istream& type variable which tells the name of the file stream from which text is read
  \param text string&  type variable where read line is to be stored
  \param delimiter const string& type variable which represents the sets of delimeter characters
  \return a flag which shows whether read operation is successful or not
  \sa 
*/
bool	GetLine(istream& stream, string& text, const string& delimiter);
}
#endif
