#ifndef pyshell_manager_hh_INCLUDED
#define pyshell_manager_hh_INCLUDED

#include "array_view.hh"
#include "env_vars.hh"
#include "string.hh"
#include "utils.hh"
#include "completion.hh"
#include "shell_manager.hh"

namespace Kakoune
{

class Context;


class PyShellManager : public Singleton<PyShellManager>
{
public:
    PyShellManager(ConstArrayView<EnvVarDesc> builtin_env_vars);

    enum class Flags
    {
        None = 0,
        WaitForStdout = 1
    };
    friend constexpr bool with_bit_ops(Meta::Type<Flags>) { return true; }

    std::pair<String, int> eval(StringView cmdline, const Context& context,
                                StringView input = {},
                                Flags flags = Flags::WaitForStdout,
                                const ShellContext& shell_context = {});

    Vector<String> get_val(StringView name, const Context& context) const;

    CandidateList complete_env_var(StringView prefix, ByteCount cursor_pos) const;

private:
    String m_shell;

    ConstArrayView<EnvVarDesc> m_env_vars;
};

}

#endif // pyshell_manager_hh_INCLUDED

