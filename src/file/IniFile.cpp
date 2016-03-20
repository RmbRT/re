#include "IniFile.hpp"

#include <fstream>
#include <vector>

namespace re
{
	namespace file
	{
		namespace IniFile
		{
			Entry::Entry():
				m_key(),
				m_parsed(),
				m_content(),
				m_value_t(EntryValue::String)
			{
			}
			
			Entry::Entry(string key, string parsed):
				m_key(std::move(key)),
				m_content(std::move(parsed)),
				m_value_t(EntryValue::String)
			{
			}

			Entry::Entry(string key, string content, int parsed):
				m_key(std::move(key)),
				m_content(std::move(content)),
				m_value_t(EntryValue::Int)
			{
				m_parsed.Int = parsed;
			}

			Entry::Entry(string key, string content, float parsed):
				m_key(std::move(key)),
				m_content(std::move(content)),
				m_value_t(EntryValue::Float)
			{
				m_parsed.Float = parsed;
			}

			Entry::Entry(string key, string content, bool parsed):
				m_key(std::move(key)),
				m_content(std::move(content)),
				m_value_t(EntryValue::Bool)
			{
				m_parsed.Bool = parsed;
			}

			bool Entry::to_float(float &out) const
			{
				if(m_value_t == EntryValue::Bool)
				{
					out = m_parsed.Bool ? 1.f : 0.f;
					return true;
				} else if(m_value_t == EntryValue::Float)
				{
					out = m_parsed.Float;
					return true;
				} else if(m_value_t == EntryValue::Int)
				{
					out = m_parsed.Int;
					return true;
				}
				else return false;
			}

			bool Entry::to_int(int &out) const
			{
				if(m_value_t == EntryValue::Bool)
				{
					out = m_parsed.Bool ? 1 : 0;
					return true;
				} else if(m_value_t == EntryValue::Int)
				{
					out = m_parsed.Int;
					return true;
				} else if(m_value_t == EntryValue::Float)
				{
					out = m_parsed.Float;
					return true;
				}
				else return false;
			}
			bool Entry::to_bool(bool &out) const
			{
				if(m_value_t == EntryValue::Bool)
					out = m_parsed.Bool;
				else if(m_value_t == EntryValue::Float)
					out = m_parsed.Float;
				else if(m_value_t == EntryValue::Int)
					out = m_parsed.Int;
				else return false;

				return true;
			}
			
			string const& Entry::to_string() const
			{
				return m_content;
			}

			string const& Section::name() const
			{
				return m_name;
			}
			std::vector<Entry> const& Section::entries() const
			{
				return m_entries;
			}
			Entry const* Section::find_entry(const string &name) const
			{
				for(const auto &entry : m_entries)
					if(entry.key() == name)
						return &entry;
				return nullptr;
			}
			Entry const* Section::operator[](const string &name) const
			{
				return find_entry(name);
			}

			int IniFile::comment(const std::vector<string> &lines, const int current_line, string &out)
			{
				int line = current_line;
				if(line >= lines.size())
					return 0;
				char buf[2048] = { 0 };
				
				while(lines[line].empty())
					line++;
				
				if(line >= lines.size())
					return 0;
				if(sscanf(lines[line++].c_str(), ";%s", buf))
				{
					out = buf;
					return line-current_line;
				}
				else return 0;
			}
			int IniFile::section(const std::vector<string> &lines, const int current_line, Section &out)
			{
				int line = current_line;
				char buf[2048] = { 0 };
				out = Section();
				if(line >= lines.size())
					return 0;
				while(lines[line].empty())
					line++;
				string comment;
				out.comment.clear();
				while(int temp = this->comment(lines, line, comment))
				{
					out.comment += comment;
					line += temp;
				}
				
				if(line >= lines.size())
					return 0;
				if(!sscanf(lines[line++].c_str(), "[%[^]]]", buf))
					return 0;
				else
				{
					Entry entry;
					while(int temp = this->entry(lines, line, entry))
					{
						out.entries.push_back(std::move(entry));
						line += temp;
					}

					out.name = buf;

					return line-current_line;
				}
			}


			int IniFile::entry(const std::vector<string> &lines, const int current_line, Entry &out)
			{
				int line = current_line;
				string out_comment;

				if(line >= lines.size())
					return 0;
				while(lines[line].empty())
					line++;

				
				string comment;
				while(int temp = this->comment(lines, line, comment))
				{
					out_comment += comment;
					line += temp;
				}


				char name[2048] = { 0 }, value[2048] = { 0 };
				
				if(line >= lines.size())
					return 0;
				if(2 != sscanf(lines[line++].c_str(), "%[^=]=%s", name, value))
					return 0;
				else
				{
					union {
						int Int;
						float Float;
						bool Bool;
					};

					if(sscanf(value, "%i", &Int))
						out = Entry(name, value, Int);
					else if(sscanf(value, "%f", &Float))
						out = Entry(name, value, Float);
					else if(!strcmp(value, "true") || !strcmp(value, "yes"))
						out = Entry(name, value, true);
					else if(!strcmp(value, "false") || !strcmp(value, "no"))
						out = Entry(name, value, false);
					else
						out = Entry(name, value);

					return line-current_line;
				}
			}

			bool IniFile::load(const string &filename)
			{
				std::vector<string> lines;
				std::ifstream file(filename, std::ios::in);
				
				string line;

				while(std::getline(file, line))
					lines.push_back(line);

				file.close();

				int current_line = 0;
				Entry entry;
				while(int temp = this->entry(lines, current_line, entry))
				{
					Unnamed.entries.push_back(entry);
					current_line += temp;
				}
				Section section;
				while(int temp = this->section(lines, current_line, section))
				{
					if(Section const* sect = findSection(section.name))
					{
						for(Entry & entry : section.entries)
						{
							if(Entry const* ent = sect->find_entry(entry.key()))
								*const_cast<Entry *>(ent) = std::move(entry);
							else
								const_cast<Section *>(sect)->entries.push_back(std::move(entry));
						}
					}
					else
					{
						sections.push_back(section);
						current_line += temp;
					}
				}

				return current_line == lines.size();
			}

			const Section * IniFile::findSection(string const& name) const
			{
				if(name.empty())
					return &Unnamed;
				for(const Section &section : sections)
					if(section.name == name)
						return &section;
				return nullptr;
			}
			const Section * IniFile::operator[](const string &name) const
			{
				if(name.empty())
					return &Unnamed;
				for(const Section &section : sections)
					if(section.name == name)
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