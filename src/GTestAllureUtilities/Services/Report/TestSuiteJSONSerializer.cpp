#include "TestSuiteJSONSerializer.h"

#include "Model/TestSuite.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONValue.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestSuiteJSONSerializer::TestSuiteJSONSerializer(std::unique_ptr<json::IJSONAdapter> jsonAdapter)
		:m_jsonAdapter(std::move(jsonAdapter))
	{
	}

	std::string TestSuiteJSONSerializer::serialize(const model::TestSuite& testSuite) const
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		auto& jsonDocumentRoot = jsonDocument->getRootValue();
		jsonDocumentRoot.setType(systelab::json::OBJECT_TYPE);

		addTestSuiteToJSON(testSuite, jsonDocumentRoot);

		return jsonDocument->serialize();
	}

	void TestSuiteJSONSerializer::addTestSuiteToJSON(const model::TestSuite& testSuite, json::IJSONValue& jsonParent) const
	{
		jsonParent.addMember("uuid", testSuite.getUUID());
		jsonParent.addMember("name", testSuite.getName());
		jsonParent.addMember("status", translateStatusToString(testSuite.getStatus()));
		jsonParent.addMember("stage", translateStageToString(testSuite.getStage()));
		jsonParent.addMember("start", testSuite.getStart());
		jsonParent.addMember("stop", testSuite.getStop());

		addLabelsToJSON(testSuite.getLabels(), jsonParent);
		addLinksToJSON(testSuite.getLinks(), jsonParent);
		addTestCasesToJSON(testSuite.getTestCases(), jsonParent);
	}

	void TestSuiteJSONSerializer::addLabelsToJSON(const std::vector<model::Label>& labels, json::IJSONValue& jsonParent) const
	{
		if (labels.size())
		{
			auto jsonLabelsArray = jsonParent.buildValue(json::ARRAY_TYPE);
			for (const auto& label : labels)
			{
				auto jsonLabel = jsonParent.buildValue(json::OBJECT_TYPE);
				jsonLabel->addMember("name", label.getName());
				jsonLabel->addMember("value", label.getValue());
				jsonLabelsArray->addArrayValue(std::move(jsonLabel));
			}

			jsonParent.addMember("labels", std::move(jsonLabelsArray));
		}
	}

	void TestSuiteJSONSerializer::addLinksToJSON(const std::vector<model::Link>& links, json::IJSONValue& jsonParent) const
	{
		if (links.size() > 0)
		{
			auto jsonLinksArray = jsonParent.buildValue(json::ARRAY_TYPE);
			for (const auto& link : links)
			{
				auto jsonLink = jsonParent.buildValue(json::OBJECT_TYPE);
				jsonLink->addMember("name", link.getName());
				jsonLink->addMember("url", link.getURL());
				jsonLink->addMember("type", link.getType());
				jsonLinksArray->addArrayValue(std::move(jsonLink));
			}

			jsonParent.addMember("links", std::move(jsonLinksArray));
		}
	}

	void TestSuiteJSONSerializer::addTestCasesToJSON(const std::vector<model::TestCase>& testCases, json::IJSONValue& jsonParent) const
	{
		if (testCases.size() > 0)
		{
			auto jsonTestCasesArray = jsonParent.buildValue(json::ARRAY_TYPE);
			for (const auto& testCase : testCases)
			{
				addActionsToJSON(testCase.getActions(), *jsonTestCasesArray);
			}

			jsonParent.addMember("steps", std::move(jsonTestCasesArray));
		}
	}


	void TestSuiteJSONSerializer::addActionsToJSON(const std::vector<model::Action>& actions, json::IJSONValue& jsonParentArray) const
	{
		if (actions.size() > 0)
		{
			for (const auto& action : actions)
			{
				auto jsonAction = jsonParentArray.buildValue(json::OBJECT_TYPE);
				jsonAction->addMember("name", "Action: " + action.getName());
				jsonAction->addMember("status", translateStatusToString(action.getStatus()));
				jsonAction->addMember("stage", translateStageToString(action.getStage()));
				jsonAction->addMember("start", action.getStart());
				jsonAction->addMember("stop", action.getStop());

				addExpectedResultsToJSON(action.getExpectedResults(), *jsonAction);

				jsonParentArray.addArrayValue(std::move(jsonAction));
			}
		}
	}

	void TestSuiteJSONSerializer::addExpectedResultsToJSON(const std::vector<model::ExpectedResult>& expectedResults,
														   json::IJSONValue& jsonAction) const
	{
		if (expectedResults.size() > 0)
		{
			auto jsonExpectedResultsArray = jsonAction.buildValue(json::ARRAY_TYPE);
			for (const auto& expectedResult : expectedResults)
			{
				auto jsonExpectedResult = jsonAction.buildValue(json::OBJECT_TYPE);
				jsonExpectedResult->addMember("name", expectedResult.getName());
				jsonExpectedResult->addMember("status", translateStatusToString(expectedResult.getStatus()));
				jsonExpectedResult->addMember("stage", translateStageToString(expectedResult.getStage()));
				jsonExpectedResult->addMember("start", expectedResult.getStart());
				jsonExpectedResult->addMember("stop", expectedResult.getStop());

				addParametersToJSON(expectedResult.getParameters(), *jsonExpectedResult);

				jsonExpectedResultsArray->addArrayValue(std::move(jsonExpectedResult));
			}

			jsonAction.addMember("steps", std::move(jsonExpectedResultsArray));
		}
	}

	void TestSuiteJSONSerializer::addParametersToJSON(const std::vector<model::Parameter>& parameters,
													  json::IJSONValue& jsonValue) const
	{
		if (parameters.size() > 0)
		{
			auto jsonParametersArray = jsonValue.buildValue(json::ARRAY_TYPE);
			for (const auto& parameter : parameters)
			{
				auto jsonParameter = jsonValue.buildValue(json::OBJECT_TYPE);
				jsonParameter->addMember("name", parameter.getName());
				jsonParameter->addMember("value", parameter.getValue());
				jsonParametersArray->addArrayValue(std::move(jsonParameter));
			}

			jsonValue.addMember("parameters", std::move(jsonParametersArray));
		}
	}

	std::string TestSuiteJSONSerializer::translateStatusToString(model::Status status) const
	{
		if (status == model::Status::SKIPPED)
		{
			return "skipped";
		}
		else if (status == model::Status::BROKEN)
		{
			return "broken";
		}
		else if (status == model::Status::FAILED)
		{
			return "failed";
		}
		else if (status == model::Status::PASSED)
		{
			return "passed";
		}
		else // (status == model::Status::UNKNOWN)
		{
			return "unknown";
		}
	}

	std::string TestSuiteJSONSerializer::translateStageToString(model::Stage stage) const
	{
		if (stage == model::Stage::FINISHED)
		{
			return "finished";
		}
		else if (stage == model::Stage::SCHEDULED)
		{
			return "scheduled";
		}
		else if (stage == model::Stage::INTERRUPTED)
		{
			return "interrupted";
		}
		else if (stage == model::Stage::RUNNING)
		{
			return "running";
		}
		else // (stage == model::Stage::PENDING)
		{
			return "pending";
		}
	}

}}}
