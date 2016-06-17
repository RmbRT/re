#include "FontAsset.hpp"

namespace re
{
	NotNull<ui::Font> FontAsset::getFont() const
	{
		strong_handle<graphics::Texture> atlasTex = alloc<graphics::Texture>();
		atlasTex->alloc(2);
		atlasTex->setData(atlas);
		{
			graphics::TextureParameters &params = atlasTex->getParameters();

			atlasTex->updateParameters();
		}

		return alloc<ui::Font>(
			std::move(atlasTex),
			std::move(entries),
			defaultEntry,
			lineHeight,
			tabWidth,
			spaceWidth);
	}
}