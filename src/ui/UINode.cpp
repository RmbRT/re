#include "UINode.hpp"


namespace re
{
	namespace ui
	{
		void UINode::content_changed() const
		{
			const UINode * node = this;

			while(node)
			{
				node->m_invalid_width = true;
				node->m_invalid_height = true;
				node->m_invalid_background_model = true;
				node->m_invalid_border_model = true;
				node->m_invalid_children = true;

				node = node->m_parent;
			}
		}

		void UINode::update_models() const
		{
			update_border_model();
			update_background_model();
		}

		void UINode::update_border_model() const
		{
			if(!m_invalid_border_model)
				return;
			m_invalid_border_model = false;

			const math::fvec2_t box_pos(absolute_left(), absolute_top());
			const math::fvec2_t box_size(absolute_box_width(), absolute_box_height());
			const math::fvec2_t inner_size(absolute_content_area_width(), absolute_content_area_height());

			float o_l(box_pos.x);
			float i_l(o_l+m_border.left.width());
			float i_r(i_l+inner_size.x);
			float o_r(box_pos.x+box_size.x);
			float o_t(-box_pos.y);
			float i_t(-box_pos.y-m_border.top.width());
			float i_b(i_t-inner_size.y);
			float o_b(-box_pos.y-box_size.y);

			math::fvec4_t color(1,1,1,1);

			float t_top_s = 1; // horizontal border horizontal tex coord
			float t_top_t = 1; // horizontal border vertical tex coord
			float t_right_s = 1; // vertical border horizontal tex coord
			float t_right_t = 1; // vertical border vertical tex coord
			float t_bot_s = 1;
			float t_bot_t = 1;
			float t_left_s = 1;
			float t_left_t = 1;

			if(m_border.top.image().texture)
			{
				size_t tex_w = m_border.top.image().texture->width();
				size_t tex_h = m_border.top.image().texture->height();

				if(m_border.top.image().repeat.x == layout::Repeat::Tile)
					t_top_s = inner_size.x / tex_w;
				if(m_border.top.image().repeat.y == layout::Repeat::Tile)
					t_top_t = -m_border.top.width() / tex_h;
			}
			if(m_border.right.image().texture)
			{
				size_t tex_w = m_border.right.image().texture->width();
				size_t tex_h = m_border.right.image().texture->height();

				if(m_border.right.image().repeat.x == layout::Repeat::Tile)
					t_right_s = inner_size.y / tex_w;
				if(m_border.right.image().repeat.y == layout::Repeat::Tile)
					t_right_t = -m_border.right.width() / tex_h;
			}
			if(m_border.bottom.image().texture)
			{
				size_t tex_w = m_border.bottom.image().texture->width();
				size_t tex_h = m_border.bottom.image().texture->height();

				if(m_border.bottom.image().repeat.x == layout::Repeat::Tile)
					t_bot_s = inner_size.x / tex_w;
				if(m_border.bottom.image().repeat.y == layout::Repeat::Tile)
					t_bot_t = -m_border.bottom.width() / tex_h;
			}
			if(m_border.left.image().texture)
			{
				uint32_t tex_w = m_border.left.image().texture->width();
				uint32_t tex_h = m_border.left.image().texture->height();

				if(m_border.left.image().repeat.x == layout::Repeat::Tile)
					t_left_s = inner_size.x / tex_w;
				if(m_border.left.image().repeat.y == layout::Repeat::Tile)
					t_left_t = -m_border.left.width() / tex_h;
			}

			std::vector<Vertex> border_verts = {
				// top border
				Vertex(math::fvec3_t(i_l,o_t,0), math::fvec2_t(0,0), m_border.top.image().color),
				Vertex(math::fvec3_t(i_l,i_t,0), math::fvec2_t(0,t_top_t), m_border.top.image().color),
				Vertex(math::fvec3_t(i_r,i_t,0), math::fvec2_t(t_top_s,t_top_t), m_border.top.image().color),

				Vertex(math::fvec3_t(i_l,o_t,0), math::fvec2_t(0,0), m_border.top.image().color),
				Vertex(math::fvec3_t(i_r,i_t,0), math::fvec2_t(t_top_s,t_top_t), m_border.top.image().color),
				Vertex(math::fvec3_t(i_r,o_t,0), math::fvec2_t(t_top_s,0), m_border.top.image().color),


				// bottom border
				Vertex(math::fvec3_t(i_l,i_b,0), math::fvec2_t(0,0), m_border.bottom.image().color),
				Vertex(math::fvec3_t(i_l,o_b,0), math::fvec2_t(0,t_bot_t), m_border.bottom.image().color),
				Vertex(math::fvec3_t(i_r,o_b,0), math::fvec2_t(t_bot_s,t_bot_t), m_border.bottom.image().color),

				Vertex(math::fvec3_t(i_l,i_b,0), math::fvec2_t(0,0), m_border.bottom.image().color),
				Vertex(math::fvec3_t(i_r,o_b,0), math::fvec2_t(t_bot_s,t_bot_t), m_border.bottom.image().color),
				Vertex(math::fvec3_t(i_r,i_b,0), math::fvec2_t(t_bot_s,0), m_border.bottom.image().color),

				// left border
				Vertex(math::fvec3_t(o_l,i_t,0), math::fvec2_t(0,0), m_border.left.image().color),
				Vertex(math::fvec3_t(o_l,i_b,0), math::fvec2_t(0,t_left_t), m_border.left.image().color),
				Vertex(math::fvec3_t(i_l,i_b,0), math::fvec2_t(t_left_s,t_left_t), m_border.left.image().color),

				Vertex(math::fvec3_t(o_l,i_t,0), math::fvec2_t(0,0), m_border.left.image().color),
				Vertex(math::fvec3_t(i_l,i_b,0), math::fvec2_t(t_left_s,t_left_t), m_border.left.image().color),
				Vertex(math::fvec3_t(i_l,i_t,0), math::fvec2_t(t_left_s,0), m_border.left.image().color),

				// right border
				Vertex(math::fvec3_t(i_r,i_t,0), math::fvec2_t(0,0), m_border.right.image().color),
				Vertex(math::fvec3_t(i_r,i_b,0), math::fvec2_t(0,t_right_t), m_border.right.image().color),
				Vertex(math::fvec3_t(o_r,i_b,0), math::fvec2_t(t_right_s,t_right_t), m_border.right.image().color),

				Vertex(math::fvec3_t(i_r,i_t,0), math::fvec2_t(0,0), m_border.right.image().color),
				Vertex(math::fvec3_t(o_r,i_b,0), math::fvec2_t(t_right_s,t_right_t), m_border.right.image().color),
				Vertex(math::fvec3_t(o_r,i_t,0), math::fvec2_t(t_right_s,0), m_border.right.image().color)
			};

			float t_tl_s = 1;
			float t_tl_t = 1;
			float t_tr_s = 1;
			float t_tr_t = 1;
			float t_bl_s = 1;
			float t_bl_t = 1;
			float t_br_s = 1;
			float t_br_t = 1;

			if(m_border_corner_top_left.texture)
			{
				uint32_t tex_w = m_border_corner_top_left.texture->width();
				uint32_t tex_h = m_border_corner_top_left.texture->height();

				if(m_border_corner_top_left.repeat.x == layout::Repeat::Tile)
					t_tl_s = m_border.left.width() / tex_w;
				if(m_border_corner_top_left.repeat.y == layout::Repeat::Tile)
					t_tl_t = -m_border.top.width() / tex_h;
			}
			if(m_border_corner_top_right.texture)
			{
				uint32_t tex_w = m_border_corner_top_right.texture->width();
				uint32_t tex_h = m_border_corner_top_right.texture->height();

				if(m_border_corner_top_right.repeat.x == layout::Repeat::Tile)
					t_tr_s = m_border.right.width() / tex_w;
				if(m_border_corner_top_right.repeat.y == layout::Repeat::Tile)
					t_tr_t = -m_border.top.width() / tex_h;
			}
			if(m_border_corner_bottom_left.texture)
			{
				uint32_t tex_w = m_border_corner_bottom_left.texture->width();
				uint32_t tex_h = m_border_corner_bottom_left.texture->height();

				if(m_border_corner_bottom_left.repeat.x == layout::Repeat::Tile)
					t_bl_s = m_border.left.width() / tex_w;
				if(m_border_corner_bottom_left.repeat.y == layout::Repeat::Tile)
					t_bl_t = -m_border.bottom.width() / tex_h;
			}
			if(m_border_corner_bottom_right.texture)
			{
				uint32_t tex_w = m_border_corner_bottom_right.texture->width();
				uint32_t tex_h = m_border_corner_bottom_right.texture->height();

				if(m_border_corner_bottom_right.repeat.x == layout::Repeat::Tile)
					t_br_s = m_border.right.width() / tex_w;
				if(m_border_corner_bottom_right.repeat.y == layout::Repeat::Tile)
					t_br_t = -m_border.bottom.width() / tex_h;
			}



			std::vector<Vertex> border_corner_verts = {
				// top left corner
				Vertex(math::fvec3_t(o_l,o_t,0), math::fvec2_t(0,0), m_border_corner_top_left.color),
				Vertex(math::fvec3_t(o_l,i_t,0), math::fvec2_t(0,t_tl_t), m_border_corner_top_left.color),
				Vertex(math::fvec3_t(i_l,i_t,0), math::fvec2_t(t_tl_s,t_tl_t), m_border_corner_top_left.color),

				Vertex(math::fvec3_t(o_l,o_t,0), math::fvec2_t(0,0), m_border_corner_top_left.color),
				Vertex(math::fvec3_t(i_l,i_t,0), math::fvec2_t(t_tl_s,t_tl_t), m_border_corner_top_left.color),
				Vertex(math::fvec3_t(i_l,o_t,0), math::fvec2_t(t_tl_s,0), m_border_corner_top_left.color),

				// top right corner
				Vertex(math::fvec3_t(i_r,o_t,0), math::fvec2_t(0,0), m_border_corner_top_right.color),
				Vertex(math::fvec3_t(i_r,i_t,0), math::fvec2_t(0,t_tr_t), m_border_corner_top_right.color),
				Vertex(math::fvec3_t(o_r,i_t,0), math::fvec2_t(t_tr_s,t_tr_t), m_border_corner_top_right.color),

				Vertex(math::fvec3_t(i_r,o_t,0), math::fvec2_t(0,0), m_border_corner_top_right.color),
				Vertex(math::fvec3_t(o_r,i_t,0), math::fvec2_t(t_tr_s,t_tr_t), m_border_corner_top_right.color),
				Vertex(math::fvec3_t(o_r,o_t,0), math::fvec2_t(t_tr_s,0), m_border_corner_top_right.color),

				// bottom right corner
				Vertex(math::fvec3_t(i_r,i_b,0), math::fvec2_t(0,0), m_border_corner_bottom_right.color),
				Vertex(math::fvec3_t(i_r,o_b,0), math::fvec2_t(0,t_br_t), m_border_corner_bottom_right.color),
				Vertex(math::fvec3_t(o_r,o_b,0), math::fvec2_t(t_br_s,t_br_t), m_border_corner_bottom_right.color),

				Vertex(math::fvec3_t(i_r,i_b,0), math::fvec2_t(0,0), m_border_corner_bottom_right.color),
				Vertex(math::fvec3_t(o_r,o_b,0), math::fvec2_t(t_br_s,t_br_t), m_border_corner_bottom_right.color),
				Vertex(math::fvec3_t(o_r,i_b,0), math::fvec2_t(t_br_s,0), m_border_corner_bottom_right.color),

				// bottom left corner
				Vertex(math::fvec3_t(o_l,i_b,0), math::fvec2_t(0,0), m_border_corner_bottom_left.color),
				Vertex(math::fvec3_t(o_l,o_b,0), math::fvec2_t(0,t_bl_t), m_border_corner_bottom_left.color),
				Vertex(math::fvec3_t(i_l,o_b,0), math::fvec2_t(t_bl_s,t_bl_t), m_border_corner_bottom_left.color),

				Vertex(math::fvec3_t(o_l,i_b,0), math::fvec2_t(0,0), m_border_corner_bottom_left.color),
				Vertex(math::fvec3_t(i_l,o_b,0), math::fvec2_t(t_bl_s,t_bl_t), m_border_corner_bottom_left.color),
				Vertex(math::fvec3_t(i_l,i_b,0), math::fvec2_t(t_bl_s,0), m_border_corner_bottom_left.color)
			};

			if(!m_border_model.exists() || !m_border_corner_model.exists())
			{
				auto * buffer = util::allocation_buffer<VertexArray *>(2);
				size_t elements = 0;
				if(!m_border_corner_model.exists())
					buffer[elements++] = &m_border_corner_model;
				if(!m_border_model.exists())
					buffer[elements++] = &m_border_model;

				VertexArray::alloc(buffer, elements);
			}

			m_border_model.set_data(
				std::move(border_verts),
				graphics::gl::RenderMode::Triangles);

			if(!m_border_corner_model.exists())
				m_border_corner_model.alloc();

			m_border_corner_model.set_data(
				std::move(border_corner_verts),
				graphics::gl::RenderMode::Triangles);
		}

		void UINode::update_background_model() const
		{
			if(!m_invalid_background_model)
				return;
			m_invalid_background_model = false;

			const math::fvec2_t inner_pos(
				absolute_left() + m_border.left.width(),
				absolute_top() + m_border.top.width());
			const math::fvec2_t inner_size(
				absolute_content_area_width(),
				absolute_content_area_height());

			const float i_l = inner_pos.x;
			const float i_r = inner_pos.x+inner_size.x;
			const float i_t = -inner_pos.y;
			const float i_b = -inner_pos.y-inner_size.y;


			float t_s = 1;
			float t_t = 1;

			if(m_background.texture)
			{
				uint32_t tex_w = m_background.texture->width();
				uint32_t tex_h = m_background.texture->height();

				if(m_background.repeat.x == layout::Repeat::Tile)
					t_s = inner_size.x / tex_w;
				if(m_background.repeat.y == layout::Repeat::Tile)
					t_t = inner_size.y / tex_h;
			}

			std::vector<Vertex> background_verts = {
				Vertex(math::fvec3_t(i_l,i_t,0), math::fvec2_t(0,0), m_background.color),
				Vertex(math::fvec3_t(i_l,i_b,0), math::fvec2_t(0,t_t), m_background.color),
				Vertex(math::fvec3_t(i_r,i_b,0), math::fvec2_t(t_s,t_t), m_background.color),

				Vertex(math::fvec3_t(i_l,i_t,0), math::fvec2_t(0,0), m_background.color),
				Vertex(math::fvec3_t(i_r,i_b,0), math::fvec2_t(t_s,t_t), m_background.color),
				Vertex(math::fvec3_t(i_r,i_t,0), math::fvec2_t(t_s,0), m_background.color)
			};

			if(!m_background_model.exists())
				m_background_model.alloc();

			m_background_model.set_data(
				std::move(background_verts),
				graphics::gl::RenderMode::Triangles);
		}


		UINode::UINode():
			m_parent(nullptr),
			m_invalid_width(true),
			m_invalid_height(true),
			m_temp_last_absolute_content_height(0),
			m_temp_last_absolute_content_width(0),
			m_invalid_background_model(true),
			m_invalid_border_model(true),
			m_invalid_children(true),
			m_font(nullptr),
			m_prev_sibling(nullptr),
			m_next_sibling(nullptr),
			m_border_corner_top_left_model(graphics::gl::BufferAccess::Dynamic, graphics::gl::BufferUsage::Draw),
			m_border_corner_top_right_model(graphics::gl::BufferAccess::Dynamic, graphics::gl::BufferUsage::Draw),
			m_border_corner_bottom_left_model(graphics::gl::BufferAccess::Dynamic, graphics::gl::BufferUsage::Draw),
			m_border_corner_bottom_right_model(graphics::gl::BufferAccess::Dynamic, graphics::gl::BufferUsage::Draw)

		{ }

		UINode::UINode(UINode && move):
			parent(move.parent),
			children(std::move(move.children)),
			name(std::move(move.name)),
			align(move.align),
			position(move.position),
			min_size(move.min_size),
			max_size(move.max_size),
			margin(move.margin),
			padding(move.padding),
			border(move.border),
			background(move.background),
			display(move.display),
			scrollbars(std::move(move.scrollbars)),
			background_model(std::move(move.background_model)),
			border_model(std::move(move.border_model)),
			invalid_background_model(move.invalid_background_model),
			invalid_border_model(move.invalid_border_model),
			invalid_width(move.invalid_width),
			invalid_height(move.invalid_height),
			temp_last_absolute_content_height(move.temp_last_absolute_content_height),
			temp_last_absolute_content_width(move.temp_last_absolute_content_width),
			invalid_children(move.invalid_children),
			border_corner_top_left(move.border_corner_top_left),
			border_corner_top_right(move.border_corner_top_right),
			border_corner_bottom_left(move.border_corner_bottom_left),
			border_corner_bottom_right(move.border_corner_bottom_right),
			border_corner_model(std::move(move.border_corner_model)),
			font(std::move(move.font)),
			prev_sibling(std::move(move.prev_sibling)),
			next_sibling(std::move(move.next_sibling))
		{
			for(auto const& child : children)
				child->parent = this;
		}

		UINode &UINode::operator=(UINode &&move)
		{
			if(this == &move)
				return *this;

			parent = move.parent;
			children = std::move(move.children);
			name = std::move(move.name);
			align = move.align;
			position = move.position;
			min_size = move.min_size;
			max_size = move.max_size;
			margin = move.margin;
			padding = move.padding;
			border = move.border;
			background = move.background;
			display = move.display;
			scrollbars = std::move(move.scrollbars);
			background_model = std::move(move.background_model);
			border_model = std::move(move.border_model);
			invalid_background_model = move.invalid_background_model;
			invalid_border_model = move.invalid_border_model;
			invalid_width = move.invalid_width;
			invalid_height = move.invalid_height;
			temp_last_absolute_content_height = move.temp_last_absolute_content_height;
			temp_last_absolute_content_width = move.temp_last_absolute_content_width;
			invalid_children = move.invalid_children;
			border_corner_top_left = move.border_corner_top_left;
			border_corner_top_right = move.border_corner_top_right;
			border_corner_bottom_left = move.border_corner_bottom_left;
			border_corner_bottom_right = move.border_corner_bottom_right;
			border_corner_model = std::move(move.border_corner_model);
			font = std::move(move.font);
			prev_sibling = std::move(move.prev_sibling);
			next_sibling = std::move(move.next_sibling);

			for(auto const& child : children)
				child->parent = this;

			return *this;
		}


		void UINode::update()
		{
			updateModels();

			for(auto const& child: children)
				child->update();
		}

		void UINode::draw(graphics::RenderSession &session) const
		{
			if(m_border.left.image.texture)
				m_border.left.image.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(m_border.left.image.color);
			session.pass_values();
			session.pop_color();
			m_border.left.model->draw();

			if(m_border.top.image.texture)
				m_border.top.image.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(m_border.top.image.color);
			session.pass_values();
			session.pop_color();
			m_border.top.model->draw();

			if(m_border.right.image.texture)
				m_border.right.image.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(m_border.right.image.color);
			session.pass_values();
			session.pop_color();
			m_border.right.model->draw();

			if(m_border.bottom.image.texture)
				m_border.bottom.image.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(m_border.bottom.image.color);
			session.pass_values();
			session.pop_color();
			m_border.bottom.model->draw();

			if(border_corner_top_right.texture)
				border_corner_top_right.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(border_corner_top_right.color);
			session.pass_values();
			session.pop_color();
			border_corner_top_right_model->draw();

			if(border_corner_top_left.texture)
				border_corner_top_left.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(border_corner_top_left.color);
			session.pass_values();
			session.pop_color();
			border_corner_top_left_model->draw();

			if(border_corner_bottom_right.texture)
				border_corner_bottom_right.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(border_corner_bottom_right.color);
			session.pass_values();
			session.pop_color();
			border_corner_bottom_right_model->draw();

			if(border_corner_bottom_left.texture)
				border_corner_bottom_left.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(border_corner_bottom_left.color);
			session.pass_values();
			session.pop_color();
			border_corner_bottom_left_model->draw();

			border_corner_model->draw();

		}

		void UINode::set_font(Shared<Font> const& font)
		{
			this->font = font;
		}
		Shared<Font> const& UINode::font() const
		{
			for(UINode const * node = this; node->parent != nullptr; node = node->parent)
				if(node->font)
					return node->font;

			return font; // == nullptr
		}


		layout::Box<layout::Border> const& UINode::border() const
		{
			return border;
		}


		inline bool imply(bool a, bool implication) { return a? a&&implication : true; }

#define IMPLEMENT_SIZE_GETTER(name,parentGetter) \
			RE_ASSERT(imply(name.relative != 0, m_parent != nullptr));	\
			return name.relative ?	\
				name.absolute + name.relative * m_parent->parentGetter() :	\
				name.absolute;

#define WIDTH_DEPEND absolute_content_area_width
#define HEIGHT_DEPEND absolute_content_area_height


		float UINode::absolute_min_width() const
		{ IMPLEMENT_SIZE_GETTER(min_size.x, WIDTH_DEPEND) }

		float UINode::absolute_min_height() const
		{ IMPLEMENT_SIZE_GETTER(min_size.y, HEIGHT_DEPEND) }

		float UINode::absolute_max_height() const
		{ IMPLEMENT_SIZE_GETTER(max_size.x, WIDTH_DEPEND) }

		float UINode::absolute_max_height() const
		{ IMPLEMENT_SIZE_GETTER(max_size.y, HEIGHT_DEPEND) }

		float UINode::absolute_content_width() const
		{
			if(invalid_width)
			{
				invalid_width = false;
				float w = 0;

				for(auto const& child: children)
					w = math::max(w, child->absolute_box_width());
				temp_last_absolute_content_width = w;
			}
			return temp_last_absolute_content_width;
		}

		float UINode::absolute_content_height() const
		{
			if(invalid_height)
			{
				invalid_height = false;
				float h = 0;

				for(auto const& child: children)
					h = math::max(h, child->absolute_box_height());
				temp_last_absolute_content_height = h;
			}
			return temp_last_absolute_content_height;
		}


		float UINode::absolute_content_area_width() const
		{
			return math::cap(
				absolute_content_width(),
				absolute_min_width(),
				absolute_max_width());
		}

		float UINode::absolute_content_area_height() const
		{
			return math::cap(
				absolute_content_height(),
				absolute_min_height(),
				absolute_max_height());
		}


		float UINode::content_area_display_width() const
		{
			return (visible_scrollbar_v() && scrollbars.y.obstructVision) ?
				absolute_content_area_width() - scrollbars.y.width :
				absolute_content_area_width();
		}

		float UINode::content_area_display_height() const
		{
			return (visibleScrollBarH() && scrollbars.x.obstructVision) ?
				absolute_content_area_height() - scrollbars.x.width :
				absolute_content_area_height();
		}



		bool UINode::visible_scrollbar_h() const
		{
			switch(scrollbars.x.visibility)
			{
			case layout::ScrollBarVisibility::Always:
				return true;
			case layout::ScrollBarVisibility::Never:
				return false;
			case layout::ScrollBarVisibility::WhenOverflow:
				return absolute_content_width() > absolute_max_width();
			case layout::ScrollBarVisibility::WhenScrolling:
				return scrollbars.x.scrolling != 0;
			default:
				RE_ASSERTION_FAILURE("Invalid / unimplemented enum!");
			}
		}

		bool UINode::visible_scrollbar_v() const
		{
			switch(scrollbars.y.visibility)
			{
			case layout::ScrollBarVisibility::Always:
				return true;
			case layout::ScrollBarVisibility::Never:
				return false;
			case layout::ScrollBarVisibility::WhenOverflow:
				return absolute_content_height() > absolute_max_height();
			case layout::ScrollBarVisibility::WhenScrolling:
				return scrollbars.y.scrolling != 0;
			default:
				RE_ASSERTION_FAILURE("Invalid / unimplemented enum!");
			}
		}

		float UINode::absolute_left() const
		{ IMPLEMENT_SIZE_GETTER(position.x, WIDTH_DEPEND) }

		float UINode::absolute_top() const
		{ IMPLEMENT_SIZE_GETTER(position.y, HEIGHT_DEPEND) }

		float UINode::absolute_margin_left() const
		{ IMPLEMENT_SIZE_GETTER(margin.left, WIDTH_DEPEND) }

		float UINode::absolute_margin_top() const
		{ IMPLEMENT_SIZE_GETTER(margin.top, HEIGHT_DEPEND) }

		float UINode::absolute_margin_right() const
		{ IMPLEMENT_SIZE_GETTER(margin.right, WIDTH_DEPEND) }

		float UINode::absolute_margin_bottom() const
		{ IMPLEMENT_SIZE_GETTER(margin.bottom, HEIGHT_DEPEND) }

		float UINode::absolute_padding_left() const
		{ IMPLEMENT_SIZE_GETTER(padding.left, WIDTH_DEPEND) }

		float UINode::absolute_padding_top() const
		{ IMPLEMENT_SIZE_GETTER(padding.top, HEIGHT_DEPEND) }

		float UINode::absolute_padding_right() const
		{ IMPLEMENT_SIZE_GETTER(padding.right, WIDTH_DEPEND) }

		float UINode::absolute_padding_bottom() const
		{ IMPLEMENT_SIZE_GETTER(padding.bottom, HEIGHT_DEPEND) }

		float UINode::absolute_box_width() const
		{
			return
				absolute_margin_left()
					+ m_border.left.width
						+ absolute_padding_left()
							+ absolute_content_area_width()
						+ absolute_padding_right()
					+ m_border.right.width;
				+ absolute_margin_right();
		}

		float UINode::absolute_box_height() const
		{
			return
				absolute_margin_top()
					+ m_border.top.width
						+ absolute_padding_top()
							+ absolute_content_area_height()
						+ absolute_padding_bottom()
					+ m_border.bottom.width
				+ absolute_margin_bottom();
		}

		math::fvec2_t UINode::absolute_position() const
		{
			math::fvec2_t pos;
			const UINode * node = this;

			while(node)
			{
				pos.x += node->absolute_left() + node->absolute_box_width();
				pos.y += node->absolute_top() + node->absolute_box_height();
				node = node->prev_sibling;
			}
			return pos;
		}

		void UINode::set_min_width(layout::Size const& min_w)
		{
			min_size.x = min_w;
			content_changed();
		}

		void UINode::set_min_height(layout::Size const& min_h)
		{
			min_size.y = min_h;
			content_changed();
		}

		void UINode::set_max_width(layout::Size const& max_w)
		{
			max_size.x = max_w;
			content_changed();
		}
		void UINode::set_max_height(layout::Size const& max_h)
		{
			max_size.y = max_h;
			content_changed();
		}

		void UINode::set_width(layout::Size const& width)
		{
			min_size.x = max_size.x = width;
			content_changed();
		}
		void UINode::set_height(layout::Size const& height)
		{
			min_size.y = max_size.y = height;
			content_changed();
		}

		void UINode::set_margin(layout::Box<layout::Size> const& margin)
		{
			this->margin = margin;
			content_changed();
		}

		void UINode::set_margin_left(layout::Size const& margin)
		{
			this->margin.left = margin;
			content_changed();
		}
		void UINode::set_margin_top(layout::Size const& margin)
		{
			this->margin.top = margin;
			content_changed();
		}
		void UINode::set_margin_right(layout::Size const& margin)
		{
			this->margin.right = margin;
			content_changed();
		}
		void UINode::set_margin_bottom(layout::Size const& margin)
		{
			this->margin.bottom = margin;
			content_changed();
		}

		void UINode::set_padding(layout::Box<layout::Size> const& padding)
		{
			this->padding = padding;
			content_changed();
		}

		void UINode::set_padding_left(layout::Size const& padding)
		{
			this->padding.left = padding;
			content_changed();
		}
		void UINode::set_padding_top(layout::Size const& padding)
		{
			this->padding.top = padding;
			content_changed();
		}
		void UINode::set_padding_right(layout::Size const& padding)
		{
			this->padding.right = padding;
			content_changed();
		}
		void UINode::set_padding_bottom(layout::Size const& padding)
		{
			this->padding.bottom = padding;
			content_changed();
		}

		void UINode::set_background(layout::Image const& background)
		{
			this->background = background;
			invalid_background_model = true;
		}

		void UINode::set_border(layout::Box<layout::Border> const& border)
		{
			this->border = border;
			content_changed();
		}

		void UINode::set_border_left(layout::Border const& border)
		{
			this->m_border.left = border;
			content_changed();
		}
		void UINode::set_border_top(layout::Border const& border)
		{
			this->m_border.top = border;
			content_changed();
		}
		void UINode::set_border_right(layout::Border const& border)
		{
			this->m_border.right = border;
			content_changed();
		}
		void UINode::set_border_bottom(layout::Border const& border)
		{
			this->m_border.bottom = border;
			content_changed();
		}

		void UINode::set_border_top_left_corner(layout::Image const& corner)
		{
			this->border_corner_top_left = corner;
			invalid_border_model = true;
		}
		void UINode::set_border_top_right_corner(layout::Image const& corner)
		{
			this->border_corner_top_right = corner;
			invalid_border_model = true;
		}
		void UINode::set_border_bottom_left_corner(layout::Image const& corner)
		{
			this->border_corner_bottom_left = corner;
			invalid_border_model = true;
		}
		void UINode::set_border_bottom_right_corner(layout::Image const& corner)
		{
			this->border_corner_bottom_right = corner;
			invalid_border_model = true;
		}

		void UINode::set_left(layout::Size const& left)
		{
			position.x = left;
			content_changed();
		}
		void UINode::set_top(layout::Size const& top)
		{
			position.y = top;
			content_changed();
		}

		std::vector<Auto<UINode>> const& UINode::getChildren() const
		{
			return children;
		}
		void UINode::add_child(
			Auto<UINode> node)
		{
			RE_ASSERT(node);
			RE_ASSERT(node->parent == nullptr);

			if(!children.empty())
			{
				children.back()->next_sibling = node;
				node->prev_sibling = children.back();
			}
			else
				node->prev_sibling = nullptr;

			node->next_sibling = nullptr;

			children.push_back(node);
			node->parent = this;
			content_changed();
		}


	}
}