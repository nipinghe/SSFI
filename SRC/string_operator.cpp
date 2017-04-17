/********************************************************************************************************
* File:              string_operator.cpp                                              
* Author:            Hexiang                                     | Boris Jeremic,                       *
* Date:              2017-02-04 20:16:04                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-03-28 13:09:33                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#include "string_operator.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>
#include <streambuf>
using namespace std;

string_operator::string_operator(){}
string_operator::string_operator(const string& str):s{str} {}
string_operator::~string_operator(){}

// this is for no nested openning flag and closing flag
vector<string> string_operator::string_extractor(string& s1, string opening_flag, string closing_flag)
{
	int index=0;
	vector<string> ret;
	string::iterator it=s1.begin();
	string::iterator opening_flag_it=s1.end();
	string temp_string;
	for (; it!=s1.end(); ++it)
	{
	// convert a char to string
		// stringstream ss;
		// string temp;
		// ss<<(*it);
		// ss>>temp;	
		string temp=get_string_component(it);
	//####################### 
		if(temp==opening_flag)
		{
			index=index+1;
			opening_flag_it=it;
			
		}
		if((it>opening_flag_it)&&(temp!=closing_flag))
		{
			temp_string=temp_string+temp;

		}
		if(temp==closing_flag)
		{
			temp_string=delete_space(temp_string);    // this line means our extraction output without spaces.
			ret.push_back(temp_string);
			temp_string="";
			opening_flag_it=s1.end();
		}
	}

	return ret;
}

vector<string> string_operator::string_extractor_with_spaces(string& s1, string opening_flag, string closing_flag)
{
	int index=0;
	vector<string> ret;
	string::iterator it=s1.begin();
	string::iterator opening_flag_it=s1.end();
	string temp_string;
	for (; it!=s1.end(); ++it)
	{
	// convert a char to string
		// stringstream ss;
		// string temp;
		// ss<<(*it);
		// ss>>temp;	
		string temp=get_string_component(it);
	//####################### 
		if(temp==opening_flag)
		{
			index=index+1;
			opening_flag_it=it;
			
		}
		if((it>opening_flag_it)&&(temp!=closing_flag))
		{
			temp_string=temp_string+temp;

		}
		if(temp==closing_flag)
		{
			// temp_string=delete_space(temp_string);    // comment this line means our extraction output with spaces.
			ret.push_back(temp_string);
			temp_string="";
			opening_flag_it=s1.end();
		}
	}

	return ret;
}

std::vector<string> string_operator::string_separator(string& s1, string separator)   
{
	vector<string> ret;
	string temp_string="";
	string::iterator it=s1.begin();
	for(; it<s1.end(); it++)
	{
		while((get_string_component(it)!=separator)&&(it<s1.end()))
		{
			temp_string=temp_string+get_string_component(it);
			it=it+1;
		}

		ret.push_back(temp_string);
		temp_string="";
	}
	return ret;	
}



string string_operator::delete_space(string& s2)
{
	string ret;
	string::iterator it=s2.begin();
	for(; it<s2.end(); ++it)
	{
		string temp=get_string_component(it);
		if(temp!=" ")
			ret=ret+temp;
	}
	return ret;

}

string string_operator::get_string_component(string::iterator it)
{
	string ret;
	stringstream ss;
	ss<<(*it);
	// ss>>ret;     //Attention: if use this way to transfer stringstream to string, it cannot handle whitespace;
	ret=ss.str();
	return ret;
}

std::regex_iterator<std::string::iterator> string_operator::search_reg(std::regex e)
{
	std::regex_iterator<std::string::iterator> rit ( (this->s).begin(), (this->s).end(), e );
	return rit;
}

string string_operator::get_string()
{
	return (this->s);
}


void string_operator::replace_reg(std::regex e, string& replace_str)
{
	string replaced_string=std::regex_replace((this->s), e, replace_str);
	this->s=replaced_string;
}

void string_operator::readfile2string(string Dir)
{
	std::ifstream input(Dir);
	if (!input) 
		std::cerr << "Could not open the file!" << std::endl;
	else
	{
		string temp_s;
		input.seekg(0, std::ios::end);
		temp_s.reserve(input.tellg()); 
		input.seekg(0, std::ios::beg);
		temp_s.assign((std::istreambuf_iterator<char>(input)),std::istreambuf_iterator<char>());
		this->s=temp_s;
	};
}

string string_operator::balanced_extractor(string& s1, string& opening_flag, string& closing_flag)   //s1 is beginning string
{
	string ret="";
	std::size_t found = (this->s).find(s1);
	// cout<<(this->s)<<endl;
	if (found!=std::string::npos)
	{
		string::iterator it=s.begin()+found+s1.length();

		for(; it<(this->s).end(); ++it)
		{
			// cout<<(*it);
			if(get_string_component(it)==opening_flag)
			{
				it=it+1;
				int counter=1;
				while(counter>0)
				{
					ret=ret+(*it);
					if(get_string_component(it)==opening_flag)
					{
						counter=counter+1;
					}
					if(get_string_component(it)==closing_flag)
					{
						counter=counter-1;
					}
					it=it+1;
				}
				int str_len=ret.length();
				return ret.substr(0,str_len-1);
			}

		}
		return ret;

	}
	else
	{
		ret="NOT FOUND";// cout<<"could not find the string!!"<<s1<<endl;
		return ret;
	}

}


void string_operator::set_string(string& str)
{
	this->s=str;
}


string string_operator::match_reg(std::regex e, std::regex_iterator<std::string::iterator> it, int component_index)
{
	string temp= it->str();
	std::smatch sm;
	std::regex_match(temp,sm,e);
	string ret=sm[component_index];
	return ret;
}



void string_operator::balanced_replace(string& insert_str, string& s1, string& opening_flag, string& closing_flag)
{
	std::size_t found = (this->s).find(s1);
	
	if (found!=std::string::npos)
	{
		string::iterator it=s.begin()+found+s1.length();

		while(get_string_component(it)!=opening_flag)  //end this while loop while lead (*it)=opening_flag
		{
			it=it+1;
		}
		int insert_pos=it-s.begin()+1;
		int counter=1;
		it=it+1;
		while(counter>0)
		{
			(this->s).erase(it);
			if(get_string_component(it)==opening_flag)
			{
				counter=counter+1;
			}
			// it=it+1;                                        //Attention: every deletion will change the (*it) do not need to do it=it+1 
			if(get_string_component(it)==closing_flag)
			{
				counter=counter-1;
			}

		}
		(this->s).insert(insert_pos,insert_str);

	}
	else
	{
		cout<<"could not find the string!!"<<s1<<endl;
	}

}

