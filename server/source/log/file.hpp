#ifndef LOGFILE_H
#define LOGFILE_H
#include <iostream>
#include <fstream>

class file
{
  public:
    static void write()
    {
        std::ofstream out("out.txt");
        if (out.is_open())
        {
            out << "This is a line.\n";
            out << "This is another line.\n";
            out.close();
        }
    }
};
#endif //LOGFILE_H
