/* chainloader.c - boot another boot loader */
/*
 *  GRUB  --  GRand Unified Bootloader
 *  Copyright (C) 2025  Free Software Foundation, Inc.
 *
 *  GRUB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GRUB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GRUB.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <grub/dl.h>
#include <grub/err.h>
#include <grub/command.h>
#include <grub/ieee1275/ieee1275.h>

GRUB_MOD_LICENSE ("GPLv3+");

static grub_err_t
grub_cmd_chainloader (grub_command_t cmd __attribute__ ((unused)),
		      int argc, char *argv[])
{
  if (argc == 0)
    return grub_error (GRUB_ERR_BAD_ARGUMENT, N_("filename expected"));
  char *filename = argv[0];
  char *command = grub_xasprintf ("boot %s", filename);
  return grub_ieee1275_interpret (command, 0);
}

static grub_command_t cmd;

GRUB_MOD_INIT(chainloader)
{
  cmd = grub_register_command ("chainloader", grub_cmd_chainloader,
			       0, N_("Load another boot loader."));
}

GRUB_MOD_FINI(chainloader)
{
  grub_unregister_command (cmd);
}
