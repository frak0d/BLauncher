#pragma once

// Licence : Apache 2.0
// Author  : Tanishq-Banyal
// Source  : github.com/Tanishq-Banyal/nini
// Changes : Made More QT Friendly (at performance cost)

#include <map>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdint>

#include <QtCore/QString>

namespace Ini
{

namespace Util
{
	char* ltrim(char* s)
	{
        while(std::isspace(*s)) s++;
		return s;
	}
	
	char* rtrim(char* s)
	{
        char* back = s + std::strlen(s);
        while(std::isspace(*--back));
		*(back+1) = '\0';
		return s;
	}
	
	char* trim(char* s)
	{
		return rtrim(ltrim(s));
	}
}

class Section
{
friend class File;

private:
	std::map<QString, QString> entries;
	
public :
	QString& operator [] (const QString& key)
	{
		return entries[key];
	}
};

class File
{
private:
	QString fpath;
	std::map<QString, Section> sections;
	
public :
	Section& operator [] (const QString& section)
	{
		return sections[section];
	}
	
	bool load(const QString& path)
	{
		Section* current_section;
		FILE* fp = fopen(path.toStdString().c_str(), "r");
		
		if (!fp) return false;
		
		char key[4096]{'\0'};
		char val[4096]{'\0'};
		char line[10000]{'\0'};
		char title[4096]{'\0'};
		
		using namespace Ini::Util;
		
		while(fgets(line, sizeof(line), fp))
		{
			if (line[0] == ';' or line[0] == '#'); // ignore comments
			
			else if (1 == sscanf(line, "[%[^]]]", title))
			{
				current_section = &sections[trim(title)];
			}
			else if (2 == sscanf(line, "%[^=]=%[^\n]", key, val))
			{
				(*current_section)[trim(key)] = trim(val);
			}
		}
		
		std::fclose(fp); return true;
	}
	
	bool save(const QString& path)
	{
		FILE* fp = fopen(path.toStdString().c_str(), "w");
		if (!fp) return false;
		
		QString line;
		
		for (auto& [title, section] : sections)
		{
			line = "\n["+title+"]\n";
			std::fprintf(fp, "%s\n", line.toStdString().c_str());
			
			for (auto& [key, value] : section.entries)
			{
				line = key+" = "+value;
				std::fprintf(fp, "%s\n", line.toStdString().c_str());
			}
		}
		
		std::fclose(fp); return true;
	}

	void clear()
	{
		sections.clear();
	}
	
	File() = default;

	File(const QString& path) : fpath(path)
	{
		load(fpath);
	}
	
	~File()
	{
		if (!fpath.isEmpty()) save(fpath);
	}
};

}
