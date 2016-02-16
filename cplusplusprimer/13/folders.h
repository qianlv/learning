/*
 * =====================================================================================
 *
 *       Filename:  folders.h
 *
 *    Description:  Class Message, Class Folder
 *
 *        Version:  1.0
 *        Created:  2016年01月11日 23时03分24秒 CST
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef FOLDERS_H_
#define FOLDERS_H_

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>
#include <utility>
#include <string>
using std::string;
#include <set>
using std::set;

class Folder;
class Message
{
    friend class Folder;
    friend void swap(Message &lhs, Message &rhs);
    friend void swap(Folder &, Folder &);
public:
    explicit Message(const string &str = string());
    Message(const Message &);
    Message(Message &&);
    Message& operator= (const Message &);
    Message& operator= (Message &&);
    ~Message();
    
    // add/remove this Message from the specified Folder's set of message;
    void save(Folder&);
    void remove(Folder&);

    void print_debug()
    {
        cout << contents << endl;
    }

private:
    string contents;
    set<Folder*> folders;
    void add_to_folders(const Message&);
    void remove_from_folders();

    void move_folders(Message *);

    void add_folder(Folder *f) { folders.insert(f); }
    void rem_folder(Folder *f) { folders.erase(f); }
};

class Folder
{
    friend class Message;
    friend void swap(Folder &, Folder &);
    friend void swap(Message &lhs, Message &rhs);

public:
    Folder() = default;
    Folder(const Folder &);
    Folder& operator= (const Folder &);
    ~Folder();

    void print_debug()
    {
        for (auto m : msgs)
            m->print_debug();
    }

private:
    set<Message*> msgs;
    
    void add_to_messages(const Folder &);
    void remove_from_messages();
    void addMsg(Message *m) { msgs.insert(m); }
    void remMsg(Message *m) { msgs.erase(m); }
};

void swap(Message &lhs, Message &rhs);
void swap(Folder &, Folder &);

#endif // FOLDERS_H_
