let addon = require("bindings")("addon");

addon.TargetType = Object.freeze({
    Xbox360    : 0,
    XboxOne    : 1,
    DualShock4 : 2,
});

addon.XUSB_BUTTON = Object.freeze({
    START          : 1 << 4,
    BACK           : 1 << 5,
    THUMB_LEFT     : 1 << 6,
    THUMB_RIGHT    : 1 << 7,
    SHOULDER_LEFT  : 1 << 8,
    SHOULDER_RIGHT : 1 << 9,
    GUIDE          : 1 << 10,
    A              : 1 << 12,
    B              : 1 << 13,
    X              : 1 << 14,
    Y              : 1 << 15
});

addon.DS4_BUTTONS = Object.freeze({
    SQUARE         : 1 << 4,
    CROSS          : 1 << 5,
    CIRCLE         : 1 << 6,
    TRIANGLE       : 1 << 7,
    SHOULDER_LEFT  : 1 << 8,
    SHOULDER_RIGHT : 1 << 9,
    TRIGGER_LEFT   : 1 << 10,
    TRIGGER_RIGHT  : 1 << 11,
    SHARE          : 1 << 12,
    OPTIONS        : 1 << 13,
    THUMB_LEFT     : 1 << 14,
    THUMB_RIGHT    : 1 << 15,
});

addon.DS4_SPECIAL_BUTTONS = Object.freeze({
    PS       : 1 << 0,
    TOUCHPAD : 1 << 1
});

module.exports = exports = Object.freeze(addon);