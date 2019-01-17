#pragma once

#include "ITestCaseJSONSerializer.h"

#include <rapidjson/document.h>
#include <vector>

namespace systelab { namespace gtest_allure_utilities { namespace model {
	class Action;
	class ExpectedResult;
	class Label;
	class Link;
	class Parameter;
	class TestCase;
	enum class Status;
	enum class Stage;
}}}

namespace systelab { namespace gtest_allure_utilities { namespace service {

	class TestCaseJSONSerializer : public ITestCaseJSONSerializer
	{
	public:
		TestCaseJSONSerializer();
		virtual ~TestCaseJSONSerializer() = default;

		std::string serialize(const model::TestCase&) const;

	private:
		void addTestCaseToJSON(const model::TestCase&, rapidjson::Value&, rapidjson::Document::AllocatorType&) const;
		void addLabelsToJSON(const std::vector<model::Label>&, rapidjson::Value&, rapidjson::Document::AllocatorType&) const;
		void addLinksToJSON(const std::vector<model::Link>&, rapidjson::Value&, rapidjson::Document::AllocatorType&) const;
		void addActionsToJSON(const std::vector<model::Action>&, rapidjson::Value&, rapidjson::Document::AllocatorType&) const;
		void addExpectedResultsToJSON(const std::vector<model::ExpectedResult>&, rapidjson::Value&, rapidjson::Document::AllocatorType&) const;
		void addParametersToJSON(const std::vector<model::Parameter>&, rapidjson::Value&, rapidjson::Document::AllocatorType&) const;

		std::string translateStatusToString(model::Status) const;
		std::string translateStageToString(model::Stage) const;
	};

}}}
