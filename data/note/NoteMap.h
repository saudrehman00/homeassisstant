/* Jun Shao
 * 251258566
 * November 7
 * Header file containing member and function delcarations for ListMap
 */

#ifndef NOTEMAP_H
#define NOTEMAP_H

#include <unordered_map>
#include <string>
#include "Note.h"
#include "../Data.h"

class NoteMap : public Data {
    private:
        std::unordered_map<std::string, Note> notes;
        Database db;
        // pointer to user

    public:
        NoteMap();
        ~NoteMap();
        void linkProfile(std::string profileName);
        void saveData(std::string username);
        void delData(std::string username);
        void add(Note list);
        void del(Note list);
        Note get(std::string key);
};
#endif