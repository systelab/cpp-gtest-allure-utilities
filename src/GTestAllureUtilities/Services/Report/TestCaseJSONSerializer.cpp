#include "TestCaseJSONSerializer.h"

#include "Model/TestCase.h"

#include "JSONAdapterInterface/IJSONAdapter.h"
#include "JSONAdapterInterface/IJSONDocument.h"
#include "JSONAdapterInterface/IJSONValue.h"


namespace systelab { namespace gtest_allure { namespace service {

	TestCaseJSONSerializer::TestCaseJSONSerializer(std::unique_ptr<json::IJSONAdapter> jsonAdapter)
		:m_jsonAdapter(std::move(jsonAdapter))
	{
	}

	std::string TestCaseJSONSerializer::serialize(const model::TestCase& testCase) const
	{
		auto jsonDocument = m_jsonAdapter->buildEmptyDocument();
		auto& jsonDocumentRoot = jsonDocument->getRootValue();
		addTestCaseToJSON(testCase, jsonDocumentRoot);
		std::string jsonContent = jsonDocument->serialize();

		return jsonContent;
	}

	void TestCaseJSONSerializer::addTestCaseToJSON(const model::TestCase& testCase, json::IJSONValue& jsonDocumentRoot) const
	{
		std::string uuid = testCase.getUUID();
		if (uuid != "")
		{
			jsonDocumentRoot.addMember("uuid", uuid);
		}

		std::string historyId = testCase.getHistoryId();
		if (historyId != "")
		{
			jsonDocumentRoot.addMember("historyId", historyId);
		}

		std::string name = testCase.getName();
		if (name != "")
		{
			jsonDocumentRoot.addMember("name", name);
		}

		std::string description = testCase.getDescription();
		if (description != "")
		{
			jsonDocumentRoot.addMember("description", description);
		}

		jsonDocumentRoot.addMember("status", translateStatusToString(testCase.getStatus()));
		jsonDocumentRoot.addMember("stage", translateStageToString(testCase.getStage()));
		jsonDocumentRoot.addMember("start", testCase.getStart());
		jsonDocumentRoot.addMember("stop", testCase.getStop());

		addLabelsToJSON(testCase.getLabels(), jsonDocumentRoot);
		addLinksToJSON(testCase.getLinks(), jsonDocumentRoot);
		addActionsToJSON(testCase.getActions(), jsonDocumentRoot);
	}

	void TestCaseJSONSerializer::addLabelsToJSON(const std::vector<model::Label>& labels, json::IJSONValue& jsonDocumentRoot) const
	{
		if (labels.size())
		{
			auto jsonLabelsArray = jsonDocumentRoot.buildValue(json::ARRAY_TYPE);
			for (const auto& label : labels)
			{
				auto jsonLabel = jsonDocumentRoot.buildValue(json::OBJECT_TYPE);
				jsonLabel->addMember("name", label.getName());
				jsonLabel->addMember("value", label.getValue());
				jsonLabelsArray->addArrayValue(std::move(jsonLabel));
			}

			jsonDocumentRoot.addMember("labels", std::move(jsonLabelsArray));
		}
	}

	void TestCaseJSONSerializer::addLinksToJSON(const std::vector<model::Link>& links, json::IJSONValue& jsonDocumentRoot) const
	{
		if (links.size() > 0)
		{
			auto jsonLinksArray = jsonDocumentRoot.buildValue(json::ARRAY_TYPE);
			for (const auto& link : links)
			{
				auto jsonLink = jsonDocumentRoot.buildValue(json::OBJECT_TYPE);
				jsonLink->addMember("name", link.getName());
				jsonLink->addMember("url", link.getURL());
				jsonLink->addMember("type", link.getType());
				jsonLinksArray->addArrayValue(std::move(jsonLink));
			}

			jsonDocumentRoot.addMember("links", std::move(jsonLinksArray));
		}
	}

	void TestCaseJSONSerializer::addActionsToJSON(const std::vector<model::Action>& actions, json::IJSONValue& jsonDocumentRoot) const
	{
		if (actions.size() > 0)
		{
			auto jsonActionsArray = jsonDocumentRoot.buildValue(json::ARRAY_TYPE);
			for (const auto& action : actions)
			{
				auto jsonAction = jsonDocumentRoot.buildValue(json::OBJECT_TYPE);
				jsonAction->addMember("name", "Action: " + action.getName());
				jsonAction->addMember("status", translateStatusToString(action.getStatus()));
				jsonAction->addMember("stage", translateStageToString(action.getStage()));
				jsonAction->addMember("start", action.getStart());
				jsonAction->addMember("stop", action.getStop());

				addExpectedResultsToJSON(action.getExpectedResults(), *jsonAction);

				jsonActionsArray->addArrayValue(std::move(jsonAction));
			}

			jsonDocumentRoot.addMember("steps", std::move(jsonActionsArray));
		}
	}

	void TestCaseJSONSerializer::addExpectedResultsToJSON(const std::vector<model::ExpectedResult>& expectedResults,
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

	void TestCaseJSONSerializer::addParametersToJSON(const std::vector<model::Parameter>& parameters,
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

	std::string TestCaseJSONSerializer::translateStatusToString(model::Status status) const
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

	std::string TestCaseJSONSerializer::translateStageToString(model::Stage stage) const
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
