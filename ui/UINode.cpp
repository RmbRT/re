#include "UINode.hpp"


namespace re
{
	namespace ui
	{

		void UINode::contentChanged() const
		{
			const UINode * node = this;

			while(node)
			{
				node->invalid_width = true;
				node->invalid_height = true;
				node->invalid_background_model = true;
				node->invalid_border_model = true; 
				node->invalid_children = true;

				node = node->parent;
			}
		}

		void UINode::updateModels() const
		{
			updateBorderModel();
			updateBackgroundModel();
		}

		void UINode::updateBorderModel() const
		{
			if(!invalid_border_model)
				return;
			invalid_border_model = false;
			
			const math::fvec2 box_pos(absoluteLeft(), absoluteTop());
			const math::fvec2 box_size(absoluteBoxWidth(), absoluteBoxHeight());
			const math::fvec2 inner_size(absoluteContentAreaWidth(), absoluteContentAreaHeight());

			float ol(box_pos.x);
			float il(ol+border.left.width);
			float ir(il+inner_size.x);
			float or(box_pos.x+box_size.x);
			float ot(-box_pos.y);
			float it(-box_pos.y-border.top.width);
			float ib(it-inner_size.y);
			float ob(-box_pos.y-box_size.y);

			math::fvec4 color(1,1,1,1);

			float t_top_s = 1; // horizontal border horizontal tex coord
			float t_top_t = 1; // horizontal border vertical tex coord
			float t_right_s = 1; // vertical border horizontal tex coord
			float t_right_t = 1; // vertical border vertical tex coord
			float t_bot_s = 1;
			float t_bot_t = 1;
			float t_left_s = 1;
			float t_left_t = 1;

			if(border.top.image.texture)
			{
				uint32 tex_w = border.top.image.texture->getWidth();
				uint32 tex_h = border.top.image.texture->getHeight();

				if(border.top.image.repeat.x == layout::Repeat::Tile)
					t_top_s = inner_size.x / tex_w;
				if(border.top.image.repeat.y == layout::Repeat::Tile)
					t_top_t = -border.top.width / tex_h;
			}
			if(border.right.image.texture)
			{
				uint32 tex_w = border.right.image.texture->getWidth();
				uint32 tex_h = border.right.image.texture->getHeight();

				if(border.right.image.repeat.x == layout::Repeat::Tile)
					t_right_s = inner_size.y / tex_w;
				if(border.right.image.repeat.y == layout::Repeat::Tile)
					t_right_t = -border.right.width / tex_h;
			}
			if(border.bottom.image.texture)
			{
				uint32 tex_w = border.bottom.image.texture->getWidth();
				uint32 tex_h = border.bottom.image.texture->getHeight();

				if(border.bottom.image.repeat.x == layout::Repeat::Tile)
					t_bot_s = inner_size.x / tex_w;
				if(border.bottom.image.repeat.y == layout::Repeat::Tile)
					t_bot_t = -border.bottom.width / tex_h;
			}
			if(border.left.image.texture)
			{
				uint32 tex_w = border.left.image.texture->getWidth();
				uint32 tex_h = border.left.image.texture->getHeight();

				if(border.left.image.repeat.x == layout::Repeat::Tile)
					t_left_s = inner_size.x / tex_w;
				if(border.left.image.repeat.y == layout::Repeat::Tile)
					t_left_t = -border.left.width / tex_h;
			}

			graphics::Vertex border_verts[3*2*4] = {
				// top border
				graphics::Vertex(math::fvec3(il,ot,0), math::fvec2(0,0), border.top.image.color),
				graphics::Vertex(math::fvec3(il,it,0), math::fvec2(0,t_top_t), border.top.image.color),
				graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(t_top_s,t_top_t), border.top.image.color),
					
				graphics::Vertex(math::fvec3(il,ot,0), math::fvec2(0,0), border.top.image.color),
				graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(t_top_s,t_top_t), border.top.image.color),
				graphics::Vertex(math::fvec3(ir,ot,0), math::fvec2(t_top_s,0), border.top.image.color),

					
				// bottom border
				graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(0,0), border.bottom.image.color),
				graphics::Vertex(math::fvec3(il,ob,0), math::fvec2(0,t_bot_t), border.bottom.image.color),
				graphics::Vertex(math::fvec3(ir,ob,0), math::fvec2(t_bot_s,t_bot_t), border.bottom.image.color),
					
				graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(0,0), border.bottom.image.color),
				graphics::Vertex(math::fvec3(ir,ob,0), math::fvec2(t_bot_s,t_bot_t), border.bottom.image.color),
				graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(t_bot_s,0), border.bottom.image.color),

				// left border
				graphics::Vertex(math::fvec3(ol,it,0), math::fvec2(0,0), border.left.image.color),
				graphics::Vertex(math::fvec3(ol,ib,0), math::fvec2(0,t_left_t), border.left.image.color),
				graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(t_left_s,t_left_t), border.left.image.color),
					
				graphics::Vertex(math::fvec3(ol,it,0), math::fvec2(0,0), border.left.image.color),
				graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(t_left_s,t_left_t), border.left.image.color),
				graphics::Vertex(math::fvec3(il,it,0), math::fvec2(t_left_s,0), border.left.image.color),

				// right border
				graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(0,0), border.right.image.color),
				graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(0,t_right_t), border.right.image.color),
				graphics::Vertex(math::fvec3(or,ib,0), math::fvec2(t_right_s,t_right_t), border.right.image.color),
					
				graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(0,0), border.right.image.color),
				graphics::Vertex(math::fvec3(or,ib,0), math::fvec2(t_right_s,t_right_t), border.right.image.color),
				graphics::Vertex(math::fvec3(or,it,0), math::fvec2(t_right_s,0), border.right.image.color)
			};

			float t_tl_s = 1;
			float t_tl_t = 1;
			float t_tr_s = 1;
			float t_tr_t = 1;
			float t_bl_s = 1;
			float t_bl_t = 1;
			float t_br_s = 1;
			float t_br_t = 1;

			if(border_corner_top_left.texture)
			{
				uint32 tex_w = border_corner_top_left.texture->getWidth();
				uint32 tex_h = border_corner_top_left.texture->getHeight();

				if(border_corner_top_left.repeat.x == layout::Repeat::Tile)
					t_tl_s = border.left.width / tex_w;
				if(border_corner_top_left.repeat.y == layout::Repeat::Tile)
					t_tl_t = -border.top.width / tex_h;
			}
			if(border_corner_top_right.texture)
			{
				uint32 tex_w = border_corner_top_right.texture->getWidth();
				uint32 tex_h = border_corner_top_right.texture->getHeight();

				if(border_corner_top_right.repeat.x == layout::Repeat::Tile)
					t_tr_s = border.right.width / tex_w;
				if(border_corner_top_right.repeat.y == layout::Repeat::Tile)
					t_tr_t = -border.top.width / tex_h;
			}
			if(border_corner_bottom_left.texture)
			{
				uint32 tex_w = border_corner_bottom_left.texture->getWidth();
				uint32 tex_h = border_corner_bottom_left.texture->getHeight();

				if(border_corner_bottom_left.repeat.x == layout::Repeat::Tile)
					t_bl_s = border.left.width / tex_w;
				if(border_corner_bottom_left.repeat.y == layout::Repeat::Tile)
					t_bl_t = -border.bottom.width / tex_h;
			}
			if(border_corner_bottom_right.texture)
			{
				uint32 tex_w = border_corner_bottom_right.texture->getWidth();
				uint32 tex_h = border_corner_bottom_right.texture->getHeight();

				if(border_corner_bottom_right.repeat.x == layout::Repeat::Tile)
					t_br_s = border.right.width / tex_w;
				if(border_corner_bottom_right.repeat.y == layout::Repeat::Tile)
					t_br_t = -border.bottom.width / tex_h;
			}



			graphics::Vertex border_corner_verts[3*2*4] = {
				// top left corner
				graphics::Vertex(math::fvec3(ol,ot,0), math::fvec2(0,0), border_corner_top_left.color),
				graphics::Vertex(math::fvec3(ol,it,0), math::fvec2(0,t_tl_t), border_corner_top_left.color),
				graphics::Vertex(math::fvec3(il,it,0), math::fvec2(t_tl_s,t_tl_t), border_corner_top_left.color),
					
				graphics::Vertex(math::fvec3(ol,ot,0), math::fvec2(0,0), border_corner_top_left.color),
				graphics::Vertex(math::fvec3(il,it,0), math::fvec2(t_tl_s,t_tl_t), border_corner_top_left.color),
				graphics::Vertex(math::fvec3(il,ot,0), math::fvec2(t_tl_s,0), border_corner_top_left.color),

				// top right corner
				graphics::Vertex(math::fvec3(ir,ot,0), math::fvec2(0,0), border_corner_top_right.color),
				graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(0,t_tr_t), border_corner_top_right.color),
				graphics::Vertex(math::fvec3(or,it,0), math::fvec2(t_tr_s,t_tr_t), border_corner_top_right.color),
					
				graphics::Vertex(math::fvec3(ir,ot,0), math::fvec2(0,0), border_corner_top_right.color),
				graphics::Vertex(math::fvec3(or,it,0), math::fvec2(t_tr_s,t_tr_t), border_corner_top_right.color),
				graphics::Vertex(math::fvec3(or,ot,0), math::fvec2(t_tr_s,0), border_corner_top_right.color),

				// bottom right corner
				graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(0,0), border_corner_bottom_right.color),
				graphics::Vertex(math::fvec3(ir,ob,0), math::fvec2(0,t_br_t), border_corner_bottom_right.color),
				graphics::Vertex(math::fvec3(or,ob,0), math::fvec2(t_br_s,t_br_t), border_corner_bottom_right.color),

				graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(0,0), border_corner_bottom_right.color),
				graphics::Vertex(math::fvec3(or,ob,0), math::fvec2(t_br_s,t_br_t), border_corner_bottom_right.color),
				graphics::Vertex(math::fvec3(or,ib,0), math::fvec2(t_br_s,0), border_corner_bottom_right.color),

				// bottom left corner
				graphics::Vertex(math::fvec3(ol,ib,0), math::fvec2(0,0), border_corner_bottom_left.color),
				graphics::Vertex(math::fvec3(ol,ob,0), math::fvec2(0,t_bl_t), border_corner_bottom_left.color),
				graphics::Vertex(math::fvec3(il,ob,0), math::fvec2(t_bl_s,t_bl_t), border_corner_bottom_left.color),
					
				graphics::Vertex(math::fvec3(ol,ib,0), math::fvec2(0,0), border_corner_bottom_left.color),
				graphics::Vertex(math::fvec3(il,ob,0), math::fvec2(t_bl_s,t_bl_t), border_corner_bottom_left.color),
				graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(t_bl_s,0), border_corner_bottom_left.color)
			};

			if(!border_model)
				border_model = alloc<graphics::VertexData>(graphics::RenderMode::RM_TRIANGLES, graphics::AllocationStrategy::AS_STATIC);

			border_model->setData(border_verts, _countof(border_verts));
			
			if(!border_corner_model)
				border_corner_model = alloc<graphics::VertexData>(graphics::RenderMode::RM_TRIANGLES, graphics::AllocationStrategy::AS_STATIC);

			border_corner_model->setData(border_corner_verts, _countof(border_corner_verts));
		}

		void UINode::updateBackgroundModel() const
		{
			if(!invalid_background_model)
				return;
			invalid_background_model = false;

			const math::fvec2 inner_pos(absoluteLeft() + border.left.width, absoluteTop() + border.top.width);
			const math::fvec2 inner_size(absoluteContentAreaWidth(), absoluteContentAreaHeight());

			const float il = inner_pos.x;
			const float ir = inner_pos.x+inner_size.x;
			const float it = -inner_pos.y;
			const float ib = -inner_pos.y-inner_size.y;


			float t_s = 1;
			float t_t = 1;

			if(background.texture)
			{
				uint32 tex_w = background.texture->getWidth();
				uint32 tex_h = background.texture->getHeight();

				if(background.repeat.x == layout::Repeat::Tile)
					t_s = inner_size.x / tex_w;
				if(background.repeat.y == layout::Repeat::Tile)
					t_t = inner_size.y / tex_h;
			}

			graphics::Vertex background_verts[2*3] = {
				graphics::Vertex(math::fvec3(il,it,0), math::fvec2(0,0), background.color),
				graphics::Vertex(math::fvec3(il,ib,0), math::fvec2(0,t_t), background.color),
				graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(t_s,t_t), background.color),

				graphics::Vertex(math::fvec3(il,it,0), math::fvec2(0,0), background.color),
				graphics::Vertex(math::fvec3(ir,ib,0), math::fvec2(t_s,t_t), background.color),
				graphics::Vertex(math::fvec3(ir,it,0), math::fvec2(t_s,0), background.color)
			};

			if(!background_model)
				background_model = alloc<graphics::VertexData>(graphics::RenderMode::RM_TRIANGLES, graphics::AllocationStrategy::AS_STATIC);

			background_model->setData(background_verts, _countof(background_verts));
		}


		UINode::UINode(): parent(nullptr),
			invalid_width(true),
			invalid_height(true),
			temp_last_absolute_content_height(0),
			temp_last_absolute_content_width(0),
			invalid_background_model(true),
			invalid_border_model(true),
			invalid_children(true),
			font(nullptr) { }

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
			font(std::move(move.font))
		{
			for(const auto &child : children)
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

			for(const auto &child : children)
				child->parent = this;

			return *this;
		}
		

		void UINode::update()
		{
			updateModels();

			for(const auto &child: children)
				child->update();
		}

		void UINode::draw(graphics::RenderSession &session) const
		{
			if(border.left.image.texture)
				border.left.image.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(border.left.image.color);
			session.pass_values();
			session.pop_color();
			border.left.model->draw();

			if(border.top.image.texture)
				border.top.image.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(border.top.image.color);
			session.pass_values();
			session.pop_color();
			border.top.model->draw();

			if(border.right.image.texture)
				border.right.image.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(border.right.image.color);
			session.pass_values();
			session.pop_color();
			border.right.model->draw();

			if(border.bottom.image.texture)
				border.bottom.image.texture->bind();
			else graphics::Texture::unbind();
			session.push_color(border.bottom.image.color);
			session.pass_values();
			session.pop_color();
			border.bottom.model->draw();

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

		void UINode::setFont(const strong_handle<Font> &font)
		{
			this->font = font;
		}
		const strong_handle<Font> &UINode::getFont() const
		{
			for(UINode const * node = this; node->parent != nullptr; node = node->parent)
				if(node->font)
					return node->font;

			return font; // == nullptr
		}


		const layout::Box<layout::Border> &UINode::getBorder() const
		{
			return border;
		}

		void UINode::setBorder(const layout::Box<layout::Border> &border)
		{
			contentChanged();
			this->border = border;
		}
		
		const layout::Image &UINode::getBackground() const { return background; }
		void UINode::setBackground(const layout::Image &background)
		{
			this->background = background;
			invalid_background_model = true;
		}

		inline bool imply(bool a, bool implication) { return a? a&&implication : true; }

#define IMPLEMENT_SIZE_GETTER(name,parentGetter) \
			RE_ASSERT(imply(name.relative != 0, parent != nullptr));	\
			return name.relative ?	\
				name.absolute + name.relative * parent->parentGetter() :	\
				name.absolute;

#define WIDTH_DEPEND absoluteContentAreaWidth
#define HEIGHT_DEPEND absoluteContentAreaHeight


		float UINode::absoluteMinWidth() const
		{ IMPLEMENT_SIZE_GETTER(min_size.x, WIDTH_DEPEND) }

		float UINode::absoluteMinHeight() const
		{ IMPLEMENT_SIZE_GETTER(min_size.y, HEIGHT_DEPEND) }

		float UINode::absoluteMaxWidth() const
		{ IMPLEMENT_SIZE_GETTER(max_size.x, WIDTH_DEPEND) }

		float UINode::absoluteMaxHeight() const
		{ IMPLEMENT_SIZE_GETTER(max_size.y, HEIGHT_DEPEND) }
		
		float UINode::absoluteContentWidth() const
		{
			if(invalid_width)
			{
				invalid_width = false;
				float w = 0;

				for(const auto &child: children)
					w = math::max(w, child->absoluteBoxWidth());
				temp_last_absolute_content_width = w;
			}
			return temp_last_absolute_content_width;
		}

		float UINode::absoluteContentHeight() const
		{
			if(invalid_height)
			{
				invalid_height = false;
				float h = 0;

				for(const auto &child: children)
					h = math::max(h, child->absoluteBoxWidth());
				temp_last_absolute_content_height = h;
			}
			return temp_last_absolute_content_height;
		}


		float UINode::absoluteContentAreaWidth() const
		{
			return math::cap(absoluteContentWidth(), absoluteMinWidth(), absoluteMaxWidth());
		}

		float UINode::absoluteContentAreaHeight() const
		{
			return math::cap(absoluteContentHeight(), absoluteMinHeight(), absoluteMaxHeight());
		}


		float UINode::contentAreaDisplayWidth() const
		{
			return (visibleScrollBarV() && scrollbars.y.obstructVision) ?
				absoluteContentAreaWidth() - scrollbars.y.width :
				absoluteContentAreaWidth();
		}

		float UINode::contentAreaDisplayHeight() const
		{
			return (visibleScrollBarH() && scrollbars.x.obstructVision) ?
				absoluteContentAreaHeight() - scrollbars.y.width :
				absoluteContentAreaHeight();
		}



		bool UINode::visibleScrollBarH() const
		{
			switch(scrollbars.x.visibility)
			{
			case layout::ScrollBarVisibility::Always:
				return true;
			case layout::ScrollBarVisibility::Never:
				return false;
			case layout::ScrollBarVisibility::WhenOverflow:
				return absoluteContentWidth() > absoluteMaxWidth();
			case layout::ScrollBarVisibility::WhenScrolling:
				return scrollbars.x.scrolling != 0;
			default:
				RE_ASSERTION_FAILURE("Invalid / unimplemented enum!");
			}
		}

		bool UINode::visibleScrollBarV() const
		{
			switch(scrollbars.y.visibility)
			{
			case layout::ScrollBarVisibility::Always:
				return true;
			case layout::ScrollBarVisibility::Never:
				return false;
			case layout::ScrollBarVisibility::WhenOverflow:
				return absoluteContentHeight() > absoluteMaxHeight();
			case layout::ScrollBarVisibility::WhenScrolling:
				return scrollbars.y.scrolling != 0;
			default:
				RE_ASSERTION_FAILURE("Invalid / unimplemented enum!");
			}
		}

		float UINode::absoluteLeft() const
		{ IMPLEMENT_SIZE_GETTER(position.x, WIDTH_DEPEND) }

		float UINode::absoluteTop() const
		{ IMPLEMENT_SIZE_GETTER(position.y, HEIGHT_DEPEND) }

		float UINode::absoluteMarginLeft() const
		{ IMPLEMENT_SIZE_GETTER(margin.left, WIDTH_DEPEND) }

		float UINode::absoluteMarginTop() const
		{ IMPLEMENT_SIZE_GETTER(margin.top, HEIGHT_DEPEND) }

		float UINode::absoluteMarginRight() const
		{ IMPLEMENT_SIZE_GETTER(margin.right, WIDTH_DEPEND) }
		
		float UINode::absoluteMarginBottom() const
		{ IMPLEMENT_SIZE_GETTER(margin.bottom, HEIGHT_DEPEND) }

		float UINode::absolutePaddingLeft() const
		{ IMPLEMENT_SIZE_GETTER(padding.left, WIDTH_DEPEND) }

		float UINode::absolutePaddingTop() const
		{ IMPLEMENT_SIZE_GETTER(padding.top, HEIGHT_DEPEND) }

		float UINode::absolutePaddingRight() const
		{ IMPLEMENT_SIZE_GETTER(padding.right, WIDTH_DEPEND) }

		float UINode::absolutePaddingBottom() const
		{ IMPLEMENT_SIZE_GETTER(padding.bottom, HEIGHT_DEPEND) }

		float UINode::absoluteBoxWidth() const
		{
			return
				absoluteMarginLeft()
					+ border.left.width
						+ absolutePaddingLeft()
							+ absoluteContentAreaWidth()
						+ absolutePaddingRight()
					+ border.right.width;
				+ absoluteMarginRight();
		}

		float UINode::absoluteBoxHeight() const
		{
			return
				absoluteMarginTop()
					+ border.top.width
						+ absolutePaddingTop()
							+ absoluteContentAreaHeight()
						+ absolutePaddingBottom()
					+ border.bottom.width
				+ absoluteMarginBottom();
		}

		void UINode::setMinWidth(const layout::Size &min_w)
		{
			min_size.x = min_w;
			contentChanged();
		}

		void UINode::setMinHeight(const layout::Size &min_h)
		{
			min_size.y = min_h;
			contentChanged();
		}

		void UINode::setMaxWidth(const layout::Size &max_w)
		{
			max_size.x = max_w;
			contentChanged();
		}
		void UINode::setMaxHeight(const layout::Size &max_h)
		{
			max_size.y = max_h;
			contentChanged();
		}

		void UINode::setWidth(const layout::Size &width)
		{
			min_size.x = max_size.x = width;
			contentChanged();
		}
		void UINode::setHeight(const layout::Size &height)
		{
			min_size.y = max_size.y = height;
			contentChanged();
		}

		void UINode::setMargin(const layout::Box<layout::Size> &margin)
		{
			this->margin = margin;
			contentChanged();
		}

		void UINode::setMarginLeft(const layout::Size &margin)
		{
			this->margin.left = margin;
			contentChanged();
		}
		void UINode::setMarginTop(const layout::Size &margin)
		{
			this->margin.top = margin;
			contentChanged();
		}
		void UINode::setMarginRight(const layout::Size &margin)
		{
			this->margin.right = margin;
			contentChanged();
		}
		void UINode::setMarginBottom(const layout::Size &margin)
		{
			this->margin.bottom = margin;
			contentChanged();
		}

		void UINode::setPadding(const layout::Box<layout::Size> &padding)
		{
			this->padding = padding;
			contentChanged();
		}

		void UINode::setPaddingLeft(const layout::Size &padding)
		{
			this->padding.left = padding;
			contentChanged();
		}
		void UINode::setPaddingTop(const layout::Size &padding)
		{
			this->padding.top = padding;
			contentChanged();
		}
		void UINode::setPaddingRight(const layout::Size &padding)
		{
			this->padding.right = padding;
			contentChanged();
		}
		void UINode::setPaddingBottom(const layout::Size &padding)
		{
			this->padding.bottom = padding;
			contentChanged();
		}

		void UINode::setBackground(const layout::Image &background)
		{
			this->background = background;
			invalid_background_model = true;
		}

		void UINode::setBorder(const layout::Box<layout::Border> &border)
		{
			this->border = border;
			contentChanged();
		}

		void UINode::setBorderLeft(const layout::Border &border)
		{
			this->border.left = border;
			contentChanged();
		}
		void UINode::setBorderTop(const layout::Border &border)
		{
			this->border.top = border;
			contentChanged();
		}
		void UINode::setBorderRight(const layout::Border &border)
		{
			this->border.right = border;
			contentChanged();
		}
		void UINode::setBorderBottom(const layout::Border &border)
		{
			this->border.bottom = border;
			contentChanged();
		}

		void UINode::setBorderTopLeftCorner(const layout::Image &corner)
		{
			this->border_corner_top_left = corner;
			invalid_border_model = true;
		}
		void UINode::setBorderTopRightCorner(const layout::Image &corner)
		{
			this->border_corner_top_right = corner;
			invalid_border_model = true;
		}
		void UINode::setBorderBottomLeftCorner(const layout::Image &corner)
		{
			this->border_corner_bottom_left = corner;
			invalid_border_model = true;
		}
		void UINode::setBorderBottomRightCorner(const layout::Image &corner)
		{
			this->border_corner_bottom_right = corner;
			invalid_border_model = true;
		}

		void UINode::setLeft(const layout::Size &left)
		{
			position.x = left;
			contentChanged();
		}
		void UINode::setTop(const layout::Size &top)
		{
			position.y = top;
			contentChanged();
		}

		const std::vector<strong_handle<UINode>> &UINode::getChildren() const
		{
			return children;
		}
		void UINode::addChild(const strong_handle<UINode> &node)
		{
			RE_ASSERT(node);
			RE_ASSERT(node->parent == nullptr);

			children.push_back(node);
			node->parent = this;
			contentChanged();
		}


	}
}