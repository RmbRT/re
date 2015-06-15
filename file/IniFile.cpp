#include "IniFile.hpp"

#include <fstream>
#include <vector>

namespace re
{
	namespace file
	{
		namespace IniFile
		{
			Entry::Entry() : key(), parsed(), content(), value_t(EntryValue::String) { }
			
			Entry::Entry(const string &key, const string &parsed) : key(key), content(content), value_t(EntryValue::String) { }
			Entry::Entry(const string &key, const string &content, int parsed) : key(key), content(content), value_t(EntryValue::Int) { this->parsed.Int = parsed; }
			Entry::Entry(const string &key, const string &content, float parsed) : key(key), content(content), value_t(EntryValue::Float) { this->parsed.Float = parsed; }
			Entry::Entry(const string &key, const string &content, bool parsed) : key(key), content(content), value_t(EntryValue::Bool) { this->parsed.Bool = parsed; }

			EntryValue Entry::valueType() const
			{
				return value_t;
			}

			bool Entry::toFloat(float &out) const
			{
				if(value_t == EntryValue::Bool)
				{
					out = parsed.Bool ? 1.f : 0.f;
					return true;
				} else if(value_t == EntryValue::Float)
				{
					out = parsed.Float;
					return true;
				} else if(value_t == EntryValue::Int)
				{
					out = parsed.Int;
					return true;
				}
				else return false;
			}

			bool Entry::toInt(int &out) const
			{
				if(value_t == EntryValue::Bool)
				{
					out = parsed.Bool ? 1 : 0;
					return true;
				} else if(value_t == EntryValue::Int)
				{
					out = parsed.Int;
					return true;
				} else if(value_t == EntryValue::Float)
				{
					out = parsed.Float;
					return true;
				}
				else return false;
			}
			bool Entry::toBool(bool &out) const
			{
				if(value_t == EntryValue::Bool)
					out = parsed.Bool;
				else if(value_t == EntryValue::Float)
					out = parsed.Float;
				else if(value_t == EntryValue::Int)
					out = parsed.Int;
				else return false;

				return true;
			}
			
			bool Entry::toString(string &out) const
			{
				out = content;
				return true;
			}

			const string &Section::name() const { return _name; }
			const std::vector<Entry> &Section::entries() const { return _entries; }
			const Entry * Section::findEntry(const string &name) const
			{
				for(const auto &entry : _entries)
					if(entry.key == name)
						return &entry;
				return nullptr;
			}
			const Entry * Section::operator[](const string &name) const
			{
				return findEntry(name);
			}

			int IniFile::comment(const std::vector<string> &lines, const int current_line, string &out)
			{
				int line = current_line;
				char buf[2048] = { 0 };
				
				while(lines[line].empty())
					line++;

				if(sscanf_s(lines[line].c_str(), ";%s", buf))
				{
					out = buf;
					return line+1-current_line;
				}
				else return 0;
			}
			int IniFile::section(const std::vector<string> &lines, const int current_line, Section &out)
			{
				int line = current_line;
				char buf[2048] = { 0 };
				out = Section();
				while(lines[line].empty())
					line++;
				string _comment;
				out._comment.clear();
				while(line != (line+=comment(lines, line, _comment))) out._comment+=_comment;

				if(!sscanf_s(lines[line].c_str(), "[%s]", buf))
					return 0;
				else
				{
					Entry _entry;
					while(line != (line+=entry(lines, line, _entry)))
						out._entries.push_back(_entry);

					return line+1-current_line;
				}
			}
			int IniFile::entry(const std::vector<string> &lines, const int current_line, Entry &out)
			{
				int line = current_line;
				out = Entry();
				while(lines[line].empty())
					line++;

				
				string _comment;
				out.comment.clear();
				while(line != (line+=comment(lines, line, _comment))) out.comment+=_comment;


				char name[2048] = { 0 }, value[2048] = { 0 };

				if(2 != sscanf_s(lines[line].c_str(), "%s=%s", name, value))
					return 0;
				else
				{
					out.key = name;
					out.content = value;
					if(sscanf_s(value, "%i", &out.parsed.Int))
						out.value_t = EntryValue::Int;
					else if(sscanf_s(value, "%f", &out.parsed.Float))
						out.value_t = EntryValue::Float;
					else if(!strcmp(value, "true") || !strcmp(value, "yes"))
					{
						out.parsed.Bool = true;
						out.value_t = EntryValue::Bool;
					} else if(!strcmp(value, "false") || !strcmp(value, "no"))
					{
						out.parsed.Bool = false;
						out.value_t = EntryValue::Bool;
					}
					else out.value_t = EntryValue::String;

					return line+1-current_line;
				}
			}

			bool IniFile::load(const string &filename)
			{
				std::vector<string> lines;
				std::ifstream file(filename, std::ios::in);
				
				string line;

				while(std::getline(file, line))
					lines.push_back(line);

				int current_line = 0;
				Entry entry;
				while(current_line != (current_line += this->entry(lines, current_line, entry)))
					Unnamed._entries.push_back(entry);
				Section section;
				while(current_line != (current_line += this->section(lines, current_line, section)))
					sections.push_back(section);

				return current_line == lines.size();
			}

			const Section * IniFile::findSection(const string &name) const
			{
				if(name.empty())
					return &Unnamed;
				for(const Section &section : sections)
					if(section._name == name)
						return &section;
				return nullptr;
			}
			const Section * IniFile::operator[](const string &name) const
			{
				if(name.empty())
					return &Unnamed;
				for(const Section &section : sections)
					if(section._name == name)
						return &section;
				return nullptr;
			}
			const Section * IniFile::unnamedSection() const
			{
				return &Unnamed;
			}

		}

		IniFile::IniFile loadIniFile(const string &filename)
		{
			IniFile::IniFile file;
			file.load(filename);
			return file;
		}
	}
}