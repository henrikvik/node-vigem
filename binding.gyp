{
    "targets": [
        {
            "target_name": "vigem",
            "sources": [ "src/module.cpp" ],
            "include_dirs": [
                "<!@(node -p \"require('node-addon-api').include\")",
                "<(module_root_dir)/libs/ViGEmClient-1.16.28.0/include",
            ],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")",
            ],
            "libraries": [
                "setupapi.lib",
                "ViGEmClient-x64-Release.lib",
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