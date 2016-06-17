#include "UIElement.hpp"

namespace re
{
	namespace ui
	{
		UIElement::UIElement()
			: _parent(nullptr),
			onCursorMoveCallback(),
			onCursorEnterCallback(),
			onCursorLeaveCallback(),
			onInputCallback(),
			onKeyCallback(),
			onFocusChangedCallback(),
			onActivateCallback(),
			onEnableCallback(),
			_text(nullptr),
			_background_texture(nullptr),
			_border_texture(nullptr),
			_border_corner_texture(nullptr),
			_border_image_x_repeat_mode(ImageRepetition::Stretch),
			_border_image_y_repeat_mode(ImageRepetition::Stretch),
			_background_image_x_repeat_mode(ImageRepetition::Stretch),
			_background_image_y_repeat_mode(ImageRepetition::Stretch),
			_background_vertex_data(nullptr),
			_border_vertex_data(nullptr),
			_border_corner_vertex_data(nullptr),
			_background_color(0,0,0,0),
			_name(),
			_position(0,0),
			_size(0,0),
			_border_color(0,0,0,0),
			_border_width(0),
			_hovered(false),
			_focused(false),
			_active(false),
			_enabled(true),
			_children(),
			_invalid_border_model(false),
			_invalid_background_model(false)
			{ }
		UIElement::UIElement(const string &name)
			: _parent(nullptr),
			onCursorMoveCallback(),
			onCursorEnterCallback(),
			onCursorLeaveCallback(),
			onInputCallback(),
			onKeyCallback(),
			onFocusChangedCallback(),
			onActivateCallback(),
			onEnableCallback(),
			_text(nullptr),
			_background_texture(nullptr),
			_border_texture(nullptr),
			_border_corner_texture(nullptr),
			_border_image_x_repeat_mode(ImageRepetition::Stretch),
			_border_image_y_repeat_mode(ImageRepetition::Stretch),
			_background_image_x_repeat_mode(ImageRepetition::Stretch),
			_background_image_y_repeat_mode(ImageRepetition::Stretch),
			_background_vertex_data(nullptr),
			_border_vertex_data(nullptr),
			_border_corner_vertex_data(nullptr),
			_background_color(0,0,0,0),
			_name(name),
			_position(0,0),
			_size(0,0),
			_border_color(0,0,0,0),
			_border_width(0),
			_hovered(false),
			_focused(false),
			_active(false),
			_enabled(true),
			_children(),
			_invalid_border_model(false),
			_invalid_background_model(false)
			{ }
		UIElement::UIElement(UIElement &&move)
			: _parent(std::move(move._parent)),
			onCursorMoveCallback(std::move(move.onCursorMoveCallback)),
			onCursorEnterCallback(std::move(move.onCursorEnterCallback)),
			onCursorLeaveCallback(std::move(move.onCursorLeaveCallback)),
			onInputCallback(std::move(move.onInputCallback)),
			onKeyCallback(std::move(move.onKeyCallback)),
			onFocusChangedCallback(std::move(move.onFocusChangedCallback)),
			onActivateCallback(std::move(move.onActivateCallback)),
			onEnableCallback(std::move(move.onEnableCallback)),
			_text(std::move(move._text)),
			_background_texture(std::move(move._background_texture)),
			_border_texture(std::move(move._border_texture)),
			_border_corner_texture(std::move(move._border_corner_texture)),
			_border_image_x_repeat_mode(std::move(move._border_image_x_repeat_mode)),
			_border_image_y_repeat_mode(std::move(move._border_image_y_repeat_mode)),
			_background_image_x_repeat_mode(std::move(move._background_image_x_repeat_mode)),
			_background_image_y_repeat_mode(std::move(move._background_image_y_repeat_mode)),
			_background_vertex_data(std::move(move._background_vertex_data)),
			_border_vertex_data(std::move(move._border_vertex_data)),
			_border_corner_vertex_data(std::move(move._border_corner_vertex_data)),
			_background_color(std::move(move._background_color)),
			_name(std::move(move._name)),
			_position(std::move(move._position)),
			_size(std::move(move._size)),
			_border_color(std::move(move._border_color)),
			_border_width(std::move(move._border_width)),
			_hovered(std::move(move._hovered)),
			_focused(std::move(move._focused)),
			_active(std::move(move._active)),
			_enabled(std::move(move._enabled)),
			_children(std::move(move._children)),
			_invalid_border_model(std::move(move._invalid_border_model)),
			_invalid_background_model(std::move(move._invalid_background_model))
		{
			for(const auto &child : _children)
				child->_parent = this;
		}

		UIElement &UIElement::operator=(UIElement &&move)
		{
			if(&move == this)
				return *this;

			_parent = std::move(move._parent);
			onCursorMoveCallback = std::move(move.onCursorMoveCallback);
			onCursorEnterCallback = std::move(move.onCursorEnterCallback);
			onCursorLeaveCallback = std::move(move.onCursorLeaveCallback);
			onInputCallback = std::move(move.onInputCallback);
			onKeyCallback = std::move(move.onKeyCallback);
			onFocusChangedCallback = std::move(move.onFocusChangedCallback);
			onActivateCallback = std::move(move.onActivateCallback);
			onEnableCallback = std::move(move.onEnableCallback);
			_text = std::move(move._text);
			_background_texture = std::move(move._background_texture);
			_border_texture = std::move(move._border_texture);
			_border_corner_texture = std::move(move._border_corner_texture);
			_border_image_x_repeat_mode = std::move(move._border_image_x_repeat_mode);
			_border_image_y_repeat_mode = std::move(move._border_image_y_repeat_mode);
			_background_image_x_repeat_mode = std::move(move._background_image_x_repeat_mode);
			_background_image_y_repeat_mode = std::move(move._background_image_y_repeat_mode);
			_background_vertex_data = std::move(move._background_vertex_data);
			_border_vertex_data = std::move(move._border_vertex_data);
			_border_corner_vertex_data = std::move(move._border_corner_vertex_data);
			_background_color = std::move(move._background_color);
			_name = std::move(move._name);
			_position = std::move(move._position);
			_size = std::move(move._size);
			_border_color = std::move(move._border_color);
			_border_width = std::move(move._border_width);
			_hovered = std::move(move._hovered);
			_focused = std::move(move._focused);
			_active = std::move(move._active);
			_enabled = std::move(move._enabled);
			_children = std::move(move._children);
			_invalid_border_model = std::move(move._invalid_border_model);
			_invalid_background_model = std::move(move._invalid_background_model);

			for(const auto &child : _children)
				child->_parent = this;

			return *this;
		}


		void UIElement::onActivate(bool active)
		{
			if(_active == active)
				return;
			_active = active;
			// if the parent object is deactivated, deactivate all children too.
			if(!active)
				for(const auto &child: _children)
					child->onActivate(false);
			onActivateCallback(*this, std::move(active));
		}

		void UIElement::onEnable(bool enabled)
		{
			for(const auto &child: _children)
				child->onEnable(enabled);
			onEnableCallback(*this, std::move(enabled));
		}

		void UIElement::onKey(const input::KeyEvent &event)
		{
			onKeyCallback(*this, event);

			if(_hovered && event.key == input::Key::MB_LEFT && event.pressed)
				onActivate(true);
			else if(_active && event.key == input::Key::MB_LEFT && !event.pressed)
				onActivate(false);

			for(const auto &child : _children)
				child->onKey(event);
		}
		void UIElement::onInput(uint32 codepoint)
		{
			for(const auto &child : _children)
				child->onInput(codepoint);

			onInputCallback(*this, std::move(codepoint));
		}
		void UIElement::onCursorMove(const math::fvec2 &pos)
		{
			if(!_hovered && pos.x >= 0 && pos.x < _size.x && pos.y >= 0 && pos.y <= _size.y)
				onCursorEnter();
			else if(_hovered && (pos.x < 0 || pos.x > _size.x || pos.y < 0 || pos.y > _size.y))
				onCursorLeave();
			if(_hovered)
			{
				for(const auto &child: _children)
					child->onCursorMove(pos - child->_position);

				onCursorMoveCallback(*this, pos);
			}
		}
		void UIElement::onCursorEnter()
		{
			// avoid redundant calls.
			if(_hovered)
				return;
			_hovered = true;
			onCursorEnterCallback(*this);
		}
		void UIElement::onCursorLeave()
		{
			// avoid redundant calls.
			if(!_hovered)
				return;
			_hovered = false;

			for(const auto &child: _children)
				child->onCursorLeave();

			onCursorLeaveCallback(*this);
		}

		void UIElement::onFocusChanged(bool focus)
		{
			// avoid redundant calls.
			if(_focused == focus)
				return;
			_focused = focus;
			onFocusChangedCallback(*this, std::move(focus));
		}

		UIElement *UIElement::parent() const
		{
			return _parent;
		}

		const string &UIElement::name() const { return _name; }
		void UIElement::setName(const string &name) { _name = name; }

		const std::vector<strong_handle<UIElement>> &UIElement::children() const { return _children; }
		std::vector<strong_handle<UIElement>> &UIElement::children() { return _children; }

		void UIElement::addChild(const strong_handle<UIElement> &uiElem)
		{
			RE_ASSERT(uiElem);
			RE_ASSERT(!uiElem->_parent);
			_children.push_back(uiElem);
			uiElem->_parent = this;
		}

		bool UIElement::hasText() const { return (bool)_text; }
		const strong_handle<Label> &UIElement::text() const { return _text; }
		void UIElement::createText(const u32string &text, const strong_handle<Font> &font)
		{
			_text = alloc<Label>();
			_text->setFont(font);
			_text->setText(text);
		}

		const math::fvec2 &UIElement::position() const { return _position; }
		void UIElement::setPosition(const math::fvec2 &position) { _position = position; }

		const math::fvec2 &UIElement::size() const { return _size; }
		void UIElement::setSize(const math::fvec2 &size) { onSizeChanged(_size, size); _size = size; }

		float UIElement::width() const { return _size.x; }
		float UIElement::height() const { return _size.y; }

		bool UIElement::hovered() const { return _hovered; }
		bool UIElement::focused() const { return _focused; }
		bool UIElement::active() const { return _active; }
		
		bool UIElement::enabled() const
		{
			const UIElement * parent = this;
			while(parent = parent->_parent)
				if(!parent->_enabled)
					return false;
			return _enabled;
		}

		void UIElement::setEnabled(bool enabled) { onEnable(enabled); _enabled = enabled; }

		strong_handle<UIElement> UIElement::findChild(const string &name) const
		{
			// do not allow unnamed elements to be found.
			if(name.empty())
				return strong_handle<UIElement>(nullptr);

			for(const auto &child: _children)
				if(child->_name == name)
					return child;

			for(const auto &child: _children)
				if(const auto &ret = child->findChild(name))
					return ret;

			return strong_handle<UIElement>(nullptr);
		}

		bool UIElement::isLeaf() const { return _children.empty(); }
		size_t UIElement::child_count() const { return _children.size(); }

		void UIElement::fitToContent()
		{
			const math::fvec2 old_size = _size;
			if(_text)
				_size = _text->getSize()+math::fvec2(_text->getMinPosition().x, -_text->getMinPosition().y);
			else _size = math::fvec2(0,0);
			for(const auto &child : _children)
			{
				const math::fvec2 max(child->boxPosition()+ child->boxSize());
				_size.x = math::max(_size.x, max.x);
				_size.y = math::max(_size.y, max.y);
			}

			onSizeChanged(old_size, _size);
		}

		void UIElement::setBorderWidth(float width)
		{
			_border_width = width;
			_invalid_border_model = true;
		}

		void UIElement::onSizeChanged(const math::fvec2 &old_size, const math::fvec2 &new_size)
		{
			onSizeChangedCallback(*this, old_size, new_size);

			_invalid_background_model = true;
			_invalid_border_model = true;
		}

		void UIElement::addCursorMoveCallback(CursorMoveCallback callback)
		{
			onCursorMoveCallback += callback;
		}

		void UIElement::addCursorEnterCallback(CursorEnterCallback callback)
		{
			onCursorEnterCallback += callback;
		}
		void UIElement::addCursorLeaveCallback(CursorLeaveCallback callback)
		{
			onCursorLeaveCallback += callback;
		}
		void UIElement::addInputCallback(InputCallback callback)
		{
			onInputCallback += callback;
		}
		void UIElement::addKeyCallback(KeyCallback callback)
		{
			onKeyCallback += callback;
		}
		void UIElement::addFocusChangedCallback(FocusChangedCallback callback)
		{
			onFocusChangedCallback += callback;
		}

		void UIElement::removeCursorMoveCallback(CursorMoveCallback callback)
		{
			onCursorMoveCallback -= callback;
		}

		void UIElement::removeCursorEnterCallback(CursorEnterCallback callback)
		{
			onCursorEnterCallback -= callback;
		}
		void UIElement::removeCursorLeaveCallback(CursorLeaveCallback callback)
		{
			onCursorLeaveCallback -= callback;
		}
		void UIElement::removeInputCallback(InputCallback callback)
		{
			onInputCallback -= callback;
		}
		void UIElement::removeKeyCallback(KeyCallback callback)
		{
			onKeyCallback -= callback;
		}
		void UIElement::removeFocusChangedCallback(FocusChangedCallback callback)
		{
			onFocusChangedCallback -= callback;
		}

		void UIElement::setBackground(const strong_handle<graphics::Texture> &background, const math::fvec4 &blend_color, ImageRepetition repeat_x, ImageRepetition repeat_y)
		{
			if(background != _background_texture || repeat_x != _background_image_x_repeat_mode || repeat_y != _background_image_y_repeat_mode)
				_invalid_background_model = true;

			_background_texture = background;
			_background_color = blend_color;
			_background_image_x_repeat_mode = repeat_x;
			_background_image_y_repeat_mode = repeat_y;
		}

		void UIElement::setBorder(const strong_handle<graphics::Texture> &border, const math::fvec4 &blend_color, const strong_handle<graphics::Texture> &border_corner, ImageRepetition repeat_x, ImageRepetition repeat_y)
		{
			if(border != _border_texture || border_corner != _border_corner_texture || repeat_x != _border_image_x_repeat_mode || repeat_y != _border_image_y_repeat_mode)
				_invalid_border_model = true;

			_border_texture = border;
			_border_color = blend_color;
			_border_corner_texture = border_corner;
			_border_image_x_repeat_mode = repeat_x;
			_border_image_y_repeat_mode = repeat_y;
		}


		void UIElement::draw(graphics::RenderSession &session) const
		{
			// update invalid models.
			if(_invalid_background_model)
				updateBackgroundVertexData();
			if(_invalid_border_model)
				updateBorderVertexData();

			glClear(GL_DEPTH_BUFFER_BIT);
			/// render background.

			if(_background_vertex_data)
			{
				// is there a background image?
				if(_background_texture)
					_background_texture->bind();
				else // unbind texture, so we have blank texture.
					graphics::Texture::unbind();

				session.push_color(_background_color);
				session.pass_values();

				_background_vertex_data->draw();

				// remove the background color from the color stack.
				session.pop_color();
			}

			/// render border.
			RE_OGL(glClear(GL_DEPTH_BUFFER_BIT));

			// is there a border set?
			if(_border_vertex_data)
			{
				if(_border_texture)
					_border_texture->bind();
				else graphics::Texture::unbind();

				session.push_color(_border_color);
				session.pass_values();

				// render the border.
				_border_vertex_data->draw();

				// is there a corner model?
				if(_border_corner_vertex_data)
				{
					if(_border_corner_texture)
						_border_corner_texture->bind();
					else
						graphics::Texture::unbind();

					_border_corner_vertex_data->draw();
				}

				session.pop_color();
			}

			RE_OGL(glClear(GL_DEPTH_BUFFER_BIT));

			// create translation matrix for the children.
			session.push_matrix(session.matrix()*math::fmat4x4::translation(math::fvec3(_position.x, -_position.y, 0)));
			session.pass_values();
			/// render text.

			if(_text)
				_text->draw();
			
			// render the children.
			for(const auto &child: _children)
				child->draw(session);

			// remove the matrix from the matrix stack.
			session.pop_matrix();
		}

		void UIElement::updateBorderVertexData() const
		{
			if(!_invalid_border_model)
				return;

			_invalid_border_model = false;

			if(_border_width <= 0)
			{
				// set the border to empty
				_border_vertex_data = unique_handle<graphics::VertexData>(nullptr);
				_border_corner_vertex_data = unique_handle<graphics::VertexData>(nullptr);
				return;
			}
			else
			{
				const math::fvec2 box_pos(boxPosition().x, boxPosition().y);


				float ol(box_pos.x), il(_position.x), ir(_position.x+_size.x), or(box_pos.x+boxWidth()),
					ot(-box_pos.y), it(-_position.y), ib(-_position.y-_size.y), ob(-box_pos.y-boxHeight());

				math::fvec4 color(1,1,1,1);

				float t_h_s = 1; // horizontal border horizontal tex coord
				float t_h_t = 1; // horizontal border vertical tex coord
				float t_v_s = 1; // vertical border horizontal tex coord
				float t_v_t = 1; // vertical border vertical tex coord
				if(_border_texture)
				{
					uint32 tex_w = _border_texture->getWidth();
					uint32 tex_h = _border_texture->getHeight();

					if(_border_image_x_repeat_mode == ImageRepetition::Tile)
					{
						t_h_s = boxWidth() / tex_w;
						t_v_s = boxHeight() / tex_w;
					}
					if(_border_image_y_repeat_mode == ImageRepetition::Tile)
					{
						t_h_t = _border_width / tex_h;
						t_v_t = _border_width / tex_h;
					}
				}

				graphics::Vertex border_verts[3*2*4] = {
					// top border
					graphics::Vertex(math::fvec3(il,ot,0), math::fvec2(0,t_h_t), color),
					graphics::Vertex(math::fvec3(il,it,0), math::fvec2(0,0), color),
					graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(t_h_s,0), color),
					
					graphics::Vertex(math::fvec3(il,ot,0), math::fvec2(0,t_h_t), color),
					graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(t_h_s,0), color),
					graphics::Vertex(math::fvec3(ir,ot,0), math::fvec2(t_h_s,t_h_t), color),

					
					// bottom border
					graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(t_h_s,0), color),
					graphics::Vertex(math::fvec3(il,ob,0), math::fvec2(t_h_s,t_h_t), color),
					graphics::Vertex(math::fvec3(ir,ob,0), math::fvec2(0,t_h_t), color),
					
					graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(t_h_s,0), color),
					graphics::Vertex(math::fvec3(ir,ob,0), math::fvec2(0,t_h_t), color),
					graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(0,0), color),

					// left border
					graphics::Vertex(math::fvec3(ol,it,0), math::fvec2(t_v_s,t_v_t), color),
					graphics::Vertex(math::fvec3(ol,ib,0), math::fvec2(0,t_v_t), color),
					graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(0,0), color),
					
					graphics::Vertex(math::fvec3(ol,it,0), math::fvec2(t_v_s,t_v_t), color),
					graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(0,0), color),
					graphics::Vertex(math::fvec3(il,it,0), math::fvec2(t_v_s,0), color),

					// right border
					graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(0,0), color),
					graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(t_v_s,0), color),
					graphics::Vertex(math::fvec3(or,ib,0), math::fvec2(t_v_s,t_v_t), color),
					
					graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(0,0), color),
					graphics::Vertex(math::fvec3(or,ib,0), math::fvec2(t_v_s,t_v_t), color),
					graphics::Vertex(math::fvec3(or,it,0), math::fvec2(0,t_v_t), color)
				};

				graphics::Vertex border_corner_verts[3*2*4] = {
					// top left corner
					graphics::Vertex(math::fvec3(ol,ot,0), math::fvec2(0,t_h_t), color),
					graphics::Vertex(math::fvec3(ol,it,0), math::fvec2(0,0), color),
					graphics::Vertex(math::fvec3(il,it,0), math::fvec2(t_v_t,0), color),
					
					graphics::Vertex(math::fvec3(ol,ot,0), math::fvec2(0,t_h_t), color),
					graphics::Vertex(math::fvec3(il,it,0), math::fvec2(t_v_t,0), color),
					graphics::Vertex(math::fvec3(il,ot,0), math::fvec2(t_v_t,t_h_t), color),

					// top right corner
					graphics::Vertex(math::fvec3(or,ot,0), math::fvec2(0,t_v_t), color),
					graphics::Vertex(math::fvec3(ir,ot,0), math::fvec2(0,0), color),
					graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(t_h_t,0), color),
					
					graphics::Vertex(math::fvec3(or,ot,0), math::fvec2(0,t_v_t), color),
					graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(t_h_t,0), color),
					graphics::Vertex(math::fvec3(or,it,0), math::fvec2(t_h_t,t_v_t), color),

					// bottom right corner
					graphics::Vertex(math::fvec3(or,ob,0), math::fvec2(0,t_h_t), color),
					graphics::Vertex(math::fvec3(or,ib,0), math::fvec2(0,0), color),
					graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(t_v_t,0), color),

					graphics::Vertex(math::fvec3(or,ob,0), math::fvec2(0,t_h_t), color),
					graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(t_v_t,0), color),
					graphics::Vertex(math::fvec3(ir,ob,0), math::fvec2(t_v_t,t_h_t), color),

					// bottom left corner
					graphics::Vertex(math::fvec3(ol,ob,0), math::fvec2(0,t_v_t), color),
					graphics::Vertex(math::fvec3(il,ob,0), math::fvec2(0,0), color),
					graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(t_h_t,0), color),
					
					graphics::Vertex(math::fvec3(ol,ob,0), math::fvec2(0,t_v_t), color),
					graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(t_h_t,0), color),
					graphics::Vertex(math::fvec3(ol,ib,0), math::fvec2(t_h_t,t_v_t), color)
				};

				if(!_border_vertex_data)
					_border_vertex_data = alloc<graphics::VertexData>(graphics::RenderMode::RM_TRIANGLES, graphics::AllocationStrategy::AS_STATIC);
				if(!_border_corner_vertex_data)
					_border_corner_vertex_data = alloc<graphics::VertexData>(graphics::RenderMode::RM_TRIANGLES, graphics::AllocationStrategy::AS_STATIC);

				_border_vertex_data->setData(border_verts, _countof(border_verts));
				_border_corner_vertex_data->setData(border_corner_verts, _countof(border_corner_verts));
			}
		}

		void UIElement::updateBackgroundVertexData() const
		{
			if(!_invalid_background_model)
				return;
			_invalid_background_model = false;

			// is the background at 0% alpha?
			if(_background_color.w == 0)
			{
				_background_vertex_data = unique_handle<graphics::VertexData>(nullptr);
				return;
			}
			else
			{
				float l(_position.x), r(_position.x+_size.x), t(-_position.y), b(-_position.y-_size.y);

				float t_h = 1;
				float t_v = 1;
				if(_background_texture)
				{
					if(_background_image_x_repeat_mode == ImageRepetition::Tile)
						t_h = _size.x / _background_texture->getWidth();
					if(_background_image_y_repeat_mode == ImageRepetition::Tile)
						t_v = _size.y / _background_texture->getHeight();
				}

				math::fvec4 color(1,1,1,1);

				graphics::Vertex background_verts[2*3] = {
					graphics::Vertex(math::fvec3(l,t,0), math::fvec2(0,t_v), color),
					graphics::Vertex(math::fvec3(l,b,0), math::fvec2(0,0), color),
					graphics::Vertex(math::fvec3(r,b,0), math::fvec2(t_h,0), color),
					
					graphics::Vertex(math::fvec3(l,t,0), math::fvec2(0,t_v), color),
					graphics::Vertex(math::fvec3(r,b,0), math::fvec2(t_h,0), color),
					graphics::Vertex(math::fvec3(r,t,0), math::fvec2(t_h,t_v), color)
				};

				if(!_background_vertex_data)
					_background_vertex_data = alloc<graphics::VertexData>(graphics::RenderMode::RM_TRIANGLES, graphics::AllocationStrategy::AS_STATIC);

				_background_vertex_data->setData(background_verts, _countof(background_verts));
			}
		}

		float UIElement::boxWidth() const
		{
			return _size.x + 2*_border_width;
		}
		float UIElement::boxHeight() const
		{
			return _size.y + 2* _border_width;
		}

		math::fvec2 UIElement::boxSize() const
		{
			return math::fvec2(boxWidth(), boxHeight());
		}
		
		math::fvec2 UIElement::boxPosition() const
		{
			return _position-math::fvec2(_border_width, _border_width);
		}
	}
}