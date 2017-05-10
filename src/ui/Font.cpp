#include "Font.hpp"
#include "Label.hpp"

#include "../util/AllocationBuffer.hpp"

#include <cmath>

namespace re
{
	namespace ui
	{

		FontSettings::FontSettings():
			color(1,1,1,1),
			size(1.0),
			letterSpacing(0.f),
			lineHeight(1.f),
			direction(TextDirection::Right),
			orientation(TextOrientation::Horizontal),
			align(TextAlign::Left)
		{
		}

		FontSettings::FontSettings(
			math::fvec4_t const& color,
			float size,
			float letterSpacing,
			float lineHeight,
			TextDirection direction,
			TextOrientation orientation,
			TextAlign align):
			color(color),
			size(size),
			letterSpacing(letterSpacing),
			lineHeight(lineHeight),
			direction(direction),
			orientation(orientation),
			align(align)
		{
		}

		typedef Font::Entry Entry;
		Font::Entry::Entry(
			uint32_t codepoint,
			math::uivec2_t const& tex_origin,
			math::hvec2_t const& bearing_h,
			math::hvec2_t const& bearing_v,
			math::hvec2_t const& size,
			math::hvec2_t const& advance)
			: codepoint(codepoint), tex_origin(tex_origin), bearing_h(bearing_h), bearing_v(bearing_v), size(size), advance(advance) { }
		Font::Entry::Entry() : codepoint(), tex_origin(), bearing_h(), bearing_v(), size(), advance() { }

		Font::Font(
			Shared<graphics::gl::Texture2D> const& atlas,
			std::unordered_map<uint32_t, Entry> entries,
			uint32_t defaultEntry,
			uint_t lineHeight,
			uint_t tabWidth,
			uint_t spaceWidth):
			m_atlas(atlas),
			m_entries(std::move(entries)),
			m_default_entry(defaultEntry),
			m_line_height(lineHeight),
			m_tab_width(tabWidth),
			m_space_width(spaceWidth)
		{
		}

		Font::Font(Font &&move):
			m_entries(std::move(move.m_entries)),
			m_atlas(std::move(move.m_atlas)),
			m_default_entry(move.m_default_entry),
			m_space_width(move.m_space_width),
			m_line_height(move.m_line_height),
			m_tab_width(move.m_tab_width)
		{
		}

		Font& Font::operator=(Font &&move)
		{
			if(this == &move)
				return *this;
			m_entries = std::move(move.m_entries);
			m_atlas = std::move(move.m_atlas);
			m_default_entry = move.m_default_entry;
			m_space_width = move.m_space_width;
			m_tab_width = move.m_tab_width;
			m_line_height = move.m_line_height;
			return *this;
		}

		Entry const& Font::entry(
			uint32_t codepoint) const
		{
			RE_DBG_ASSERT(!m_entries.empty());

			auto it = m_entries.find(codepoint);
			if(it == m_entries.end())
			{
				it = m_entries.find(m_default_entry);
				RE_DBG_ASSERT(it != m_entries.end());
				return it->second;
			}
			else return it->second;
		}

		Shared<graphics::gl::Texture2D> const& Font::texture() const
		{
			return m_atlas;
		}

		math::fvec2_t Font::size(
			string8_t const& text,
			FontSettings const& settings) const
		{
			return size(to_u32(text), settings);
		}
		math::fvec2_t Font::size(
			string32_t const& text,
			FontSettings const& settings) const
		{
			if(settings.orientation == TextOrientation::Horizontal)
			{
				math::fvec2_t max(0,-m_line_height*settings.lineHeight);
				math::fvec2_t pen(0,-m_line_height*settings.lineHeight);

				for(size_t i = 0; i<text.length(); i++)
				{
					const auto c = text[i];
					switch(c)
					{
					case '\v':case '\n':
						{
							pen.x = 0;
							pen.y+= m_line_height * settings.lineHeight;
						} break;
					case '\t':
						{
							if(!m_tab_width)
								break;

							pen.x += m_tab_width - std::fmod(pen.x, m_tab_width);
						} break;
					case '\r':
						{
							pen.x = 0;
						} break;
					case ' ':
						{
							pen.x += m_space_width;
						} break;
					default:
						{
							auto entry = this->entry(text[i]);
							uint_t tw = m_atlas->width(), th = m_atlas->height();

							math::fvec2_t const pos_o(
								pen.x+entry.bearing_h.x,
								pen.y-entry.bearing_h.y);
							math::fvec2_t const pos_t(
								pos_o.x+entry.size.x,
								pos_o.y+entry.size.y);

							if(max.x<pos_t.x) max.x = pos_t.x;
							if(max.x<pos_o.x) max.x = pos_o.x;
							if(max.y>pos_t.y) max.y = pos_t.y;
							if(max.y>pos_o.y) max.y = pos_o.y;

							pen.x += entry.advance.x + settings.letterSpacing;
						} break;
					}
				}
				return math::fvec2_t(max.x, -max.y) * settings.size;
			}
			else // Vertical Text.
			{
				math::fvec2_t max(0,0);
				math::fvec2_t pen(0,0);

				RE_LOG("vertical text not yet implemented.");

				return math::fvec2_t(max.x, -max.y) * settings.size;
			}
		}

		void Font::compile(
			string8_t const& text,
			FontSettings const& settings,
			math::fvec2_t &pen_position,
			VertexArray &out) const
		{
			compile(
				to_u32(text),
				settings,
				pen_position,
				out);
		}

		void Font::compile(
			string32_t const& text,
			FontSettings const& settings,
			math::fvec2_t &pen_position,
			VertexArray &out) const
		{
			if(!out.exists())
			{
				VertexArray * const addr = &out;
				VertexArray::alloc(&addr, 1);
			}

			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			size_t const renderable_count = renderables(text);
			vertices.reserve(renderable_count*4);
			indices.reserve(renderable_count*6);


			const math::fvec2_t bounds = size(text, settings);

			pen_position = (settings.orientation == TextOrientation::Horizontal)
				? math::fvec2_t(0, -m_line_height * settings.lineHeight)
				: math::fvec2_t(0,0);

				for(size_t i = 0; i<text.length(); i++)
				{
					const auto c = text[i];
					switch(c)
					{
					case '\v':case '\n':
						{
							pen_position.x = 0;
							pen_position.y-= m_line_height * settings.lineHeight;
						} break;
					case '\t':
						{
							if(!m_tab_width)
								break;

							pen_position.x += m_tab_width - std::fmod(pen_position.x, m_tab_width);
						} break;
					case '\r':
						{
							pen_position.x = 0;
						} break;
					case ' ':
						{
							pen_position.x += m_space_width;
						} break;
					default:
						{
							auto &entry = this->entry(text[i]);
							uint_t tw = m_atlas->width(), th = m_atlas->height();
							math::fvec2_t tex_o(entry.tex_origin);
							math::fvec2_t tex_t(math::hvec2_t(entry.tex_origin)+entry.size);

							tex_o.x /= tw;
							tex_o.y = 1.f- tex_o.y / th;
							tex_t.x /= tw;
							tex_t.y = 1.f- tex_t.y / th;

							math::fvec2_t const pos_o(settings.size * math::fvec2_t(pen_position.x+entry.bearing_h.x, pen_position.y+entry.bearing_h.y));
							math::fvec2_t const pos_t(settings.size * math::fvec2_t(pos_o.x+entry.size.x, pos_o.y-entry.size.y));

							vertices.reserve(vertices.size() + 4);
							size_t const base_index = vertices.size();
							/* Vertex data is passed as follows:
							2---1
							|  /|
							| / |
							|/  |
							0---3. */
							vertices.emplace_back(
								math::fvec3_t(pos_o.x, pos_t.y, 0),
								math::fvec2_t(tex_o.x, tex_t.y),
								settings.color);
							vertices.emplace_back(
								math::fvec3_t(pos_t.x, pos_o.y, 0),
								math::fvec2_t(tex_t.x, tex_o.y),
								settings.color);
							vertices.emplace_back(
								math::fvec3_t(pos_o.x, pos_o.y, 0),
								math::fvec2_t(tex_o.x, tex_o.y),
								settings.color);
							vertices.emplace_back(
								math::fvec3_t(pos_t.x, pos_t.y, 0),
								math::fvec2_t(tex_t.x, tex_t.y),
								settings.color);

							indices.push_back(base_index + 0);
							indices.push_back(base_index + 1);
							indices.push_back(base_index + 2);

							indices.push_back(base_index + 0);
							indices.push_back(base_index + 3);
							indices.push_back(base_index + 1);

							pen_position.x += entry.advance.x + settings.letterSpacing;
						} break;
					}
				}
			out.set_data(
				std::move(vertices),
				graphics::gl::RenderMode::Triangles,
				std::move(indices));
		}

		size_t Font::renderables(string8_t const& text)
		{
			size_t count = 0;
			for(size_t i = text.length(); i-->0;)
				if(!renderable(text[i]))
					count++;
			return text.length()-count;
		}

		size_t Font::renderables(string32_t const& text)
		{
			size_t count = 0;
			for(size_t i = text.length(); i-->0;)
				if(!renderable(text[i]))
					count++;
			return text.length()-count;
		}

		bool Font::renderable(uint32_t codepoint)
		{
			switch(codepoint)
			{
			case' ':case'\n':case'\t':case'\r':case'\v': return false;
			default: return true;
			}
		}

		string32_t Font::to_u32(string8_t const& str)
		{
			string32_t data;
			data.resize(str.length());
			for(size_t i = 0; i<str.length(); i++)
				data[i] = str[i];

			return data;
		}
	}
}