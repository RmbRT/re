#ifndef __re_ui_layout_layout_hpp_defined
#define __re_ui_layout_layout_hpp_defined

#include "../../types.hpp"
#include "../../math/Vector.hpp"
#include "../../graphics/gl/Texture.hpp"
#include "../Rendering.hpp"

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
				/** Tiles the texture when the edge is reached.
					The texture is also stretched by the texture scale parameter. */
				Tile,
				/** Stretches the texture to fit the Image.
					Leaves the texture unaffected by the texture scale parameter, except its sign. */
				Fit
			};

			enum class Display
			{
				Block,
				Inline
			};

			class Image
			{
				math::Vec2<Repeat> m_repeat;
				math::fvec2_t m_texture_scale;
				math::fvec4_t m_color;
				Shared<graphics::gl::Texture2D> m_texture;
				math::fvec2_t m_position;
				math::fvec2_t m_size;
				mutable VertexArray m_model;
				mutable bool m_invalid_model;
			public:
				Image(
					graphics::gl::BufferAccess access);

				/** @return The image repetition mode. */
				REIL math::Vec2<Repeat> const& repeat() const;
				/** Sets the image repetition mode.
				@param[in] repeat:
					The image repetition mode. */
				void set_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the image repetition mode.
					Equal to `set_repeat(math::Vec2<Repeat>(repeat, repeat)`.
				@param[in] repeat:
					The image repetition mode. */
				void set_repeat(
					Repeat repeat);

				/** Sets the image to a color.
					Clears the texture that was set before.
				@param[in] color:
					The RGBA values. */
				void set_image(
					math::fvec4_t const& color);

				void set_image(
					Shared<graphics::gl::Texture2D> texture);

				void set_image(
					Shared<graphics::gl::Texture2D> texture,
					math::fvec4_t const& color);

				void set_position(
					math::fvec2_t const& position);

				void set_size(
					math::fvec2_t const& size);

				void set_texture_scale(
					math::fvec2_t const& scale);

				void update_model() const;

				void draw() const;
			};

			inline Size Absolute(float value) { return { value, 0 }; }
			inline Size Relative(float value) { return { 0, value }; }

			template<class T>
			struct Box
			{
				T top, right, bottom, left;

				// sets all values of the box.
				REIL Box<T> &operator=(const T& value) { top = right = bottom = left = value; return *this; }
			};

			template<class T>
			struct Corners
			{
				T top_left, top_right, bottom_left, bottom_right;
			};


			enum class Side
			{
				Left,
				Right,
				Top,
				Bottom
			};

			/** The borders used by the `UINode` class.
				Consists of four borders and four corners, each of which can be set to have a custom image. Always call `set_box()` after the position or size of the borders changed, for example because the `UINode` resized. */
			class Borders
			{
				/** The borders. */
				Box<Image> m_borders;
				/** The corners of the borders. */
				Corners<Image> m_corners;
				Box<float> m_width;
			public:
				Borders();

				/** Sets the left border's width to `width`.
				@param[in] width:
					The left border's new width. */
				REIL void set_left_width(
					float width);
				/** Sets the right border's width to `width`.
				@param[in] width:
					The right border's new width. */
				REIL void set_right_width(
					float width);
				/** Sets the top border's width to `width`.
				@param[in] width:
					The top border's new width. */
				REIL void set_top_width(
					float width);
				/** Sets the bottom border's width to `width`.
				@param[in] width:
					The bottom border's new width.*/
				REIL void set_bottom_width(
					float width);
				/** Sets every borders' width to `width`.
				@param[in] width:
					The borders' new width. */
				REIL void set_width(
					float width);


				/** @return The left border's width. */
				REIL float left_width() const;
				/** @return The right border's width. */
				REIL float right_width() const;
				/** @return The top border's width. */
				REIL float top_width() const;
				/** @return The bottom border's width. */
				REIL float bottom_width() const;


				/** Sets the left border's image repetition.
				@param[in] repeat:
					The left border's image repetition. */
				void set_left_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the right border's image repetition.
				@param[in] repeat:
					The right border's image repetition. */
				void set_right_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the top border's image repetition.
				@param[in] repeat:
					The top border's image repetition. */
				void set_top_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the bottom border's image repetition.
				@param[in] repeat:
					The bottom border's image repetition. */
				void set_bottom_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the horizontal borders' image repetition.
					Equal to a call to both `set_top_repeat()` and `set_bottom_repeat()`.
				@param[in] repeat:
					The horizontal borders' image repetition. */
				void set_horizontal_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the vertical borders' image repetition.
					Equal to a call to both `set_left_repeat()` and `set_right_repeat()`.
				@param[in] repeat:
					The vertical borders' image repetition. */
				void set_vertical_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the top left corner's image repetition.
				@param[in] repeat:
					The corner's image repetition. */
				void set_top_left_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the top right corner's image repetition.
				@param[in] repeat:
					The corner's image repetition. */
				void set_top_right_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the bottom left corner's image repetition.
				@param[in] repeat:
					The corner's image repetition. */
				void set_bottom_left_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets the bottom right corner's image repetition.
				@param[in] repeat:
					The corner's image repetition. */
				void set_bottom_right_repeat(
					math::Vec2<Repeat> const& repeat);
				/** Sets every corners' image repetition.
				@param[in] repeat:
					The corners' image repetition. */
				void set_corner_repeat(
					math::Vec2<Repeat> const& repeat);

				/** Sets the left border's image.
				@param[in] texture:
					The texture to draw, or `nullptr` for a uni-colored border.
				@param[in] color:
					The blending color. */
				void set_left_image(
					Shared<graphics::gl::Texture2D> texture,
					math::fvec4_t const& color);
				/** Sets the right border's image.
				@param[in] texture:
					The texture to draw, or `nullptr` for a uni-colored border.
				@param[in] color:
					The blending color. */
				void set_right_image(
					Shared<graphics::gl::Texture2D> texture,
					math::fvec4_t const& color);
				/** Sets the top border's image.
				@param[in] texture:
					The texture to draw, or `nullptr` for a uni-colored border.
				@param[in] color:
					The blending color. */
				void set_top_image(
					Shared<graphics::gl::Texture2D> texture,
					math::fvec4_t const& color);
				/** Sets the bottom border's image.
				@param[in] texture:
					The texture to draw, or `nullptr` for a uni-colored border.
				@param[in] color:
					The blending color. */
				void set_bottom_image(
					Shared<graphics::gl::Texture2D> texture,
					math::fvec4_t const& color);
				/** Sets the top left corner's image.
				@param[in] texture:
					The texture to draw, or `nullptr` for a uni-colored corner.
				@param[in] color:
					The blending color. */
				void set_top_left_image(
					Shared<graphics::gl::Texture2D> texture,
					math::fvec4_t const& color);
				/** Sets the top right corner's image.
				@param[in] texture:
					The texture to draw, or `nullptr` for a uni-colored corner.
				@param[in] color:
					The blending color. */
				void set_top_right_image(
					Shared<graphics::gl::Texture2D> texture,
					math::fvec4_t const& color);
				/** Sets the bottom left corner's image.
				@param[in] texture:
					The texture to draw, or `nullptr` for a uni-colered corner.
				@param[in] color:
					The blending color. */
				void set_bottom_left_image(
					Shared<graphics::gl::Texture2D> texture,
					math::fvec4_t const& color);
				/** Sets the bottom right corner's image.
				@param[in] texture:
					The texture to draw, or `nullptr` for a uni-colered corner.
				@param[in] color:
					The blending color. */
				void set_bottom_right_image(
					Shared<graphics::gl::Texture2D> texture,
					math::fvec4_t const& color);

				/** Sets the left border's texture scale.
				@param[in] scale:
					The texture scale. */
				void set_left_texture_scale(
					math::fvec2_t const& scale);
				/** Sets the right border's texture scale.
				@param[in] scale:
					The texture scale. */
				void set_right_texture_scale(
					math::fvec2_t const& scale);
				/** Sets the top border's texture scale.
				@param[in] scale:
					The texture scale. */
				void set_top_texture_scale(
					math::fvec2_t const& scale);
				/** Sets the bottom border's texture scale.
				@param[in] scale:
					The texture scale. */
				void set_bottom_texture_scale(
					math::fvec2_t const& scale);
				/** Sets the borders' texture scales by mirroring them.
					Mirrors the right border scale horizontally and the bottom border scale vertically.
				@param[in] scale:
					The top and right botders' texure scale. */
				void set_mirrored_border_texture_scale(
					math::fvec2_t const& scale);
				/** Sets the top left corner's texture scale.
				@param[in] scale:
					The texture scale. */
				void set_top_left_texture_scale(
					math::fvec2_t const& scale);
				/** Sets the top right corner's texture scale.
				@param[in] scale:
					The texture scale. */
				void set_top_right_texture_scale(
					math::fvec2_t const& scale);
				/** Sets the bottom left corner's texture scale.
				@param[in] scale:
					The texture scale. */
				void set_bottom_left_texture_scale(
					math::fvec2_t const& scale);
				/** Sets the bottom right corner's texture scale.
				@param[in] scale:
					The texture scale. */
				void set_bottom_right_texture_scale(
					math::fvec2_t const& scale);

				/** Sets the corner's texture scales, and mirrors them.
					The right corners' texture scales will be horizontally mirrored, and the bottom corners' texture scales will be vertically mirrored. The passed values set the top left corner without modification, and set the other corners after mirroring.
				@param[in] scale:
					The top left corners texture scale. */
				void set_mirrored_corner_texture_scale(
					math::fvec2_t const& scale);


				/** Sets the inner box that is covered by the borders.
				@param[in] origin:
					The top-left outer corner of the borders.
				@param[in] inner_size:
					The boxes inner size. */
				void set_box(
					math::fvec2_t const& origin,
					math::fvec2_t const& inner_size);

				void update_model() const;

				void draw() const;
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
				ScrollBar();
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

#include "Layout.inl"

#endif