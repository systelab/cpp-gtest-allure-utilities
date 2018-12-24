#include "EntityComparatorConfiguration.h"


namespace systelab { namespace test_utility {

	EntityComparatorConfiguration::EntityComparatorConfiguration()
		:m_excludedMembers()
	{
	}

	EntityComparatorConfiguration::EntityComparatorConfiguration(std::vector<std::string> excludedMembers)
		:m_excludedMembers(excludedMembers)
	{
	}

	EntityComparatorConfiguration::~EntityComparatorConfiguration()
	{
	}

	bool EntityComparatorConfiguration::isMemberExcluded(const std::string& member) const
	{
		for (unsigned int i = 0; i < m_excludedMembers.size(); i++)
		{
			if (m_excludedMembers[i] == member)
			{
				return true;
			}
		}

		return false;
	}

}}
