#pragma once

#include <optional>
#include <string>

enum class CliCommand{
    ListStudents,
    InsertStudent,
};


class CliArgs{
public:
    CliArgs(int argc,const char* argv[])
    {
        parse(argc,argv);
    }

    bool hasArg() const {
        return cli_command.has_value();
    }

    std::optional<CliCommand> cliCommand() const{
        return cli_command;
    }
    
    bool isGood() const {return good;}

    void printUsage();
private:
    void parse(int argc, const char* argv[]);
    std::optional<CliCommand> cli_command{};
    std::string program{};
    bool good = true;

};