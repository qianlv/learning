/*
 * =====================================================================================
 *
 *       Filename:  text_query.h
 *
 *    Description:  Text Query
 *
 *        Version:  1.0
 *        Created:  2016年01月07日 15时56分31秒 CST
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
#include <fstream>
using std::ifstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <set>
using std::set;

#include <memory>
using std::shared_ptr;
using std::make_shared;

class QueryResult;

class TextQuery
{
public:
    using line_no = vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

class QueryResult
{
friend ostream& print(ostream&, const QueryResult&);
public:
    using line_no = vector<string>::size_type;
    using ResultIter = set<line_no>::iterator;
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f) :
        sought(s), lines(p), file(f) { }
    ResultIter begin() const { return lines->begin(); }
    ResultIter end() const { return lines->end(); }
    shared_ptr<vector<string>> get_file() const { return file; }
private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;
};
