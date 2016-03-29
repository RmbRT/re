namespace re
{
	namespace graphics
	{
		namespace GL
		{
			Version::Version(uint major, uint minor):
				m_major(major),
				m_minor(minor)
			{
			}

			uint Version::major() const
			{
				return m_major;
			}

			uint Version::minor() const
			{
				return m_minor;
			}

			bool operator<(Version const& rhs) const
			{
				return (m_major < rhs.m_major)
					|| (m_major == rhs.major && m_minor < rhs.m_minor);
			}

			bool operator>=(Version const& rhs) const
			{
				return (m_major > rhs.m_major)
					|| (m_major == rhs.m_major && m_minor >= rhs.m_minor);
			}

			bool Version::valid() const
			{
				return m_major && m_minor;
			}
		}
	}
}