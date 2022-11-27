/* Jun Shao
 * 251258566
 * November 7
 * Header file containing member and function delcarations for ListMap
 */

#ifndef NOTEMAP_H
#define NOTEMAP_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Note.h"
#include "../Data.h"

class NoteMap : public Data {
    private:
        std::string username;
        std::unordered_map<std::string, Note> notes;
        std::unordered_map<std::string, Note> batchToDel;
        Database db;

    public:
        NoteMap(std::string username);
        ~NoteMap();
        void saveData();
        void delData();
        void loadData();
        void add(Note list);
        void del(Note list);
        Note get(std::string key);
        std::unordered_map<std::string, Note> getNotes();
};
#endif