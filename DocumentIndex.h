#ifndef	DocumentIndex_h
#define	DocumentIndex_h

//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<fstream>
#include    <sstream>
#include	<map>
#include	<set>
#include	<string>

using namespace std;

//****************************************************************************************
//
//	CONSTANT DEFINITIONS
//
//****************************************************************************************

//****************************************************************************************
//
//	CLASSES, TYPEDEFS AND STRUCTURES
//
//****************************************************************************************
typedef	string::size_type	StringSize;

//!  DocumentFile Class. 
/*!
  A class for the document File.
*/
class	DocumentFile
{
	public:
		//! A constructor.
		/*!
		  A constructor for DocumentFile class. It sets pagenumber_ to 1.
		*/
		DocumentFile() : pageNumber_(1) { }
		
		//! A close function which doesnt takes any arguments.
		/*!
		  A function to close the document.
		  \sa file_.close() and file_.clear()
		*/
		void	Close();
		
		//! A public function which takes no argument and return an integer.
		/*!
		  A function to get the page number.
		  \return An integer containing the current page number
		  \sa none
		*/
		int		GetPageNumber();			//	Returns the current pge number.

		//! A public function which takes no argument and return a string.
		/*!
		  A function to get the next legal word not on the exception list.
		  \return A string containing the next word or empty string if there are no more words.
		  \sa ispunct(), string.at(), string.substr(), string.begin(), string.end() and string.length()
		*/
		string	GetWord();					//	Returns the next legal word not on the exception list;
											//	returns an empty string if there are no more words in
											//	the line.

		//! A public member which takes one argument, and return a boolean variable.
		/*!
		  \param name an string& argument, which specifies the name of the file from where exclusions are to be loaded.
		  \return A flag which specifies that whether laoding was successful or not.
		  \sa DocumentFile(), Close(), GetPageNumber() and GetWord()
		*/
		bool	LoadExclusions(const string& name);	//	Loads a list of words to be excluded from the index
													//	from a file of the given name.

		//! A public function to open the document file.
		/*!
		  \param name an string& argument, which specifies the name of the file to be opened.
		  \return A flag which specifies that whether file opening was successful or not.
		  \sa 
		*/
		bool	Open(const string& name);	//	Opens a document file of the given name.

		//! A public function to read the next line from the document file.
		/*!
		  \return A flag which specifies that whether file read was successful or not.
		  \sa 
		*/
		bool	Read();						//	Reads the next line of the document file, skipping over
											//	the double empty lines that mark page separations.
											//	Returns false if there are no more lines in the file.

		//! a set of string data type.
		/*!
		  \typedef MySet 
		*/
        typedef set<string> MySet;
		//! MySetIterator an iterator for MySet data type.
		/*!
		  \typedef MySetIterator
		*/
        typedef MySet::iterator MySetIterator;
		//! a public variable of MySet data type to hold the words.
		/*!
		  \var mySet 
		*/
        MySet mySet;
		//!  a public variable of MySetIterator type used as a pointer for mySet.
		/*!
		  \var mySetIterator
		*/
        MySetIterator mySetIterator;

	private:
		//!  used to hold the start postion of the word.
		/*!
		  \var beginPosition_
		*/
		StringSize	beginPosition_;
		//!  used to hold the information for the opened file.
		/*!
		  \var file_
		*/
		fstream		file_;
		//!  used to hold the current page number.
		/*!
		  \var pageNumber_
		*/
		int			pageNumber_;
		//!  used to hold the read text from the file.
		/*!
		  \var text_
		*/
		string		text_;
		//!  used to hold a line read from the file.
		/*!
		  \var line_stream_
		*/
		stringstream   line_stream_;


};
//!  DocumentIndex Class. 
/*!
  A class for the document indexing.
*/
class	DocumentIndex
{
	public:
		//! A public function to create an index for the given filename.
		/*!
		  \param documentFile an DocumentFile& argument, which specifies document to be indexed.
		  \return none.
		  \sa 
		*/
		void	Create(DocumentFile& documentFile);	//	Creates an index for the given document file.
		//! A public function to show the current document index.
		/*!
		  \param stream an ostream& argument, which specifies the stream where the index to be write.
		  \return none.
		  \sa 
		*/
		void	Show(ostream& stream);
		//! A public function to wrtie the current index to a file.
		/*!
		  \param indexFile an ostream& argument, which specifies file stream where index is to be wrote.
		  \return none.
		  \sa 
		*/
		void	Write(ostream& indexFile);	//	Writes the index to the given file.
											//	The argument is a stream so that this function
											//	can be called to wrtite its output to cout for
											//	test purposes.

	private:
		//! MyMap a map is defined for a string and a set of integer types.
		/*!
		  \typedef MyMap
		*/
	    typedef map<string,set<int>> MyMap;
		//! MyMapIterator an iterator for MyMap data type.
		/*!
		  \typedef MyMapIterator
		*/
        typedef MyMap::iterator MyMapIterator;
		//! a map to hold the document index.
		/*!
		  \var myMap
		*/
        MyMap myMap;
		//! an iterator for the document index Map(myMap).
		/*!
		  \var myMapIterator
		*/
        MyMapIterator myMapIterator;

		//! MyMap2 a map is defined for storing the count for each word in the index.
		/*!
		  \typedef MyMap2
		*/
        typedef map<string,int> MyMap2;
		//! an iterator for the MyMap2 datatype.
		/*!
		  \typedef MyMapIterator2
		*/
        typedef MyMap2::iterator MyMapIterator2;
		//! a map of MyMap2 type to hold the count for each word.
		/*!
		  \var myMap2
		*/
        MyMap2 myMap2;
		//! an iterator for myMap2.
		/*!
		  \var myMapIterator2
		*/
        MyMapIterator2 myMapIterator2;

};

#endif
