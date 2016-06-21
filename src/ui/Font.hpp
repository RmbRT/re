#ifndef __re_font_hpp_defined
#define __re_font_hpp_defined

#include <unordered_map>
#include "../graphics/VertexData.hpp"
#include "../graphics/Texture.hpp"
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
			FontSettings(const math::fvec4 &color, float size, float letterSpacing, float lineHeight, TextDirection direction, TextOrientation orientation, TextAlign align);
			/** Text color. */
			math::fvec4 color;
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
				math::uivec2 tex_origin;
				/** The upper left corner of the glyph relative to the pen position. */
				math::hvec2 bearing_h;
				/** The upper left corner of the glyph relative to the pen position. */
				math::hvec2 bearing_v;
				/** The width and height of the glyph (in pixels). */
				math::hvec2 size;
				/** How much the pen position is moved after this character. */
				math::hvec2 advance;

				Entry(uint32_t codepoint, const math::uivec2 &tex_origin, const math::hvec2 &bearing_h, const math::hvec2 &bearing_v, const math::hvec2 &size, const math::hvec2 &advance);
				Entry();
			};
		private:
			strong_handle<graphics::Texture> atlas;
			std::unordered_map<uint32_t, Entry> entries;
			uint32_t defaultEntry;

			/** Default line height (in text coordinates. */
			int lineHeight;
			/** Horizontal distance of lines in vertical text mode. */
			uint_t lineWidth;
			uint_t tabWidth;
			uint_t spaceWidth;
		public:
			Font(const strong_handle<graphics::Texture> &atlas, std::unordered_map<uint32_t, Entry> &&entries, uint32_t defaultEntry, uint_t lineHeight, uint_t tabWidth, uint_t spaceWidth);
			Font(Font &&move);

			Font &operator=(Font &&move);

			NotNull<const Entry> getEntry(uint32_t codepoint) const;

			unique_handle<graphics::VertexData> compile(const string &text, const FontSettings &settings, math::fvec2 &pen_position) const;
			unique_handle<graphics::VertexData> compile(const u32string &text, const FontSettings &settings, math::fvec2 &pen_position) const;

			math::fvec2 size(const string &text, const FontSettings &settings) const;
			math::fvec2 size(const u32string &text, const FontSettings &settings) const;

			weak_handle<graphics::Texture> getTexture() const;

			static size_t renderables(const string &text);
			static size_t renderables(const u32string &text);
			static bool renderable(uint32_t codepoint);

			static u32string toU32(const string &text);
		};
	}
}

#endif