#include "TestSuiteJSONSerializer.h"

#include "Model/StepType.h"
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
		if (model::Format::ALLURE_FOR_JENKINS != testSuite.getFormat())
			jsonParent.addMember("uuid", testSuite.getUUID());
		
		jsonParent.addMember("name", testSuite.getName());
		jsonParent.addMember("status", translateStatusToString(testSuite.getStatus()));
		jsonParent.addMember("stage", translateStageToString(testSuite.getStage()));
		jsonParent.addMember("start", testSuite.getStart());
		jsonParent.addMember("stop", testSuite.getStop());

		addLabelsToJSON(testSuite, jsonParent);
		addLinksToJSON(testSuite.getLinks(), jsonParent);
		addTestCasesToJSON(testSuite.getTestCases(), jsonParent);
	}

	void TestSuiteJSONSerializer::addLabelsToJSON(const model::TestSuite& testSuite, json::IJSONValue& jsonParent) const
	{
		auto jsonLabelsArray = jsonParent.buildValue(json::ARRAY_TYPE);

		auto jsonSuiteLabel = jsonParent.buildValue(json::OBJECT_TYPE);
		jsonSuiteLabel->addMember("name", "suite");
		jsonSuiteLabel->addMember("value", testSuite.getName());
		jsonLabelsArray->addArrayValue(std::move(jsonSuiteLabel));

		const std::vector<model::Label>& labels = testSuite.getLabels();
		if (labels.size() > 0)
		{
			for (const auto& label : labels)
			{
				auto jsonLabel = jsonParent.buildValue(json::OBJECT_TYPE);
				jsonLabel->addMember("name", label.getName());
				jsonLabel->addMember("value", label.getValue());
				jsonLabelsArray->addArrayValue(std::move(jsonLabel));
			}
		}

		jsonParent.addMember("labels", std::move(jsonLabelsArray));
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
				auto jsonTestCase = jsonParent.buildValue(json::OBJECT_TYPE);
				jsonTestCase->addMember("name", "Action: " + testCase.getName());
				jsonTestCase->addMember("status", translateStatusToString(testCase.getStatus()));
				jsonTestCase->addMember("stage", translateStageToString(testCase.getStage()));
				jsonTestCase->addMember("start", testCase.getStart());
				jsonTestCase->addMember("stop", testCase.getStop());

				addTestCaseStepsToJSON(testCase, *jsonTestCase);

				jsonTestCasesArray->addArrayValue(std::move(jsonTestCase));
			}

			jsonParent.addMember("steps", std::move(jsonTestCasesArray));
		}
	}

	void TestSuiteJSONSerializer::addTestCaseStepsToJSON(const model::TestCase& testCase, json::IJSONValue& jsonParent) const
	{
		unsigned int nSteps = testCase.getStepCount();
		if (nSteps > 0)
		{
			auto jsonStepsArray = jsonParent.buildValue(json::ARRAY_TYPE);
			for (unsigned int i = 0; i < nSteps; i++)
			{
				auto step = testCase.getStep(i);
				auto jsonStep = jsonStepsArray->buildValue(json::OBJECT_TYPE);
				auto actionPrefix = (step->getStepType() == model::StepType::ACTION_STEP) ? "Action: " : "";

				jsonStep->addMember("name", actionPrefix + step->getName());
				jsonStep->addMember("status", translateStatusToString(step->getStatus()));
				jsonStep->addMember("stage", translateStageToString(step->getStage()));
				jsonStep->addMember("start", step->getStart());
				jsonStep->addMember("stop", step->getStop());

				jsonStepsArray->addArrayValue(std::move(jsonStep));
			}

			jsonParent.addMember("steps", std::move(jsonStepsArray));
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
