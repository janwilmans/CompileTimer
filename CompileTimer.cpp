// CompileTimeTest1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define GTEST_HAS_TR1_TUPLE 0
#pragma warning( disable : 4251)
#pragma warning( disable : 4275)

#include "gtest/gtest.h"
#include <thread>
#include <chrono>
#include <functional>
#include <filesystem>
#include <fstream>
#include "PopenSystemCommand.h"

namespace test
{
    namespace fs = std::experimental::filesystem;
    using popen = cobaltfusion::PopenSystemCommand;
    using namespace std::chrono_literals;
    using clock = std::chrono::steady_clock;
    using stringbuilder = cobaltfusion::stringbuilder;

    void repeat(int times, const std::function<void()>& func)
    {
        if (times > 25)
        {
            for (int i = 0; i<times; ++i)
                func();
            return;
        }

        for (int i = 0; i<times; ++i)
        {
            const auto t1 = clock::now();
            func();
            auto d = clock::now() - t1;
            //std::cerr << "[---(" << i << ")----] cycletime: " << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << "ms\n";
        }
    }

    std::chrono::microseconds toUs(clock::duration duration)
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(duration);
    }

    std::chrono::milliseconds toMs(clock::duration duration)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    }

    clock::duration timedRepeat(int times, const std::function<void()>& func)
    {
        const auto t1 = clock::now();
        repeat(times, func);
        auto d = clock::now() - t1;
        return std::chrono::nanoseconds(d.count() / times);
    }

    TEST(BaselineEmptyTest, BuildTimesTest) 
    {
        const int times = 10000; // 10000x runs in < 1ms
        auto duration = timedRepeat(times, [] {});
        std::cerr << "[ AVG TIME ] " << "EMPTY_BASELINE: " << duration.count() << "ns\n";
    }

    TEST(BaselineSleep1msTest, BuildTimesTest)
    {
        const int times = 5; 
        auto duration = toUs(timedRepeat(times, [] { std::this_thread::sleep_for(20ms); }));
        std::cerr << "[ AVG TIME ] " << "20ms Baseline: " << duration.count() / 1000.0 << "ms\n";
    }

    std::string createVCProject1(const std::string& code)   // no errors, also no files are copied?? WTF?
    {
        fs::remove_all("gen");
        // fs::create_directories("gen"); // shouldn't be needed
        auto src = fs::absolute(fs::path("template"));
        auto dst = fs::absolute(fs::path("gen"));

        std::cerr << "src: " << src << std::endl;
        std::cerr << "dst: " << dst << std::endl;

        fs::copy(src, dst, fs::copy_options::overwrite_existing);
        return "gen";
    }

    std::string createVCProject(const std::string& code)
    {
        fs::remove_all("gen");
        fs::create_directories("gen");
        auto src = fs::absolute(fs::path("template"));
        auto dst = fs::absolute(fs::path("gen"));

        for (const auto p : fs::directory_iterator(src))
        {
            if (!fs::is_regular_file(p)) continue;
            auto sf = fs::absolute(p);
            auto df = fs::absolute("gen") / sf.filename();
            //std::cerr << "copy " << sf << " -> " << df << std::endl;
            fs::copy_file(sf, df, fs::copy_options::overwrite_existing);
        }

        std::ofstream projectcppfile("gen/project.cpp");
        projectcppfile << code;
        return "gen\\project.vcxproj";
    }

    const std::string msbuild = R"raw("C:\Program Files (x86)\Microsoft Visual Studio\Preview\Community\MSBuild\15.0\Bin\MSBuild.exe")raw";
    const std::string options = R"raw(/t:Rebuild /p:Configuration=Debug)raw";

    std::string buildProject(const std::string& filename)
    {
        if (filename.empty())
            throw std::runtime_error("no filename specified for buildProject()");
        //std::cerr << "             msbuild " << filename + " " + options + "\n";

        auto[result, output] = popen(msbuild + " " + filename + " " + options).GetResult();
        if (result != 0)
            throw std::runtime_error(output);
        return output;
    }

    void testcode(int times, const std::string& code)
    {
        auto filename = createVCProject(code);
        auto duration = toUs(timedRepeat(times, [filename] { buildProject(filename); }));
        std::cerr << "[ AVG TIME ] " << duration.count() / 1000 << "ms\n";
    }

    TEST(EmptyProjectTest, BuildTimesTest)
    {
        const int times = 5;
        testcode(times, R"rawcode(
            #include "stdafx.h"

            int main()
            {
                return 0;
            }
        )rawcode");
    }

    TEST(WindowsHeaderTest, BuildTimesTest)
    {
        const int times = 5;
        testcode(times, R"rawcode(
            #include "stdafx.h"
            #include "windows.h"

            int main()
            {
                return 0;
            }
        )rawcode");
    }

    TEST(Vector1kTest, BuildTimesTest)
    {
        std::string start = R"rawcode(
            #include "stdafx.h"

            #include <vector>

            int main()
            {
            )rawcode";

        std::string code;
        for (int i = 0; i < 1000; ++i)
        {
            code += stringbuilder() << " std::vector<int> v" << i << "(" << i << ");\n";
        }

        std::string end = R"rawcode(
                return 0;
            }
        )rawcode";

        const int times = 5;
        testcode(times, start + code + end);
    }

    TEST(VectorInit1kTest, BuildTimesTest)
    {
        std::string start = R"rawcode(
            #include "stdafx.h"

            #include <vector>

            int main()
            {
            )rawcode";

        std::string code;
        for (int i = 0; i < 1000; ++i)
        {
            code += stringbuilder() << " std::vector<int> v" << i << " = {};\n";
        }

        std::string end = R"rawcode(
                return 0;
            }
        )rawcode";

        const int times = 5;
        testcode(times, start + code + end);
    }

    TEST(VectorWith10Values1kTest, BuildTimesTest)
    {
        std::string start = R"rawcode(
            #include "stdafx.h"

            #include <vector>

            int main()
            {
            )rawcode";

        std::string init = "{ 0 ";
        for (int i = 1; i < 10; ++i)
        {
            init += stringbuilder() << ", " << i;
        }
        init += "}";

        std::string code;
        for (int i = 0; i < 1000; ++i)
        {
            code += stringbuilder() << " std::vector<int> v" << i << " = " << init << ";";
        }

        std::string end = R"rawcode(
                return 0;
            }
        )rawcode";

        const int times = 5;
        testcode(times, start + code + end);
    }

    TEST(VectorWith20Values1kTest, BuildTimesTest)
    {
        std::string start = R"rawcode(
            #include "stdafx.h"

            #include <vector>

            int main()
            {
            )rawcode";

        std::string init = "{ 0 ";
        for (int i = 1; i < 20; ++i)
        {
            init += stringbuilder() << ", " << i;
        }
        init += "}";

        std::string code;
        for (int i = 0; i < 1000; ++i)
        {
            code += stringbuilder() << " std::vector<int> v" << i << " = " << init << ";";
        }

        std::string end = R"rawcode(
                return 0;
            }
        )rawcode";

        //std::cerr << code << std::endl;

        const int times = 5;
        testcode(times, start + code + end);
    }

    TEST(Vector2KTest, BuildTimesTest)
    {
        std::string start = R"rawcode(
            #include "stdafx.h"

            #include <vector>

            int main()
            {
            )rawcode";

        std::string code;
        for (int i = 0; i < 2000; ++i)
        {
            code += stringbuilder() << " std::vector<int> v" << i << "(" << i << ");\n";
        }

        std::string end = R"rawcode(
                return 0;
            }
        )rawcode";

        testcode(1, start + code + end);
    }

    TEST(Vector2kSameTest, BuildTimesTest)
    {
        std::string start = R"rawcode(
            #include "stdafx.h"

            #include <vector>

            int main()
            {
            )rawcode";

        std::string code;
        for (int i = 0; i < 2000; ++i)
        {
            code += stringbuilder() << " std::vector<int> v" << i << "(10);\n";
        }

        std::string end = R"rawcode(
                return 0;
            }
        )rawcode";

        testcode(1, start + code + end);
    }

    TEST(Vector5kTest, BuildTimesTest)
    {
        std::string start = R"rawcode(
            #include "stdafx.h"

            #include <vector>

            int main()
            {
            )rawcode";

        std::string code;
        for (int i = 0; i < 5000; ++i)
        {
            code += stringbuilder() << " std::vector<int> v" << i << "(10);\n";
        }

        std::string end = R"rawcode(
                return 0;
            }
        )rawcode";

        testcode(1, start + code + end);
    }
}

int main(int argc, char **argv)
{
    system("taskkill /F /IM tracker.exe");
    system("taskkill /F /IM cl.exe");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
