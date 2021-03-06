#include <string>
#include <sstream>

namespace cobaltfusion
{
    template <typename CharType, typename Traits = std::char_traits<CharType>, typename Allocator = std::allocator<CharType> >
    class basic_stringbuilder
    {
    public:
        typedef typename std::basic_string<CharType, Traits, Allocator> string_type;

        template <typename T>
        basic_stringbuilder& operator<<(const T& t)
        {
            m_ss << t;
            return *this;
        }

        string_type str() const
        {
            return m_ss.str();
        }

        operator string_type() const
        {
            return str();
        }

    private:
        std::basic_ostringstream<CharType, Traits, Allocator> m_ss;
    };

    using stringbuilder = basic_stringbuilder<char>;
    using wstringbuilder = basic_stringbuilder<wchar_t>;

    class PopenSystemCommand
    {
    public:
        explicit PopenSystemCommand(const std::string& command);
        std::string GetOutput() const;
        std::pair<int, std::string> GetResult();
        int close();
        ~PopenSystemCommand();

    private:
        FILE * m_pipe;
        stringbuilder m_output;
    };

}
