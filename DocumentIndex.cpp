//!  Document Index Implementation. 
/*!
  Implementation for document index.
*/

//****************************************************************************************
//
//	INCLUDE FILES
//
//****************************************************************************************
#include	<fstream>
#include	<iostream>
#include	<string>

// #include	<unistd.h>

#include	"DocumentIndex.h"
#include	"GetLine.h"

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

//****************************************************************************************
//
//	PUBLIC DATA
//
//****************************************************************************************

//****************************************************************************************
//
//	PRIVATE DATA
//
//****************************************************************************************

//****************************************************************************************
//
//	FUNCTION PROTOTYPES
//
//****************************************************************************************

//****************************************************************************************
//
//	DocumentFile::Close
//
//****************************************************************************************
	//! MySetIterator an iterator for MySet data type.
	/*!
	  \fn DocumentFile::Close()
	*/
void	DocumentFile::Close()
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	file_.close();
	file_.clear();

	return;
}

//****************************************************************************************
//
//	DocumentFile::GetPageNumber
//
//****************************************************************************************
	//! MySetIterator an iterator for MySet data type.
	/*!
	  \fn DocumentFile::GetPageNumber()
	*/
int	DocumentFile::GetPageNumber()
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS

	return(pageNumber_);
}

//****************************************************************************************
//
//	DocumentFile::GetWord
//
//****************************************************************************************
	//! MySetIterator an iterator for MySet data type.
	/*!
	  \fn DocumentFile::GetWord()
	*/
string	DocumentFile::GetWord()
{
	//************************************************************************************
	//	LOCAL DATA
	string	word,nextword;
	bool success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
    std::string str = " .,:;?!()\"'";
    while(1){
        success = GetLine(line_stream_,word, " ");

        if(!success){
            word = "";
            break;
        }
        else if(word.empty())
            continue;
        else{
            if(ispunct(word.at(0)))
                word = word.substr(1, word.length()-1);
            if(word.empty())
                continue;
            if(ispunct(word.at(word.length()-1)))
                word = word.substr(0, word.length()-1);
            if(word.length()>1)
                if(word.at(word.length()-2)== '\'' && word.at(word.length()-1)== 's')
                    word = word.substr(0, word.length()-2);
            if(word.empty())
                continue;

            mySetIterator= mySet.find(word);
            if(mySetIterator == mySet.end()){
                string::iterator it;
                for(it= word.begin();it!=word.end();it++)
                {
                    if(!isalpha(*it))
                        break;

                }
                if(it == word.end())
                    break;
            }

        }
    }
	/*
	if(success == true){

        mySetIterator= mySet.find(word);
        while(mySetIterator != mySet.end()){
            if(word.empty())
            {
                success = GetLine(line_stream_,word, str);
                if(!success)break;
                mySetIterator= mySet.find(word);
            }
            else{

                string::iterator it;
                for(it= word.begin();it!=word.end();it++)
                {
                    if(!isalpha(*it))
                        break;
                }
                if(it != word.end())
                {
                    success = GetLine(line_stream_,word, str);
                    if(!success)break;
                    mySetIterator= mySet.find(word);
                }
            }

        }
	}
	else
        word = "";
    */
	return(word);
}

//****************************************************************************************
//
//	DocumentFile::LoadExclusions
//
//****************************************************************************************
	//! MySetIterator an iterator for MySet data type.
	/*!
	  \fn DocumentFile::LoadExclusions
	*/
bool	DocumentFile::LoadExclusions(const string& name)
{
	//************************************************************************************
	//	LOCAL DATA
	bool	success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	fstream file2_;
	file2_.open(name.c_str(), ios::in);
	if (!file2_.fail())
	{
		//	You may add any useful initialization here.
        string word;
        while(GetLine(file2_, word))
        {
            mySetIterator = mySet.find(word);
            if(mySetIterator == mySet.end())
                mySet.insert(word);
        }
        file2_.close();
		success = true;
	}
	else
	{
		success = false;
	}
	return(success);
}

//****************************************************************************************
//
//	DocumentFile::Open
//
//****************************************************************************************
	//! MySetIterator an iterator for MySet data type.
	/*!
	  \fn DocumentFile::Open
	*/
bool	DocumentFile::Open(const string& name)
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	file_.open(name.c_str(), ios::in);
	if (!file_.fail())
	{
		//	You may add any useful initialization here.

		return(true);
	}
	else
	{
		return(false);
	}
}

//****************************************************************************************
//
//	DocumentFile::Read
//
//****************************************************************************************
	//! MySetIterator an iterator for MySet data type.
	/*!
	  \fn DocumentFile::Read
	*/
bool	DocumentFile::Read()
{
	//************************************************************************************
	//	LOCAL DATA
	bool	success;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	success = GetLine(file_,text_);
    if(text_.compare("")==0)
        {
        success = GetLine(file_,text_);
        if(text_.compare("")==0)
        {
            success = GetLine(file_,text_);
            pageNumber_++;
        }
    }

    line_stream_.str(text_);
    line_stream_.clear();

	return(success);
}

//****************************************************************************************
//
//	DocumentIndex::Create
//
//****************************************************************************************
	//! MySetIterator an iterator for MySet data type.
	/*!
	  \fn DocumentIndex::Create
	*/
void	DocumentIndex::Create(DocumentFile& documentFile)
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS

	bool			success;

	string			word;

	//************************************************************************************
	//	EXECUTABLE STATEMENTS

	while (true)
	{
		success = documentFile.Read();
		if (!success)
		{
			break;
		}

		while (true)
		{
			word = documentFile.GetWord();
			if (!word.empty())
			{
			    myMapIterator2 = myMap2.find(word);
			    if(myMapIterator2 != myMap2.end())
                {
                    myMap2[word] = myMap2[word] + 1;
                    if(myMap2[word]<=10){
                        myMapIterator = myMap.find(word);
                        myMap[word].insert(documentFile.GetPageNumber());
                    }
                    else{
                        documentFile.mySet.insert(word);
                        myMap2.erase(myMapIterator2);
                        myMapIterator = myMap.find(word);
                        myMap.erase(myMapIterator);
                    }
                }
                else{
                    myMap2.insert(pair<string,int>(word, 1));
                    set<int> mySet;
                    mySet.insert(documentFile.GetPageNumber());
                    myMap.insert(pair<string, set<int>>(word, mySet));
                }
			}
			else
			{
				break;
			}
		}
	}

	return;
}

//****************************************************************************************
//
//	DocumentIndex::Write
//
//****************************************************************************************
	//! MySetIterator an iterator for MySet data type.
	/*!
	  \fn DocumentIndex::Write
	*/
void	DocumentIndex::Write(ostream& indexStream)
{
	//************************************************************************************
	//	LOCAL DATA

	//************************************************************************************
	//	EXECUTABLE STATEMENTS
	for(myMapIterator = myMap.begin(); myMapIterator != myMap.end();myMapIterator++)
    {
        indexStream << myMapIterator->first;
        set<int> mySet = myMapIterator->second;
        set<int>::iterator it;
        for(it = mySet.begin();it != mySet.end();it++)
        {
            if(it == mySet.begin())
                indexStream << " "<<*it;
            else
                indexStream << ", "<<*it;
        }
        indexStream <<endl;
    }

	return;
}
