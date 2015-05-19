#include "UIElement2.hpp"


namespace re
{
	namespace ui
	{

		void UIElement::contentChanged() const
		{
			invalid_width = true;
			invalid_height = true;
			invalid_background_model = true;
			invalid_border_model = true; 
			invalid_children = true;
		}


		UIElement::UIElement(): parent(nullptr),
			invalid_width(true),
			invalid_height(true),
			temp_last_absolute_content_height(0),
			temp_last_absolute_content_width(0),
			invalid_background_model(true),
			invalid_border_model(true),
			invalid_children(true)
		{ }
		UIElement::UIElement(UIElement && move):
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
			label(std::move(move.label)),
			scrollbars(std::move(move.scrollbars)),
			background_model(std::move(move.background_model)),
			border_model(std::move(move.border_model)),
			invalid_background_model(move.invalid_background_model),
			invalid_border_model(move.invalid_border_model),
			invalid_width(move.invalid_width),
			invalid_height(move.invalid_height),
			temp_last_absolute_content_height(move.temp_last_absolute_content_height),
			temp_last_absolute_content_width(move.temp_last_absolute_content_width),
			invalid_children(move.invalid_children)

		{
			for(const auto &child : children)
				child->parent = this;
		}

		UIElement &UIElement::operator=(UIElement &&move)
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
			label = std::move(move.label);
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

			for(const auto &child : children)
				child->parent = this;

			return *this;
		}



		const Label &UIElement::getLabel() const
		{
			return label;
		}

		void UIElement::setText(const u32string &text)
		{
			label.setText(text);
		}

		const u32string &UIElement::getText() const
		{
			return label.getText();
		}

		void UIElement::setFont(const strong_handle<Font> &font)
		{
			label.setFont(font);
		}

		const strong_handle<Font> &UIElement::getFont() const
		{
			return label.getFont();
		}
		
		void UIElement::updateLabel()
		{
			label.update();
			contentChanged();
		}



		
		const layout::Box<layout::Border> &UIElement::getBorder() const
		{
			return border;
		}

		void UIElement::setBorder(const layout::Box<layout::Border> &border)
		{
			contentChanged();
			this->border = border;
		}
		
		const layout::Image &UIElement::getBackground() const { return background; }
		void UIElement::setBackground(const layout::Image &background)
		{
			this->background = background;
			invalid_background_model = true;
		}

		inline bool imply(bool a, bool implication) { return a? a&&implication : true; }

#define IMPLEMENT_SIZE_GETTER(name, parentGetter) \
			RE_ASSERT(imply(name.relative != 0, parent != nullptr));	\
			return name.relative ?	\
				name.absolute + name.relative * parent->parentGetter() :	\
				name.absolute;

#define WIDTH_DEPEND absoluteContentAreaWidth
#define HEIGHT_DEPEND absoluteContentAreaHeight


		float UIElement::absoluteMinWidth() const
		{ IMPLEMENT_SIZE_GETTER(min_size.x, WIDTH_DEPEND) }

		float UIElement::absoluteMinHeight() const
		{ IMPLEMENT_SIZE_GETTER(min_size.y, HEIGHT_DEPEND) }

		float UIElement::absoluteMaxWidth() const
		{ IMPLEMENT_SIZE_GETTER(max_size.x, WIDTH_DEPEND) }

		float UIElement::absoluteMaxHeight() const
		{ IMPLEMENT_SIZE_GETTER(max_size.y, HEIGHT_DEPEND) }
		
		float UIElement::absoluteContentWidth() const
		{
			if(invalid_width)
			{
				invalid_width = false;
				float w = label.getMinPosition().x+label.getSize().x;

				for(const auto &child: children)
					w = math::max(w, child->absoluteBoxWidth());
				temp_last_absolute_content_width = w;
			}
			return temp_last_absolute_content_width;
		}

		float UIElement::absoluteContentHeight() const
		{
			if(invalid_height)
			{
				invalid_height = false;
				float h = -label.getMinPosition().y-label.getSize().y;

				for(const auto &child: children)
					h = math::max(h, child->absoluteBoxWidth());
				temp_last_absolute_content_height = h;
			}
			return temp_last_absolute_content_height;
		}


		float UIElement::absoluteContentAreaWidth() const
		{
			return math::cap(absoluteContentWidth(), absoluteMinWidth(), absoluteMaxWidth());
		}

		float UIElement::absoluteContentAreaHeight() const
		{
			return math::cap(absoluteContentHeight(), absoluteMinHeight(), absoluteMaxHeight());
		}


		float UIElement::contentAreaDisplayWidth() const
		{
			return (visibleScrollBarV() && scrollbars.y.obstructVision) ?
				absoluteContentAreaWidth() - scrollbars.y.width :
				absoluteContentAreaWidth();
		}

		float UIElement::contentAreaDisplayHeight() const
		{
			return (visibleScrollBarH() && scrollbars.x.obstructVision) ?
				absoluteContentAreaHeight() - scrollbars.y.width :
				absoluteContentAreaHeight();
		}



		bool UIElement::visibleScrollBarH() const
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

		bool UIElement::visibleScrollBarV() const
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

		float UIElement::absoluteLeft() const
		{ IMPLEMENT_SIZE_GETTER(position.x, WIDTH_DEPEND) }

		float UIElement::absoluteTop() const
		{ IMPLEMENT_SIZE_GETTER(position.y, HEIGHT_DEPEND) }

		float UIElement::absoluteMarginLeft() const
		{ IMPLEMENT_SIZE_GETTER(margin.left, WIDTH_DEPEND) }

		float UIElement::absoluteMarginTop() const
		{ IMPLEMENT_SIZE_GETTER(margin.top, HEIGHT_DEPEND) }

		float UIElement::absoluteMarginRight() const
		{ IMPLEMENT_SIZE_GETTER(margin.right, WIDTH_DEPEND) }
		
		float UIElement::absoluteMarginBottom() const
		{ IMPLEMENT_SIZE_GETTER(margin.bottom, HEIGHT_DEPEND) }

		float UIElement::absolutePaddingLeft() const
		{ IMPLEMENT_SIZE_GETTER(padding.left, WIDTH_DEPEND) }

		float UIElement::absolutePaddingTop() const
		{ IMPLEMENT_SIZE_GETTER(padding.top, HEIGHT_DEPEND) }

		float UIElement::absolutePaddingRight() const
		{ IMPLEMENT_SIZE_GETTER(padding.right, WIDTH_DEPEND) }

		float UIElement::absolutePaddingBottom() const
		{ IMPLEMENT_SIZE_GETTER(padding.bottom, HEIGHT_DEPEND) }

		float UIElement::absoluteBoxWidth() const
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

		float UIElement::absoluteBoxHeight() const
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

	}
}