namespace re
{
	namespace graphics
	{
		namespace gl
		{
			bool Texture::bound()
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");

				RE_DBG_ASSERT(size_t(m_type) < _countof(s_binding));

				return s_binding[size_t(m_type)] == handle();
			}

			Texture::Texture(TextureType type):
				m_type(type)
			{
			}

			TextureType Texture::type() const
			{
				return m_type;
			}

			uint Texture1D::size() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");

				return m_size;
			}

			uint Texture2D::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint Texture2D::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint Texture3D::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint Texture3D::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint Texture3D::depth() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_depth;
			}

			uint Texture2DMultisample::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint Texture2DMultisample::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint Texture2DMultisample::samples() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_samples;
			}

			uint Texture1DArray::size() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_size;
			}

			uint Texture1DArray::layers() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_layers;
			}

			uint Texture2DArray::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint Texture2DArray::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint Texture2DArray::layers() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_layers;
			}

			uint Texture2DMultisampleArray::width() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_width;
			}

			uint Texture2DMultisample::height() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_height;
			}

			uint Texture2DMultisampleArray::samples() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_samples;
			}

			uint Texture2DMultisampleArray::layers() const
			{
				RE_DBG_ASSERT(exists() &&
					"Texture must exist.");
				return m_layers;
			}

			



		}
	}
}