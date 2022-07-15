// Command.hpp
// Virtual class for a command in spider solitaire
#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command {
    public:
    virtual void execute() = 0;
    virtual void undo() = 0;
};

#endif