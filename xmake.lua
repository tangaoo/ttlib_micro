add_rules("mode.debug", "mode.release")
--add_includedirs("src/ttlib")
set_languages("c11") 

target("ttlib_micro")
    set_kind("static")
    add_files("src/ttlib_micro/**.c")
    add_headerfiles("src/(ttlib_micro/**.h)")

    if is_plat("windows") then
    -- set third party lib
        add_includedirs("F:\\work\\tool\\pthreads-w32-2-9-1-release\\Pre-built.2\\include")
        add_linkdirs("F:\\work\\tool\\pthreads-w32-2-9-1-release\\Pre-built.2\\lib\\x86")
        add_links("pthreadVC2")
    end

    if is_plat("linux", "macosx") then
        add_syslinks("pthread")
    end


target("demo")
    set_kind("binary")
    add_deps("ttlib_micro")
    add_files("src/demo/**.c")    
    -- add_syslinks("pthread")

    -- set ttlib .h file
    add_includedirs("src/ttlib_micro/")
    
--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
-- 
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

