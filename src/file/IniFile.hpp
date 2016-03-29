#ifndef __re_file_inifile_hpp_defined
#define __re_file_inifile_hpp_defined

#include "../types.hpp"

namespace re
{
	namespace file
	{
		/** Contains functions and classes used to load Ini files. */
		namespace IniFile
		{
			/** Represents what kind of value the Entry has. */
			enum class EntryValue
			{
				Float,
				Int,
				Bool,
				String
			};

			/** Represents a key-value Entry in a IniFile. */
			struct Entry
			{
				/** The comment line before the line that stores the key and value.
					This is used when generating IniFiles, to create a documentation of the values. */
				string m_comment;
				/** The key. */
				string m_key;
				/** Determines what field to use as value. */
				EntryValue m_value_t;
				/** Compact storage of the parsed value. */
				union
				{
					int Int;
					float Float;
					bool Bool;
				} m_parsed;
				/** The value as it is written in the IniFile. */
				string m_content;
			public:
				/** Creates an empty Entry. */
				Entry();
				/** Creates an Entry with the given key and the given string as value.
				@param[in] key:
					The name of the property stored by this Entry.
				@param[in] parsed:
					The value of the property stored by this Entry. */
				Entry(string key, string parsed, string comment);
				/** Creates an Entry with the given key and the given int as value.
				@param[in] key:
					The name of the property stored by this Entry.
				@param[in] content:
					The value of the property stored by this Entry, as it is written in the IniFile.
				@param[in] parsed:
					The parsed integer value of the property stored by this Entry. */
				Entry(string key, string content, string comment, int parsed);
				/** Creates an Entry with the given key and the given float as value.
				@param[in] key:
				The name of the property stored by this Entry.
				@param[in] content:
				The value of the property stored by this Entry, as it is written in the IniFile.
				@param[in] parsed:
				The parsed float value of the property stored by this Entry. */
				Entry(string key, string content, string comment, float parsed);
				/** Creates an Entry with the given key and the given bool as value.
				@param[in] key:
				The name of the property stored by this Entry.
				@param[in] content:
				The value of the property stored by this Entry, as it is written in the IniFile.
				@param[in] parsed:
				The parsed bool value of the property stored by this Entry. */
				Entry(string key, string content, string comment, bool parsed);

				/** Determines what type the value of this Entry has. */
				RECX EntryValue value_type() const;

				/** Retrieves the stored value into the given float.
					If the stored value is a bool, stores 1.f or 0.f.
					If the stored value is an int, stores the float representing the int.
					If the stored value is a string, fails.
				@param[out] out:
					Where the output should be stored.
				@return
					True, if the value could be read, otherwise false. */
				bool to_float(float & out) const;
				/** Retrieves the stored value into the given integer.
					If the stored value is a bool, sets out to 1 or 0.
					If the stored value is a float, casts the stored float into out.
					If the stored value is a string, fails.
				@param[out] out:
					Where the output should be stored.
				@return
					True, if the value could be read, otherwise false. */
				bool to_int(int & out) const;

				/** Retrieves the stored value into the given bool.
					If the stored value is an int or float, sets out to true, when the stored value is not 0.
					If the stored value is a string, fails.
				@param[out] out: Where the output should be stored.
				@return True, if the value could be read, otherwise false. */
				bool to_bool(bool & out) const;

				/** Retrieves the stored value as it was written in the file. */
				RECX string const& content() const;
				/** Returns the key of the Entry. */
				RECX string const& key() const;
				/** Returns the comment of the Entry. */
				RECX string const& comment() const;
			};

			/** Describes a section ("[sectionname]") of an IniFile. */
			struct Section
			{
				/** The name of the section. */
				string name;
				/** The contents of the section. */
				std::vector<Entry> entries;
				/** The comment line before the section line.
					This is used for the creation of IniFiles, to create a documentation. */
				string comment;
				

				/** Tries to find an Entry with the given name.
				@param[in] name:
					The name / key of the Entry to be looked for.
				@return
					If an Entry with a matching name was found, returns its address, otherwise null. */
				Entry * find_entry(string const& name);
				/** Tries to find an Entry with the given name.
				@param[in] name:
					The name/key of the Entry to be looked for.
				@return
					If an Entry with a matching name was found, returns its address, otherwise null. */
				Entry const* find_entry(string const& name) const;
				/** @see find_entry. */
				RECX Entry * operator[](string const& name);
				/** @see find_entry. */
				RECX Entry const* operator[](string const& name) const;
			};

			/** Represents a .ini file. */
			class IniFile
			{
				/** The unnamed / default section of the file. */
				Section m_unnamed_section;
				/** The named sections of the file. */
				std::vector<Section> m_sections;

				/** Reads a Section out of the given lines.
				@return The number of lines consumed. */
				int section(std::vector<string> const& lines, const int current_line, Section & out);
				/** Reads an Entry out of the given lines.
				@return The number of lines consumed. */
				int entry(std::vector<string> const& lines, const int current_line, Entry & out);
				/** Reads a comment out of the given lines.
				@return The number of lines consumed. */
				int comment(std::vector<string> const& lines, const int current_line, string & out);

			public:

				/** Tries to find the Section with the given name.
					Pass "" for the unnamed section. */
				Section * find_section(string const& name);
				/** Tries to find the Section with the given name.
					Pass "" for the unnamed section. */
				Section const* find_section(string const& name) const;
				/** Tries to find the Section with the given name.
					Pass "" for the unnamed section.*/
				RECX Section * operator[](string const& name);
				/** Tries to find the Section with the given name.
					Pass "" for the unnamed section.*/
				RECX Section const* operator[](string const& name) const;
				/** Returns the unnamed / default Section of the file. */
				RECX Section & unnamed_section();
				/** Returns the unnamed / default Section of the file. */
				RECX Section const& unnamed_section() const;

				/** Tries to load the given file. */
				bool load(string const& filename);
			};
		}
	}
}

#include "IniFile.inl"

#endif