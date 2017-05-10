#include "FontAsset.hpp"

using re::graphics::gl::Texture2D;

namespace re
{
	Shared<ui::Font> FontAsset::createFont() const
	{
		Shared<Texture2D> atlasTex = Shared<Texture2D>::alloc();
		atlasTex->alloc();

		atlasTex->set_texels(atlas, 0);

		return Shared<ui::Font>::alloc(
			std::move(atlasTex),
			entries,
			defaultEntry,
			lineHeight,
			tabWidth,
			spaceWidth);
	}
}