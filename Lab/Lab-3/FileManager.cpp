//
// Created by Matteo Bonfadini on 14/01/24.
//

#include "FileManager.h"

// Matteo
const FileManager::table_type& FileManager::parse_file (const std::string& filename, char d)
{
    fields.clear();
    std::ifstream ifs(filename);

    if (ifs) { // if I managed to open it
        std::string line;
        while (getline(ifs, line)) {
            row_type row;
            std::istringstream current_line(line);
            std::string info;
            while (getline(current_line, info, d)) {
                row.push_back(info);
            }
            fields.push_back(row);
        }
    } else {
        std::cerr << "ERROR: cannot open file " << filename << std::endl;
    }
    return fields;
}

// Lorenzo
const FileManager::table_type& FileManager::parse_file2 (const std::string& filename, char d)
{
    fields.clear();
    std::ifstream ist {filename};

    if (!ist)
        std::cerr << "Can’t open input file " << filename << std::endl;

    std::string line;
    unsigned i=0;
    while ( getline(ist, line) ) {
        std::istringstream record(line);
        std::string info;
        row_type a;
        fields.push_back(a);
        while (getline(record, info, d)) {
            fields[i].push_back(info);
        }
        ++i;
    }
    return fields;
}