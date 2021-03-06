#include "stdafx.h"
#include "PopenSystemCommand.h"
#include <vector>

namespace cobaltfusion
{
    PopenSystemCommand::PopenSystemCommand(const std::string& command)
        : m_pipe(nullptr)
    {
        std::vector<char> line(128);
        m_pipe = _popen(command.c_str(), "r");

        while (0 == feof(m_pipe))
        {
            if (fgets(&line[0], static_cast<int>(line.size()), m_pipe) != nullptr)
            {
                m_output << std::string(&line[0]);
            }
        }
    }

    std::string PopenSystemCommand::GetOutput() const
    {
        return m_output.str();
    }

    std::pair<int, std::string> PopenSystemCommand::GetResult()
    {
        return std::make_pair(close(), m_output.str());
    }

    int PopenSystemCommand::close()
    {
        int result = 0;
        if (m_pipe != nullptr)
        {
            result = _pclose(m_pipe);
            m_pipe = nullptr;
        }
        return result;
    }

    PopenSystemCommand::~PopenSystemCommand()
    {
        close();
    }
}
