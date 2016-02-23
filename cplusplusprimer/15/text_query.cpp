/*
 * =====================================================================================
 *
 *       Filename:  text_query.cpp
 *
 *    Description:  Class TextQuery
 *
 *        Version:  1.0
 *        Created:  2016年01月07日 16时00分49秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <fstream>
#include <sstream>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::ostream;

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
#include <algorithm>
#include <cctype>


#include "text_query.h"

TextQuery::TextQuery(ifstream &is): file(new vector<string>)
{
    string text;
    while (getline(is, text))
    {
        file->push_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while (line >> word)
        {
            for (auto iter = word.begin(); iter != word.end(); ++iter)
            {
                if (ispunct(*iter))
                {
                    iter = word.erase(iter);
                    --iter;
                }
            }
#ifdef DEBUG
            cout << word << endl;
#endif
            auto &lines = wm[word];
            if (!lines)
                lines.reset(new set<line_no>);
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " " 
       << (qr.lines->size() > 1 ? "times" : "time") << endl;
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ") "
           << *(qr.file->begin() + num) << endl;
    return os;
}

ostream& operator<< (ostream &os, const QueryResult &qr)
{
    return print(os, qr);
}

ostream& operator<< (ostream &os, const Query &query)
{
    return os << query.rep();
}

inline Query operator~ (const Query &operand)
{
    return shared_ptr<QueryBase>(new NotQuery(operand));
}

Query operator| (const Query &l, const Query &r)
{
    cout << "Query operato|(l, r)" << endl;
    return shared_ptr<QueryBase>(new OrQuery(l, r));
}

Query operator& (const Query &l, const Query &r)
{
    cout << "Query operato&(l, r)" << endl;
    return shared_ptr<QueryBase>(new AndQuery(l, r));
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
    auto result = query.eval(text);
    auto ret_lines = make_shared<set<line_no>>();
    line_no sz = result.get_file()->size();
    auto beg = result.begin(), end = result.end();
    for (size_t n = 0; n != sz; ++n)
    {
        if (beg == end || *beg != n)
            ret_lines->insert(n);
        else if (beg != end)
            ++beg;
    }

    return QueryResult(rep(), ret_lines, result.get_file());
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>();
    std::set_intersection(left.begin(), left.end(),
                          right.begin(), right.end(),
                          std::inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left.get_file());
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), right.end());
    return QueryResult(rep(), ret_lines, left.get_file());
}

int main()
{
    ifstream in("textquery.txt");
    TextQuery text(in);
    Query q = (Query("fiery") & Query("bird")) | Query("wind");
    QueryResult qr = q.eval(text);
    cout << qr << endl;

    Query q1 = Query("hair") & Query("Alice"); 
    cout << q1.eval(text) << endl;

    Query q2 = ~Query("Alice");
    cout << q2.eval(text) << endl;

    Query q3 = Query("hair") | Query("Alice"); 
    cout << q3.eval(text) << endl;

    Query q4 = Query("hair") | Query("----"); 
    cout << q4.eval(text) << endl;

    Query q5 = Query("=---") | Query("Alice"); 
    cout << q5.eval(text) << endl;
}

