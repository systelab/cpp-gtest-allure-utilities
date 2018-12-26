#pragma once

#include "EntityComparatorConfiguration.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>


using namespace testing;
namespace systelab { namespace test_utility {

	class EntityComparator
	{
	public:
		EntityComparator(const EntityComparatorConfiguration& configuration = EntityComparatorConfiguration())
			:m_configuration(configuration)
		{}

		template <typename _Entity>
		testing::AssertionResult operator() (const _Entity& expected, const _Entity& actual) const;

	protected:
		EntityComparatorConfiguration m_configuration;
	};

}}

// Macro that declares a matcher that compares the passed value with a specific entity using an EntityComparator
MATCHER_P(isEqualTo, expectedEntity, "EntityComparison") \
	{ \
		AssertionResult rc = systelab::test_utility::EntityComparator()(expectedEntity, arg); \
		*result_listener << rc.message(); \
		return rc; \
	};

// Macro that declares a matcher that compares the passed value with a specific entity using an EntityComparator
MATCHER_P2(isEqualTo, expectedEntity, comparatorConfiguration, "EntityComparison") \
	{ \
		AssertionResult rc = systelab::test_utility::EntityComparator(comparatorConfiguration)(expectedEntity, arg); \
		*result_listener << rc.message(); \
		return rc; \
	};

// Macros to be used by the comparators to compare the same expression for 2 entities of the same type
#define COMPARATOR_ASSERT_EQUAL(EXPECTED, TO_TEST, EXPRESSION) \
	if (TO_TEST.EXPRESSION != EXPECTED.EXPRESSION) \
	{ \
		return AssertionFailure() << "Result for expression " #EXPRESSION " is different: expected=" << EXPECTED.EXPRESSION << ", actual=" << TO_TEST.EXPRESSION;\
	}

#define COMPARATOR_ASSERT_NEAR(EXPECTED, TO_TEST, EXPRESSION, TOLERANCE) \
	if (fabs(TO_TEST.EXPRESSION - EXPECTED.EXPRESSION) > TOLERANCE) \
	{ \
		return AssertionFailure() << "Result for expression " #EXPRESSION " is different: expected=" << EXPECTED.EXPRESSION << ", actual=" << TO_TEST.EXPRESSION << ", tolerance=" << TOLERANCE;\
	}

#define COMPARATOR_ASSERT_EQUAL_WITH_EXCLUSION(EXPECTED, TO_TEST, EXPRESSION, MEMBER_NAME) \
	if (!m_configuration.isMemberExcluded(MEMBER_NAME))\
	{\
		if (TO_TEST.EXPRESSION != EXPECTED.EXPRESSION) \
		{ \
			return AssertionFailure() << "Result for expression " #EXPRESSION " is different: expected=" << EXPECTED.EXPRESSION << ", actual=" << TO_TEST.EXPRESSION;\
		}\
	}
