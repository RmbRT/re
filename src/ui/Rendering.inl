namespace re
{
	namespace ui
	{
		RECX Vertex::Vertex(
			math::fvec2_t const& position,
			math::fvec2_t const& texture,
			math::fvec4_t const& color):
			position(position),
			texture(texture),
			color(color)
		{
		}
	}
}