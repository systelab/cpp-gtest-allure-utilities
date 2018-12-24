#include "TestCaseJSONSerializer.h"

#include "Model/TestCase.h"

#include <rapidjson/writer.h>


namespace systelab { namespace gtest_allure_utilities { namespace service {

	TestCaseJSONSerializer::TestCaseJSONSerializer()
	{
	}

	std::string TestCaseJSONSerializer::serialize(const model::TestCase& testCase) const
	{
		rapidjson::Document jsonDocument;
		rapidjson::Document::AllocatorType& allocator = jsonDocument.GetAllocator();

		addTestCaseToJSON(testCase, jsonDocument, allocator);

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> jsonWriter(buffer);
		jsonDocument.Accept(jsonWriter);
		std::string jsonContent = buffer.GetString();

		return jsonContent;
	}

	void TestCaseJSONSerializer::addTestCaseToJSON(const model::TestCase& testCase,
												   rapidjson::Value& jsonDocument,
												   rapidjson::Document::AllocatorType& allocator) const
	{
		std::string uuid = testCase.getUUID();
		if (uuid != "")
		{
			jsonDocument.AddMember("uuid", uuid, allocator);
		}

		std::string historyId = testCase.getHistoryId();
		if (historyId != "")
		{
			jsonDocument.AddMember("historyId", historyId, allocator);
		}

		std::string name = testCase.getName();
		if (name != "")
		{
			jsonDocument.AddMember("name", name, allocator);
		}

		std::string description = testCase.getDescription();
		if (description != "")
		{
			jsonDocument.AddMember("description", description, allocator);
		}

		jsonDocument.AddMember("status", translateStatusToString(testCase.getStatus()), allocator);
		jsonDocument.AddMember("stage", translateStageToString(testCase.getStage()), allocator);
		jsonDocument.AddMember("start", testCase.getStart(), allocator);
		jsonDocument.AddMember("stop", testCase.getStop(), allocator);

		addLabelsToJSON(testCase.getLabels(), jsonDocument, allocator);
		addLinksToJSON(testCase.getLinks(), jsonDocument, allocator);
		addActionsToJSON(testCase.getActions(), jsonDocument, allocator);
	}

	void TestCaseJSONSerializer::addLabelsToJSON(const std::vector<model::Label>& labels,
												 rapidjson::Value& jsonDocument,
												 rapidjson::Document::AllocatorType& allocator) const
	{
		if (labels.size())
		{
			rapidjson::Value jsonLabelsArray(rapidjson::kArrayType);
			for (const auto& label : labels)
			{
				rapidjson::Value jsonLabel(rapidjson::kObjectType);
				jsonLabel.AddMember("name", label.getName(), allocator);
				jsonLabel.AddMember("value", label.getValue(), allocator);
				jsonLabelsArray.PushBack(jsonLabel.Move(), allocator);
			}

			jsonDocument.AddMember("labels", jsonLabelsArray.Move(), allocator);
		}
	}

	void TestCaseJSONSerializer::addLinksToJSON(const std::vector<model::Link>& links,
												rapidjson::Value& jsonDocument,
												rapidjson::Document::AllocatorType& allocator) const
	{
		if (links.size() > 0)
		{
			rapidjson::Value jsonLinksArray(rapidjson::kArrayType);
			for (const auto& link : links)
			{
				rapidjson::Value jsonLink(rapidjson::kObjectType);
				jsonLink.AddMember("name", link.getName(), allocator);
				jsonLink.AddMember("url", link.getURL(), allocator);
				jsonLink.AddMember("type", link.getType(), allocator);
				jsonLinksArray.PushBack(jsonLink.Move(), allocator);
			}

			jsonDocument.AddMember("links", jsonLinksArray.Move(), allocator);
		}
	}

	void TestCaseJSONSerializer::addActionsToJSON(const std::vector<model::Action>& actions,
												  rapidjson::Value& jsonDocument,
												  rapidjson::Document::AllocatorType& allocator) const
	{
		if (actions.size() > 0)
		{
			rapidjson::Value jsonActionsArray(rapidjson::kArrayType);
			for (const auto& action : actions)
			{
				rapidjson::Value jsonAction(rapidjson::kObjectType);
				jsonAction.AddMember("name", "Action: " + action.getName(), allocator);
				jsonAction.AddMember("status", translateStatusToString(action.getStatus()), allocator);
				jsonAction.AddMember("stage", translateStageToString(action.getStage()), allocator);
				jsonAction.AddMember("start", action.getStart(), allocator);
				jsonAction.AddMember("stop", action.getStop(), allocator);

				addExpectedResultsToJSON(action.getExpectedResults(), jsonAction, allocator);

				jsonActionsArray.PushBack(jsonAction.Move(), allocator);
			}

			jsonDocument.AddMember("steps", jsonActionsArray.Move(), allocator);
		}
	}

	void TestCaseJSONSerializer::addExpectedResultsToJSON(const std::vector<model::ExpectedResult>& expectedResults,
														  rapidjson::Value& jsonAction,
														  rapidjson::Document::AllocatorType& allocator) const
	{
		if (expectedResults.size() > 0)
		{
			rapidjson::Value jsonExpectedResultsArray(rapidjson::kArrayType);
			for (const auto& expectedResult : expectedResults)
			{
				rapidjson::Value jsonExpectedResult(rapidjson::kObjectType);
				jsonExpectedResult.AddMember("name", expectedResult.getName(), allocator);
				jsonExpectedResult.AddMember("status", translateStatusToString(expectedResult.getStatus()), allocator);
				jsonExpectedResult.AddMember("stage", translateStageToString(expectedResult.getStage()), allocator);
				jsonExpectedResult.AddMember("start", expectedResult.getStart(), allocator);
				jsonExpectedResult.AddMember("stop", expectedResult.getStop(), allocator);

				addParametersToJSON(expectedResult.getParameters(), jsonExpectedResult, allocator);

				jsonExpectedResultsArray.PushBack(jsonExpectedResult.Move(), allocator);
			}

			jsonAction.AddMember("steps", jsonExpectedResultsArray.Move(), allocator);
		}
	}

	void TestCaseJSONSerializer::addParametersToJSON(const std::vector<model::Parameter>& parameters,
													 rapidjson::Value& jsonValue,
													 rapidjson::Document::AllocatorType& allocator) const
	{
		if (parameters.size() > 0)
		{
			rapidjson::Value jsonParametersArray(rapidjson::kArrayType);
			for (const auto& parameter : parameters)
			{
				rapidjson::Value jsonParameter(rapidjson::kObjectType);
				jsonParameter.AddMember("name", parameter.getName(), allocator);
				jsonParameter.AddMember("value", parameter.getValue(), allocator);
				jsonParametersArray.PushBack(jsonParameter.Move(), allocator);
			}

			jsonValue.AddMember("parameters", jsonParametersArray.Move(), allocator);
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
