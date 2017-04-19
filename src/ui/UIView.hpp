#ifndef __re_ui_uiview_hpp_defined
#define __re_ui_uiview_hpp_defined

#include "UINode.hpp"
#include "../math/Vector.hpp"
#include "../math/Matrix.hpp"
#include "../math/Angle.hpp"
#include "../math/Plane.hpp"
#include "../math/Intersection.hpp"

namespace re
{
	namespace ui
	{
		/** A UIView contains a UIElement tree and is used to draw UI in a Scene.
		Note that a UIView can only represent a planar UI. */
		struct UIView
		{
			/** The root UIElement / container for this UIView. */
			Auto<UINode> content;

			/** The Position of this UIView in 3D space. */
			math::fvec3_t position;
			/** The Rotation of this UIView in 3D space. */
			math::Vec3<math::Angle> rotation;
			/** The Scaling of this UIView in 3D space. */
			math::fvec3_t scaling;

			/** Calculates the transformation Matrix for this UIView.
			@note: This can be quite expensive so avoid redundant calls.
			@return
				the transformation Matrix. */
			math::fmat4x4_t transformation() const;

			/** The plane of this UIView in the 3D space.
			Can be used to determine the local cursor position via intersection.
			The UIView is inside the plane at the coordinates (0,0) to (1,1). */
			math::STPlane<float> ui_plane() const;

			/** Updates the Cursor position and generates events for the UIElement tree if needed.
			@param[in] cursor:
				a Ray for calculating the intersection with the UIView. */
			void update_cursor(math::Ray<float> const& cursor);

			/** Updates the Cursor position and generates events for the UIElement tree if needed.
			@param[in] cursor:
				the local cursor position. */
			void update_cursor(math::fvec2_t const& cursor);

			/** Searches and returns the UIElement described by the name, if exists. */
			UINode * findElement(string8_t const& name) const;

		};
	}
}


#endif