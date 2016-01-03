/*
 * =====================================================================================
 *
 *       Filename:  generic_algorithm.h
 *
 *    Description:  generic_algorithm.h
 *
 *        Version:  1.0
 *        Created:  2016年01月01日 16时33分25秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
using std::ostream;

#include <string>
using std::string;

#include <vector>
using std::vector;

bool isShorter(const string &s1, const string &s2);
void elimDups(vector<string> &words);
void biggies(vector<string> &words, vector<string>::size_type sz);
void biggies(vector<string> &words, vector<string>::size_type sz, ostream &os, char c);
void biggies_p(vector<string> &words, vector<string>::size_type sz);
void biggies_sp(vector<string> &words, vector<string>::size_type sz);
void biggies_bp(vector<string> &words, vector<string>::size_type sz);
bool check_size(const string &s, string::size_type sz);
