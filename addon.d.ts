declare module "node-vigem" {
    enum TargetType {
        Xbox360,
        XboxOne,
        DualShock4,
    }

    /** Flags for XUSB_Report.buttons */
    enum XUSB_BUTTON {
        START,
        BACK,
        THUMB_LEFT,
        THUMB_RIGHT,
        SHOULDER_LEFT,
        SHOULDER_RIGHT,
        GUIDE,
        A,
        B,
        X,
        Y
    }

    /** Flags for DS4_Report.buttons */
    enum DS4_BUTTONS {
        SQUARE,
        CROSS,
        CIRCLE,
        TRIANGLE,
        SHOULDER_LEFT,
        SHOULDER_RIGHT,
        TRIGGER_LEFT,
        TRIGGER_RIGHT,
        SHARE,
        OPTIONS,
        THUMB_LEFT,
        THUMB_RIGHT,
    }

    /** Flags for DS4_Report.specials */
    enum DS4_SPECIAL_BUTTONS {
        PS,
        TOUCHPAD
    }

    /** Created by the alloc function and serves as a pointer to the ViGEm Client managed by the addon. */
    class Client {
        private constructor();
    }

    /** Created by the target_*_alloc functions and serves as a pointer to the ViGEm Target managed by the addon. */
    class Target {
        private constructor();
    }

    /** Represents a 2D direction, "x" and "y" has a range of -1.0 to 1.0. */
    interface Axis {
        x: number;
        y: number;
    }

    /** Generic that represents an object with the values "left" and "right" of type T */
    interface LR<T> {
        left:  T;
        right: T;
    }

    /** Represents the state of a X360 Target */
    interface XUSB_Report {
        dpad:     Axis;
        thumbs:   LR<Axis>;
        buttons:  number;
        triggers: LR<number>;
    }

    /** Represents the state of a DS4 Target */
    interface DS4_Report extends XUSB_Report {
        specials: number;
    }

    // VIGEM_API PVIGEM_CLIENT vigem_alloc(void);
    /** Allocates an object representing a driver connection. */
    function alloc(): Client;

    // VIGEM_API VIGEM_ERROR vigem_connect(PVIGEM_CLIENT vigem);
    /** Initializes the driver object and establishes a connection to the emulation bus driver. Throws an error if no compatible bus device has been found. */
    function connect(client: Client): void;

    // VIGEM_API void vigem_disconnect(PVIGEM_CLIENT vigem);
    /** Disconnects from the bus device and resets the driver object state. The driver object may be reused again after calling this function. When called, all targets which may still be connected will be destroyed automatically. Be aware, that allocated target objects won't be automatically freed, this has to be taken care of by the caller. */
    function disconnect(client: Client): void;

    // VIGEM_API PVIGEM_TARGET vigem_target_x360_alloc(void);
    /** Allocates an object representing an Xbox 360 Controller device. */
    function target_x360_alloc(): Target;

    // VIGEM_API PVIGEM_TARGET vigem_target_ds4_alloc(void);
    /** Allocates an object representing a DualShock 4 Controller device. */
    function target_ds4_alloc(): Target;

    // VIGEM_API VIGEM_ERROR vigem_target_add(PVIGEM_CLIENT vigem, PVIGEM_TARGET target);
    /** Adds a provided target device to the bus driver, which is equal to a device plug-in event of a physical hardware device. This function blocks until the target device is in full operational mode. */
    function target_add(client: Client, target: Target): void;

    // VIGEM_API VIGEM_ERROR vigem_target_add_async(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_TARGET_ADD_RESULT result);
    /** Adds a provided target device to the bus driver, which is equal to a device plug-in event of a physical hardware device. This function immediately returns. An optional callback may be registered which gets called on error or if the target device has become fully operational. */
    // TODO function target_add_async(client: Client, target: Target, PFN_VIGEM_TARGET_ADD_RESULT result): void;

    // VIGEM_API VIGEM_ERROR vigem_target_remove(PVIGEM_CLIENT vigem, PVIGEM_TARGET target);
    /** Removes a provided target device from the bus driver, which is equal to a device unplug event of a physical hardware device. The target device object may be reused after this function is called. If this function is never called on target device objects, they will be removed from the bus when the owning process terminates. */
    function target_remove(client: Client, target: Target): void;

    // VIGEM_API VIGEM_ERROR vigem_target_x360_register_notification(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_X360_NOTIFICATION notification);
    /** Registers a function which gets called, when LED index or vibration state changes occur on the provided target device. This function fails if the provided target device isn't fully operational or in an erroneous state. */
    // TODO function target_x360_register_notification(client: Client, target: Target, PFN_VIGEM_X360_NOTIFICATION notification): void;

    // VIGEM_API VIGEM_ERROR vigem_target_ds4_register_notification(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PFN_VIGEM_DS4_NOTIFICATION notification);
    /** Registers a function which gets called, when LightBar or vibration state changes occur on the provided target device. This function fails if the provided target device isn't fully operational or in an erroneous state. */
    // TODO function target_ds4_register_notification(client: Client, target: Targett, PFN_VIGEM_DS4_NOTIFICATION notification): void;

    // VIGEM_API void vigem_target_x360_unregister_notification(PVIGEM_TARGET target);
    /** Removes a previously registered callback function from the provided target object. */
    // TODO function target_x360_unregister_notification(target: Target): void;

    // VIGEM_API void vigem_target_ds4_unregister_notification(PVIGEM_TARGET target);
    /** Removes a previously registered callback function from the provided target object. */
    // TODO function target_ds4_unregister_notification(target: Target): void;

    // VIGEM_API void vigem_target_set_vid(PVIGEM_TARGET target, USHORT vid);
    /**  Overrides the default Vendor ID value with the provided one. */
    function target_set_vid(target: Target, vid: number): void;

    // VIGEM_API void vigem_target_set_pid(PVIGEM_TARGET target, USHORT pid);
    /**  Overrides the default Product ID value with the provided one. */
    function target_set_pid(target: Target, pid: number): void;

    // VIGEM_API USHORT vigem_target_get_vid(PVIGEM_TARGET target);
    /** Returns the Vendor ID of the provided target device object. */
    function target_get_vid(target: Target): number;

    // VIGEM_API USHORT vigem_target_get_pid(PVIGEM_TARGET target);
    /** Returns the Product ID of the provided target device object. */
    function target_get_pid(target: Target): number;

    // VIGEM_API VIGEM_ERROR vigem_target_x360_update(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, XUSB_REPORT report);
    /** Sends a state report to the provided target device. */
    function target_x360_update(client: Client, target: Target, report: XUSB_Report): void;

    // VIGEM_API VIGEM_ERROR vigem_target_ds4_update(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, DS4_REPORT report);
    /** Sends a state report to the provided target device. */
    function target_ds4_update(client: Client, target: Target, report: DS4_Report): void;

    // VIGEM_API ULONG vigem_target_get_index(PVIGEM_TARGET target);
    /** Returns the internal index (serial number) the bus driver assigned to the provided target device object. Note that this value is specific to the inner workings of the bus driver, it does not reflect related values like player index or device arrival order experienced by other APIs. It may be used to identify the target device object for its lifetime. This value becomes invalid once the target device is removed from the bus and may change on the next addition of the device. */
    function target_get_index(target: Target): number;

    // VIGEM_API VIGEM_TARGET_TYPE vigem_target_get_type(PVIGEM_TARGET target);
    /** Returns the type of the provided target device object. */
    function target_get_type(target: Target): TargetType;

    // VIGEM_API BOOL vigem_target_is_attached(PVIGEM_TARGET target);
    /** Returns TRUE if the provided target device object is currently attached to the bus, FALSE otherwise. */
    function target_is_attached(target: Target): boolean;

    // VIGEM_API VIGEM_ERROR vigem_target_x360_get_user_index(PVIGEM_CLIENT vigem, PVIGEM_TARGET target, PULONG index);
    /** Returns the user index of the emulated Xenon device. This value correspondents to the (zero-based) index number representing the player number via LED present on a physical controller and is compatible to the dwUserIndex propery of the XInput* APIs. */
    function target_x360_get_user_index(client: Client, target: Target): number;
}