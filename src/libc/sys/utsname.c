#include <string.h>
#include <sys/utsname.h>
#include "../../shim.h"
#include "utsname.h"

int shim_uname_impl(struct linux_utsname* linux_name) {

  struct utsname name;

  int err = uname(&name);
  if (err == 0) {
    memset(linux_name, 0, sizeof(struct linux_utsname));

    strlcpy(linux_name->machine,
      strcmp(name.machine, "amd64") == 0 ? "x86_64" : name.machine, 65);

    strlcpy(linux_name->sysname,    name.sysname,  65);
    strlcpy(linux_name->nodename,   name.nodename, 65);
    strlcpy(linux_name->release,    name.release,  65);
    strlcpy(linux_name->version,    name.version,  65);
    strlcpy(linux_name->domainname, "",            65);
  }

  return err;
}

SHIM_WRAP(uname);
