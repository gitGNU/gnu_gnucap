/*                             -*- C++ -*-
 * Copyright (C) 2016 Felix Salfelder
 * Author: same
 *
 * This file is part of "Gnucap", the Gnu Circuit Analysis Package
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "u_probe.h"
#include "u_function.h"
#include "globals.h"
#include "e_card.h"
#include "e_cardlist.h"
#include "e_node.h"

namespace {
class strlen : public FUNCTION {
public:
	strlen() : FUNCTION()
	{ untested();
	}
public:
	std::string eval(CS& Cmd, const CARD_LIST* Scope)const
	{ untested();
		std::string what(Cmd.ctos(TOKENTERM));
		return to_string(unsigned(what.size()));
	}
} p_strlen;
DISPATCHER<FUNCTION>::INSTALL d_strlen(&function_dispatcher, "strlen", &p_strlen);
/*--------------------------------------------------------------------------*/
}
