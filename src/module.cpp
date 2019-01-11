#include <napi.h>

#pragma region WinTypeMin
#define RtlZeroMemory(ptr, size) memset(ptr, 0, size)
#define FORCEINLINE
#define VOID void
#define BOOL bool
typedef unsigned char BYTE;
typedef unsigned char UCHAR;
typedef short SHORT;
typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef unsigned long *PULONG;
#pragma endregion

#include <ViGEm/Client.h>
#include <ViGEm/Common.h>
#include <functional>
#include "util.hpp"
#include <limits>

#define export_function(env, exports, key, function)\
exports.Set(                                        \
    Napi::String::New(env, key),                    \
    Napi::Function::New(env, function))

#define VIGEM_ASSERT(error)                             \
if (!VIGEM_SUCCESS(error)) {                            \
    Napi::Error::New(info.Env(), VIGEM_ERROR_STR(error))\
        .ThrowAsJavaScriptException();                  \
}

#define GET_AS_OBJ(obj, key) obj.Get(key).As<Napi::Object>()
#define GET_AS_INT(obj, key) obj.Get(key).As<Napi::Number>().Int32Value()
#define GET_AS_FLOAT(obj, key) obj.Get(key).As<Napi::Number>().FloatValue()
#define GET_AS_FLOAT2(obj, key, subkey) GET_AS_FLOAT(GET_AS_OBJ(obj, key), subkey)

namespace module
{
    const float DPAD_EPSILON = 0.5;
    const uint64_t XUSB_TRIGGER_MAX = std::numeric_limits<BYTE>::max();
    const uint64_t XUSB_THUMB_MAX = std::numeric_limits<SHORT>::max();
    const uint64_t DS4_TRIGGER_MAX = std::numeric_limits<BYTE>::max();
    const uint64_t DS4_THUMB_MAX = std::numeric_limits<BYTE>::max();

    using ExternalClient = Napi::External<_VIGEM_CLIENT_T>;
    using ExternalTarget = Napi::External<_VIGEM_TARGET_T>;

    //VIGEM_API PVIGEM_CLIENT vigem_alloc(void);
    ExternalClient module_alloc(const Napi::CallbackInfo& info) {
        return ExternalClient::New(info.Env(), vigem_alloc(),
            [] (Napi::Env env, PVIGEM_CLIENT client) {
                vigem_free(client);
            }
        );
    }

    //VIGEM_API void vigem_free(PVIGEM_CLIENT vigem);
    void module_free(const Napi::CallbackInfo& info) {
        vigem_free(info[0].As<ExternalClient>().Data());
    }

    //VIGEM_API VIGEM_ERROR vigem_connect(PVIGEM_CLIENT vigem);
    void module_connect(const Napi::CallbackInfo& info) {
        VIGEM_ASSERT(vigem_connect(info[0].As<ExternalClient>().Data()));
    }

    //VIGEM_API void vigem_disconnect(PVIGEM_CLIENT vigem);
    void module_disconnect(const Napi::CallbackInfo& info) {
        vigem_disconnect(info[0].As<ExternalClient>().Data());
    }

    //VIGEM_API PVIGEM_TARGET vigem_target_x360_alloc(void);
    ExternalTarget module_target_x360_alloc(const Napi::CallbackInfo& info) {
        return ExternalTarget::New(info.Env(), vigem_target_x360_alloc(),
            [] (Napi::Env env, PVIGEM_TARGET target) {
                vigem_target_free(target);
            }
        );
    }

    // VIGEM_API PVIGEM_TARGET vigem_target_ds4_alloc(void);
    ExternalTarget module_target_ds4_alloc(const Napi::CallbackInfo& info) {
        return ExternalTarget::New(info.Env(), vigem_target_ds4_alloc(),
            [] (Napi::Env env, PVIGEM_TARGET target) {
                vigem_target_free(target);
            }
        );
    }

    //VIGEM_API void vigem_target_free(PVIGEM_TARGET target);
    void module_target_free(const Napi::CallbackInfo& info) {
        vigem_target_free(info[0].As<ExternalTarget>().Data());
    }

    //VIGEM_API VIGEM_ERROR vigem_target_add(PVIGEM_CLIENT vigem, PVIGEM_TARGET target);
    void module_target_add(const Napi::CallbackInfo& info) {
        VIGEM_ASSERT(vigem_target_add(
            info[0].As<ExternalClient>().Data(),
            info[1].As<ExternalTarget>().Data()
        ));
    }

    //VIGEM_API VIGEM_ERROR vigem_target_add_async(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_TARGET_ADD_RESULT result);
    // TODO

    //VIGEM_API VIGEM_ERROR vigem_target_remove(PVIGEM_CLIENT vigem, PVIGEM_TARGET target);
    void module_target_remove(const Napi::CallbackInfo& info) {
        VIGEM_ASSERT(vigem_target_remove(
            info[0].As<ExternalClient>().Data(),
            info[1].As<ExternalTarget>().Data()
        ));
    }

    //VIGEM_API VIGEM_ERROR vigem_target_x360_register_notification(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_X360_NOTIFICATION notification);
    // TODO

    //VIGEM_API VIGEM_ERROR vigem_target_ds4_register_notification(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_DS4_NOTIFICATION notification);
    // TODO

    //VIGEM_API void vigem_target_x360_unregister_notification(PVIGEM_TARGET target);
    // TODO

    //VIGEM_API void vigem_target_ds4_unregister_notification(PVIGEM_TARGET target);
    // TODO

    //VIGEM_API void vigem_target_set_vid(PVIGEM_TARGET target, USHORT vid);
    void module_target_set_vid(const Napi::CallbackInfo& info) {
        vigem_target_set_vid(
            info[0].As<ExternalTarget>().Data(),
            info[1].As<Napi::Number>().Uint32Value()
        );
    }

    //VIGEM_API void vigem_target_set_pid(PVIGEM_TARGET target, USHORT pid);
    void module_target_set_pid(const Napi::CallbackInfo& info) {
        vigem_target_set_pid(
            info[0].As<ExternalTarget>().Data(),
            info[1].As<Napi::Number>().Uint32Value()
        );
    }

    //VIGEM_API USHORT vigem_target_get_vid(PVIGEM_TARGET target);
    Napi::Number module_target_get_vid(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), vigem_target_get_vid(
            info[0].As<ExternalTarget>().Data()
        ));
    }

    //VIGEM_API USHORT vigem_target_get_pid(PVIGEM_TARGET target);
    Napi::Number module_target_get_pid(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), vigem_target_get_pid(
            info[0].As<ExternalTarget>().Data()
        ));
    }

    //VIGEM_API VIGEM_ERROR vigem_target_x360_update(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, XUSB_REPORT report);
    void module_target_x360_update(const Napi::CallbackInfo& info) {
        XUSB_REPORT report = {};

        auto obj = info[2].As<Napi::Object>();
        report.wButtons = GET_AS_INT(obj, "buttons");

        auto triggers = GET_AS_OBJ(obj, "triggers");
        report.bLeftTrigger  = GET_AS_FLOAT(triggers, "left")  * XUSB_TRIGGER_MAX;
        report.bRightTrigger = GET_AS_FLOAT(triggers, "right") * XUSB_TRIGGER_MAX;

        auto thumbs = GET_AS_OBJ(obj, "thumbs");
        report.sThumbLX = GET_AS_FLOAT2(thumbs, "left",  "x") * XUSB_THUMB_MAX;
        report.sThumbLY = GET_AS_FLOAT2(thumbs, "left",  "y") * XUSB_THUMB_MAX;
        report.sThumbRX = GET_AS_FLOAT2(thumbs, "right", "x") * XUSB_THUMB_MAX;
        report.sThumbRY = GET_AS_FLOAT2(thumbs, "right", "y") * XUSB_THUMB_MAX;

        auto dpad_x = GET_AS_FLOAT2(obj, "dpad", "x");
        auto dpad_y = GET_AS_FLOAT2(obj, "dpad", "y");
        if (std::abs(dpad_x) > DPAD_EPSILON) {
            report.wButtons |= std::signbit(dpad_x)
                ? XUSB_GAMEPAD_DPAD_LEFT
                : XUSB_GAMEPAD_DPAD_RIGHT;
        }
        if (std::abs(dpad_y) > DPAD_EPSILON) {
            report.wButtons |= std::signbit(dpad_y)
                ? XUSB_GAMEPAD_DPAD_DOWN
                : XUSB_GAMEPAD_DPAD_UP;
        }

        VIGEM_ASSERT(vigem_target_x360_update(
            info[0].As<ExternalClient>().Data(),
            info[1].As<ExternalTarget>().Data(),
            report
        ));
    }

    //VIGEM_API VIGEM_ERROR vigem_target_ds4_update(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, DS4_REPORT report);
    void module_target_ds4_update(const Napi::CallbackInfo& info) {
        DS4_REPORT report = {};

        auto obj = info[2].As<Napi::Object>();
        report.wButtons = GET_AS_INT(obj, "buttons");
        report.bSpecial = GET_AS_INT(obj, "specials");

        auto triggers = GET_AS_OBJ(obj, "triggers");
        report.bTriggerL  = GET_AS_FLOAT(triggers, "left")  * DS4_TRIGGER_MAX;
        report.bTriggerR = GET_AS_FLOAT(triggers, "right") * DS4_TRIGGER_MAX;

        auto thumbs = GET_AS_OBJ(obj, "thumbs");
        report.bThumbLX = (GET_AS_FLOAT2(thumbs, "left",  "x") + 1) * 0.5 * DS4_THUMB_MAX;
        report.bThumbLY = (GET_AS_FLOAT2(thumbs, "left",  "y") + 1) * 0.5 * DS4_THUMB_MAX;
        report.bThumbRX = (GET_AS_FLOAT2(thumbs, "right", "x") + 1) * 0.5 * DS4_THUMB_MAX;
        report.bThumbRY = (GET_AS_FLOAT2(thumbs, "right", "y") + 1) * 0.5 * DS4_THUMB_MAX;

        auto dpad = GET_AS_OBJ(obj, "dpad");
        auto dpad_x = GET_AS_FLOAT(dpad, "x");
        auto dpad_y = GET_AS_FLOAT(dpad, "y");

        if (std::abs(dpad_x) > DPAD_EPSILON) {
            if (std::abs(dpad_y) > DPAD_EPSILON) {
                if (std::signbit(dpad_y)) {
                    report.wButtons |= std::signbit(dpad_x)
                        ? DS4_BUTTON_DPAD_SOUTHWEST
                        : DS4_BUTTON_DPAD_SOUTHEAST;
                } else {
                    report.wButtons |= std::signbit(dpad_x)
                        ? DS4_BUTTON_DPAD_NORTHWEST
                        : DS4_BUTTON_DPAD_NORTHEAST;
                }
            } else {
                report.wButtons |= std::signbit(dpad_x)
                    ? DS4_BUTTON_DPAD_WEST
                    : DS4_BUTTON_DPAD_EAST;
            }
        } else if (std::abs(dpad_y) > DPAD_EPSILON) {
            report.wButtons |= std::signbit(dpad_y)
                ? DS4_BUTTON_DPAD_SOUTH
                : DS4_BUTTON_DPAD_NORTH;
        } else {
            report.wButtons |= DS4_BUTTON_DPAD_NONE;
        }

        VIGEM_ASSERT(vigem_target_ds4_update(
            info[0].As<ExternalClient>().Data(),
            info[1].As<ExternalTarget>().Data(),
            report
        ));
    }

    //VIGEM_API ULONG vigem_target_get_index(PVIGEM_TARGET target);
    Napi::Number module_target_get_index(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), vigem_target_get_index(
            info[0].As<ExternalTarget>().Data()
        ));
    }

    //VIGEM_API VIGEM_TARGET_TYPE vigem_target_get_type(PVIGEM_TARGET target);
    Napi::Number module_target_get_type(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), vigem_target_get_type(
            info[0].As<ExternalTarget>().Data()
        ));
    }

    //VIGEM_API BOOL vigem_target_is_attached(PVIGEM_TARGET target);
    Napi::Boolean module_targe_is_attached(const Napi::CallbackInfo& info) {
        return Napi::Boolean::New(info.Env(), vigem_target_is_attached(
            info[0].As<ExternalTarget>().Data()
        ));
    }

    //VIGEM_API VIGEM_ERROR vigem_target_x360_get_user_index(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PULONG index);
    Napi::Number module_target_x360_get_user_index(const Napi::CallbackInfo& info) {
        PULONG index = nullptr;
        VIGEM_ASSERT(vigem_target_x360_get_user_index(
            info[0].As<ExternalClient>().Data(),
            info[0].As<ExternalTarget>().Data(),
            index
        ));
        return Napi::Number::New(info.Env(), *index);
    }


    Napi::Object Init(Napi::Env env, Napi::Object exports)
    {
        export_function(env, exports, "alloc", module_alloc);
        // export_function(env, exports, "free", module_free);
        export_function(env, exports, "connect", module_connect);
        export_function(env, exports, "disconnect", module_disconnect);
        export_function(env, exports, "target_x360_alloc", module_target_x360_alloc);
        export_function(env, exports, "target_ds4_alloc", module_target_ds4_alloc);
        // export_function(env, exports, "target_free", module_target_free);
        export_function(env, exports, "target_add", module_target_add);
        export_function(env, exports, "target_remove", module_target_remove);
        export_function(env, exports, "target_set_vid", module_target_set_vid);
        export_function(env, exports, "target_set_pid", module_target_set_pid);
        export_function(env, exports, "target_get_vid", module_target_get_vid);
        export_function(env, exports, "target_get_pid", module_target_get_pid);
        export_function(env, exports, "target_x360_update", module_target_x360_update);
        export_function(env, exports, "target_ds4_update", module_target_ds4_update);
        export_function(env, exports, "target_get_index", module_target_get_index);
        export_function(env, exports, "target_get_type", module_target_get_type);
        export_function(env, exports, "targe_is_attached", module_targe_is_attached);
        export_function(env, exports, "target_x360_get_user_index", module_target_x360_get_user_index);
        return exports;
    }

    NODE_API_MODULE(vigem, Init)
} // namespace module