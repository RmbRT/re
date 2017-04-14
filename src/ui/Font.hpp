#ifndef __re_font_hpp_defined
#define __re_font_hpp_defined

#include <unordered_map>
#include "../graphics/gl/VertexArray.hpp"
#include "../graphics/gl/Texture.hpp"
#include "../types.hpp"
#include "../defines.hpp"

namespace re
{
	namespace ui
	{
		enum class TextOrientation
		{
			Horizontal,
			Vertical
		};
		enum class TextDirection
		{
			Right,
			Left
		};
		enum class TextAlign
		{
			Left,
			Right
		};

		/** Parameters for customizing texts. */
		struct FontSettings
		{
			FontSettings();
			FontSettings(const math::fvec4_t &color, float size, float letterSpacing, float lineHeight, TextDirection direction, TextOrientation orientation, TextAlign align);
			/** Text color. */
			math::fvec4_t color;
			/** Overal scaling factor for the text. */
			float size;
			/** Additional margin between the letters (in text coordinates). */
			float letterSpacing;
			/** Scaling factor for the line height. */
			float lineHeight;
			/** Text reading directio. */
			TextDirection direction;
			/** Horizontal / Vertical text. */
			TextOrientation orientation;
			/** Text align. */
			TextAlign align;
		};

		class Font
		{
		public:
			struct Entry
			{
				/** the Unicode codepoint for this entry. */
				uint32_t codepoint;

				/** The upper left corner of the glyph in the texture (in pixels). */
				math::uivec2_t tex_origin;
				/** The upper left corner of the glyph relative to the pen position. */
				math::hvec2_t bearing_h;
				/** The upper left corner of the glyph relative to the pen position. */
				math::hvec2_t bearing_v;
				/** The width and height of the glyph (in pixels). */
				math::hvec2_t size;
				/** How much the pen position is moved after this character. */
				math::hvec2_t advance;

				Entry(uint32_t codepoint, const math::uivec2_t &tex_origin, const math::hvec2_t &bearing_h, const math::hvec2_t &bearing_v, const math::hvec2_t &size, const math::hvec2_t &advance);
				Entry();
			};
		private:
			Shared<graphics::gl::Texture> m_atlas;
			std::unordered_map<utf32_t, Entry> m_entries;
			utf32_t m_default_entry;

			/** Default line height (in text coordinates). */
			int m_line_height;
			/** Horizontal distance of lines in vertical text mode. */
			uint_t m_line_width;
			/** How wide (in text coordinates) the tab character should be. */
			uint_t m_tab_width;
			/** How wide (in text coordinates) the space character should be. */
			uint_t m_space_width;
		public:
			/** Creates font object.
			@param[in] atlas:
				The texture atlas containing all the symbols.
			@param[in] entries:
				The symbol positions on the atlas.
			@param[in] default_entry:
				The default symbol to display if a symbol that is not in the font is encountered. If set to `0`, no symbol will be drawn in these cases.
			@param[in] line_height:
				The line height (in text coordinates). This only applies to horizontal text.
			@param[in]  */
			Font(
				Shared<graphics::gl::Texture> const& atlas,
				std::unordered_map<uint32_t, Entry> && entries,
				uint32_t default_entry,
				uint_t line_height,
				uint_t tab_width,
				uint_t space_width);

			Font(Font &&move);

			Font &operator=(Font &&move);

			NotNull<const Entry> getEntry(
				uint32_t codepoint) const;

			/** Creates a model from */
			Auto<graphics::gl::VertexArrayBase> compile(
				string8_t const& text,
				FontSettings const& settings,
				math::fvec2_t &pen_position) const;

			Auto<graphics::gl::VertexArrayBase> compile(
				string32_t const& text,
				FontSettings const& settings,
				math::fvec2_t &pen_position) const;

			math::fvec2_t size(
				string8_t &text,
				FontSettings const& settings) const;
			math::fvec2_t size(
				string32_t const& text,
				FontSettings const& settings) const;

			Shared<graphics::gl::Texture> const& getTexture() const;

			static size_t renderables(
				string8_t const& text);
			static size_t renderables(
				string32_t const& text);
			static bool renderable(
				uint32_t codepoint);

			static string32_t toU32(string8_t const& text);
		};
	}
}

#endif