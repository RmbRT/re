#ifndef __re_ui_uielement_hpp_defined
#define __re_ui_uielement_hpp_defined
#include <vector>
#include "../types.hpp"
#include "../math/Vector.hpp"
#include "../input/InputManager.hpp"
#include "Label.hpp"
#include "UIElementStyle.hpp"
#include "../graphics/RenderSession.hpp"

namespace re
{
	namespace ui
	{
		class UIElement;
		/*Callback function signature for cursor move events.
		@param[inout] sender: the UIElement that caused this event.
		@param[in] pos: the cursor position (relative to the position of this UIElement).*/
		typedef void (*CursorMoveCallback)(UIElement &sender, const math::fvec2 &pos);
		/*Callback function signature for cursor enter events.
		@param[inout] sender: the UIElement that caused this event.*/
		typedef void (*CursorEnterCallback)(UIElement &sender);
		/*Callback function signature for cursor leave events.
		@param[inout] sender: the UIElement that caused this event.*/
		typedef void (*CursorLeaveCallback)(UIElement &sender);
		/*Callback function signature for input events.
		@param[inout] sender: the UIElement that caused this event.
		@param[in] codepoint: the unicode codepoint of the input character.*/
		typedef void (*InputCallback)(UIElement &sender, uint32 codepoint);
		/*Callback function signature for key events.
		@param[inout] sender: the UIElement that caused this event.
		@param[in] event: the input::KeyEvent describing the key event.*/
		typedef void (*KeyCallback)(UIElement &sender, const input::KeyEvent &event);
		/*Callback function signature for focus change events.
		@param[inout] sender: the UIElement that caused this event.
		@param[in] focused: true, if the UIElement gained focus, false, if it lost focus.*/
		typedef void (*FocusChangedCallback)(UIElement &sender, bool focused);
		/*Callback function signature for activate events.
		@param[inout] sender: the UIElement that caused this event.
		@param[in] active: true, if the UIElement was activated.*/
		typedef void (*ActivateCallback)(UIElement &sender, bool active);
		/*Callback function signature for element size change events.
		@param[inout] sender: the UIElement that caused this event.
		@param[in] old_size: the old size of this UIElement.
		@param[in] new_size: the new size of this UIElement.*/
		typedef void (*SizeChangedCallback)(UIElement &sender, const math::fvec2 &old_size, const math::fvec2 &new_size);
		/*Callback function signature for enable events.
		@param[inout] sender: the UIElement that caused this event.
		@param[in] enabled: true, if the UIElement (or its parent) was enabled.
		@note:
			The passed value might not represent the actual enabled state of the UIElement.
			Use @[UIElement::enabled] to check whether the UIElement itself is enabled.
		@usage: This callback should be used to update the visual appearance of the UIElement.*/
		typedef void (*EnableCallback)(UIElement &sender, bool enabled);

		RE_ENUM (ImageRepetition)
		{
			Tile,
			Stretch
		};



		/*Class used for all User Interface Objects. Represents a tree of UIElements.
		UIElements are positioned via offsets relative to the origin of their parent element.
		@note: UIElements do not resize automatically*/
		class UIElement
		{
			UIElement *_parent;
			/*The text of the UIElement, if it is a text node.*/
			strong_handle<Label> _text;

			/*A Texture that fills the UIElement.*/
			strong_handle<graphics::Texture> _background_texture;
			strong_handle<graphics::Texture> _border_texture;
			strong_handle<graphics::Texture> _border_corner_texture;
			/*The background vertex data.*/
			mutable unique_handle<graphics::VertexData> _background_vertex_data;
			/*The border vertex data. If there is no border, then it is unused.*/
			mutable unique_handle<graphics::VertexData> _border_vertex_data;

			mutable unique_handle<graphics::VertexData> _border_corner_vertex_data;


			/*The background Color.
			If there was no Texture set as background Texture, then this is the background color.
			If there was a Texture set as background Texture, then this is used for blending the color.*/
			math::fvec4 _background_color;

			/*Used for finding and accessing an UIElement.*/
			string _name;

			/*The position of the UIElement, relative to its parent elements origin.*/
			math::fvec2 _position;
			/*The size of the UIElement.*/
			math::fvec2 _size;
			/*The border color of this UIElement.*/
			math::fvec4 _border_color;
			/*The border width of this UIElement*/
			float _border_width;


			/*Used for event generation.*/
			bool _hovered, _focused, _active, _enabled;

			/*Flag indicating that the border model should be updated.*/
			mutable bool _invalid_border_model;
			/*Flag indicating that the background model shuold be updated.*/
			mutable bool _invalid_background_model;


			/*The child elements of this UIElement.*/
			std::vector<strong_handle<UIElement>> _children;

			/*The background image repetition behaviour.*/
			ImageRepetition _background_image_x_repeat_mode, _background_image_y_repeat_mode;
			/*The border image repetition behaviour.
			Specifies the image repitition bahaviour for the sideward axis
			(horizontal axis for top and bottom border, vertical axis for left and right border).*/
			ImageRepetition _border_image_x_repeat_mode;
			/*The border image repetition behaviour.
			Specifies the image repitition bahaviour for the outward axis
			(vertical axis for top and bottom border, horizontal axis for left and right border).*/
			ImageRepetition _border_image_y_repeat_mode;

			/*Stores the callback functions to be called in case of a cursor move event.*/
			Delegate<CursorMoveCallback> onCursorMoveCallback;
			/*Stores the callback functions to be called in case of a cursor enter event.*/
			Delegate<CursorEnterCallback> onCursorEnterCallback;
			/*Stores the callback functions to be called in case of a cursor leave event.*/
			Delegate<CursorLeaveCallback> onCursorLeaveCallback;
			/*Stores the callback functions to be called in case of an inut event.*/
			Delegate<InputCallback> onInputCallback;
			/*Stores the callback functions to be called in case of a key event.*/
			Delegate<KeyCallback> onKeyCallback;
			/*Stores the callback functions to be called in case of a focus change event.*/
			Delegate<FocusChangedCallback> onFocusChangedCallback;
			/*Stores the callback functions to be called in case of a size change event.*/
			Delegate<SizeChangedCallback> onSizeChangedCallback;
			/*Stores the callback functions to be called in case of an activation event.*/
			Delegate<ActivateCallback> onActivateCallback;
			/*Stores the callback functions to be called in case of an enable event.
			@note:
				The passed value might not represent the actual enabled state of the UIElement.
				Use @[UIElement::enabled] to check whether the UIElement itself is enabled.
			@usage: This callback should be used to update the visual appearance of the UIElement.*/
			Delegate<EnableCallback> onEnableCallback;
			
			/*Called by onCursorMove in case the cursor entered the UIElement in the current update.*/
			void onCursorEnter();
			/*Called by setSize and fitToContent.*/
			void onSizeChanged(const math::fvec2 &old_size, const math::fvec2 &new_size);

			/*Called by onKey, if the UIElement was clicked.*/
			void onActivate(bool active);
			void onEnable(bool enabled);

			/*Updates the @{re::graphics::VertexData} for the borders of this UIElement.*/
			void updateBorderVertexData() const;
			/*Updates the @{re::graphics::VertexData} for the background of this UIElement.*/
			void updateBackgroundVertexData() const;

		public:

			UIElement();
			UIElement(const string &name);

			UIElement(UIElement &&move);
			UIElement &operator=(UIElement &&move);

			UIElement &operator=(const UIElement &copy) = delete;
			UIElement(const UIElement &copy) = delete;

			/*Calls the input event callbacks with the given codepoint as argument.*/
			void onInput(uint32 codepoint);
			/*Calls the key event callbacks with the given KeyEvent as argument.*/
			void onKey(const input::KeyEvent &event);
			/*Calls the cursor move event callbacks with the given cursor position as argument.
			This also generates the onCursorEntered event if necessary.*/
			void onCursorMove(const math::fvec2 &pos);
			/*Calls the cursor leave event callbacks and the leave event of all childrens.
			This is called by the onCursorMove function in case the cursor left this UIElements bounds.
			Call this manually if there is some other kind of reason why the cursor left the element.*/
			void onCursorLeave();
			/*Calls the focus changed event callbacks with the new focused state as argument.
			@param[in] focused: true, if focus was gained, false, if focus was lost.*/
			void onFocusChanged(bool focused);

			/*Adds <callback> to the cursor move event callback list.*/
			void addCursorMoveCallback(CursorMoveCallback callback);
			/*Adds <callback> to the cursor enter event callback list.*/
			void addCursorEnterCallback(CursorEnterCallback callback);
			/*Adds <callback> to the cursor leave event callback list.*/
			void addCursorLeaveCallback(CursorLeaveCallback callback);
			/*Adds <callback> to the input event callback list.*/
			void addInputCallback(InputCallback callback);
			/*Adds <callback> to the key event callback list.*/
			void addKeyCallback(KeyCallback callback);
			/*Adds <callback> to the focus changed event callback list.*/
			void addFocusChangedCallback(FocusChangedCallback callback);
			/*@note:
				The passed value might not represent the actual enabled state of the UIElement.
				Use @[UIElement::enabled] to check whether the UIElement itself is enabled.
			@usage: This callback should be used to update the visual appearance of the UIElement.*/
			void addEnableCallback(EnableCallback callback);

			/*Removes <callback> from the cursor move event callback list.*/
			void removeCursorMoveCallback(CursorMoveCallback callback);
			/*Removes <callback> from the cursor enter event callback list.*/
			void removeCursorEnterCallback(CursorEnterCallback callback);
			/*Removes <callback> from the cursor leave event callback list.*/
			void removeCursorLeaveCallback(CursorLeaveCallback callback);
			/*Removes <callback> from the input event callback list.*/
			void removeInputCallback(InputCallback callback);
			/*Removes <callback> from the key event callback list.*/
			void removeKeyCallback(KeyCallback callback);
			/*Removes <callback> from the focus changed event callback list.*/
			void removeFocusChangedCallback(FocusChangedCallback callback);
			/*Removes <callback> from the enable event callback lis.*/
			void removeEnableCallback(EnableCallback callback);

			/*Returns the parent of this UIElement. If this UIElement does not have a parent, returns null.*/
			UIElement *parent() const;

			/*Returns the name of this UIElement, by which it can be addressed.*/
			const string &name() const;
			/*Sets the name of this UIElement, by which it can be addressed.*/
			void setName(const string &name);


			/*Returns the children of this UIElement.*/
			const std::vector<strong_handle<UIElement>> &children() const;
			/*Returns the children of this UIElement.*/
			std::vector<strong_handle<UIElement>> &children();

			/*Returns whether this UIElement has no children.*/
			bool isLeaf() const;
			/*The number of children this UIElement has.*/
			size_t child_count() const;

			/*Adds a child UIElement to this UIElement.
			The passed UIElement must not belong to another UIElement already.*/
			void addChild(const strong_handle<UIElement> &uiElem);

			/*Returns whether this UIElement posseses a Label.*/
			bool hasText() const;
			/*Returns the handle to the Label of this UIElement. If this UIElement has no Label, returns null.*/
			const strong_handle<Label> &text() const;
			/*Creates a Label with the given text for this UIElement.
			The Label is not allocated by default to reduce the memory overhead caused by UIElements without text.*/
			void createText(const u32string &text, const strong_handle<Font> &font);

			/*Returns the position of this UIElement.
			@return: the position of this UIElement relative to the origin of its parent.*/
			const math::fvec2 &position() const;
			/*Sets the position of this UIElement.
			@param[in] position: the position of this UIElement relative to the origin of its parent.*/
			void setPosition(const math::fvec2 &position);

			/*Sets the background of this UIElement. Invalidates the background model.
			@param[in] background: the background image of this UIElement. null for no image (uni color).
			@param[in] blend_color: the background color of this UIElement.
				If background is null, then this is the color of the background,
				otherwise this is a factor to multiply the background image by.*/
			void setBackground(const strong_handle<graphics::Texture> &background, const math::fvec4 &blend_color, ImageRepetition repeat_x, ImageRepetition repeat_y);
			/*Sets the border of this UIElement. Invalidates the border model.
			@param[in] border: the border texture. Pass null for blank.
			@param[in] blend_color: the border (blending) color. also applies to corners.
			@param[in] border_corner: the border corner texture. Pass null for blank.
			@param[in] repeat_x: the texture repetition @see _border_image_x_repeat_mode.
			@param[in] repeat_y: the texture repetition @see _border_image_y_repeat_mode.*/
			void setBorder(const strong_handle<graphics::Texture> &border, const math::fvec4 &blend_color, const strong_handle<graphics::Texture> &border_corner, ImageRepetition repeat_x, ImageRepetition repeat_y);


			/*Returns the width of this UIElement's border.*/
			float borderWidth() const;
			/*Sets the width of this UIElement's border.*/
			void setBorderWidth(float width);

			/*Returns the color of this UIElement's border.*/
			const math::fvec4 &borderColor() const;
			/*Sets the color of this UIElement's border.*/
			void setBorderColor(const math::fvec4 &color);

			/*Resizes the UIElement to contain all its children and its text.*/
			void fitToContent();


			/*Returns the size of the content of this UIElement.*/
			const math::fvec2 &size() const;
			/*Sets the size of the content of this UIElement.*/
			void setSize(const math::fvec2 &size);
			/*Returns the width of the content of this UIElement.*/
			float width() const;
			/*Returns the height of the content of this UIElement.*/
			float height() const;

			/*Returns the width of this UIElement and its borders.*/
			float boxWidth() const;
			/*Returns the height of this UIElement and its borders.*/
			float boxHeight() const;
			/*Returns the size of this UIElement and its borders.*/
			math::fvec2 boxSize() const;
			/*Returns the position of this UIElement and its borders.*/
			math::fvec2 boxPosition() const;

			/*Returns whether this UIElement contained the cursor the last time it was updated.*/
			bool hovered() const;
			/*Returns whether this UIElement was focused the last time it was updated.*/
			bool focused() const;
			/*Returns whether this UIElement was active (clicked/held) the last time it was updated.*/
			bool active() const;
			/*Returns whether this UIElement is enabled. This can be used to switch interactive behaviour on / off.*/
			bool enabled() const;
			/*Sets the enabled flag to <enabled>.*/
			void setEnabled(bool enabled);

			/*Returns the child or a child of a child with the given name. If no child was found, returns null.*/
			strong_handle<UIElement> findChild(const string &name) const;

			/*Draws the UIElement.
			If the border and background models of this UIElement are invalid, they are updated.*/
			void draw(graphics::RenderSession &session) const;
		};

	}
}


#endif // !__re_ui_uielement_hpp_defined
