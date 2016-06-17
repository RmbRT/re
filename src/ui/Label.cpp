#include "Label.hpp"
#include "../graphics/OpenGL.hpp"

namespace re
{
	namespace ui
	{
		Label::Label(): font(), text() { }
		Label::Label(const Label &copy) : font(copy.font), vertexData(copy.vertexData), text(copy.text) { }
		Label::Label(Label &&move): font(move.font), vertexData(std::move(move.vertexData)), text(std::move(move.text)) { }
		Label& Label::operator=(Label &&move)
		{
			if(this == &move)
				return *this;
			font = move.font;
			vertexData = move.vertexData;
			text = move.text;
			return *this;
		}

		void Label::setFont(const strong_handle<Font> &font)
		{
			this->font = font;
		}
		const strong_handle<Font> &Label::getFont() const
		{
			return font;
		}
		void Label::setText(const u32string &text)
		{
			this->text = text;
		}
		const u32string &Label::getText() const
		{
			return text;
		}

		void Label::update()
		{
			if(font)
				vertexData = font->compile(text, settings, pen_position);
		}

		const strong_handle<graphics::VertexData> &Label::getVertexData() const
		{
			return vertexData;
		}

		math::fvec2 Label::getSize() const
		{
			if(text.empty())
				return math::fvec2(0,0);
			else
				return math::vec2<float>(vertexData->getAABB().size());
		}
		math::fvec2 Label::getMinPosition() const
		{
			if(vertexData)
				return math::fvec2(vertexData->getAABB().min());
			else return math::fvec2(0,0);
		}

		void Label::draw() const
		{
			RE_OGL(glEnable(GL_BLEND));
			RE_OGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			font->getTexture()->bind();
			vertexData->draw();
			RE_OGL(glDisable(GL_BLEND));
		}

		FontSettings &Label::fontSettings()
		{
			return settings;
		}
		const FontSettings &Label::fontSettings() const
		{
			return settings;
		}

	}
}