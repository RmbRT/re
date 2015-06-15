#ifndef __re_file_inifile_hpp_defined
#define __re_file_inifile_hpp_defined

#include "../types.hpp"

#include <map>

namespace re
{
	namespace file
	{
		namespace IniFile
		{
			RE_ENUM (EntryValue)
			{
				Float,
				Int,
				Bool,
				String
			};
			class Entry
			{	friend class Section; friend class IniFile;
				string comment;
				string key;
				EntryValue value_t;
				union
				{
					int Int;
					float Float;
					bool Bool;
				} parsed;
				string content;
			public:
				Entry();
				Entry(const string &key, const string &parsed);
				Entry(const string &key, const string &content, int parsed);
				Entry(const string &key, const string &content, float parsed);
				Entry(const string &key, const string &content, bool parsed);

				EntryValue valueType() const;

				bool toFloat(float &out) const;
				bool toInt(int &out) const;
				bool toBool(bool &out) const;
				bool toString(string &out) const;
			};
			class Section
			{	friend class IniFile;
				string _name;
				std::vector<Entry> _entries;
				string _comment;
			public:
				const string &name() const;
				const std::vector<Entry> &entries() const;

				const Entry * findEntry(const string &name) const;
				const Entry * operator[](const string &name) const;
			};

			class IniFile
			{
				Section Unnamed;
				std::vector<Section> sections;

				
				int section(const std::vector<string> &lines, const int current_line, Section &out);
				int entry(const std::vector<string> &lines, const int current_line, Entry &out);
				int comment(const std::vector<string> &lines, const int current_line, string &out);

			public:
				/*pass "" for the unnamed section.*/
				Section * findSection(const string &name) const;
				/*pass "" for the unnamed section.*/
				Section * operator[](const string &name) const;
				Section * unnamedSection() const;

				bool load(const string &filename);
			};

		}

		IniFile::IniFile loadIniFile(const string &filename);
	}
}

#endif