#pragma once

#include "ITestSuiteJSONSerializer.h"

#include <memory>
#include <vector>


namespace systelab { namespace json {
	class IJSONAdapter;
	class IJSONValue;
}}

namespace systelab { namespace gtest_allure { namespace model {
	class Action;
	class ExpectedResult;
	class Label;
	class Link;
	class Parameter;
	class TestCase;
	class TestSuite;
	enum class Status;
	enum class Stage;
}}}

namespace systelab { namespace gtest_allure { namespace service {

	class TestSuiteJSONSerializer : public ITestSuiteJSONSerializer
	{
	public:
		TestSuiteJSONSerializer(std::unique_ptr<json::IJSONAdapter>);
		virtual ~TestSuiteJSONSerializer() = default;

		std::string serialize(const model::TestSuite&) const;

	private:
		void addTestSuiteToJSON(const model::TestSuite&, json::IJSONValue&) const;
		void addLabelsToJSON(const std::vector<model::Label>&, json::IJSONValue&) const;
		void addLinksToJSON(const std::vector<model::Link>&, json::IJSONValue&) const;
		void addTestCasesToJSON(const std::vector<model::TestCase>&, json::IJSONValue&) const;
		void addActionsToJSON(const std::vector<model::Action>&, json::IJSONValue&) const;
		void addExpectedResultsToJSON(const std::vector<model::ExpectedResult>&, json::IJSONValue&) const;
		void addParametersToJSON(const std::vector<model::Parameter>&, json::IJSONValue&) const;

		std::string translateStatusToString(model::Status) const;
		std::string translateStageToString(model::Stage) const;

	private:
		std::unique_ptr<json::IJSONAdapter> m_jsonAdapter;
	};

}}}
