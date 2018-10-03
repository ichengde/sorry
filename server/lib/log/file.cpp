#include "sorry/log/file.hpp"


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