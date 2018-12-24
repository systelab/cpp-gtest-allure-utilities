#include "EntityComparator.h"

#include <rapidjson/document.h>


using testing::AssertionResult;
using testing::AssertionFailure;
using testing::AssertionSuccess;

namespace systelab { namespace test_utility {

	template<>
	testing::AssertionResult EntityComparator::operator() (const rapidjson::Value& expected, const rapidjson::Value& toTest) const
	{

		if ((expected.GetType() == rapidjson::kFalseType || expected.GetType() == rapidjson::kTrueType)
			&& (toTest.GetType() == rapidjson::kFalseType || toTest.GetType() == rapidjson::kTrueType))
		{
			if (expected.GetType() != toTest.GetType())
			{
				std::string expectedBooleanValue = expected.GetType()== rapidjson::kFalseType?"'false'":"'true'";
				std::string toTestBooleanValue = toTest.GetType() == rapidjson::kFalseType ? "'false'" : "'true'";
				return AssertionFailure() << "Result for evaluation of boolean value is different: expected="
						<< expectedBooleanValue << ", actual=" << toTestBooleanValue;
			}
		}
		else
		{
			COMPARATOR_ASSERT_EQUAL(expected, toTest, GetType());
		}	

		if (expected.GetType() == rapidjson::kStringType)
		{
			std::string expectedString = expected.GetString();
			std::string toTestString = toTest.GetString();
			if (expectedString != toTestString)
			{
				return AssertionFailure() << "Result for expression GetString() is different: expected="
										  << expectedString << ", actual=" << toTestString;
			}
		}
		else if (expected.GetType() == rapidjson::kNumberType)
		{
			COMPARATOR_ASSERT_EQUAL(expected, toTest, IsInt());
			if (expected.IsInt())
			{
				COMPARATOR_ASSERT_EQUAL(expected, toTest, GetInt());
			}
			else
			{
				COMPARATOR_ASSERT_NEAR(expected, toTest, GetDouble(), 1e-5);
			}
		}
		else if (expected.GetType() == rapidjson::kObjectType)
		{
			COMPARATOR_ASSERT_EQUAL(expected, toTest, GetObject().MemberCount());

			for (auto itr = expected.GetObject().MemberBegin(); itr != expected.GetObject().MemberEnd(); ++itr)
			{
				std::string memberName = itr->name.GetString();
				if (!toTest.HasMember(memberName))
				{
					return AssertionFailure() << "Expected member '" << memberName << "' not found.";
				}

				testing::AssertionResult memberValueResult = EntityComparator()(expected[memberName], toTest[memberName]);
				if (!memberValueResult)
				{
					return AssertionFailure() << memberName << ": " << memberValueResult.message();
				}
			}
		}
		else if (expected.GetType() == rapidjson::kArrayType)
		{
			COMPARATOR_ASSERT_EQUAL(expected, toTest, GetArray().Size());

			rapidjson::SizeType nItems = expected.Size();
			for (rapidjson::SizeType i = 0; i < nItems; i++)
			{
				testing::AssertionResult itemResult = EntityComparator()(expected[i], toTest[i]);
				if (!itemResult)
				{
					return AssertionFailure() << "[" << i << "]: " << itemResult.message();
				}
			}
		}

		return AssertionSuccess();
	}

}}