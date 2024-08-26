{
  "targets": [
    {
      "target_name": "catch22_C",
      "sources": [
        "<!@(ls -1 C/*.c)"
      ],
      "include_dirs": [
        "C"
      ],
      "libraries": [],
      "configurations": {
        "Release_win32": {
          "target_os": "win32",
          "target_arch": "ia32",
          "cflags": [
            "-std=c99"
          ],
          "cflags_cc": [
            "-std=c++11"
          ]
        },
        "Release_linux": {
          "target_os": "linux",
          "target_arch": "x64",
          "cflags": [
            "-std=c99"
          ],
          "cflags_cc": [
            "-std=c++11"
          ]
        },
        "Release_mac": {
          "target_os": "mac",
          "target_arch": "x64",
          "cflags": [
            "-std=c99"
          ],
          "cflags_cc": [
            "-std=c++11"
          ]
        }
      }
    }
  ]
}