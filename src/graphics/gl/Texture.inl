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

				return s_binding[m_type].bound(handle());
			}

			RECX Texture::Texture(TextureType type):
				m_type(type)
			{
			}

			TextureType Texture::type() const
			{
				return m_type;
			}

			RECX Texture1D::Texture1D():
				Texture(TextureType::k1D),
				m_size()
			{
			}

			REIL bool Texture1D::available()
			{
				return Context::require();
			}

			uint_t Texture1D::size() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");

				return m_size;
			}

			RECX Texture2D::Texture2D():
				Texture(TextureType::k2D),
				m_width(),
				m_height()
			{
			}

			REIL bool Texture2D::available()
			{
				return Context::require();
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