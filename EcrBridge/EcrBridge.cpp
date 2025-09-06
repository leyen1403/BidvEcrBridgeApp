#include "pch.h"
#include "EcrBridge.h"
#using <EcrClient.dll>

using namespace System;
using namespace com::ingenico::vn::EcrClient;

namespace EcrBridge
{
    String^ Bridge::Init(String^ clientConfig)
    {
        try {
            EcrClient::init(clientConfig);
            return "OK";
        }
        catch (Exception^ ex) {
            return "ERR: " + ex->Message;
        }
    }

    String^ Bridge::Connect(String^ posUrl, String^ ecrClientConfig)
    {
        try {
            auto task = EcrClient::connect(posUrl, ecrClientConfig);
            task->Wait();
            return task->Result;
        }
        catch (Exception^ ex) {
            return "ERR: " + ex->Message;
        }
    }

    bool Bridge::Connected()
    {
        return EcrClient::connected();
    }

    String^ Bridge::Execute(String^ command, String^ sessionId)
    {
        try {
            auto task = EcrClient::execute(command, sessionId);
            task->Wait();
            return task->Result;
        }
        catch (Exception^ ex) {
            return "ERR: " + ex->Message;
        }
    }

    String^ Bridge::qrDecode(String^ cipher)
    {
        try {
            return EcrClient::qrDecode(cipher);
        }
        catch (Exception^ ex) {
            return "ERR: " + ex->Message;
        }
	}
    String^ Bridge::qrEncode(String^ plain)
    {
        try
        {
			return EcrClient::qrEncode(plain);
        }
        catch (Exception^ ex)
        {
            return "ERR: " + ex->Message;
		}
    }
}
