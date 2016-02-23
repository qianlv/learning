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
friend ostream& operator<< (ostream &, const QueryResult &);

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

class QueryBase
{
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~QueryBase() = default;

private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual string rep() const = 0;
};

class WordQuery: public QueryBase
{
    friend class Query;
private:
    WordQuery(const string &s): query_word(s) 
    {
#ifdef DEBUG
        cout << "WordQuery(const string &s): query_word(s)" << endl;
#endif
    }
    QueryResult eval(const TextQuery &t) const
    {
        return t.query(query_word);
    }
    string rep() const
    {
        return query_word;
    }
    string query_word;
};


class Query
{
    friend Query operator~ (const Query &);
    friend Query operator| (const Query &, const Query &);
    friend Query operator& (const Query &, const Query &);
    friend ostream& operator<< (ostream &, const Query &);

public:
    Query(const string &s): q(new WordQuery(s)) 
    {
#ifdef DEBUG
        cout << "Query(const string &s): q(new WordQuery(s))" << endl;
#endif
    }
    QueryResult eval(const TextQuery &t) const
    {
        return q->eval(t);
    }

    string rep() const
    {
        return q->rep();
    }

private:
    Query(shared_ptr<QueryBase> query) : q(query)
    {
#ifdef DEBUG
        cout << "Query(shared_ptr<QueryBase> query)" << endl;
#endif
    }
    shared_ptr<QueryBase> q;
};

ostream& operator<< (ostream &, const Query &);

class NotQuery: public QueryBase
{
    friend Query operator~ (const Query &);
private:
    NotQuery(const Query &q): query(q)
    {
#ifdef DEBUG
        cout << "NotQuery(const Query &q): query(q)" << endl;
#endif
    }
    string rep() const
    {
        return "~(" + query.rep() + ")";
    }
    QueryResult eval(const TextQuery&) const;
    Query query;
};

class BinaryQuery: public QueryBase
{
protected:
    BinaryQuery(const Query &l, const Query &r, string s):
        lhs(l), rhs(r), opSym(s) 
    {
#ifdef DEBUG
        cout << "BinaryQuery(const Query &l, const Query &r, string s):"
                 " lhs(l), rhs(r), opSym(s) " << endl;
#endif
    }
    string rep() const
    {
        return "(" + lhs.rep() + " " + opSym
                + " " + rhs.rep() + ")";
    }
    Query lhs, rhs;
    string opSym;
};

class AndQuery: public BinaryQuery
{
    friend Query operator& (const Query &, const Query &);
    AndQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "&") 
    {
#ifdef DEBUG
        cout << "AndQuery(const Query &left, const Query &right):"
                " BinaryQuery(left, right, \"&\") " << endl;
#endif
    }
    QueryResult eval(const TextQuery &) const;
};

class OrQuery: public BinaryQuery
{
    friend Query operator| (const Query &, const Query &);
    OrQuery(const Query &left, const Query &right):
        BinaryQuery(left, right, "|") 
    {
#ifdef DEBUG
        cout << "OrQuery(const Query &left, const Query &right):"
                " BinaryQuery(left, right, \"|\") " << endl;
#endif
    }
    QueryResult eval(const TextQuery &) const;
};

Query operator~ (const Query &);
Query operator| (const Query &, const Query &);
Query operator& (const Query &, const Query &);
ostream& operator<< (ostream &, const Query &);
ostream& operator<< (ostream &, const QueryResult &);
