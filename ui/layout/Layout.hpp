#ifndef __re_ui_layout_layout_hpp_defined
#define __re_ui_layout_layout_hpp_defined

#include "../../types.hpp"
#include "../../math/Vector.hpp"
#include "../../graphics/Texture.hpp"

namespace re
{
	namespace ui
	{
		namespace layout
		{

			RE_ENUM (Align)
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

			RE_ENUM (Repeat)
			{
				Tile,
				Fit
			};

			RE_ENUM (Display)
			{
				Block,
				Inline
			};

			struct Image
			{
				math::vec2<Repeat> repeat;
				math::fvec4 color;
				strong_handle<graphics::Texture> texture;

				Image &operator=(const math::fvec4 &color)
				{
					this->color = color;
					texture = nullptr;
					return *this;
				}
				Image &operator=(const strong_handle<graphics::Texture> &texture)
				{
					color = math::fvec4(1,1,1,1);
					this->texture = texture;
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
				inline Box &operator=(const T& value) { top = right = bottom = left = value; return *this; }
			};

			struct Border
			{
				float width;
				Image image;
				strong_handle<graphics::VertexData> model;
			};

			RE_ENUM (ScrollBarVisibility)
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

			RE_ENUM (Positioning)
			{
				Dynamic,
				Absolute,
				Fixed
			};
		}
	}
}

#endif