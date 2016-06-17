#ifndef __re_ui_label_hpp_defined
#define __re_ui_label_hpp_defined

#include "Font.hpp"
#include "../graphics/ShaderProgram.hpp"

namespace re
{
	namespace ui
	{
		class Label
		{

			strong_handle<Font> font;
			strong_handle<graphics::VertexData> vertexData;

			std::u32string text;
			
			FontSettings settings;

			// The last pen position of this Label. Used to append Labels.
			math::fvec2 pen_position;

		public:
			Label();
			Label(const Label &copy);
			Label(Label &&move);
			Label& operator=(Label &&move);

			/*Sets the Font of the Label and compiles the text to match the new Font.*/
			void setFont(const strong_handle<Font> &font);
			const strong_handle<Font> &getFont() const;
			/*Sets he text of the Label and compiles it.*/
			void setText(const u32string &text);
			/*Sets the X offset for inline appending labels.*/
			void setXOffset(float xOffset);

			const u32string &getText() const;



			const strong_handle<graphics::VertexData> &getVertexData() const;

			FontSettings &fontSettings();
			const FontSettings &fontSettings() const;

			void update();

			math::fvec2 getSize() const;
			math::fvec2 getMinPosition() const;

			const math::fvec2 &penPosition();

			void draw() const;
		};
	}
}


#endif