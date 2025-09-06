#include "pch.h"
#include <string>
#include <msclr/marshal_cppstd.h>
#include "EcrBridge.h"
using namespace msclr::interop;

extern "C" __declspec(dllexport)
const wchar_t* Ecr_Init(const wchar_t* config) {
    System::String^ result = EcrBridge::Bridge::Init(gcnew System::String(config));
    static std::wstring buffer;
    buffer = marshal_as<std::wstring>(result);
    return buffer.c_str();
}

extern "C" __declspec(dllexport)
const wchar_t* Ecr_Connect(const wchar_t* posUrl, const wchar_t* config) {
    System::String^ result = EcrBridge::Bridge::Connect(gcnew System::String(posUrl), gcnew System::String(config));
    static std::wstring buffer;
    buffer = marshal_as<std::wstring>(result);
    return buffer.c_str();
}

extern "C" __declspec(dllexport)
bool Ecr_Connected() {
    return EcrBridge::Bridge::Connected();
}

extern "C" __declspec(dllexport)
const wchar_t* Ecr_Execute(const wchar_t* cmd, const wchar_t* sessionId) {
    System::String^ result = EcrBridge::Bridge::Execute(gcnew System::String(cmd), gcnew System::String(sessionId));
    static std::wstring buffer;
    buffer = marshal_as<std::wstring>(result);
    return buffer.c_str();
}

extern "C" __declspec(dllexport)
const wchar_t* Ecr_QrDecode(const wchar_t* cipher) {  
    static std::wstring buffer;  
    if (EcrBridge::Bridge^ bridgeInstance = gcnew EcrBridge::Bridge()) {  
        System::String^ result = bridgeInstance->qrDecode(gcnew System::String(cipher));  
        buffer = marshal_as<std::wstring>(result);  
    }  
    return buffer.c_str();  
}

extern "C" __declspec(dllexport)
const wchar_t* Ecr_QrEncode(const wchar_t* plain) {  
    static std::wstring buffer;  
    if (EcrBridge::Bridge^ bridgeInstance = gcnew EcrBridge::Bridge()) {  
        System::String^ result = bridgeInstance->qrEncode(gcnew System::String(plain));  
        buffer = marshal_as<std::wstring>(result);  
    }  
    return buffer.c_str();  
}