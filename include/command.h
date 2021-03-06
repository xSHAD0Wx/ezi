#ifndef EZI_COMMAND_H
#define EZI_COMMAND_H

#include "config.h"
#include "ds/slist.h"
#include "data/software_database.h"

struct ezi_command_ctx;
struct ezi_command;

typedef int (*command_func)(const struct ezi_command_ctx *ctx,
                            const struct ezi_slist *);

typedef const struct ezi_command *(*get_command_func)(const char *);
typedef int (*add_command_func)(const char *, const struct ezi_command *);

struct ezi_command
{
    const char *display_name;
    const char *description;
    const char *usage;

    command_func func;
};

struct ezi_command_ctx
{
    const struct ezi_config *config;
    struct ezi_software_database *db;

    get_command_func get_command;
    add_command_func add_command;
};

extern struct ezi_command echo_command;
extern struct ezi_command add_software_command;
extern struct ezi_command list_software_command;
extern struct ezi_command install_software_command;
extern struct ezi_command show_usage_command;

void
export_known_commands(add_command_func add_cmd);

#endif /* EZI_COMMAND_H */
