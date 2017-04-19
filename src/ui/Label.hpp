#ifndef __re_ui_label_hpp_defined
#define __re_ui_label_hpp_defined

#include "Font.hpp"
#include "../graphics/gl/ShaderProgram.hpp"
#include "Rendering.hpp"

namespace re
{
	namespace ui
	{
		class Label
		{

			Shared<Font> m_font;
			Auto<VertexArray> m_vertex_array;

			string32_t m_text;

			FontSettings m_settings;

			// The last pen position of this Label. Used to append Labels.
			math::fvec2_t m_pen_position;

		public:
			Label();
			Label(Label &&move);
			Label& operator=(Label &&move);

			/** Sets the Font of the Label and compiles the text to match the new Font. */
			void set_font(
				Shared<Font> const& font);
			Shared<Font> const& font() const;
			/** Sets he text of the Label and compiles it. */
			void set_text(
				string32_t const& text);
			/** Sets the X offset for inline appending labels. */
			void set_x_offset(
				float xOffset);

			string32_t const& text() const;

			Auto<VertexArray> const& vertex_array() const;

			FontSettings &font_settings();
			FontSettings const& font_settings() const;

			void update();

			math::fvec2_t size() const;
			math::fvec2_t min_position() const;

			math::fvec2_t const& pen_position() const;

			void draw() const;
		};
	}
}


#endif