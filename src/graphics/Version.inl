namespace re
{
	namespace graphics
	{
		Version::Version(uint_t major, uint_t minor):
			m_major(major),
			m_minor(minor)
		{
		}

		uint_t Version::major() const
		{
			return m_major;
		}

		uint_t Version::minor() const
		{
			return m_minor;
		}

		bool Version::operator<(Version const& rhs) const
		{
			return (m_major < rhs.m_major)
				|| (m_major == rhs.major && m_minor < rhs.m_minor);
		}

		bool Version::operator>=(Version const& rhs) const
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