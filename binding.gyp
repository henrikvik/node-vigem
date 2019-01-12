{
    "targets": [
        {
            "target_name": "addon",
            "platform"
            "sources": [ "src/addon.cc" ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "<(module_root_dir)/libs/ViGEmClient-1.16.28.0/include",
            ],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")",
            ],
            "libraries": [
                "setupapi.lib",
                "ViGEmClient-$(PlatformShortName).lib",
            ],
            "msbuild_settings": {
                "ClCompile": {
                    "AdditionalOptions": [ "/std:c++17" ],
                    "ExceptionHandling": "Sync"
                },
                "Link": {
                    "AdditionalLibraryDirectories": [
                        "<(module_root_dir)/libs/ViGEmClient-1.16.28.0/lib"
                    ]
                }
            },
        },
    ]
}