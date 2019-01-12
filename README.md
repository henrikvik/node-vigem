# node-vigem
!! This is a Windows Only Package !!

Credit goes to Nefarius for his fantatstic work on [ViGEm](https://github.com/ViGEm/ViGEmClient)

Requires [ViGEM Bus Driver](https://docs.vigem.org/#!vigem-bus-driver-installation.md)

Zero runtime checks so use together with TypeScript.

Almost a 1:1 mapping of the C++ API for ViGEm Client.

Differences
* No manual freeing of memory, managed by v8 Garbage Collector
* Report has a nested structure

Check [addon.d.ts](./addon.d.ts) for documentation.

Example
```js
import * as vigem from "node-vigem";
// create client
let client = vigem.alloc();
// create controller
let x360 = vigem.target_x360_alloc();
// connect client to driver
vigem.connect(client);
// connect controller to client
vigem.target_add(client, x360);

let report = {
    // both button A and B are pressed
    buttons: vigem.XUSB_BUTTON.A | vigem.XUSB_BUTTON.B,
    triggers: { left: 0, right: 0 },
    // set dpad to South East
    dpad: { x: 1, y: -1 },
    thumbs: {
        left: { x: 0, y: 0 },
        right: { x: 0, y: 0 }
    },
};

// set state of the connected controller
vigem.target_x360_update(client, x360, report);
```