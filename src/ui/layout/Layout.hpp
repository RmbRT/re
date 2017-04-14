#ifndef __re_ui_layout_layout_hpp_defined
#define __re_ui_layout_layout_hpp_defined

#include "../../types.hpp"
#include "../../math/Vector.hpp"
#include "../../graphics/gl/Texture.hpp"

namespace re
{
	namespace ui
	{
		namespace layout
		{

			enum class Align
			{
				// Aligning to the negative axis direction.
				Negative,
				// Aligning to the positive axis direction.
				Positive,
				// Aligning to the center.
				Centered,
				// Inheriting the value from a parent.
				Inherit
			};
			struct Size
			{
				float absolute;
				float relative;

				inline Size operator+(const Size &other) const
				{ return { absolute+other.absolute, relative+other.relative }; }
				inline Size operator-(const Size &other) const
				{ return { absolute-other.absolute, relative-other.relative }; }
			};

			enum class Repeat
			{
				Tile,
				Fit
			};

			enum class Display
			{
				Block,
				Inline
			};

			struct Image
			{
				math::Vec2<Repeat> repeat;
				math::fvec4_t color;
				Shared<graphics::gl::Texture> texture;

				Image &operator=(const math::fvec4_t &color)
				{
					this->color = color;
					texture = nullptr;
					return *this;
				}
				Image &operator=(Shared<graphics::gl::Texture> texture)
				{
					color = math::fvec4_t(1,1,1,1);
					this->texture = std::move(texture);
					return *this;
				}
			};

			inline Size Absolute(float value) { return { value, 0 }; }
			inline Size Relative(float value) { return { 0, value }; }

			template<class T>
			struct Box
			{
				T top, right, bottom, left;

				// sets all values of the box.
				inline Box<T> &operator=(const T& value) { top = right = bottom = left = value; return *this; }
			};

			struct Border
			{
				float width;
				Image image;
				VertexArray model;
			};

			enum class ScrollBarVisibility
			{
				Always,
				Never,
				WhenScrolling,
				WhenOverflow
			};

			struct ScrollBar
			{
				ScrollBarVisibility visibility;
				float width;
				float heightPercent;
				float positionPercent;
				float scrolling; // scroll speed. if 0, does not currently scroll
				bool obstructVision; // whether the ScrollBar reduces the rendering area of the UIElement.
				Image background;
				Image knob;

			};
		}
	}
}

#endif