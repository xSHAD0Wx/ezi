#include "log/errno.h"

#include <errno.h>
#include <string.h>

#define EZI_ERRORS_COUNT (EZI_ERR_LAST_MARKER - EZI_ERR_FIRST_MARKER - 1)

static const char *ezi_errors[EZI_ERRORS_COUNT] = {
    "NULL arguments were passed",
    "Could not allocate memory",
    "Unintialized data was used",
    "No items were found",
    "No such command",
    "Command return with an error",
    "Invalid command arguments",
    "Invalid command line arguments",
    "Could not parse arguments list",
    "Initialization failed",
    "Could not open database source files",
    "Could not open file",
    "Could not write to file",
    "Could not read from file",
    "An End-of-file has been reached",
    "Could not download file",
    "Could not compile regular expression",
    "No Matches were found for the regular expression"
};

const char *
ezi_strerror(int err)
{
    if (err < EZI_ERR_FIRST_MARKER) {
        return strerror(err);
    } else if (err < EZI_ERR_LAST_MARKER) {
        return ezi_errors[err - EZI_ERR_FIRST_MARKER - 1];
    }

    return NULL;
}
