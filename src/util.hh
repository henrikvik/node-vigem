#pragma once
#include <napi.h>
#include "vigem_types.hh"
#include <ViGEm/Client.h>

const char* VIGEM_ERROR_STR(VIGEM_ERROR error) {
    switch (error) {
    case VIGEM_ERROR_NONE:                        return "VIGEM_ERROR_NONE";
    case VIGEM_ERROR_BUS_NOT_FOUND:               return "VIGEM_ERROR_BUS_NOT_FOUND";
    case VIGEM_ERROR_NO_FREE_SLOT:                return "VIGEM_ERROR_NO_FREE_SLOT";
    case VIGEM_ERROR_INVALID_TARGET:              return "VIGEM_ERROR_INVALID_TARGET";
    case VIGEM_ERROR_REMOVAL_FAILED:              return "VIGEM_ERROR_REMOVAL_FAILED";
    case VIGEM_ERROR_ALREADY_CONNECTED:           return "VIGEM_ERROR_ALREADY_CONNECTED";
    case VIGEM_ERROR_TARGET_UNINITIALIZED:        return "VIGEM_ERROR_TARGET_UNINITIALIZED";
    case VIGEM_ERROR_TARGET_NOT_PLUGGED_IN:       return "VIGEM_ERROR_TARGET_NOT_PLUGGED_IN";
    case VIGEM_ERROR_BUS_VERSION_MISMATCH:        return "VIGEM_ERROR_BUS_VERSION_MISMATCH";
    case VIGEM_ERROR_BUS_ACCESS_FAILED:           return "VIGEM_ERROR_BUS_ACCESS_FAILED";
    case VIGEM_ERROR_CALLBACK_ALREADY_REGISTERED: return "VIGEM_ERROR_CALLBACK_ALREADY_REGISTERED";
    case VIGEM_ERROR_CALLBACK_NOT_FOUND:          return "VIGEM_ERROR_CALLBACK_NOT_FOUND";
    case VIGEM_ERROR_BUS_ALREADY_CONNECTED:       return "VIGEM_ERROR_BUS_ALREADY_CONNECTED";
    case VIGEM_ERROR_BUS_INVALID_HANDLE:          return "VIGEM_ERROR_BUS_INVALID_HANDLE";
    case VIGEM_ERROR_XUSB_USERINDEX_OUT_OF_RANGE: return "VIGEM_ERROR_XUSB_USERINDEX_OUT_OF_RANGE";
    }
    return "VIGEM_UNKNOWN_ERROR";
};

#define EXPORT_FUNC(env, exports, key, function)\
exports.Set(                                    \
    Napi::String::New(env, key),                \
    Napi::Function::New(env, function))

#define VIGEM_ASSERT(env, error)                 \
if (!VIGEM_SUCCESS(error)) {                     \
    Napi::Error::New(env, VIGEM_ERROR_STR(error))\
        .ThrowAsJavaScriptException();}

#define GET_AS_OBJ(obj, key) obj.Get(key).As<Napi::Object>()
#define GET_AS_INT(obj, key) obj.Get(key).As<Napi::Number>().Int32Value()
#define GET_AS_FLOAT(obj, key) obj.Get(key).As<Napi::Number>().FloatValue()
#define GET_AS_FLOAT2(obj, key, subkey) GET_AS_FLOAT(GET_AS_OBJ(obj, key), subkey)
