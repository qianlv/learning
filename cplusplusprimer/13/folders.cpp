/*
 * =====================================================================================
 *
 *       Filename:  folders.cpp
 *
 *    Description:  Class Message Class Folder
 *
 *        Version:  1.0
 *        Created:  2016年01月12日 11时02分48秒 CST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  qianlv (), qianlv7@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */


#include <algorithm>
#include <utility>
#include <string>
using std::string;
#include <set>
using std::set;

#include "folders.h"

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_to_folders(const Message &m)
{
    for (auto f : m.folders)
        f->addMsg(this);
}

void Message::remove_from_folders()
{
    for (auto f : folders)
        f->remMsg(this);
}

void move_folders(Message *m)
{
    if (m)
    {
        folders = std::move(m->folders);
        for (auto f : folders)
        {
            f->remMsg(m);
            f->addMsg(this);
        }
        m->folders.clear();
    }
}

Message::Message(const string &cts /* =  string() */)
    : contents(cts)
{
}

Message::Message(const Message &m):
    contents(m.contents), folders(m.folders)
{
    add_to_folders(m);
}

Message::Message(Message &&m) :
    contents(std::move(m.contents)) 
{
    move_folders(&m);
}

Message::~Message()
{
    remove_from_folders();
}

Message& Message::operator= (const Message &rhs)
{
    remove_from_folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}

Message& Message::operator= (Message &&m) 
{
    if (this != &rhs)
    {
        remove_from_folders();
        contents = std::move(m.contents);
        move_folders(&m);
    }
    return *this;
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    for (auto f : lhs.folders)
        f->remMsg(&lhs);
    for (auto f : rhs.folders)
        f->remMsg(&rhs);

    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);

    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

Folder::Folder(const Folder &f) : msgs(f.msgs)
{
    add_to_messages(*this);
}

Folder::~Folder()
{
    remove_from_messages();
}

Folder& Folder::operator= (const Folder &rhs)
{
    remove_from_messages();
    msgs = rhs.msgs;
    add_to_messages(*this);
    return *this;
}

void Folder::add_to_messages(const Folder &f)
{
    for (auto m : f.msgs)
        m->add_folder(this);
}

void Folder::remove_from_messages()
{
    for (auto m : msgs)
        m->rem_folder(this);
}

void swap(Folder &lhf, Folder &rhf)
{
    using std::swap;
    for (auto m : lhf.msgs)
        m->rem_folder(&lhf);
    for (auto m : rhf.msgs)
        m->rem_folder(&rhf);

    swap(lhf.msgs, rhf.msgs);

    for (auto m : lhf.msgs)
        m->add_folder(&lhf);
    for (auto m : rhf.msgs)
        m->add_folder(&rhf);
}

int main()
{
    Message m1("hello world");
    Folder  f1;
    m1.save(f1);
    f1.print_debug();
}
