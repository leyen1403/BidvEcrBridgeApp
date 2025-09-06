#pragma once
using namespace System;

namespace EcrBridge
{
    public ref class Bridge
    {
    public:
        static String^ Init(String^ clientConfig);
        static String^ Connect(String^ posUrl, String^ ecrClientConfig);
        static bool Connected();
        static String^ Execute(String^ command, String^ sessionId);
        String^ qrDecode(String^ cipher);
		String^ qrEncode(String^ plain);
    };
}
