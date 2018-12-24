#pragma once

#include <string>
#include <vector>

namespace systelab { namespace test_utility {

	class EntityComparatorConfiguration
	{
	public:
		EntityComparatorConfiguration();
		EntityComparatorConfiguration(std::vector<std::string>);
		virtual ~EntityComparatorConfiguration();

		bool isMemberExcluded(const std::string&) const;

	private:
		std::vector<std::string> m_excludedMembers;
	};

}}

