/********************************************************************************************************
* File:              string_operator.h                                              
* Author:            Hexiang                                     | Boris Jeremic,                       *
* Date:              2017-02-02 18:56:11                         | University of California, Davis,95616*
* Description:       #############                               | California                           *
* Rev:               Version 1                                   | jeremic@ucdavis.edu                  *
* Email:             hexwang@ucdavis.edu                         | Computational Geomechanics Group     *
* * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * 
*                           Last Modified time: 2017-03-28 13:10:47                                     *            
*  * * * * * * * * * * * *  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *         
* The copyright to the computer program(s) herein is the property of Hexiang Wang and Boris Jeremic     *
* The program(s) may be used and/or copied only with written permission of Hexiang Wang or in accordance* 
* with the terms and conditions stipulated in the agreement/contract under which the program have been  *
* supplied.                                                                                             *
*********************************************************************************************************/
#ifndef STRING_OPERATOR_H
#define STRING_OPERATOR_H
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <streambuf>


using namespace std;
class string_operator
{
	public:
		string_operator();
		~string_operator();
		string_operator(const string& str);
		std::vector<string> string_extractor(string& s1, string opening_flag, string closing_flag);
		std::vector<string> string_extractor_with_spaces(string& s1, string opening_flag, string closing_flag);
		string delete_space(string& s2);
		string get_string_component(string::iterator it);
		string get_string();
		std::regex_iterator<std::string::iterator> search_reg(std::regex e);
		void replace_reg(std::regex e, string& replace_str);
		void readfile2string(string Dir);
		void set_string(string& str);
		string balanced_extractor(string& s1, string& opening_flag, string& closing_flag);    //s1 is the beginning string before opening_flag
		void balanced_replace(string& insert_str, string& s1, string& opening_flag, string& closing_flag);   //s1 is the beginning string before opening_flag
		std::vector<string> string_separator(string& s1, string separator);
		string match_reg(std::regex e, std::regex_iterator<std::string::iterator> it, int component_index);   //index begins from 0; 0 corresponds to the whole matched string

	private:
		string s;

};
#endif