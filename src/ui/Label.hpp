#ifndef __re_ui_label_hpp_defined
#define __re_ui_label_hpp_defined

#include "Font.hpp"
#include "../graphics/gl/ShaderProgram.hpp"

namespace re
{
	namespace ui
	{
		class Label
		{

			Shared<Font> font;
			Shared<graphics::gl::VertexArrayBase> vertexData;

			string32_t text;

			FontSettings settings;

			// The last pen position of this Label. Used to append Labels.
			math::fvec2_t pen_position;

		public:
			Label();
			Label(const Label &copy);
			Label(Label &&move);
			Label& operator=(Label &&move);

			/** Sets the Font of the Label and compiles the text to match the new Font. */
			void setFont(
				Shared<Font> const& font);
			Shared<Font> const& getFont() const;
			/** Sets he text of the Label and compiles it. */
			void setText(
				string32_t const& text);
			/** Sets the X offset for inline appending labels. */
			void setXOffset(
				float xOffset);

			string32_t const& getText() const;

			Shared<graphics::gl::VertexArrayBase> const& getVertexData() const;

			FontSettings &fontSettings();
			FontSettings const& fontSettings() const;

			void update();

			math::fvec2_t const& getSize() const;
			math::fvec2_t const& getMinPosition() const;

			math::fvec2_t const& penPosition() const;

			void draw() const;
		};
	}
}


#endif