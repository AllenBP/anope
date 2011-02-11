/* OperServ core functions
 *
 * (C) 2003-2011 Anope Team
 * Contact us at team@anope.org
 *
 * Please read COPYING and README for further details.
 *
 * Based on the original code of Epona by Lara.
 * Based on the original code of Services by Andy Church.
 */

/*************************************************************************/

#include "module.h"

class CommandOSShutdown : public Command
{
 public:
	CommandOSShutdown() : Command("SHUTDOWN", 0, 0, "operserv/shutdown")
	{
		this->SetDesc("Terminate services with save");
	}

	CommandReturn Execute(CommandSource &source, const std::vector<Anope::string> &params)
	{
		User *u = source.u;
		quitmsg = "SHUTDOWN command received from " + u->nick;

		if (Config->GlobalOnCycle)
			oper_global("", "%s", Config->GlobalOnCycleMessage.c_str());
		shutting_down = true;
		return MOD_CONT;
	}

	bool OnHelp(CommandSource &source, const Anope::string &subcommand)
	{
		source.Reply(_("Syntax: \002SHUTDOWN\002\n"
				" \n"
				"Causes Services to save all databases and then shut down."));
		return true;
	}
};

class OSShutdown : public Module
{
	CommandOSShutdown commandosshutdown;

 public:
	OSShutdown(const Anope::string &modname, const Anope::string &creator) : Module(modname, creator)
	{
		this->SetAuthor("Anope");
		this->SetType(CORE);

		this->AddCommand(OperServ, &commandosshutdown);
	}
};

MODULE_INIT(OSShutdown)
