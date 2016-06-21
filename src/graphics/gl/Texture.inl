namespace re
{
	namespace graphics
	{
		namespace gl
		{
			bool Texture::bound() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");

				RE_DBG_ASSERT(size_t(m_type) < _countof(s_binding));

				return s_binding[size_t(m_type)].bound(handle());
			}

			REIL Texture::Texture(TextureType type):
				m_type(type)
			{
			}

			TextureType Texture::type() const
			{
				return m_type;
			}

			uint_t Texture1D::size() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");

				return m_size;
			}

			uint_t Texture2D::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint_t Texture2D::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint_t Texture3D::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint_t Texture3D::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint_t Texture3D::depth() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_depth;
			}

			uint_t Texture2DMultisample::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint_t Texture2DMultisample::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint_t Texture2DMultisample::samples() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_samples;
			}

			uint_t Texture1DArray::size() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_size;
			}

			uint_t Texture1DArray::layers() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_layers;
			}

			uint_t Texture2DArray::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint_t Texture2DArray::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint_t Texture2DArray::layers() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_layers;
			}

			uint_t Texture2DMultisampleArray::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint_t Texture2DMultisampleArray::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint_t Texture2DMultisampleArray::samples() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_samples;
			}

			uint_t Texture2DMultisampleArray::layers() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_layers;
			}
		}
	}
}