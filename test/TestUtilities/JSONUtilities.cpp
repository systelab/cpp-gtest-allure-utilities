#include "JSONUtilities.h"

#include "EntityComparator.h"

#include <rapidjson/document.h>


namespace systelab { namespace test_utility {

	testing::AssertionResult compareJSONs(const std::string& expected, const std::string& toTest)
	{
		rapidjson::Document expectedDocument(rapidjson::kObjectType);
		expectedDocument.Parse(expected);
		if (expectedDocument.HasParseError())
		{
			return testing::AssertionFailure() << "Expected value is not valid JSON document";
		}

		rapidjson::Document toTestDocument(rapidjson::kObjectType);
		toTestDocument.Parse(toTest);
		if (toTestDocument.HasParseError())
		{
			return testing::AssertionFailure() << "ToTest value is not valid JSON document";
		}

		testing::AssertionResult comparisonResult = test_utility::EntityComparator()((rapidjson::Value&) expectedDocument, (rapidjson::Value&) toTestDocument);
		if (!comparisonResult)
		{
			return testing::AssertionFailure() << "JSON objects are different: " << comparisonResult.message();
		}

		return testing::AssertionSuccess();
	}

}}


