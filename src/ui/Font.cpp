#include "Font.hpp"
#include "Label.hpp"

namespace re
{
	namespace ui
	{

		FontSettings::FontSettings(): color(1,1,1,1), size(1.0), letterSpacing(0.f), lineHeight(1.f), direction(TextDirection::Right), orientation(TextOrientation::Horizontal), align(TextAlign::Left) {}
		FontSettings::FontSettings(const math::fvec4 &color, float size, float letterSpacing, float lineHeight, TextDirection direction, TextOrientation orientation, TextAlign align)
			: color(color), size(size), letterSpacing(letterSpacing), lineHeight(lineHeight), direction(direction), orientation(orientation), align(align) {}
		typedef Font::Entry Entry;
		Font::Entry::Entry(uint32 codepoint, const math::uivec2 &tex_origin, const math::hvec2 &bearing_h, const math::hvec2 &bearing_v, const math::hvec2 &size, const math::hvec2 &advance)
			: codepoint(codepoint), tex_origin(tex_origin), bearing_h(bearing_h), bearing_v(bearing_v), size(size), advance(advance) { }
		Font::Entry::Entry() : codepoint(), tex_origin(), bearing_h(), bearing_v(), size(), advance() { }

		Font::Font(const strong_handle<graphics::Texture> &atlas, std::unordered_map<uint32, Entry> &&entries, uint32 defaultEntry, uint lineHeight, uint tabWidth, uint spaceWidth):
			atlas(atlas), entries(entries), defaultEntry(defaultEntry), lineHeight(lineHeight), tabWidth(tabWidth), spaceWidth(spaceWidth) { }

		Font::Font(Font &&move) : entries(std::move(move.entries)), atlas(std::move(move.atlas)), defaultEntry(move.defaultEntry), spaceWidth(move.spaceWidth), lineHeight(move.lineHeight), tabWidth(move.tabWidth) { }
		Font& Font::operator=(Font &&move)
		{
			if(this == &move)
				return *this;
			entries = std::move(move.entries);
			atlas = std::move(move.atlas);
			defaultEntry = move.defaultEntry;
			spaceWidth = move.spaceWidth;
			tabWidth = move.tabWidth;
			lineHeight = move.lineHeight;
			return *this;
		}

		NotNull<const Entry> Font::getEntry(uint32 codepoint) const
		{
			auto it = entries.find(codepoint);
			if(it == entries.end())
				return entries.find(defaultEntry)->second;
			else return it->second;
		}

		weak_handle<graphics::Texture> Font::getTexture() const
		{
			return atlas;
		}

		math::fvec2 Font::size(const string &text, const FontSettings &settings) const
		{
			return size(toU32(text), settings);
		}
		math::fvec2 Font::size(const u32string &text, const FontSettings &settings) const
		{
			if(settings.orientation == TextOrientation::Horizontal)
			{
				math::fvec2 max(0,-lineHeight*settings.lineHeight);
				math::fvec2 pen(0,-lineHeight*settings.lineHeight);
				for(size_t i = 0; i<text.length(); i++)
				{
					const auto c = text[i];
					switch(c)
					{
					case '\v':case '\n':
						{
							pen.x = 0;
							pen.y+=lineHeight * settings.lineHeight;
						} break;
					case '\t':
						{
							if(!tabWidth)
								break;

							pen.x += tabWidth - fmodf(pen.x, tabWidth);
						} break;
					case '\r':
						{
							pen.x = 0;
						} break;
					case ' ':
						{
							pen.x += spaceWidth;
						} break;
					default:
						{
							auto entry = getEntry(text[i]);
							uint tw = atlas->getWidth(), th = atlas->getHeight();
					

							const math::fvec2 pos_o(pen.x+entry->bearing_h.x, pen.y-entry->bearing_h.y);
							const math::fvec2 pos_t(pos_o.x+entry->size.x, pos_o.y+entry->size.y);

							if(max.x<pos_t.x) max.x = pos_t.x;
							if(max.x<pos_o.x) max.x = pos_o.x;
							if(max.y>pos_t.y) max.y = pos_t.y;
							if(max.y>pos_o.y) max.y = pos_o.y;

							pen.x += entry->advance.x + settings.letterSpacing;
						} break;
					}
				}
				return math::fvec2(max.x, -max.y) * settings.size;
			}
			else // Vertical Text.
			{
				math::fvec2 max(0,0);
				math::fvec2 pen(0,0);


				return math::fvec2(max.x, -max.y) * settings.size;
			}
		}

		unique_handle<graphics::VertexData> Font::compile(const string &text, const FontSettings &settings, math::fvec2 &pen_position) const
		{
			return compile(toU32(text), settings, pen_position);
		}

		unique_handle<graphics::VertexData> Font::compile(const u32string &text, const FontSettings &settings, math::fvec2 &pen_position) const
		{
			unique_handle<graphics::VertexData> vdata(alloc<graphics::VertexData>(graphics::RenderMode::RM_TRIANGLES, graphics::AllocationStrategy::AS_STATIC));
			vdata->alloc();
			std::vector<graphics::Vertex> vertices;
			vertices.reserve(renderables(text)*6);

			const math::fvec2 bounds = size(text, settings);

			pen_position = (settings.orientation == TextOrientation::Horizontal)?math::fvec2(0,-lineHeight*settings.lineHeight) : math::fvec2(0,0);
			
				for(size_t i = 0; i<text.length(); i++)
				{
					const auto c = text[i];
					switch(c)
					{
					case '\v':case '\n':
						{
							pen_position.x = 0;
							pen_position.y-=lineHeight*settings.lineHeight;
						} break;
					case '\t':
						{
							if(!tabWidth)
								break;

							pen_position.x += tabWidth - fmodf(pen_position.x, tabWidth);
						} break;
					case '\r':
						{
							pen_position.x = 0;
						} break;
					case ' ':
						{
							pen_position.x += spaceWidth;
						} break;
					default:
						{
							auto entry = getEntry(text[i]);
							uint tw = atlas->getWidth(), th = atlas->getHeight();
							math::fvec2 tex_o(entry->tex_origin);
							math::fvec2 tex_t(math::hvec2(entry->tex_origin)+entry->size);
					
							tex_o.x /= tw;
							tex_o.y = 1.f- tex_o.y / th;
							tex_t.x /= tw;
							tex_t.y = 1.f- tex_t.y / th;

							const math::fvec2 pos_o(settings.size * math::fvec2(pen_position.x+entry->bearing_h.x, pen_position.y+entry->bearing_h.y));
							const math::fvec2 pos_t(settings.size * math::fvec2(pos_o.x+entry->size.x, pos_o.y-entry->size.y));

							vertices.insert(vertices.end(), {
								graphics::Vertex(math::fvec3(pos_o.x, pos_t.y, 0), math::fvec2(tex_o.x, tex_t.y), settings.color),
								graphics::Vertex(math::fvec3(pos_t.x, pos_o.y, 0), math::fvec2(tex_t.x, tex_o.y), settings.color),
								graphics::Vertex(math::fvec3(pos_o.x, pos_o.y, 0), math::fvec2(tex_o.x, tex_o.y), settings.color),

								graphics::Vertex(math::fvec3(pos_o.x, pos_t.y, 0), math::fvec2(tex_o.x, tex_t.y), settings.color),
								graphics::Vertex(math::fvec3(pos_t.x, pos_t.y, 0), math::fvec2(tex_t.x, tex_t.y), settings.color),
								graphics::Vertex(math::fvec3(pos_t.x, pos_o.y, 0), math::fvec2(tex_t.x, tex_o.y), settings.color) });

							pen_position.x += entry->advance.x + settings.letterSpacing;
						} break;
					}
				}
			vdata->setData(vertices.data(), vertices.size());
			
			return vdata;
		}

		size_t Font::renderables(const string &text)
		{
			size_t count = 0;
			for(size_t i = text.length(); i-->0;)
				if(!renderable(text[i]))
					count++;
			return text.length()-count;
		}

		size_t Font::renderables(const u32string &text)
		{
			size_t count = 0;
			for(size_t i = text.length(); i-->0;)
				if(!renderable(text[i]))
					count++;
			return text.length()-count;
		}

		bool Font::renderable(uint32 codepoint)
		{
			switch(codepoint)
			{
			case' ':case'\n':case'\t':case'\r':case'\v': return false;
			default: return true;
			}
		}

		u32string Font::toU32(const std::string &str)
		{
			u32string data(str.length(), '\0');
			for(size_t i = 0; i<str.length(); i++)
				data[i] = str[i];

			return data;
		}
	}
}