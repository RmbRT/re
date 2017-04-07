namespace re
{
	namespace graphics
	{
		namespace gl
		{
			RECX Version::Version(uint_t major, uint_t minor):
				m_major(major),
				m_minor(minor)
			{
			}

			RECX uint_t Version::major() const
			{
				return m_major;
			}

			RECX uint_t Version::minor() const
			{
				return m_minor;
			}

			RECX bool Version::operator<(Version const& rhs) const
			{
				return (m_major < rhs.m_major)
					|| (m_major == rhs.m_major && m_minor < rhs.m_minor);
			}

			RECX bool Version::operator>=(Version const& rhs) const
			{
				return (m_major > rhs.m_major)
					|| (m_major == rhs.m_major && m_minor >= rhs.m_minor);
			}

			RECX bool Version::valid() const
			{
				return m_major && m_minor;
			}
		}
	}
}