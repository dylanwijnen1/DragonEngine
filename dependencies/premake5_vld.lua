local dependencies = require "dependency-injector"

local vld = 
{
    shortname = "Visual Leak Detector",
    description = "Detects leaking memory and memory corruption."
}

function vld.include(rootdir)
    includedirs 
    {
        rootdir .. [[include]],
    }
end

function vld.link(rootdir, dragonlibdir)
    filter { "architecture:x86" }
        libdirs
        {
            rootdir .. [[lib\Win32\]]
        }

    filter { "architecture:x64" }
        libdirs
        {
            rootdir .. [[lib\Win64\]]
        }
end

dependencies.add("vld", vld)